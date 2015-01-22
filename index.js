var express  = require('express');
var app      = express();
var http     = require('http').Server(app);
var io       = require('socket.io')(http);
var fs       = require('fs');
var path     = require('path');
var sendData = "";

var serialport = require("serialport");
var SerialPort = serialport.SerialPort; // localize object constructor

// var sp = new SerialPort('/dev/ttyACM0', {
var sp = new SerialPort('/dev/tty.usbmodem14211', {
//sp.parsers.readline('\r')
//serialport.parsers.raw
    baudrate: 9600,
    parser: serialport.parsers.readline('\n')
}); 

var spawn = require('child_process').spawn;
var proc;

app.use('/', express.static(path.join(__dirname, 'stream')));

app.get('/', function(req, res) {
    res.sendFile(__dirname + '/index.html');
});

var sockets = {};

io.on('connection', function(socket) {

  sockets[socket.id] = socket;
  console.log("Total clients connected : ", Object.keys(sockets).length);

  socket.on('disconnect', function() {
    delete sockets[socket.id];

    // no more sockets, kill the stream
    if (Object.keys(sockets).length == 0) {
      app.set('watchingFile', false);
      if (proc) proc.kill();
      fs.unwatchFile('stream/image_stream.jpg');
    }
  });

  socket.on('start-stream', function() {
    startStreaming(io);
  });

  socket.on('start-door', function() {
    startDoor();
  });

  socket.on('stop-door', function() {
    // startStreaming(io);
    stopDoor();
  });
});

http.listen(3000, function() {
  console.log('listening on *:3000');
});

sp.on("data", function (data) {
    var receivedData = data.toString();
    if (receivedData.indexOf('}') > 0 && receivedData.indexOf('{') >= 0)
    {
      // save the data between '{' and '}'
       console.log('Solve this: ', receivedData);
       sendData = receivedData.substring(receivedData.indexOf('{') + 1, receivedData.indexOf('}'));
       console.log('sendData: ', sendData);
       receivedData = '';
    }
    //all that comes without data format 
    console.log('data from serial port: ', receivedData);
});  

//serialPort function
function startDoor() {
  sp.write('{'+'2'+'}', function (err, results) {
    if(err){
      console.log('Serial Port Write error: \n' + err);
      return;
    }
    console.log('results startDoor: ' + results);
  });   
}

function stopDoor() {
  sp.write('{'+'3'+'}', function (err, results) {
    if(err){
      console.log('Serial Port Write error: \n' + err);
      return;
    }
    console.log('results stopDoor: ' + results);
  });   
  // io.sockets.emit('doorState', sp.)
}

//socketIO functions
function stopStreaming() {
  if (Object.keys(sockets).length == 0) {
    app.set('watchingFile', false);
    if (proc) proc.kill();
    fs.unwatchFile('stream/image_stream.jpg');
  }
}

function startStreaming(io) {
  if (app.get('watchingFile')) {
    io.sockets.emit('liveStream', 'image_stream.jpg?_t=' + (Math.random() * 100000));
    return;
  }

  var args = ["-w", "640", "-h", "480", "-o", "stream/image_stream.jpg", "-t", "999999999", "-tl", "100"];
  proc = spawn('raspistill', args);

  console.log('Watching for changes...');

  app.set('watchingFile', true);

  fs.watchFile('stream/image_stream.jpg', function(current, previous) {
    io.sockets.emit('liveStream', 'image_stream.jpg?_t=' + (Math.random() * 100000));
  })
}
