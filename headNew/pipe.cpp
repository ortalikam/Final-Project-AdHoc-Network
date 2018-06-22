#include "pipe.h"

//c'tor
pipe::pipe() {
	this->addressRx = new char[6];
	this->addressTx = new char[6];
}

pipe::pipe(char * addT, char* addR) {
	//this->addressRx = new char[5];
	//this->addressTx = new char[5];

	for (int i = 0; i < 5; i++) {
		this->addressRx[i] = addR[i];
		this->addressTx[i] = addT[i];
	}
	this->addressTx[5] = '\0';
	//this->addressRx = addR;
	//this->addressTx = addT;
}

void pipe::setaddressRx(char* addR) { //לבדוק תקינות
	//this->addressRx = new char[5];
	for (int i = 0; i < 5; i++) {
		this->addressRx[i] = addR[i];
	}
	this->addressTx[5] = '\0';

} 
void pipe::setaddressTx(char* addT) {
	//this->addressTx = new char[5];
	for (int i = 0; i < 5; i++) {
		this->addressTx[i] = addT[i];
	}
	this->addressTx[5] = '\0';
}

char* pipe::getaddressRx() { return this->addressRx; }

char* pipe::getaddressTx() { return this->addressTx; }