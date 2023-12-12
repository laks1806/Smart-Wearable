#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;
float accelX, accelY, accelZ;
float gyroX, gyroY, gyroZ;

// Apply offsets


void setup() {
  Serial.begin(9600);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("AccelX: "); Serial.print(a.acceleration.x);
  Serial.print(" AccelY: "); Serial.print(a.acceleration.y);
  Serial.print(" AccelZ: "); Serial.print(a.acceleration.z);
  Serial.print(" GyroX: "); Serial.print(g.gyro.x);
  Serial.print(" GyroY: "); Serial.print(g.gyro.y);
  Serial.print(" GyroZ: "); Serial.print(g.gyro.z);
  accelX = a.acceleration.x - 10.02;
  Serial.print(" cal "); Serial.print(accelX);


  Serial.println();

  delay(100);
}
