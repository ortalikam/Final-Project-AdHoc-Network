#include "pipe.h"

//c'tor
pipe::pipe() {
	this->addressRx = new char[6];
	this->addressTx = new char[6];
}

pipe::pipe(char * addT, char* addR) {
	this->addressRx = addR;
	this->addressTx = addT;
}

void pipe::setaddressRx(char* addR) {this->addressRx = addR;} //לבדוק תקינות
void pipe::setaddressTx(char* addT) {this->addressTx = addT; }

char* pipe::getaddressRx() { return this->addressRx; }

char* pipe::getaddressTx() { return this->addressTx; }