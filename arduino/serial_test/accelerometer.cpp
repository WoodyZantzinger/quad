/*
 Woody Zantzinger
 Accelerometer.cpp
 Works with https://www.sparkfun.com/datasheets/Sensors/Accelerometer/ADXL345.pdf
 5/16/2014
 
1)the unit of sensitivity (lsb/g) what does it mean,what lsb stand for
Least Significant Bit - so this is the value read from the accelerometer for 1g at your chosen range (2g, 4g, 8g, 16g)
2)the scale factor ,how will i use it
Inverse of the sensitivity. So get the value from the accelerometer, muliply by the right scale factor and you have the number of g.
3)what is the value of g
Leon is right - 9.8m/s/s - in terms of the accelerometers measurements however this would be '1g'
 
 
 
 
 */

#include "Arduino.h"
#include "accelerometer.h"
#include <Wire.h>
#include <math.h>
#include "packet.h"

const int Accelerometer::scale2 = 3.74;
const int Accelerometer::scale4 = 7.8;
const int Accelerometer::scale8 = 15.6;
const int Accelerometer::scale16 = 31.2;

Accelerometer::Accelerometer(int addr) {
    this->i2c_addr = addr;
    
    Wire.beginTransmission(this->i2c_addr);
    Wire.write(0x00);
    Wire.endTransmission();
    
    //Debug code below:
    /*
    Wire.requestFrom(this.i2c_addr, 1);
    byte ch;

    while (!Wire.available()) {
        ch = Wire.read();
    }
    Serial.print("ACCEL INIT IS 0x");
    Serial.println(ch,HEX);
     */
    
    //Setup Power Control. 0x08 puts it into "Measure" mode.
    Wire.beginTransmission(this->i2c_addr);
    Wire.write(0x2d);
    Wire.write(0x08);
    Wire.endTransmission();
    
    //Setup FIFO control, not 100% sure why we want this setting, but it seems to work. May need to change if it is caching old data.
    Wire.beginTransmission(this->i2c_addr);
    Wire.write(0x38);
    Wire.write(0x84);
    Wire.endTransmission();
}

void Accelerometer::update() {
    Wire.beginTransmission(this->i2c_addr);
    
    Wire.write(0x32);
    Wire.endTransmission();

    
    Wire.requestFrom(this->i2c_addr, 6);
    int x = 0;
   
    while(Wire.available()) {
        this->buffer.buff[x] = Wire.read();
        x++;
    }
    
    this->pitch = atan(this->getRawX()/sqrt(pow(this->getRawY(),2) + pow(this->getRawZ(),2)));
    this->roll = atan(this->getRawY()/sqrt(pow(this->getRawX(),2) + pow(this->getRawZ(),2)));
    
    //convert radians into degrees
    this->pitch = pitch * (180.0/PI);
    this->roll = roll * (180.0/PI) ;
}

short Accelerometer::getRawX() {
    return this->buffer.value.x * this->scale2;
}

short Accelerometer::getRawY() {
    return this->buffer.value.y * this->scale2;
}

short Accelerometer::getRawZ() {
    return this->buffer.value.z * this->scale2;
}

float Accelerometer::getPitch() {
    return this->pitch;
}

float Accelerometer::getRoll() {
    return this->roll;
}

byte* Accelerometer::getBuffer() {
    return this->buffer.buff;
}

void Accelerometer::print() {

    union packet{
      struct{
        float roll,pitch;
      } value;
      unsigned char buff[8];
    };

    packet msg;

    msg.value.roll = this->getRoll();
    msg.value.pitch = this->getPitch();
    
    Serial.write((byte)msg.buff);
}
