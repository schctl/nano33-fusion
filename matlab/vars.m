arduinoObj = serialport("COM3",9600);
configureTerminator(arduinoObj,"CR/LF");
flush(arduinoObj);
