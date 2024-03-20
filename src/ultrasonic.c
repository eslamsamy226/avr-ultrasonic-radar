/*
 * ultrasonic.c
 *
 * Created: 01/03/2024 10:27:36
 *  Author: Eslam
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "std_macros.h"
short input_capture(){
	DDRD&=0b10111111;
	TCCR1A=0;
	short a=0,b=0;
	SET_BIT(TIFR,ICF1);
	TCCR1B=0xc4;
	while(READ_BIT(TIFR,ICF1)==0);
	a=ICR1;	
	SET_BIT(TIFR,ICF1);
	TCCR1B=0x84;
	while(READ_BIT(TIFR,ICF1)==0);
	b=ICR1;
	SET_BIT(TIFR,ICF1);
	TCCR1B=0;
	ICR1=0;
	TCNT1=0;
	return b-a;
};


short ultrasonic_distance(){
	SET_BIT(DDRC,0);
	SET_BIT(PORTC,0);
	_delay_ms(20);
	CLR_BIT(PORTC,0);
	long time=input_capture();//*(1024.0/F_CPU);
	//time=time/2;
	long distance=(34600.0*(double)time)/((F_CPU/256.0)*2);
	
	return (short)distance;
	
};
