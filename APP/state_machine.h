/*
 * state_machine.h
 *
 *  Created on: 5 Aug 2019
 *      Author: root
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_



typedef enum
{
	init,
	operation,
	terminate,
	default_state

}state;

typedef enum
{
ret_init,
ret_operation,
ret_terminate,
default_ret

}ret_state;



ret_state init_fun(void);
ret_state operation_fun(void);
ret_state terminate_fun(void);
ret_state lookup_table(state current_state,ret_state dir_state);

#endif /* STATE_MACHINE_H_ */
