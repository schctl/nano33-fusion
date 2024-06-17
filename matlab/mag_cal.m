% Magnetometer calibration
% Rotate the sensor in a spherical motion during the calibration

ts = tic;

magReadings=[];

flush(arduinoObj);

while(toc(ts) < 50)
   data = readline(arduinoObj);
   readings = str2num(data);

   magReadings = [magReadings;readings(4:6)]; 
end

[A, b] = magcal(magReadings); % A = 3x3 matrix for soft iron correction 
                              % b = 3x1 vector for hard iron correction
