const redis = require('redis'); //redis module
const Pqueue = require("priorityqueuejs");
const {promisify} = require('util');
const calcSize = require('./calcSize');


// create client
const client = redis.createClient();
let connected = false;
let gCallback;

client.auth("pcpsMontag2", function(err) {
	if (err) console.log(err);
});

//connect client to redis-server
client.on('connect', function() {
	connected = true;
	if (gCallback !== undefined) {
		gCallback();
		gCallback = undefined;
	}
});

const getAsync = promisify(client.get).bind(client);
const llenAsync = promisify(client.llen).bind(client);
const lindexAsync = promisify(client.lindex).bind(client);
const rpushAsync = promisify(client.rpush).bind(client);

//only one instance of saveData allowed at a time
let queueRunning = false;
let isSaving = false;

//priority order
let queue = new Pqueue(function(a, b) {
	return a.time + b.time; 
});


function readySubscribe(callback) {
	if (!connected) {
		gCallback = callback;
	} else {
		callback();
	}
}

function restructureObject (object, newNames) {
	Object.keys(newNames).forEach(key => {
		object = renameKey(object, key, newNames[key]);
	});
	return object;
}

function renameKey (o, oldKey, newKey) {
	if (oldKey !== newKey) {
		Object.defineProperty(o, newKey, Object.getOwnPropertyDescriptor(o, oldKey));
		delete o[oldKey];
	}
	return o;
}

function filterObjectKeys(object, allowedKeys) {
	let newObject = {};
	Object.keys(object).forEach(key => {
		if (allowedKeys.indexOf(key) >= 0)
			newObject[key] = object[key];
	});
	return newObject;
}

function ensureLoopRunning () {
	if (isSaving === false) setTimeout(dequeueHandler, 200);
}

function enqueueSensors(sensorElement) {
	queue.enq({
		payload: sensorElement,
		time: (new Date()).getTime()
	});
	ensureLoopRunning();
}

function enqueueStatus(statusElement) {
	queue.enq({
		payload: statusElement,
		time: (new Date()).getTime()
	});
	ensureLoopRunning();
}

function enqueueBackup(backupElement, id, type) {
	backupElement.name = id;
	backupElement.type = type;
	queue.enq({
		payload: backupElement,
		time: (new Date()).getTime()
	});
	ensureLoopRunning();
}


function getNodePlantName(node) {
	return getAsync(node + "_arduino").then(plantName => {
		return !!plantName ? plantName : false;
	});
}

function getLatestMeasurements(plantName) {
	return lindexAsync(plantName, -1).then(newMeasurementKey => {
		return getAsync(newMeasurementKey);
	}).then(measurements => {
		return !!measurements ? measurements : undefined;
	}).catch(e => {
		return undefined;
	});
}

function saveSensors (sensorElement) {
	return getNodePlantName(sensorElement.nodeId).then(plantName => {
		if (plantName === false) throw "Unknown plant";
		
		sensorElement.name = plantName;
		return Promise.all([sensorElement, plantName, llenAsync(plantName)]);
	}).then(plantInfo => {
		let [sensorElement, plantName, measurementCount] = plantInfo;
		const key = plantName + "#" + measurementCount;
		return Promise.all([sensorElement, key, rpushAsync(plantName, key)]);
	}).then(plantInfo => {
		let [sensorElement, key, ok] = plantInfo;
		sensorElement = filterObjectKeys(sensorElement, ["nodeId", "timestamp", "light", "water", "moisture", "temperature", "humidity", "name"]);
		sensorElement = restructureObject(sensorElement, {
			"nodeId": "id",
			"timestamp": "date",
			"temperature": "temp"
		});
		return client.set(key, JSON.stringify(sensorElement));
	}).then(() => {
		console.log("Successfully set sensor values.");
		return true;
	}).catch(e => {
		if (e !== "Unknown plant") console.log(e);
		return false;
	});
}

function saveStatus (statusElement) {
	return getNodePlantName(statusElement.nodeId).then(plantName => {
		if (plantName === false) throw "Unknown plant";
		
		statusElement.name = plantName;
		return Promise.all([statusElement, plantName, llenAsync(plantName + "_status"), getAsync(plantName + "_template")]);
	}).then(plantInfo => {
		let [statusElement, plantName, statusCount, templateName] = plantInfo;
		return Promise.all([statusElement, plantName, statusCount, getAsync(templateName)]);
	}).then(plantInfo => {
		let [statusElement, plantName, statusCount, template] = plantInfo;
		template = JSON.parse(template);
		statusElement.size = calcSize(template.maxSize, template.growSpeed, statusElement.size);
		const key = plantName + "_status#" + statusCount;
		return Promise.all([statusElement, key, getStatusImage(plantName, template, statusElement), rpushAsync(plantName + "_status", key)]);
	}).then(plantInfo => {
		let [statusElement, key, statusImage, ok] = plantInfo;
		statusElement.status = statusImage;

		statusElement = filterObjectKeys(statusElement, ["nodeId", "timestamp", "size", "health", "name", "status"]);
		statusElement = restructureObject(statusElement, {"nodeId": "id", "timestamp": "date"});
		
		return client.set(key, JSON.stringify(statusElement));
	}).then(() => {
		console.log("Successfully set status values.");
		return true;
	}).catch(e => {
		if (e !== "Unknown plant") console.log(e);
		return false;
	});
}

function getStatusImage(plantName, template, values) {
	return getLatestMeasurements(plantName).then(measurements => {
		let status;
		if (values.health <= 0) {
			status = "bmtomb";
		} else {
			if (values.size <= template.maxSize / 5) {
				status = "bm1";
			} else if (values.size <= 2 * template.maxSize / 5) {
				status = "bm2";
			} else if (values.size <= 3 * template.maxSize / 5) {
				status = "bm3";
			} else if (values.size <= 4 * template.maxSize / 5) {
				status = "bm4";
			} else {
				status = "bm5";
				if (measurements !== undefined) {
					if (measurements.light >= 800 && values.health > 80)
					status = "bm5_2";
				}
			}
			
			if (values.health <= 80)
			status += "_sick";
		}
		return status;
	});
}

function dequeueHandler() {
	isSaving = true;
	while (!queue.isEmpty()) {
		if (queueRunning === true) {
			setTimeout(dequeueHandler, 100);
			break;
		} else {
			queueRunning = true;
			let element = queue.deq();
			console.log("Dequeue item");
			if (element.payload.type === 1) {
				saveStatus(element.payload).then(() => { queueRunning = false; });
			} else if (element.payload.type === 2) {
				saveSensors(element.payload).then(() => { queueRunning = false; });
			}   
		}
	}
	isSaving = false;
}

module.exports = { enqueueSensors, enqueueStatus, enqueueBackup, readySubscribe };
