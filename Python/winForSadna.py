import serial
import time

import tkinter as tk
from Tkinter import *

menu=['Please Enter your choice:','1. Build the Network','2 .Bring Sons Araay', '3. Bring Pipes Araay','4. Send Message to Sons']
sons=[]

ArduinoSerial = serial.Serial('com11',9600)
ArduinoSerial.flushInput()
ArduinoSerial.timeout=2
time.sleep(3)

window = tk.Tk()
window.title("AdHoc Project")
window.geometry("600x600")
#window.configure(background='gray')

#--------FUNCTIONS----------
def reqSons():
    global sons
    ArduinoSerial.write('reqSons')
    time.sleep(2)
    data= ArduinoSerial.read(100)
    sons=data.split("_")
    for s in sons:
        print s

def Build_Netwotk():
    ArduinoSerial.write('start')
    time.sleep(2)
    print ArduinoSerial.read(2000)


def Viewing_network():
    reqSons()
    top = Toplevel()
    top.title("Viewing network mode")
    top.geometry("600x600")
    top.mainloop()
    


#--------END_FUNCTIONS----------



#--Build Netwotk--
button1=tk.Button(text="Build Netwotk",  fg="red", command=Build_Netwotk)
button1.grid(column=0,row=4)

#--Viewing network mode--
button1=tk.Button(text="Viewing network mode",  fg="red", command=Viewing_network)
button1.grid(column=0,row=5)




window.mainloop()



