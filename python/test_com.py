from time import sleep
import serial
import sys
from serial_read import serial_bus
import pdb
import visual_sim
import pyglet
from print_msg import print_msg

bus = None
win = None

def update(dt):
    messages = bus.read()
    #print "Update!"
    for msg in messages:
        #print "Looking at Message!"
        if serial_bus.get_type(msg) == serial_bus.msg_type.MESSAGE:
            msg, success = serial_bus.decode_msg(msg)
            if success:
                print print_msg.MESSAGE + msg

        if serial_bus.get_type(msg) == serial_bus.msg_type.POSITION:
            roll, pitch, success = serial_bus.decode_pos(msg)
            if success:
                win.pitch = pitch
                win.roll = roll
            #print "Roll:" + str(roll)
            #print "Pitch:" + str(pitch)

if __name__ == "__main__":

    #Test command line Arguments (Need 1 for Serial File)
    if len(sys.argv) < 2:
        print 'Usage is test_com.py Serial_Port'
        sys.exit(1)

    #Open the Serial Port from command line argument
    print 'Opening Serial Port ' + sys.argv[1] + ':',
    try:
        ser = serial.Serial(sys.argv[1],
                            9600,
                            bytesize=serial.EIGHTBITS,
                            parity=serial.PARITY_NONE,
                            stopbits=serial.STOPBITS_ONE,
                            timeout=1)
    except serial.SerialException as e:
        print print_msg.FAIL
        print "\t" + e.strerror
        sys.exit(0)
    else:
         print print_msg.OK

    bus = serial_bus(ser)
    win = visual_sim.Window(600,600, "Quad")
    pyglet.clock.schedule_interval(update, 1.0/30)
    pyglet.app.run()
    ser.close()