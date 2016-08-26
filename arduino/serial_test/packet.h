/*
 Woody Zantzinger
 Packet.h
 8/25/2016
 */

#ifndef PACK_H
#define PACK_H

class Packet
{
public:
    Packet(unsigned int, char const *);
    Packet(unsigned int, float roll, float pitch);
    unsigned char* getBytes();
    int getLen();

    static unsigned int TYPE_ERROR;
    static unsigned int TYPE_POS;
    static unsigned int TYPE_MSG;
    static char END_CHAR;
    static char START_CHAR;

private:
    union packet{
        //Type 0, ERROR OR Type 2, MESSAGE
        struct{
            char first_byte; //1 byte
            unsigned int type; //2 Bytes
            char error[8]; // 8 Bytes
            char last_byte; //1 byte
        } msg_value;
        
        //Type 1, POSITION
        struct{
            char first_byte; //1 byte
            unsigned int type; //2 Bytes
            float roll, pitch; // 8 Bytes
            char last_byte; //1 byte
        } pos_value;
        
        unsigned char buff[12];
    };
    
    packet main_msg;

};

#endif
