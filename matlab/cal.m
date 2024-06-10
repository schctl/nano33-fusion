ts = tic; 

magReadings=[];

while(toc(ts) < 50) 
    % Rotate the sensor along x axis from 0 to 360 degree. 
    % Take 2-3 rotations to improve accuracy. 
    % For other axes, rotate along that axes. 
   data = readline(arduinoObj);
   readings = str2num(data);

   magReadings = [magReadings;readings(4:6)]; 
end 

[A, b] = magcal(magReadings); % A = 3x3 matrix for soft iron correction 
                              % b = 3x1 vector for hard iron correction
