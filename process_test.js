process.stdin.resume();

process.stdin.setEncoding('utf8');
process.stdout.setEncoding('utf8');

process.stdin.on('data', function(data) {
    process.stdout.write(data);
})
.on('end', function() {
    process.stdin.destroy();
})
.on('close', function() {
    process.exit();
})
.on('error', function() {
    process.stdin.destroy();
});

process.stdout.on('close', function() {
    process.exit();
})
.on('error', function() {
    process.stdout.destroy();
});


