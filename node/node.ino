// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       node.ino
    Created:	04/06/2018 20:35:17
    Author:     DELL\ortal
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//
#include "pipe.h"
#include <stdlib.h> 
#include <RF24_config.h>
#include <printf.h>
#include <Nrf2401.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define SONSIZE 10
#define FATHERSIZE 10
#define MAXMSG 5
RF24 radio(7, 8); // CE, CSN
byte addressTx[6] = { 'A','B','C','D','E' };
byte addressRx[6] = { 'E','D','C','B','A' };


//An array of messages that pass through the network
char message[][50] = { "discoNeighbors", // message[0]
					   "Id_", // message[1]
					   "reqSons", // message[2]
					   "msg_"}; // message[3]

//Buffer for receiving data
char data[100] = "";

struct dataStruct {
	//String  id = "010";
	String  id = "001";

	String fathers[FATHERSIZE]; // array of suns
	pipe* fathersPipes[FATHERSIZE]; // array of pipes for sons
	int fathers_size = 0; //how much sons exists

	String msg[MAXMSG];
	int msgs_size = 0; //how much msgs exists
	/*this data is for the final project only!! 
	String sons[SONSIZE]; // array of suns
	pipe* pipes[SONSIZE]; // array of pipes for sons
	int sons_size = 0; //how much sons exists
	*/
}myData;



// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);
	radio.begin();
	radio.openReadingPipe(0, addressRx); //rec
	radio.setPALevel(RF24_PA_MIN);
	//Serial.println("hi");

}

// Add the main program code into the continuous loop() function
void loop()
{
	
	radio.startListening();
	while (radio.available()) {
		char text[50] = "";
		radio.read(&text, sizeof(text));
		String newText(text);
		if (newText == message[0]) //get discoNeighbors message
		{
			//Serial.println("get...");
			String msg = message[1] + myData.id;
			char send_msg[100];
			strncpy(send_msg, msg.c_str(), sizeof(send_msg));
			writeToWireless(addressTx, send_msg); //send "id_"+idNumber
			Serial.println("sent id...");
			
		}
		else if (newText.substring(0, 6) == message[1] + myData.id) //get id+myId
		{
			
			String msg = message[1] + myData.id + "_ackPipe";
			writeToWireless(addressTx, msg);
			writeToSerial("ack");
			//addFather(newText.substring(7, 10), newText.substring(11, 16));

		}
		else if (newText.substring(0, 4) == message[3]) //get msg
		{

		}
		else Serial.println("ather:"+newText);


	}
} //loop


// write string to serial port
void writeToSerial(String str)
{
	Serial.println(str);
}

// write string to wireless pipe
//addTx- the address of the pipe 
bool writeToWireless(byte* addTx, char* str)
{
	radio.stopListening();
	radio.openWritingPipe(addTx);
	delay(rand() % 100+10);
	if (radio.write(str, strlen(str)))
		return true;
	return false;
	//delay(1000);
	//delay(rand() % 1000 + 100);
}

bool writeToWireless(byte* addTx, String str)
{
	char send_msg[100];
	strncpy(send_msg, str.c_str(), sizeof(send_msg));
	return writeToWireless(addTx, send_msg);
}

bool readFromWireless()
{

}

// add father with idNumber to the array of sons id exist place in the array
bool addFather(String idNumber, String p)
{
	//writeToSerial("pipe" + p);
	if (myData.fathers_size <FATHERSIZE) {
		for (int i = 0; i < FATHERSIZE; i++)
		{
			if (myData.fathers[i] == idNumber) //son already exists
				return true;
		}
		myData.fathers[myData.fathers_size] = idNumber;
		char pipeNum[6];
		strncpy(pipeNum, p.c_str(), sizeof(pipeNum));
		//Serial.println(pipeNum);
		myData.fathersPipes[myData.fathers_size] = new pipe();
		myData.fathersPipes[myData.fathers_size]->setaddressRx(pipeNum);
		myData.fathersPipes[myData.fathers_size]->setaddressTx(pipeNum);

		myData.fathers_size++;

		openPipe(pipeNum);

		return true;
	}
	return false;
}

void openPipe(char *p)
{
	byte pNum[6];
	for (int i = 0; i < 5; i++)
		pNum[i] = p[i];
	radio.openReadingPipe(0, pNum); //rec
}

/* this functions is for the final project only!!
//sending "discover Neighbors" message and wait for replay and update suns accordance
void find_Neighbors() {

	writeToSerial("find_Neighbors");

	if (!writeToWireless(addressTx, message[0])) //sending "discover Neighbors" message
		writeToSerial("error in sending find_Neighbors");

	radio.startListening();
	delay(1000);
	while (radio.available()) {
		char text[50] = "";
		radio.read(&text, sizeof(text));
		String newText(text);
		String msg = newText.substring(0, strlen(message[1]));
		if (msg == message[1])
		{
			String idNumber = newText.substring(strlen(message[1]), strlen(text));
			if (!addSon(idNumber)) writeToSerial("error in addSon");
		}
		delay(1000);
	}

}


bool addSon(String idNumber)
{
	if (myData.sons_size<SONSIZE) {
		myData.sons[myData.sons_size++] = idNumber;
		return true;
	}
	else return false;

}

void resSuns() //return the susns array 
{
	if (myData.sons_size == 0)
	{
		Serial.println(message[1] + myData.id + "no suns");
	}
	else
	{
		String s = message[1] + myData.id;
		for (int i = 0; i< myData.sons_size; i++) {
			s += myData.sons[i];
		}
		Serial.println(s);
	}
}
*/

