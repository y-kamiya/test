<script src='socket.io/socket.io.js'></script>
<script>
    var socket = io.connect('http://localhost:8000');

    socket.on('msg', function(data) {
        console.log(data);
    });

    setInterval(function() {
        socket.emit('msg', { msg: 'From client', now: new Date()});
    }, 1000);
</script>

