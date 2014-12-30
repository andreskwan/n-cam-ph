var spawn = require('child_process').spawn;
spawn
var args = ["-o"];
var proc = spawn('raspistill', args);
var args = ["-o", "cam.jpg"];
var proc = spawn('raspistill', args);
var args = ["-w", "640", "-h", "480", "-o", "'stream/cam.jpg'"];
var proc = spawn('raspistill', args);
var args = ["-w", "640", "-h", "480", "-o", "'./stream/cam.jpg'"];
var proc = spawn('raspistill', args);
var args = ["-w", "640", "-h", "480", "-o", "'cam.jpg'"];
var args = ["-w", "640", "-h", "480", "-o", "cam.jpg"];
var proc = spawn('raspistill', args);
var args = ["-w", "640", "-h", "480", "-o", "stream/cam.jpg"];
var proc = spawn('raspistill', args);
