/*
 * main.h
 *
 *  Created on: Mar 4, 2020
 *      Author: embeddedfab
 */

#ifndef MAIN_H_
#define MAIN_H_

#include"APP/state_machine.h"

#include<avr/io.h>
#include<util/delay.h>


#include"MCAL/spechial_timer.h"
#include"HAL/EF_LCD.h"
#include"HAL/CS811.h"
#include"HAL/ESP_8266.h"
#include"HAL/temp_sensor_lm35.h"


typedef enum
{
	TEMP_uploade,
	CO2_uploade,
	TVOC_uploade,
}current_uploade;


#endif /* MAIN_H_ */
