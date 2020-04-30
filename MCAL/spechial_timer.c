/*
 * spechial_timer.c
 *
 *  Created on: Apr 28, 2020
 *      Author: embeddedfab
 */

#include"spechial_timer.h"


timer_struct  timers_list[MAX_NUMBER_OF_TIMERS];


void spechial_timer_init(void)
{
uint16_t timer_counter;

	timer_init();
	timer_set_callBack_fun(spechial_timer_update);

for(timer_counter=0;timer_counter<MAX_NUMBER_OF_TIMERS;timer_counter++)
{
	timer_delete(timer_counter);
}

}


void timer_delete(uint16_t timer_number)
{
	timers_list[timer_number].time_out  =0;
	timers_list[timer_number].counter  =0;
	timers_list[timer_number].is_time_out  =FALSE;
	timers_list[timer_number].is_enabled  =FALSE;
}



void spechial_timer_update(void)
{
	uint16_t timer_counter;


	for(timer_counter=0;timer_counter<MAX_NUMBER_OF_TIMERS;timer_counter++)
	{
		if(	timers_list[timer_counter].is_enabled  ==TRUE)
		{
			timers_list[timer_counter].counter++;
			if(	timers_list[timer_counter].counter  ==timers_list[timer_counter].time_out)
			{
				timers_list[timer_counter].is_time_out=TRUE;
				timers_list[timer_counter].counter    =   0;
			}

		}
	}


}


void timer_create(uint8_t timer_number,uint32_t timer_time_out)
{
	if(	timers_list[timer_number].time_out==0)
	{

		timers_list[timer_number].time_out  =timer_time_out;
		timers_list[timer_number].counter  =0;
		timers_list[timer_number].is_time_out  =FALSE;
		timers_list[timer_number].is_enabled  =FALSE;

	}
}


void timer_start(uint8_t timer_number)
{
	if(	timers_list[timer_number].time_out!=0)
	{
		timers_list[timer_number].is_enabled  =TRUE;
	}

}

void timer_stop(uint8_t timer_number)
{
		timers_list[timer_number].is_enabled  =FALSE;
}

void timer_reset(uint8_t timer_number)
{
		timers_list[timer_number].counter  =0;
}

void timer_change_timeout(uint8_t timer_number,uint32_t timer_time_out)
{

		timers_list[timer_number].time_out  =timer_time_out;

}

uint8_t timer_is_time_out(uint8_t timer_number)
{
	return(	timers_list[timer_number].is_time_out);
}

uint8_t timer_check(uint8_t timer_number)
{
	uint8_t timer_time_OUT=FALSE;
	if(timers_list[timer_number].is_time_out)
	{
		timers_list[timer_number].is_time_out=FALSE;
		timer_time_OUT=TRUE;
	}
	return timer_time_OUT;
}


uint32_t timer_counter_current_value(uint8_t timer_number)
{
	return(	timers_list[timer_number].counter);
}


