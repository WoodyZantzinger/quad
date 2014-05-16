
#include <Wire.h>

#define ACCELADDR 0x53
#define GYROADDR 0x68

union XYZBuffer{
  struct{
    short x,y,z;
  } value;
  byte buff[6];
};

void init_accel(int device_id) {
  Serial.print("We got here!");
  Wire.beginTransmission(device_id);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(device_id, 1);
  byte ch;
  Serial.print("We got here!");
  while (!Wire.available()) {
    ch = Wire.read();
  }
  Serial.print("ACCEL INIT IS 0x");
  Serial.println(ch,HEX);
  Wire.beginTransmission(device_id);
  Wire.write(0x2d);
  Wire.write(0x08);
  Wire.endTransmission();
  Wire.beginTransmission(device_id);
  Wire.write(0x38);
  Wire.write(0x84);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(9600); // set the baud rate
  Serial.println("Ready!"); // print "Ready" once
  Serial.print(sizeof(char)); // print "Ready" once
  init_accel(ACCELADDR);
}

void loop() {
  while (true) {
    Wire.beginTransmission(ACCELADDR);
    Wire.write(0x32);
    Wire.endTransmission();
    Wire.requestFrom(ACCELADDR, 6);
    XYZBuffer buffer;
    int x = 0;
    while(Wire.available()) {
        buffer.buff[x] = Wire.read();
        x++;
    }
    Serial.print("ACCEL : ");
    Serial.print(buffer.value.x / 3.9);
    Serial.print(":");
    Serial.print(buffer.value.y / 3.9);
    Serial.print(":");
    Serial.print(buffer.value.z / 3.9);
    Serial.print('\n');
    
    Wire.beginTransmission(GYROADDR);
    Wire.write(0x1D);
    Wire.endTransmission();
    Wire.requestFrom(GYROADDR, 6);
    x = 0;
    while(Wire.available()) {
        buffer.buff[x] = Wire.read();
        x++;
    }
    Serial.print("GYRO : ");
    Serial.print(buffer.value.x / 14.375);
    Serial.print(":");
    Serial.print(buffer.value.y / 14.375);
    Serial.print(":");
    Serial.print(buffer.value.z / 14.375);
    Serial.print('\n');
    
    delay(100); // delay for 1/10 of a second
  }
}
