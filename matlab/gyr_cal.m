% Gyroscope calibration
% Keep the sensor stationary during calibration

ts = tic; 

gyrReadings=[];

flush(arduinoObj);

while(toc(ts) < 5)
   data = readline(arduinoObj);
   readings = str2num(data);

   gyrReadings = [gyrReadings;readings(7:9)]; 
end

gyrOffset = mean(gyrReadings);
