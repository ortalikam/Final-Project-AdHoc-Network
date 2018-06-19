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

def apply():
    ArduinoSerial.write('start')
    time.sleep(2)
    print ArduinoSerial.read(2000)
    #text_filed=tk.Text(master=window,height=10,width=30)
    #text_filed.grid(column=0,row=3)
    #text_filed.insert(tk.END,str(ent.get()))

def Viewing_network():
    reqSons()
    #top = Toplevel()
    #top.title("Viewing network mode")
    #top.geometry("600x600")
    #top.mainloop()
    

def Send_message():
    reqSons()
    if len(sons)==0  or sons[0]=='no suns':
        print '\n no sons'
    else:
        print 'Please Enter Message to send:'
        inpt = raw_input()
        ArduinoSerial.write('sendMessage_'+inpt)

#--------END_FUNCTIONS----------

#--lable--
title=tk.Label(text="Configuration settings:",font=('verdana', 18, 'bold'))
title.grid(column=0,row=0)

#--param1--
param1=tk.Label(text="Time to stretch the timer to get ACK:",font=("verdana",14))
param1.grid(column=0,row=1)

param1_val = Spinbox(window, from_=0, to=10)
param1_val.pack(side=LEFT)
param1_val.grid(column=2,row=1)

#--param2--
param2=tk.Label(text="Number of attempts to send a message after it failed:",font=("verdana",14))
param2.grid(column=0,row=2)

param2_val = Spinbox(window, from_=0, to=10)
param2_val.pack(side=LEFT)
param2_val.grid(column=2,row=2)

#--param3--
param3=tk.Label(text="Time to rebuild the network:",font=("verdana",14))
param3.grid(column=0,row=3)

param3_val = Spinbox(window, from_=0, to=10)
param3_val.pack(side=LEFT)
param3_val.grid(column=2,row=3)

#--Apply--
button1=tk.Button(text="Apply",  fg="red", command=apply)
button1.grid(column=0,row=4)

#--Viewing network mode--
button1=tk.Button(text="Viewing network mode",  fg="red", command=Viewing_network)
button1.grid(column=0,row=5)

#--Send a message on the network--
button1=tk.Button(text="Send a message on the network",  fg="red", command=Send_message)
button1.grid(column=1,row=5)


window.mainloop()



