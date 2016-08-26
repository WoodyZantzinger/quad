__author__ = 'woodyzantzinger'

import serial
import struct
import pdb
from print_msg import print_msg

class serial_bus:

    serialPort = None

    class msg_type:
        UNKNOWN = 0
        ERROR = 1
        POSITION = 2
        MESSAGE = 3

    __MSG_NUM = 0
    __END_CHAR = "\xFE"
    __START_CHAR = "\xFF"

    message_stack = []
    current_message = []

    def __init__(self, serial):
        self.data = []
        self.current_message = []
        self.serialPort = serial

    def read(self):
        oldNum = self.__MSG_NUM
        bytesToRead = self.serialPort.inWaiting()
        byteData = self.serialPort.read(bytesToRead)
        if len(byteData) > 0:
            #pdb.set_trace()
            for byte in byteData:
                #print "Found Byte!"
                if byte == self.__START_CHAR: #start Char
                    self.current_message = []
                    self.current_message.append(byte)
                    #print "Found a Start!"

                elif byte == self.__END_CHAR:
                    self.current_message.append(byte)
                    self.message_stack.append(self.current_message)
                    self.current_message = []
                    self.__MSG_NUM += 1
                    #print len(self.current_message)

                else: #just regular data
                    self.current_message.append(byte)
                    #print "Regular Byte"

        return self.message_stack[oldNum:self.__MSG_NUM]

    @staticmethod
    def get_type(str):
        if str[0] == serial_bus.__START_CHAR: #check if valid message
            s = struct.Struct('h')
            #pdb.set_trace()
            #print s.unpack(''.join(str[1:3]))[0]
            return s.unpack(''.join(str[1:3]))[0]

    @staticmethod
    def decode_msg(str):

        s = struct.Struct('=c h 8s c')
        try:
            start, type, msg, end = s.unpack(''.join(str))
        except struct.error:
            print print_msg.WARNING + " A Message failed to unpack"
            print "\t" + "".join(str)
            return "", False
        return msg, True

    @staticmethod
    def decode_pos(str):

        s = struct.Struct('=c h f f c')
        #pdb.set_trace()
        try:
            start, type, roll, pitch, end = s.unpack(''.join(str))
        except struct.error:
            print print_msg.WARNING + " A Position failed to unpack"
            print "\t" + "".join(str)
            return 0,0, False

        return roll, pitch, True

