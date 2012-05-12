var http = require('http');
var fs   = require('fs');
var url  = require('url');

onRequest = function(req, res) {
    var parsed_url = url.parse(req.url, true);
    pathname = parsed_url.pathname;
    if(pathname === '/favicon.ico') {
        return;
    }

    req.setEncoding('utf8');
    res.setHeader('Content-Type', 'text/plain');

    // post用処理
    req.on('data', function(chunk) {
        console.log(chunk);
        res.end('\naccess url:  ' + req.url);
    });

    // 入力画面
    if(pathname === '/send') {
        fs.readFile('./http_test.html', function(err, content) {
            if(err) {
                throw err;
            }
            res.setHeader('Content-Type', 'text/html');
            res.write(content);
            res.end('\naccess url:  ' + req.url);
        });
    }
    else {
        for(key in parsed_url.query) {
            res.write(key + ': ' + parsed_url.query[key] + '\n');
        }
        res.end('\naccess url:  ' + req.url);
    }
}
http.createServer(onRequest).listen(8000);
