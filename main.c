/*
 * main.c
 *
 *  Created on: Jan 28, 2018
 *      Author: Hani
 */
#include"main.h"

#include "avr/io.h"


ret_state return_state;

ret_state (* states[3])(void)={init_fun,operation_fun,terminate_fun};


int main(void)
{
	state	current_state=init;
	ret_state (*state_fun)(void);

	while(1)                     /* Super LOOP */
	{
		state_fun=states[current_state];
		return_state=state_fun();

		current_state=lookup_table(current_state,return_state);








	}
	return 0 ;
}

