#include <Arduino.h>
#include <Arduino_LSM9DS1.h>

#include "Fusion.h"

FusionAhrs ahrs;
unsigned long last_t;

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
    IMU.readGyroscope(mag.axis.x, mag.axis.y, mag.axis.z);

    unsigned long dt = millis() - last_t;
    
    FusionAhrsUpdate(&ahrs, gyr, acc, mag, dt);

    const FusionEuler euler = FusionQuaternionToEuler(FusionAhrsGetQuaternion(&ahrs));

    Serial.print("Roll: ");
    Serial.print(euler.angle.roll);
    Serial.print(" Pitch: ");
    Serial.print(euler.angle.pitch);
    Serial.print(" Yaw: ");
    Serial.println(euler.angle.yaw);
    Serial.println();
  }

  delay(150);
}
