% https://in.mathworks.com/help/fusion/ug/Estimating-Orientation-Using-Inertial-Sensor-Fusion-and-MPU-9250.html

viewer = HelperOrientationViewer('Title',{'AHRS Filter'});

ts = tic;

FUSE = ahrsfilter('SampleRate', 200, ...
        'GyroscopeNoise', 0.3, ...
        'AccelerometerNoise', 0.0061);

flush(arduinoObj);
gyrplot = plot(0, '-o');

allReadings = [];

while (toc(ts) < 30)
    data = readline(arduinoObj);
    readings = str2num(data);

    % magnetometer bias correction
    readings(4) = readings(4)-b(1);
    readings(5) = readings(5)-b(2);
    readings(6) = readings(6)-b(3);
    readings(4:6) = readings(4:6) * A;

    % convert gyro units
    readings(7:9) = readings(7:9) - gyrOffset;
    readings(7:9) = deg2rad(readings(7:9));

    allReadings = [allReadings; readings];
 
    ydata = [get(gyrplot,'YData') readings(9)];
    set(gyrplot,'YData',ydata(max(1, end - 300):end));

    rotators = FUSE(readings(1:3), readings(7:9), readings(4:6));
    % rotators = ecompass(readings(1:3), readings(4:6));
 
    for j = numel(rotators)
        viewer(rotators(j));
    end
end

now = datetime('now');
now.Format = 'yyyy-MM-dd_HH-mm-ss';
writematrix(allReadings, sprintf("logs/%s.txt", string(now)));
