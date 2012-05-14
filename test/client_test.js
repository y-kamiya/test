var http = require('http');

var options = {
    host: '127.0.0.1',
    port: 8000,
    path: '/clientTest',
    method: 'POST',
};

var req = http.request(options);

req.on('response', function(res) {
    res.setEncoding('utf8');

    res.on('data', function(chunk) {
        console.log('body: ' + chunk);
    });
});

req.on('error', function(e) {
    console.log('error: ' + e.message);
});

req.write('Send data');

setInterval(function() {
    req.write('Send body');
}, 500);

process.on('exit', function() {
    console.log('About to exit.');
    req.end();
});
