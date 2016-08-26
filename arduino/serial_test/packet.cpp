/*
 Woody Zantzinger
 Packet.h
 8/25/2016
 */

#include "packet.h"
#include <string.h>

unsigned int Packet::TYPE_ERROR = 1;
unsigned int Packet::TYPE_POS = 2;
unsigned int Packet::TYPE_MSG = 3;

char Packet::END_CHAR = 0xFE;
char Packet::START_CHAR = 0xFF;

Packet::Packet(unsigned int type, char const msg[]) {
    //Can be either Error or Message
    this->main_msg.msg_value.type = type;

    // Copy 8 Bytes from Char array into our fixed length message spot
    strncpy(this->main_msg.msg_value.error, msg, 8);

    //Always copy start and end characters
    this->main_msg.msg_value.first_byte = Packet::START_CHAR;
    this->main_msg.msg_value.last_byte = Packet::END_CHAR;
}

Packet::Packet(unsigned int type, float roll, float pitch) {
  //Quick validity check on message type
  if (type == Packet::TYPE_POS) {
    this->main_msg.pos_value.type = type;
    this->main_msg.pos_value.roll = roll;
    this->main_msg.pos_value.pitch = pitch;
    this->main_msg.pos_value.first_byte = Packet::START_CHAR;
    this->main_msg.pos_value.last_byte = Packet::END_CHAR;
  }
}

unsigned char* Packet::getBytes() {
    return this->main_msg.buff;
}

int Packet::getLen() {
    return sizeof(this->main_msg.buff);
}
