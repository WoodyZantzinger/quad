
#include <Wire.h>

#define ACCELADDR 0x53

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
  Serial.print("Ready"); // print "Ready" once
  Serial.println("Ready"); // print "Ready" once
  Serial.print("Ready"); // print "Ready" once
  init_accel(ACCELADDR);
}

void loop() {
  while (true) {
    XYZBuffer temp;
    Wire.beginTransmission(ACCELADDR);
    Wire.write(0x32);
    Wire.endTransmission();
    Wire.requestFrom(ACCELADDR, 6);
    long start = millis();
    while(Wire.available()) {
      for (int i=1; i< 6; i++) {
        temp.buff[i] = Wire.read();
      }
    }
    Serial.print(temp.value.x);
    Serial.print(':');
    Serial.print(temp.value.y);
    Serial.print(':');
    Serial.print(temp.value.z);
    Serial.print('\n');
    delay(100); // delay for 1/10 of a second
  }
}
