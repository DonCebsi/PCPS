var express = require('express');
var router = express.Router();
var nodeManager = require('../nodeManager');
const redis = require('redis');
const {promisify} = require('util');
const calcSize = require('../calcSize');

// Create Redis Client
let client = redis.createClient();
client.auth("pcpsMontag2");

client.on('connect', function(){
	console.log('Connected to Redis...');
});
const lrangeAsync = promisify(client.lrange).bind(client);
const getAsync = promisify(client.get).bind(client);
const lindexAsync = promisify(client.lindex).bind(client);
const smembersAsync = promisify(client.smembers).bind(client);

/* GET plants listing. */
/// Will list all plants with their last sensor and status values
router.get('/', function(req, res, next){
	// Will always send JSON
	res.setHeader('Content-Type', 'application/json');
	
	let responseTemplate = {
		name: null,
		status: null,
		deployed: null,
		temperature: null,
		moisture: null,
		humidity: null,
		brightness: null,
		waterAboveGround: null,
		size: null,
		health: null,
		active: false
	};
	// Get all plant names and all node names
	Promise.all([smembersAsync('plants'), smembersAsync('nodes')]).then(identifiers => {
		const [plantNames, nodeNames] = identifiers;
		// Get array with the key of the last measurement, status values for each plant
		const lastMeasurementKeys = Promise.all(plantNames.map(name => lindexAsync(name, -1)));
		const lastStatusKeys = Promise.all(plantNames.map(name => lindexAsync(name+"_status", -1)));
		// Get the name of the plant on each node
		const nodePlants = Promise.all(nodeNames.map(name => getAsync(name)));
		
		return Promise.all([plantNames, lastMeasurementKeys, lastStatusKeys, nodeNames, nodePlants]);
	}).then(dbAnswers => {
		const [plantNames, lastMeasurementKeys, lastStatusKeys, nodeNames, nodePlants] = dbAnswers;
		// Resolve the keys to values
		const lastMeasurements = Promise.all(lastMeasurementKeys.map(name => name === null ? null : getAsync(name)));
		const lastStatuses = Promise.all(lastStatusKeys.map(name => name === null ? null : getAsync(name)));
		// Check each node for recent activity
		const nodeActivity = Promise.all(nodeNames.map(name => name === null ? null : nodeManager.getActiveAsync(name)));
		
		return Promise.all([
			plantNames,
			lastMeasurements,
			lastStatuses,
			nodeActivity,
			nodeNames,
			nodePlants
		]);
	}).then(dbAnswers => {
		let [
			plantNames,
			lastMeasurements,
			lastStatuses,
			nodeActivity,
			nodeNames,
			nodePlants
		] = dbAnswers;
		let replies = [];
		
		for (let plantIndex in plantNames) {
			if (plantNames.hasOwnProperty(plantIndex)) {
				// Create a new object from template
				let plantOverview = Object.assign({}, responseTemplate);
				plantOverview.name = plantNames[plantIndex];
				
				// Copy values from database results
				if (lastMeasurements[plantIndex] !== null) {
					let sensors = JSON.parse(lastMeasurements[plantIndex]);
					plantOverview.temperature = sensors.temp;
					plantOverview.moisture = sensors.moisture;
					plantOverview.humidity = sensors.humidity;
					plantOverview.brightness = sensors.light;
					plantOverview.waterAboveGround = sensors.water;
				}
				
				if (lastStatuses[plantIndex] !== null) {
					let status = JSON.parse(lastStatuses[plantIndex]);
					plantOverview.health = status.health;
					plantOverview.size = status.size;
					plantOverview.status = status.status;
				}
				
				if (nodePlants.indexOf(plantNames[plantIndex]) >= 0) {
					plantOverview.deployed = nodeNames[nodePlants.indexOf(plantNames[plantIndex])];
					plantOverview.active = nodeActivity[nodePlants.indexOf(plantNames[plantIndex])];
				}
				
				replies.push(plantOverview);
			}
		}
		
		// if ?active=1 filter for active plants.
		if (req.query.active) replies = replies.filter(r => r.active);
		res.send(JSON.stringify(replies));
	}).catch(e => {
		console.log(e);
		// We ALWAYS send valid JSON
		res.status(200).send("[]");
	});
});

/* GET specific plant */
router.get('/:id', function(req, res, next){
	// Will always send JSON
	res.setHeader('Content-Type', 'application/json');
	let plantName = req.params.id;
	
	let response = {
		id: plantName,
		status: null,
		deployed: null,
		timestamps: [],
		temperature: [],
		moisture: [],
		humidity: [],
		brightness: [],
		waterAboveGround: [],
		size: [],
		health: [],
		active: false
	};
	
	let limit = 2500;
	if (!isNaN(req.query.limit)) {
		const proposedLimit = Math.floor(parseFloat(req.query.limit));
		limit = proposedLimit > 0 ? proposedLimit : 0;
	}
	
	// Get all plant names and all node names
	smembersAsync("plants").then(plants => {
		if (plants.indexOf(plantName) < 0) {
			console.log("Plant not found");
			throw 404;
		}
		return Promise.all([
			lrangeAsync(plantName, 0, -1),
			lrangeAsync(plantName+"_status", 0, -1),
			smembersAsync('nodes')
		]);
	}).then(dbResults => {
		const [measurementKeys, statusKeys, nodeNames] = dbResults;
		const measurements = Promise.all(measurementKeys.map(key => key === null ? null : getAsync(key)));
		const statuses = Promise.all(statusKeys.map(key => key === null ? null : getAsync(key)));
		const nodePlants = Promise.all(nodeNames.map(name => getAsync(name)));
		const nodeActivity = Promise.all(nodeNames.map(name => name === null ? null : nodeManager.getActiveAsync(name)));
		return Promise.all([
			measurements,
			statuses,
			nodeNames,
			nodePlants,
			nodeActivity
		]);
	}).then(dbResults => {
		let [
			measurements,
			statuses,
			nodeNames,
			nodePlants,
			nodeActivity
		] = dbResults;
		
		measurements = measurements.filter(m => m !== null);
		statuses = statuses.filter(m => m !== null);
		
		if (nodePlants.indexOf(plantName) >= 0) {
			response.deployed = nodeNames[nodePlants.indexOf(plantName)];
			response.active = nodeActivity[nodePlants.indexOf(plantName)];
		}

		response.status = JSON.parse(statuses[statuses.length - 1]).status;
		
		measurements = measurements.map(i => {
			i = JSON.parse(i);
			i.date = new Date(i.date);
			return i;
		});
		
		statuses = statuses.map(i => {
			i = JSON.parse(i);
			i.date = new Date(i.date);
			return i;
		});

		/* FILTER measurements and statuses here */
		if (!isNaN(req.query.from)) {
			measurements = measurements.filter(m => m.date >= parseFloat(req.query.from));
			statuses = statuses.filter(m => m.date >= parseFloat(req.query.from));
		}
		if (!isNaN(req.query.to) && req.query.to > 0) {
			measurements = measurements.filter(m => m.date <= parseFloat(req.query.to));
			statuses = statuses.filter(m => m.date <= parseFloat(req.query.to));
		}
		
		if (limit > 0) {
			console.log("limited");
			let sampledMeasurements = [];
			let sampledStatuses = [];

			let deltaM = Math.floor( measurements.length / limit );
			let deltaS = Math.floor( statuses.length / limit );
			deltaM = deltaM >= 1 ? deltaM : 1;
			deltaS = deltaS >= 1 ? deltaS : 1;
			console.log("Only doing every " + deltaM + "th sensor value and every " + deltaS + "th status");

			for (let i = 0; i < measurements.length; i=i+deltaM) {
				sampledMeasurements.push(measurements[i]);
			}

			for (let i = 0; i < measurements.length; i=i+deltaS) {
				sampledStatuses.push(statuses[i]);
			}

			statuses = sampledStatuses;
			measurements = sampledMeasurements;


			// If we couldn't sample, we cut the start to meet the requirements
			if (statuses.length > limit) {
				statuses.splice(0, statuses.length - limit);
			}
			if (measurements.length > limit) {
				measurements.splice(0, measurements.length - limit);
			}
		}

		
		for (let measurement of measurements) {
			response.timestamps.push(measurement.date.getTime());
			response.temperature.push(measurement.temp);
			response.moisture.push(measurement.moisture);
			response.humidity.push(measurement.humidity);
			response.brightness.push(measurement.light);
			response.waterAboveGround.push(measurement.water);
		}

		// Positive: More measurements than statuses, negative: less measurements than statuses
		let difference = measurements.length - statuses.length;
		
		if (difference < 0) {
			// push empty rows to the start
			for (let i = 0; i < (-difference); i++) {
				let status = statuses.shift();
				response.timestamps.unshift(status.date).getTime();
				response.temperature.unshift(null);
				response.moisture.unshift(null);
				response.humidity.unshift(null);
				response.brightness.unshift(null);
				response.waterAboveGround.unshift(null);
				response.size.push(status.size);
				response.size.push(status.size);
				response.health.push(status.health);
			}
		} else if (difference > 0) {
			for (let i = 0; i < difference; i++) {
				response.health.push(null);
			}
		}
		
		console.log("Corrected difference of " + difference + " to " + (measurements.length - statuses.length));
		
		for (let status of statuses) {
			response.size.push(status.size);
			response.health.push(status.health);
		}
		res.send(JSON.stringify(response));
	}).catch(e => {
		let error = 200;
		if (e === 404) {
			error = 404;
		} else {
			console.log(e);
		}
		// We ALWAYS send valid JSON
		res.status(error).send(JSON.stringify(response));
	});
});

// creates new plant with given id and template name
router.post("/:id", function(request, response, next) {
	let id = request.body.name;
	let template = request.body.template;
	//tocheck
	//check existence
	client.sismember("plants",id, function(err, reply) {
		if (err) {
			throw err; 
		} else if (reply) { 
			//plant exists
			response.status(500).send("Plant name already in use.");
		} else {
			//plant does not exist
			client.sadd("plants", id, function(err) {
				if (err) throw err;
			});
			var saveKey = id + "_template";
			client.set(saveKey, template, function(err) {
				if (err) throw err;
			});
			response.status(200).send();
		}
	});
});

// delete plant with given id and all connected data
router.delete("/:id", function(req,res,next){
	let id = req.params.id;
	client.srem('plants',id,function(err,reply){
		if(err) {
			throw err;
		} else {
			if (!reply) {
				res.status(404).send("Plant not Found.");
			} else {
				client.srem('plants',id);
				//delete all measurements of given id
				client.lrange(id,0,-1,function(err,m_list) {
					m_list.forEach(measurement => {
						client.del(measurement);
					});
					client.del(id);
				});
				// delete all status data of given id
				id = id+"_status";
				client.lrange(id,0,-1,function(err,s_list) {
					s_list.forEach(status => {
						client.del(status);
					});
					client.del(id);
				});
				//delete plant-template pair
				id = id+"_template";
				client.del(id);
				res.status(200).send();
			}
		}
	});
});

module.exports = router;
