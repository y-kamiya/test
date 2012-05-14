var io = require('socket.io').listen(8000);

io.sockets.on('connection', function(socket) {
    setInterval(function() {
        socket.emit('msg', { msg: 'From server', now: new Date() });
    }, 1000);

    socket.on('msg', function(data) {
        console.log('Recieved: ', data);
    });

    socket.on('disconnect', function() {
        console.log('disconnect');
    });
});

