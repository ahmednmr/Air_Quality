/*
 * spechial_timer.h
 *
 *  Created on: Apr 28, 2020
 *      Author: embeddedfab
 */

#ifndef MCAL_SPECHIAL_TIMER_H_
#define MCAL_SPECHIAL_TIMER_H_

#include"timer.h"
#define FALSE 0
#define TRUE  1

#define MAX_NUMBER_OF_TIMERS 10

#define server_update_timer_ID   1
#define server_update_timer_time_OUT   300000
#define update_screen_timer_ID   2
#define update_screen_timer_time_OUT   10000
#define wifi_module_timer_ID   3
#define wifi_module_timer_time_OUT   10000





void spechial_timer_init(void);
void spechial_timer_update(void);
void timer_delete(uint16_t timer_number);
void timer_create(uint8_t timer_number,uint32_t timer_time_out);
void timer_start(uint8_t timer_number);
void timer_stop(uint8_t timer_number);
void timer_reset(uint8_t timer_number);
void timer_change_timeout(uint8_t timer_number,uint32_t timer_time_out);
uint8_t timer_is_time_out(uint8_t timer_number);
uint32_t timer_counter_current_value(uint8_t timer_number);
uint8_t timer_check(uint8_t timer_number);

typedef struct mystruct
{
	volatile uint32_t   time_out;
	volatile uint32_t   counter;

	volatile uint8_t   is_time_out;
	volatile uint8_t   is_enabled;

}timer_struct;


#endif /* MCAL_SPECHIAL_TIMER_H_ */
