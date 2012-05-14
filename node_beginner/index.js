var server = require('./server');
var router = require('./router.js');
var requestHandlers = require('./requestHandlers');

var handle = {};
handle['/'] = requestHandlers.start;
handle['/start'] = requestHandlers.start;
handle['/upload'] = requestHandlers.upload;
handle['/uploadFile'] = requestHandlers.uploadFile;
handle['/show'] = requestHandlers.show
handle['/clientTest'] = requestHandlers.clientTest;

server.start(router.route, handle);
