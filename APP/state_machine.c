/*
 * state_machine.c
 *
 *  Created on: 5 Aug 2019
 *      Author: root
 */
#include"state_machine.h"


ret_state  lookup_table_array[3][3]=
{
		{init,operation,terminate},
		{init,operation,terminate},
		{init,operation,terminate}
};








ret_state lookup_table(state current_state,ret_state dir_state)
{
	ret_state next_state=0;


	next_state=lookup_table_array[current_state][dir_state];




	return next_state;
}
