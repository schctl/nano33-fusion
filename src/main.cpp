#include <Arduino.h>
#include <Arduino_LSM9DS1.h>

#include "Fusion.h"

FusionAhrs ahrs;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  FusionAhrsInitialise(&ahrs);
}

FusionVector acc, gyr, mag;

void loop() {
  if (IMU.accelerationAvailable())
    IMU.readAcceleration(acc.axis.x, acc.axis.y, acc.axis.z);

  if (IMU.magneticFieldAvailable())
    IMU.readMagneticField(mag.axis.x, mag.axis.y, mag.axis.z);

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gyr.axis.x, gyr.axis.y, gyr.axis.z);
    
    Serial.print(-acc.axis.x);
    Serial.print(" ");
    Serial.print(-acc.axis.y);
    Serial.print(" ");
    Serial.print(acc.axis.z);
    Serial.print(" ");
    Serial.print(-mag.axis.x);
    Serial.print(" ");
    Serial.print(mag.axis.y);
    Serial.print(" ");
    Serial.print(-mag.axis.z);
    Serial.print(" ");
    Serial.print(gyr.axis.x);
    Serial.print(" ");
    Serial.print(-gyr.axis.y);
    Serial.print(" ");
    Serial.print(gyr.axis.z);
    Serial.print("\r\n");
  }

  delay(150);
}
