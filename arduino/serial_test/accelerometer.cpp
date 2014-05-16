/*
 Woody Zantzinger
 Accelerometer.cpp
 Works with https://www.sparkfun.com/datasheets/Sensors/Accelerometer/ADXL345.pdf
 5/16/2014
 */

#include "Arduino.h"
#include "accelerometer.h"
#include <Wire.h>

const int Accelerometer::scale = 3.9;

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
}

short Accelerometer::getX() {
    return this->buffer.value.x / this->scale;
}

short Accelerometer::getY() {
    return this->buffer.value.y / this->scale;
}

short Accelerometer::getZ() {
    return this->buffer.value.z / this->scale;
}

byte* Accelerometer::getBuffer() {
    return this->buffer.buff;
}

void Accelerometer::print() {
    Serial.print("ACCEL : ");
    Serial.print(this->getX());
    Serial.print(":");
    Serial.print(this->getY());
    Serial.print(":");
    Serial.print(this->getZ());
    Serial.print('\n');
}
