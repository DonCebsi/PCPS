const express = require('express');
const router = express.Router();
const redis = require('redis');
const addLineToDB = require('../dbSaver');
const { promisify } = require('util');

// Create Redis Client
const client = redis.createClient();
client.auth("pcpsMontag2");

client.on('connect', function(err) {
  if (err) throw err;
});

const getAsync = promisify(client.get).bind(client);
const delAsync = promisify(client.del).bind(client);
const lrangeAsync = promisify(client.lrange).bind(client);

/* GET users listing. */
router.post("/", function(req, res, next) {
  res.setHeader('Content-Type', 'text/plain');
  let override = req.body.override;
  let newName = req.body.newName;
  const rename = !!newName;
  let id = "";
  let dataArray = req.body.data.split("\n"); //data to array

  if (rename) id = newName;
  else id = dataArray[0];
  checkExistence(id, exist => {
    if (exist && override) {
      //plant name(id) exists, but existing data will be overridden
      client.smembers("nodes", function(err, reply) {
        Promise.all(reply)
          .then(reply => {
            reply = reply.map(r => getAsync(r));
            return Promise.all(reply);
          }).then(reply => {
            if (reply.includes(id)) {
              throw new Error('active plant set');
              return null;
            } else deleteData(id).then(done => {
              console.log(id + " has been deleted");
              savePlant(id, dataArray).then(done => {
                console.log("Plant <" + id + "> has been saved");
              });

            })
          }).catch(err => {
            if (err.message === 'active plant set')
              res.status(500).send("Can't override plant, because it's active on any arduino.");
            else res.status(500).send("Something went wrong!");
          });
      });
      //add new plant id to plants list
    } else if (exist) {
      //error plant with this name(id) already exists
      res.status(500).send("Error! Plant with the given name does already exist and overriding is disabled.");
    } else savePlant(id, dataArray).then(done => {
      console.log("Plant <" + id + "> has been saved");
      res.status(200).send();
    }); //plant name(id) does not exist yet
  });
});

function savePlant(id, dataArray) {
  let data_type = -1;
  let saving = dataArray.map(function(ele, i) {
    if (i === 0) client.sadd("plants", id);
    else if (data_type === 3) {
      data_type = -1;
      client.set(id + "_template", ele, function(err, reply) {
        if (err) console.log(err);
      });
    } else if (ele === "MEASSURED") data_type = 2;
    else if (ele === "STATUS") data_type = 1;
    else if (ele === "TEMPLATE") data_type = 3;
    else if (data_type !== -1) {
      addLineToDB.enqueueBackup(ele, id, data_type);
    }
  });
  return Promise.all(saving);
}

router.get("/:id", function(req, res, next) {
  const id = req.params.id;
  client.smembers("plants", function(err, reply) {
    if (err) console.log(err);
    else if (!reply.includes(id)) res.status(404).send("Plant not found!");
    else {
      client.lrange(id, 0, -1, function(err, reply) {
        if (err) console.log(err);
        createBackup(reply, id, res);
      });
    }
  });
});
//read the redis data and save it line by line in the backup file
//each line contains one data sample ordered by the redis entries
function createBackup(data_keys, id, res) {
  //add id and start of measured data
  let dataString = id + "\nMEASSURED\n";
  //add measured data to string
  Promise.all(data_keys.map(k => getAsync(k))).then(data_keys => {
    dataString += data_keys.join("\n");
    //start of status Data
    dataString += "\nSTATUS\n";
    return lrangeAsync(id + "_status", 0, -1);
    //add status data
  }).then(status_keys => {
    return Promise.all(status_keys.map(k => getAsync(k)));
  }).then(status_data => {
    dataString += status_data.join("\n");
    dataString += "\nTEMPLATE\n";
    return getAsync(id + "_template");
  }).then(template => {
    dataString += template;
    res.setHeader('Content-Type', 'text/plain');
    let filename = id + ".backup";
    res.attachement(filename);
    res.send(dataString);
  }).catch(err => {
    console.log(err);
  });
}

//checking whether the plant does already exist or not
function checkExistence(id, callback) {
  client.lrange("plants", 0, -1, function(err, reply) {
    if (err) throw err;
    if (reply.indexOf(id) == -1) callback(false);
    else callback(true);
  });
}

//override function - deleting all existing data of a plant
function deleteData(id) {
  //delete meassured data, the associated key list and the <plant> in plants
  let one = lrangeAsync(id, 0, -1).then(reply => {
    reply.map(k => delAsync(k));
    client.del(id);
    client.srem("plants", id);
  }).catch(err => {
    console.log(err);
  });

  //delete status data and status key list
  let two = lrangeAsync(id + "_status", 0, -1).then(reply => {
    reply.map(k => delAsync(k));
    client.del(id + "_status");
  }).catch(err => {
    console.log(err);
  });

  //delete template
  let three = delAsync(id + "_template").catch(err => {
    console.log(err);
  });
  //return when everything is done
  return Promise.all([one, two, three]);
}
module.exports = router;