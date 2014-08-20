/*
 Woody Zantzinger
 Accelerometer.h
 Works with https://www.sparkfun.com/datasheets/Sensors/Accelerometer/ADXL345.pdf
 5/16/2014
 */

#ifndef ACCEL_H
#define ACCEL_H

#include "Arduino.h"

class Accelerometer
{
public:
    Accelerometer(int addr);
    void update();
    short getRawX();
    short getRawY();
    short getRawZ();
    float getRoll();
    float getPitch();
    byte* getBuffer();
    void print();
    
private:
    union XYZBuffer{
        struct{
            short x,y,z;
        } value;
        byte buff[6];
    };
    
    XYZBuffer buffer;

    float roll;
    float pitch;
    int i2c_addr;
    static const int scale2;
    static const int scale4;
    static const int scale8;
    static const int scale16;
};

#endif
