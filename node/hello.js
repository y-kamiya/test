var util = require('util');
var http = require('http');

var s = http.createServer(function(req, res) {
    res.writeHead(200, { 'content-type' : 'text/plain' });
    res.write('hello\n');
    setTimeout(function() {
        res.end('world\n');
    }, 2000);
    
});

function foo() {
    debugger;
    return util.log(1 + 2);
}

foo();

s.listen(8001);

util.log('Server running at http://test_vm:8001');
