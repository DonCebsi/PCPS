var express = require('express');
var router = express.Router();
const redis = require('redis');
const {promisify} = require('util');
const sender = require('../loadPlant');
const nodeManager = require('../nodeManager');

// Create Redis Client
let client = redis.createClient();
client.auth("pcpsMontag2");

client.on('connect', function(){
	console.log('Connected to Redis...');
});

const getAsync = promisify(client.get).bind(client);
const lindexAsync = promisify(client.lindex).bind(client);

// GET all nodes
router.get('/', function(req,res,next){
  client.smembers('nodes', function(err,l_nodes){
    let response = [];
    lnodes = l_nodes.map(r => getAsync(r));
    active = l_nodes.map(r => nodeManager.getActiveAsync(r));
    Promise.all(lnodes.concat(active)).then(answer => {
      console.log(answer);
      nodes = answer.splice(0, l_nodes.length);
      for (var i = 0; i < nodes.length; i++) {
        response[i] = {name:l_nodes[i],plant:nodes[i], active:answer[i]};
      }
      res.setHeader('Content-Type', 'application/json');
      res.send(JSON.stringify(response));
    });
  });
});

router.post('/:id', (req,res,next) => {
  const nodeId = req.params.id;
  const plantId = req.body.plant;

  // Get plant template name and last status from db
  Promise.all([getAsync(plantId + "_template"), lindexAsync(plantId + "_status", -1)]).then(results => {
    let [templateName, lastStatus] = results;
    // Resolve template name
    console.log("last Status " + lastStatus);
    return Promise.all([getAsync(templateName), lastStatus ? getAsync(lastStatus) : undefined]);
  }).then(results2 => {
    // send
    let [template, lastStatus] = results2;
    console.log("template " + template);
    console.log("last Status " + lastStatus);
    sender.loadPlant(nodeId, plantId, JSON.parse(template), lastStatus ? JSON.parse(lastStatus) : {id: 255, date: new Date(), size: 0, health: 100});
    res.send("Queued for transmission");
  }).catch(e => {
    console.log(e);
    res.status(500).send("Database error");
  })
});

module.exports = router;
