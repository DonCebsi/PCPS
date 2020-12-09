var request = require ('supertest'), app = require ('../app')

// TODO: Timeouts handlen. Deleten klappt trotzdem.

//-----------plants.js------------------

describe ("test app.js_1", function() {
	it ("catch error handler", function (done) {
		request(app).get("/")
			.expect(404, done)
	})
})


describe ("test plantsrouter_get", function() {
	it ("test connection to plants api get any plant", function () {
		request(app).get("/api/plants")
			.expect([])
			.expect(200)
	})
})


describe ("test plantsrouter_post", function() {
	it ("test connection to plants api post", function (done) {
		request(app).post("/api/plants/:id")
			.send({name:"TEST1", template:"t1"})
			.expect(200, done)
	})
})


describe ("test plantsrouter_postAfterPost", function() {
	it ("test connection to plants api second post", function (done) {
		request(app).post("/api/plants/:id")
			.send({name:"TEST2", template:"t1"})
			.expect(200, done)
	})
})


describe ("test plantsrouter_getAfterPost", function() {
	it ("test connection to plants api get existing plants", function (done) {
		request(app).get("/api/plants")
			.expect([ { name: 'TEST1',
						temperatue: null,
						moisture: null,
						humiditity: null,
						brightness: null,
						waterAboveGround: null },
					  { name: 'TEST2',
						temperatue: null,
						moisture: null,
						humiditity: null,
						brightness: null,
						waterAboveGround: null } ])
			.expect(200, done)
	})
})


describe ("test plantsrouter_postAfterPostWhileAlreadyExists", function() {
	it ("test connection to plants api post while already in use", function (done) {
		request(app).post("/api/plants/:id")
			.send({name:"TEST1"})
			.expect("Plant name already in use.")
			.expect(500, done)
	})
})


describe ("test plantsrouter_delete TEST 1", function() {
	it ("test connection to plants api delete TEST1", function (done) {
		this.timeout(300);
		request(app).delete("/api/plants/TEST1")
			.expect(200, done)
	})
})


describe ("test plantsrouter_delete TEST 2", function() {
	it ("test connection to plants api delete TEST2", function (done) {
		this.timeout(300);
		request(app).delete("/api/plants/TEST2")
			.expect(200, done)
	})
})


describe ("test plantsrouter_delete non existing plant", function() {
	it ("test connection to plants api delete while not exisiting", function (done) {
		request(app).delete("/api/plants/sdfds")
			.expect("Plant not Found.")
			.expect(404, done)
	})
})


describe ("test plantsrouter_get at end of test", function() {
	it ("test connection to plants api get any plant at end of test", function () {
		request(app).get("/api/plants")
			.expect([])
			.expect(200)
	})
})






//-----------templates.js------------------


describe ("test templatesrouter_get", function() {
	it ("test connection to templates api get any template", function () {
		request(app).get("/api/templates")
			.expect(200)
	})
})


describe ("test templatesrouter_post", function() {
	it ("test connection to templates api post", function (done) {
		request(app).post("/api/templates/TMP1")
			.expect(200, done)
	})
})


describe ("test templatesrouter_post2", function() {
	it ("test connection to templates api second post", function (done) {
		request(app).post("/api/templates/TMP2")
			.expect(200, done)
	})
})


describe ("test templatesrouter_post template with already existing name", function() {
	it ("test connection to templates while name exists", function (done) {
		request(app).post("/api/templates/TMP2")
			.expect("Template with given name already exists.")
			.expect(500, done)
	})
})


describe ("test templatesrouter_delete success TMP1", function() {
	it ("test connection to templates api delete success TMP1", function (done) {
		this.timeout(300);
		request(app).delete("/api/templates/TMP1")
			.expect(200, done)
	})
})


describe ("test templatesrouter_delete success TMP2", function() {
	it ("test connection to templates api delete success TMP2", function (done) {
		this.timeout(300);
		request(app).delete("/api/templates/TMP2")
			.expect(200, done)
	})
})


describe ("test templatesrouter_delete non existing template", function() {
	it ("test connection to templates api delete non existing template", function (done) {
		this.timeout(300);
		request(app).delete("/api/templates/asnasd")
			.expect(404, done)
	})
})




//-----------nodes.js------------------


describe ("test nodesrouter_get", function() {
	it ("test connection to nodes api get any node", function (done) {
		request(app).get("/api/nodes")
			.expect("[]")
			.expect(200, done)
	})
})


describe ("test nodesrouter_post", function() {
	it ("test connection to nodes api post node", function (done) {
		request(app).post("/api/nodes/:id")
			.send({id: 5, plant: 7})
			.expect(200, done)
	})
})




//-----------backup.js------------------


describe ("test backup_get", function() {
	it ("test connection to nodes api get any node", function (done) {
		request(app).get("/api/backup/:id", {id: 1312})
			.expect("Plant not found!")
			.expect(404, done)
	})
})
