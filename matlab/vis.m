% https://in.mathworks.com/help/fusion/ug/Estimating-Orientation-Using-Inertial-Sensor-Fusion-and-MPU-9250.html

viewer = HelperOrientationViewer('Title',{'AHRS Filter'});

ts = tic;

FUSE = ahrsfilter('SampleRate', 119, ...
        'GyroscopeNoise', 3.0462e-06, ...
        'AccelerometerNoise', 0.0061);

while (toc(ts) < 100)
    data = readline(arduinoObj);
    readings = str2num(data);

    readings(4) = readings(4)-b(1);
    readings(5) = readings(5)-b(2);
    readings(6) = readings(6)-b(3);
    readings(4:6) = readings(4:6) * A;

    rotators = FUSE(readings(1:3), readings(7:9), readings(4:6));
 
    for j = numel(rotators)
        viewer(rotators(j));
    end
end
