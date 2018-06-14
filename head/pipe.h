#pragma once
#include <stdint.h>
class pipe
{
private:
	char* addressRx;
	char*  addressTx;
public:
	//c'tor
	pipe::pipe();
	pipe::pipe(char*  addT, char*  addR);

	void pipe::setaddressRx(char*  addR);
	void pipe::setaddressTx(char*  addT);

	char*  pipe::getaddressRx();
	char*  pipe::getaddressTx();

};
