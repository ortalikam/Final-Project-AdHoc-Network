import serial
import time
<<<<<<< HEAD

=======
import igraph as ig
>>>>>>> 9342dc5c904d292e1c3cf219ab511b99cf11b8a2

ArduinoSerial = serial.Serial('com11',9600)
ArduinoSerial.flushInput()
ArduinoSerial.timeout=2
time.sleep(2)

menu=['Please Enter your choice:','1. Build the Network','2 .Bring Sons Araay', '3. Bring Pipes Araay','4. Send Message to Sons']
sons=[]


def reqSons():
    global sons
    ArduinoSerial.write('reqSons')
    time.sleep(2)
    data= ArduinoSerial.read(100)
    sons=data.split("_")
    for s in sons:
        print s

while 1:
    try:
        for m in menu:
           print m
        var = raw_input()
        if var=='1':
            ArduinoSerial.write('start')
            time.sleep(2)
            print ArduinoSerial.read(2000)
        elif var=='2':
            reqSons()
        elif var=='3':
            ArduinoSerial.write('reqPipes')
            time.sleep(1)
            print ArduinoSerial.read(100)
        elif var=='4':
            reqSons()
            if len(sons)==0  or sons[0]=='no suns':
                print '\n no sons'
            else:
                print 'Please Enter Message to send:'
                inpt = raw_input()
                ArduinoSerial.write('sendMessage_'+inpt)
                                
            
        else: print 'Non Valid Choice'
       
    except:
            print("Keyboard Interrupt")
            raise

