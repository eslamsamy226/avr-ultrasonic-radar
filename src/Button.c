

#include "DIO.h"


void button_vInit(unsigned char portname,unsigned char pinnumber){
	
		DIO_vsetPINDir(portname,portname,0);
		DIO_vconnectpullup(portname,portname,1);
}


unsigned char button_u8read(unsigned char portname,unsigned char pinnumber){
	
	return DIO_u8read(portname,pinnumber);
}