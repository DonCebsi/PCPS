var express = require('express');
var router = express.Router();
const redis = require('redis');
const {promisify} = require('util');

// Create Redis Client
let client = redis.createClient();
client.auth("pcpsMontag2");

client.on('connect', function(){
	console.log('Connected to Redis...');
});
const getAsync = promisify(client.get).bind(client);

// get list of templates
router.get('/', function(req, res, next){
	client.smembers('templates',function(err,templ_ids) { //list of plants
		if (err) {
			res.send(err);
		} else {
			templs = templ_ids.map(r => getAsync(r));
			Promise.all(templs).then(templates => {
				for (var i = 0; i < templates.length; i++) {
					templates[i] = JSON.parse(templates[i]);
					templates[i].name = templ_ids[i];
				}
				res.setHeader('Content-Type', 'application/json');
				res.send(JSON.stringify(templates));
			});
		}
	});
});

const templateCreationHandler = (req, res, next) => {
	let id = req.params.name;
	let data = req.body;
	if (!data) return;
	//template set exist
	client.sismember('templates', id, (err,reply) => {
		if(reply == 1){
			//template already exist
			res.status(500).send("Template with given name already exists.");
		} else {
			//template(s) does not exist
			client.sadd('templates',id, err => {
				if (err) throw err;
			});
			client.set(id, JSON.stringify(data), err => {
				if (err) throw err;
			});
			res.status(200).send();
		}
	});
};

// create new template
router.post('/:name', templateCreationHandler);

// create new template (legacy path)
router.post('/', (req, res, next) => {
	req.params = {};
	req.params.name = req.body.name;
	req.body = JSON.parse(req.body.template);
	templateCreationHandler(req, res, next);
});

//delete template
router.delete('/:id', function(req, res, next){
	client.sismember('templates',req.params.id, function(err, reply){
		if (reply == 1) {
			client.srem('templates', req.params.id, (err) => {
				if (err) res.status(500).send("Could not delete from templates");
				client.del(req.params.id, (err) => {
					if (err) {
						client.sadd('templates',req.params.id, (err) => {
							if (err) res.status(500).send("Could not delete from templates. Additionally, an error occurred while trying to roll back");
						});
						res.status(500).send("Could not delete from templates. Rolling back");
					}
					res.status(200).send("Deleted "+ req.params.id);
				});
			});
		}
		else res.status(404).send("template not found!");
	});
});

module.exports = router;
