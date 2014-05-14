from time import sleep
import serial
import sys
import time

class print_msg:
    OK = '\033[92m [SUCCESS] \033[0m'
    WARNING = '\033[93m [WARN] \033[0m'
    FAIL = '\033[91m [FAIL] \033[0m'

def main():

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
    except OSError as e:
        print print_msg.FAIL
        print e.errno
        print e.filename
        print e.strerror
        sys.exit(0)
    else:
         print print_msg.OK

#Loop in reading then sending messages

    while True:
        cmd = input('Enter Command: ')
        try:
            print "Sending Message:",
            ser.write(cmd) #
        except serial.SerialTimeoutException as e:
            print print_msg.FAIL
            print e.errno
            print e.filename
            print e.strerror
            sys.exit(0)
        else:
            print print_msg.OK

        byteData = ser.read(8)
        print byteData

    ser.close()

if __name__ == "__main__":
    main()