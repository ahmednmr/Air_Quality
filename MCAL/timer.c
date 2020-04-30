/*
 * timer.c
 *
 *  Created on: Apr 28, 2020
 *      Author: embeddedfab
 */

#include"timer.h"



void timer_init (void)
{

	TCCR0=0b00001011;
	TCNT0=0;
	OCR0=125;
	TIMSK |=0x02;
	TIFR  |=0x02;

	sei();
}


void timer_set_callBack_fun(void (*User_fun)(void))
{
	ISR_timer0_fun=User_fun;
}



ISR(TIMER0_COMP_vect)
{
	ISR_timer0_fun();
}

