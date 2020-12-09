module.exports = function(maxSize,growSpeed, progress){
	return maxSize - maxSize * Math.pow(Math.E, - growSpeed * progress);
}