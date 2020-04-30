/*
 * temp_sensor_lm35.h
 *
 *  Created on: Apr 30, 2020
 *      Author: embeddedfab
 */

#ifndef HAL_TEMP_SENSOR_LM35_H_
#define HAL_TEMP_SENSOR_LM35_H_

#include"../MCAL/ADC.h"


void temp_sensor_init(void);
char Get_Temp_reading(char ch);

#endif /* HAL_TEMP_SENSOR_LM35_H_ */
