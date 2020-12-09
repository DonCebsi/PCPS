const redis = require('redis'); //redis module
const {promisify} = require('util');


let client = redis.createClient();
client.auth("pcpsMontag2");

client.on('connect', function(){
	console.log('Connected to Redis...');
});

const getAsync = promisify(client.get).bind(client);
const setAsync = promisify(client.set).bind(client);
const saddAsync = promisify(client.sadd).bind(client);

// add new node
function addNode(id) {
	// Sets will only add elements which are not contained
	//client.sismember('nodes',id,function(err,replies){
	saddAsync('nodes', id+"_arduino").then(() => {
		setLastSeen(id);
		console.log("Wrote node");
	});
}

function registerActivePlant(node,plant) {
	return setAsync(node+"_arduino", plant);
}

function setLastSeen (id) {
	const dateStr = (new Date()).toString();
	return setAsync(id+"_arduino_lastseen", dateStr);
}

function getActiveAsync(id, threshold) {
	if (threshold === undefined) threshold = 60 * 2 * 1000;
	const now = (new Date()).getTime();
	const lastPossiblePing = now - threshold;

	return getAsync(id+"_lastseen").then(dateStr => {
		const lastPing = new Date(dateStr);
		return lastPing.getTime() - lastPossiblePing >= 0;
	})
}

module.exports = { addNode, registerActivePlant, setLastSeen, getActiveAsync };
