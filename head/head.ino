// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       head.ino
    Created:	04/06/2018 20:55:47
    Author:     DELL\ortal
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//
#include "pipe.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define SONSIZE 10 
RF24 radio(7, 8); // pin CE,pin CSN
byte addressRx[6] = { 'A','B','C','D','E' };
byte addressTx[6] = { 'E','D','C','B','A' };

//An array of messages that pass through the network
char* message[50]= { "discoNeighbors", // message[0]
					 "Id_", //message[1]
					 "start", //message[2]
					 "reqSons" , //message[3]
					 "reqPipes"}; //message[4]			

//Buffer for receiving data
char data[100] = "";


struct dataStruct { 
	String id = "000"; 
	String sons[SONSIZE]; // array of suns
	pipe pipes[SONSIZE]; // array of pipes for sons
	int sons_size=0; //how much sons exists
}myData;



// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);
	radio.begin();
	radio.openReadingPipe(0, addressRx); //rec
	radio.setPALevel(RF24_PA_MIN);

}

// Add the main program code into the continuous loop() function
void loop()
{
	while (Serial.available()) {
		Serial.readBytes(data, sizeof(data));

		String newText(data);
		String msg;

		if (newText.substring(0, strlen(message[2])) == message[2])//start
		{
			while (!find_Neighbors());
			//find_Neighbors();
		}
		else if (newText.substring(0, strlen(message[3])) == message[3]) { //reqsun
			resSuns();
		}
		else if (newText.substring(0, strlen(message[4])) == message[4]) { //reqpipes
			resPipes();
		}
		else
			writeToSerial("unrecognized message");
	}

}//loop

// write string to serial port
void writeToSerial(String str)
{
	Serial.println(str);
}

// write string to wireless pipe
//addTx- the address of the pipe 
bool writeToWireless(byte* addTx,char* str)
{
	radio.stopListening();
	radio.openWritingPipe(addTx);
	if (radio.write(str, strlen(str)))
		return true;
	return false;
	delay(1000);
}

bool readFromWireless()
{

}

bool handShake(String idNumber)
{
	//Serial.print("handShake..");
	//delay(1000);
	String pipeNumber = idNumber + idNumber.substring(0, 2);
	String msg= message[1]+idNumber+"_"+ pipeNumber;
	char send_msg[100];
	strncpy(send_msg, msg.c_str(), sizeof(send_msg));
	writeToWireless(addressTx, send_msg);

	radio.startListening();
	delay(500);
	while (radio.available()) {
		char text[50] = "";
		radio.read(&text, sizeof(text));
		String msg(text);
		//String msg = newText.substring(0, strlen(message[1]))+idNumber;
		if (msg == (message[1] + idNumber + "_ackPipe"))
		{
			return addSon(idNumber, pipeNumber);
		}
			


	}
}

//sending "discover Neighbors" message and wait for replay and update suns accordance
bool find_Neighbors() {
	String ids[SONSIZE];
	int idsNum = 0;

	//writeToSerial("find_Neighbors");

	if (!writeToWireless(addressTx, message[0])) { //sending "discover Neighbors" message
		//writeToSerial("error in sending find_Neighbors");
		return false;
	}
	 
	radio.startListening();
	delay(100);
	while (radio.available(addressRx)) {
		char text[50] = "";
		radio.read(&text, sizeof(text));
		String newText(text);
		//writeToSerial(newText);
		String msg = newText.substring(0, strlen(message[1]));
		if (msg == message[1]) //id_
		{
			String idNumber = newText.substring(strlen(message[1]), strlen(text));
			ids[idsNum++] = idNumber;
			//writeToSerial(idNumber);
			//if (!handShake(idNumber)) writeToSerial("error in handShake");
		}
		//delay(2000);
	}
	for (int i=0;i<idsNum;i++)
		if (!handShake(ids[i])) {
			writeToSerial("error in handShake");
			return false;
		}
	return true;

}



// add son with idNumber to the array of sons id exist place in the array
bool addSon(String idNumber,String p)
{
	//Serial.print("addson...");
	if(myData.sons_size <SONSIZE) {
		for (int i = 0; i < SONSIZE; i++)
		{
			if (myData.sons[i] == idNumber) //son already exists
				return true;
		}
		myData.sons[myData.sons_size] = idNumber;
		char pipeNum[100];
		strncpy(pipeNum, p.c_str(), sizeof(pipeNum));
		//Serial.print("pipeNum:");
		//Serial.println(p); 
		myData.pipes[myData.sons_size].setaddressRx(pipeNum);
		myData.sons_size++;
		return true;
		
	}
	return false;
}

//write to the serial port the susns array 
void resSuns()
{
	if (myData.sons_size == 0)
	{
		writeToSerial(message[1] + myData.id + "no suns");
	}
	else
	{
		String s = message[1] + myData.id;
		for (int i = 0; i< myData.sons_size; i++) {
			s += "_"+myData.sons[i];
		}
		char send_msg[100];
		strncpy(send_msg, s.c_str(), sizeof(send_msg));
		writeToSerial(send_msg);
	}
}

//write to the serial port the pipes array 
void resPipes()
{
	if (myData.sons_size == 0)
	{
		writeToSerial(message[1] + myData.id + "no suns");
	}
	else
	{
		String s = message[1] + myData.id;
		for (int i = 0; i< myData.sons_size; i++) {
			s += "_" + String(myData.pipes[i].getaddressRx());
		}
		char send_msg[100];
		strncpy(send_msg, s.c_str(), sizeof(send_msg));
		writeToSerial(send_msg);
	}
}
