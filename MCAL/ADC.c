/*
 * ADC.c
 *
 *  Created on: Nov 6, 2019
 *      Author: embeddedfab
 */

#include"ADC.h"




void ADC_init(void)
{

	ADMUX=0b11000000;     // vcc refrence - ADLAR=0/CH0
	ADCSRA=0b10000111;    //Enable ADC - Prescaler "/128"

}



unsigned int ADC_Get_reading_mv(char ch)
{

ADMUX =(ADMUX&0xF8)|ch;
	ADCSRA |=(1<<ADSC);  // start conversion
	while(!(ADCSRA&(1<<ADIF)));

	return ADC;


}

