const dbSaver = require('./dbSaver');
const net = require('net');
const nodes = require('./nodeManager.js');

let sendToArduinoQueue = {};

/// Returns the expected length for a message type in bytes.
function getLen(messageType) {
	let length = 6;
	if (messageType === 1) length = 14;
	if (messageType === 2) length = 19;
	if (messageType === 3) length = 115;
	return length;
}

/// Returns a header for a communications package (6 bytes) with
/// message type and node id set according to arguments
function createHeader(type, id) {
	let header = Buffer.allocUnsafe(6);
	
	if (type < 0 || type > 255 || id < 0 || id > 255)
		throw "Out of range arguments";
	
	header.writeUInt8(type, 0);
	header.writeUInt8(id, 1);
	const timestamp = Math.round((new Date()).getTime() / 1000);
	header.writeUInt32LE(timestamp, 2);
	
	return header;
}


/// Returns a pong package for a given node id
function createPong(id) {
	const pong = createHeader(0, id);
	console.log([...pong]);
	return pong;
}


/// Queue a plant for sending to a node
/// May throw an exception if there already is a plant waiting for transmission
function sendPlantToArduino(id, plant) {
	id = String(id),
	id = parseInt(id.replace(/[^0-9]/g, ""));
	if (isNaN(id)) return false;
	plant.chunk = 0;
	if (!sendToArduinoQueue[id]) {
		plant.queued = new Date();
		sendToArduinoQueue[id] = plant;
		console.log("Queued");
	} else {
		throw "Already waiting for plant";
	}
}


/// Returns a parsed message
/// Expects a single arduino message as a buffer
function parseArduinoMessage(messageBuffer) {
	let message = {};

	message.type = messageBuffer.readUInt8(0);
	message.nodeId = messageBuffer.readUInt8(1);

	if (Buffer.byteLength(messageBuffer) < getLen(message.type)) {
		throw { error: "Incomplete package", nodeId: message.nodeId };
	}

	message.timestamp = new Date(messageBuffer.readUInt32LE(2) * 1000);
	message.payload = {};
	console.log("Received a message " + message.type + " from node " + message.nodeId);

	switch (message.type) {
		case 1:
		message.payload.size = messageBuffer.readFloatLE(6);
		message.payload.health = messageBuffer.readFloatLE(10);
		break;

		case 2:
		message.payload.water = !!(messageBuffer.readUInt8(6));
		message.payload.light = messageBuffer.readUInt16LE(7);
		message.payload.moisture = messageBuffer.readUInt16LE(9);
		message.payload.temperature = messageBuffer.readFloatLE(11);
		message.payload.humidity = messageBuffer.readFloatLE(15);
		break;
	}

	console.log(message);
	return message;
}

/// Adds the payload properties of a message to the top level
function inlineMessagePayload(message) {
	const payload = message.payload;
	delete message.payload;
	return { ...message, ...payload };
}

/// Returns an object which tells us what we can do afterwards
/// Processes the received buffer and saves data to database if neccessary
/// Buffer may contain multiple messages,
/// incomplete messages at start or end, however, will be discarded
function handleIncomingData(buffer) {
	let messages = [];

	while (Buffer.byteLength(buffer) > 0) {
		try {
			messages.push(parseArduinoMessage(buffer));
			// Cut the length of the first message off of our buffer
			buffer = buffer.slice( getLen(messages[messages.length - 1].type) );
		} catch (e) {
			// Dropping incomplete packages completely
			console.log(e);
			buffer = new Buffer([]);
		}
	}

	let pong = false;
	let moreData = false;
	let nodeId = messages.length > 0 ? messages[0].nodeId : undefined;

	if (nodeId !== undefined) {
		nodes.addNode(nodeId);
	}

	messages.forEach(message => {
		switch (message.type) {
			case 0:
			pong = true && !moreData;
			break;

			case 1:
			dbSaver.enqueueStatus(inlineMessagePayload(message));
			break;

			case 2:
			dbSaver.enqueueSensors(inlineMessagePayload(message));
			break;

			case 4:
			pong = false;
			moreData = true;
			break;
		}
	});

	return { pong, moreData, nodeId };
}


/// Sends a part of the specification of a plant to a socket.
/// Calls cb_done if it has sent the last chunk
function sendChunk(plant, id, socket, cb_done) {
	console.log("A spec");
	([...plant.spec]).forEach(byte => { console.log("  " + byte); });
	console.log("End spec\n");
	let start = plant.chunk * 40;
	plant.chunk++;
	socket.write(plant.spec.slice(start, start + 40 < plant.spec.length ? start+40 : plant.spec.length));
	console.log("wrote spec to arduino " + id);
	console.log("Chunk " + (plant.chunk - 1));

	if (start + 40 >= plant.spec.length) {
		nodes.registerActivePlant(id, plant.name);
		if (plant.state) {
			setTimeout(() => {
				socket.write(plant.state);
				console.log("set stats on arduino " + id);
				console.log([...plant.state]);
				cb_done();
			}, 500);
		} else {
			cb_done();
		}
	}
}

function runArduinoServer(port) {
	
	net.createServer(function(socket) {
		// Receive from client
		socket.on('data', function(data) {
			const actions = handleIncomingData(data);
    		if (actions.pong) {
				console.log("Sending pong");
				socket.write(createPong(255));
			}
			if (actions.nodeId in sendToArduinoQueue) {
				let now = (new Date()).getTime();
				if (now > sendToArduinoQueue[actions.nodeId].queued.getTime() + 90 * 1000) {
					console.log("Exceeded time to send, deleting target spec for " + actions.nodeId);
					delete sendToArduinoQueue[actions.nodeId];
					return;
				}
				console.log("Can send to Arduino");
				if (sendToArduinoQueue[actions.nodeId].chunk !== 0 && !actions.moreData) return; 
    			sendChunk(sendToArduinoQueue[actions.nodeId], actions.nodeId, socket, () => {
    				console.log("Delete from queue");
    				delete sendToArduinoQueue[actions.nodeId];
    			});
			}
		});
	}).listen(port);
}

module.exports = {
	runArduinoServer,
	createHeader,
	sendPlantToArduino
};
