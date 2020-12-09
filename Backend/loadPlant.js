const arduCom = require('./arduinoConnectivity')
// 
function loadPlant(arduid, name, plantjson, state){ //create a byte stream with plant's specifications
	let payload  = Buffer.allocUnsafe(109); //allocate toal space needed
	let statPyl  = Buffer.allocUnsafe(8); //allocate toal space needed
	// Not needed, because we overwrite all the things
	//payload.fill(0); // fill up buffer with 0 to guarentee nothing's there
	if (!plantjson) {
		plantjson = {
			maxSize : 40,
			growSpeed : 0.5,
			regenerationSpeed : 5,
			tempRange : {min: 0, max: 40},
			tempBoost : {susceptibility: 2, range: 9.9, amount: 1, optimum: 26},
			moistureThreshold : 900,
			moistureStruggleSeconds : 560,
			moistureLackSusceptibility : 34,
			waterCanGetAboveGround : 1,
			humidityRange : {min: 5.01, max: 68},
			humidityBoost : {susceptibility: 5, range: 6, amount: 30, optimum: 30},
			darkMaxSeconds: 14000,
			lightMaxSeconds: 45600,
			darkLightThreshold: 3000,
			darkSusceptibility: 46,
			lightBoost: {susceptibility: 1, range: 5000, amount: 2.1, optimum: 10000}
		}
	}

	if (!state) {
		state = { health: 100, size: 0 };
	}

	payload.writeFloatLE(plantjson.maxSize, 0);
	payload.writeFloatLE(plantjson.growSpeed, 4);
	payload.writeFloatLE(plantjson.regenerationSpeed, 8);

	payload.writeFloatLE(plantjson.tempRange.min, 12);
	payload.writeFloatLE(plantjson.tempRange.max, 16);

	payload.writeFloatLE(plantjson.tempBoost.optimum, 20);
	payload.writeFloatLE(plantjson.tempBoost.amount, 24);
	payload.writeFloatLE(plantjson.tempBoost.range, 28);
	payload.writeFloatLE(plantjson.tempBoost.susceptibility, 32);
	
	// working with little endian because both arduino and pi seem to be in LE mode.
	payload.writeUInt16LE(plantjson.moistureThreshold, 36);
	payload.writeUInt32LE(plantjson.moistureStruggleSeconds, 38);
	payload.writeFloatLE(plantjson.moistureLackSusceptibility, 42);
	payload.writeInt8(plantjson.waterCanGetAboveGround, 43);

	payload.writeFloatLE(plantjson.humidityRange.min, 47);
	payload.writeFloatLE(plantjson.humidityRange.max, 51);

	payload.writeFloatLE(plantjson.humidityBoost.optimum, 55);
	payload.writeFloatLE(plantjson.humidityBoost.amount, 59);
	payload.writeFloatLE(plantjson.humidityBoost.range, 63);
	payload.writeFloatLE(plantjson.humidityBoost.susceptibility, 67);
	
	payload.writeDoubleLE(plantjson.darkMaxSeconds, 71);
	payload.writeDoubleLE(plantjson.lightMaxSeconds, 79);
	payload.writeUInt32LE(plantjson.darkLightThreshold, 87);
	payload.writeFloatLE(plantjson.darkSusceptibility, 91);

	payload.writeUInt16LE(plantjson.lightBoost.optimum, 95);
	payload.writeFloatLE(plantjson.lightBoost.amount, 97);
	payload.writeFloatLE(plantjson.lightBoost.range, 101);
	payload.writeFloatLE(plantjson.lightBoost.susceptibility, 105);

	if (state !== null) {
		statPyl.writeFloatLE(state.size, 0);
		statPyl.writeFloatLE(state.health, 4);
	}

	const header = arduCom.createHeader(3,255);
	const headerS = arduCom.createHeader(1,255);
	const final = Buffer.concat([header, payload], header.length + payload.length);

	const finalS = Buffer.concat([headerS, statPyl], headerS.length + statPyl.length);

	let retry = (id, package, tries) => {
		if (tries > 0) {
			try {
				arduCom.sendPlantToArduino(id, package);
			} catch (e) {
				console.log("Failed to queue plant for sending. Trying again soon ...");
				setTimeout(() => {retry(id, package, tries - 1 )}, 2000);
			}
		} else {
			console.log("I'm quitting trying to queue for " + id);
		}
	}
	retry(arduid, {spec: final, name: name, state: state === null ? undefined : finalS}, 5);
	
	//TODO: encode buffer with boost parameters(not sure ATM, needs further considerations)
}

module.exports = { loadPlant };

//TODO: send to arduino