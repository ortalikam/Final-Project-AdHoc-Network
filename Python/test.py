import serial
import time
ArduinoSerial = serial.Serial('com11',9600)
ArduinoSerial.flushInput()
ArduinoSerial.timeout=2
time.sleep(2)

while 1:
    try:
        print 'enter commend \n 1 for build the network\n 2 for bring sons araay \n 3 for bring pipes araay '
        var = raw_input()
        if var=='1':
            ArduinoSerial.write('start')
            time.sleep(3)
            print ArduinoSerial.read(2000)
        elif var=='2':
            ArduinoSerial.write('reqSons')
            time.sleep(2)
            print ArduinoSerial.read(100)
        elif var=='3':
            ArduinoSerial.write('reqPipes')
            time.sleep(1)
            print ArduinoSerial.read(100)
       
    except:
            print("Keyboard Interrupt")
            raise

