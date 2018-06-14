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


#include <RF24_config.h>
#include <printf.h>
#include <Nrf2401.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define SONSIZE 10
RF24 radio(7, 8); // CE, CSN
byte addressTx[6] = { 'A','B','C','D','E' };
byte addressRx[6] = { 'E','D','C','B','A' };


//An array of messages that pass through the network
char message[][50] = { "discoNeighbors", // message[0]
					   "Id_", // message[1]
						"reqSons" }; // message[2]

//Buffer for receiving data
char data[100] = "";

struct dataStruct {
	//String  id = "010";
	String  id = "001";
	/*this data is for the final project only!! 
	String  sons[SONSIZE]; // array of suns
	uint64_t pipes[SONSIZE][6]; // array of pipes for sons
	int sons_size = 0; //how much suns exists
	*/
}myData;



// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);
	radio.begin();
	radio.openReadingPipe(0, addressRx); //rec
	radio.setPALevel(RF24_PA_MIN);
	Serial.println("hi");

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
			
		}
		else if (newText.substring(0, 6) == message[1] + myData.id)
		{
			//Serial.print("get the pipe...");
			String msg = message[1] + myData.id + "_ackPipe";
			char send_msg[100];
			strncpy(send_msg, msg.c_str(), sizeof(send_msg)); 
			writeToWireless(addressTx, send_msg);
		}

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
	if (radio.write(str, strlen(str)))
		return true;
	return false;
	delay(1000);
}

bool readFromWireless()
{

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

