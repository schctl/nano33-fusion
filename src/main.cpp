#include <Arduino.h>
#include <Arduino_LSM9DS1.h>

#include "Fusion.h"

FusionAhrs ahrs;

// ------------------ LSM9DS1 -------------------

#define LSM9DS1_ADDRESS     0x6b
#define LSM9DS1_CTRL_REG1_G 0x10
#define LSM9DS1_CTRL_REG2_G 0x11

int writeRegister(uint8_t address, uint8_t reg, uint8_t value) {
  Wire1.beginTransmission(address);
  Wire1.write(reg);
  Wire1.write(value);
  if (Wire1.endTransmission() != 0) {
    return 0;
  }
  return 1;
}

// ------------------ Setup ---------------------

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  writeRegister(LSM9DS1_ADDRESS, LSM9DS1_CTRL_REG1_G, 0x78); // 119 Hz, 2000 dps, 14 Hz BW
  writeRegister(LSM9DS1_ADDRESS, LSM9DS1_CTRL_REG2_G, 0x03); // apply LPF1 & LPF2

  FusionAhrsInitialise(&ahrs);
}

// ------------------ Loop ----------------------

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
    Serial.print(gyr.axis.y);
    Serial.print(" ");
    Serial.print(-gyr.axis.z);
    Serial.print("\r\n");
  }

  delay(5);
}
