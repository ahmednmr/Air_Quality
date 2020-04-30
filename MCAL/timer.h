/*
 * timer.h
 *
 *  Created on: Apr 28, 2020
 *      Author: embeddedfab
 */

#ifndef TIMER_H_
#define TIMER_H_

#include<AVR/io.h>
#include<AVR/interrupt.h>

void (*ISR_timer0_fun)(void);

void timer_set_callBack_fun(void (*User_fun)(void));

void timer_init (void);

#endif /* TIMER_H_ */
