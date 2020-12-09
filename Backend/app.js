const createError = require('http-errors');
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const arduinoCom = require('./arduinoConnectivity.js');

const backupRouter = require('./routes/backup.js');
const plantsRouter = require('./routes/plants.js');
const templatesRouter = require('./routes/templates.js');
const nodesRouter = require('./routes/nodes.js');

const app = express();

arduinoCom.runArduinoServer(7275);

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
//app.use(express.static(path.join(__dirname, 'public')));

//app.use('/api/activePlant', indexRouter);
//app.use('/api/backup', indexRouter);
app.use('/api/backup', backupRouter);
//app.use('/api/newPlant', indexRouter);
app.use('/api/plants', plantsRouter);
//app.use('/api/plant', indexRouter);
app.use('/api/templates', templatesRouter);
app.use('/api/nodes', nodesRouter);
// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
