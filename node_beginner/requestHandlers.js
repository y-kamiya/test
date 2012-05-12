var querystring = require('querystring'),
    fs = require('fs'),
    formidable = require('formidable');

function start(req, res) {
    console.log("Request handler 'start' was called.");
    req.setEncoding('utf8');
    var header = '<html>'+
        '<head>'+
        '<meta http-equiv="Content-Type" content="text/html; '+
        'charset=UTF-8" />'+
        '</head>'+
        '<body>';

    var footer = '</body>'+'</html>';

    var textarea = 
        '<form action="/upload" method="post">'+
        '<textarea name="text" rows="20" cols="60"></textarea>'+
        '<input type="submit" value="Submit text" />'+
        '</form>';

    var file = 
        '<form action="/uploadFile" enctype="multipart/form-data" '+
        'method="post">'+
        '<input type="file" name="upload">'+
        '<input type="submit" value="Upload file" />'+
        '</form>';

    var body = header + textarea + file + footer;

    //exec('ls -lah', function(err, stdout, stderr) {
        res.writeHead(200, {'Content-Type':'text/html'});
        res.write(body);
        res.end();
    //});
}

function upload(req, res) {
    var postData = '';
    req.setEncoding('utf8');
    console.log("Request handler 'upload' was called.");

    req.on('data', function(postDataChunk) {
        postData += postDataChunk;
        console.log('Received POST data chunk "' + postDataChunk + '".');
    });
    req.on('end', function() {
        res.writeHead(200, {'Content-Type':'text/plain'});
        res.write('sent: ' + 
        querystring.parse(postData).text);
        console.log(querystring.parse(postData));
        res.end();
    });
}

function uploadFile(req,res) { 
    console.log("Request handler 'uploadFile' was called.");

    var form = new formidable.IncomingForm();
    console.log('about to parse');
    form.parse(req, function(error, field, files) {
        console.log('parsing done');

        fs.rename(files.upload.path, '/tmp/test.jpg', function(err) {
            if(err) {
                fs.unlink('/tmp/test.jpg');
                fs.rename(files.upload.path, '/tmp/test.jpg');
            }
        });
        res.writeHead(200, {"Content-Type": "text/html"});
        res.write("received image:<br/>");
        res.write("<img src='/show' />");
        res.end();
    });
}

function show(req, res) {
    console.log("Request handler 'show' was called.");
    fs.readFile('/tmp/test.jpg', 'binary', function(error, file) {
        if(error) {
            res.writeHead(500, {"Content-Type": "text/plain"});
            res.write(error + "\n");
            res.end();
        } else {
            res.writeHead(200, {"Content-Type": "image/jpg"});
            res.write(file, "binary");
            res.end();
        }
    });
}


exports.start = start;
exports.upload = upload;
exports.uploadFile = uploadFile;
exports.show = show;
