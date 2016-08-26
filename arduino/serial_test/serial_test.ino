
#include <Wire.h>
#include "accelerometer.h"
#include "packet.h"

#define ACCELADDR 0x53
#define GYROADDR 0x68

Accelerometer *Accel;

union XYZBuffer{
  struct{
    short x,y,z;
  } value;
  byte buff[6];
};

void setup() {
  Serial.begin(9600); // set the baud rate
  
  Packet *to_send = new Packet(Packet::TYPE_MSG, "BOOTED");
  Serial.write(to_send->getBytes(), to_send->getLen());

  Accel = new Accelerometer(ACCELADDR);
}

void loop() {
  while (true) {
    
    Accel->update();
    
    //Accel->print();
    

    Packet *to_send = new Packet(Packet::TYPE_POS, Accel->getRoll(), Accel->getPitch());
    Serial.write(to_send->getBytes(), to_send->getLen());

    /*
    Wire.beginTransmission(GYROADDR);
    Wire.write(0x1D);
    Wire.endTransmission();
    Wire.requestFrom(GYROADDR, 6);
    int x = 0;
    XYZBuffer buffer;
    while(Wire.available()) {
        buffer.buff[x] = Wire.read();
        x++;
    }
    /*
    Serial.print("GYRO : ");
    Serial.print(buffer.value.x / 14.375);
    Serial.print(":");
    Serial.print(buffer.value.y / 14.375);
    Serial.print(":");
    Serial.print(buffer.value.z / 14.375);
    Serial.print('\n');
    */    
    delay(125); // delay for 1/8 of a second
  }
}
