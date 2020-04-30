/*
 * temp_sensor_lm35.c
 *
 *  Created on: Apr 30, 2020
 *      Author: embeddedfab
 */


#include"temp_sensor_lm35.h"









void temp_sensor_init(void)
{

	ADC_init();

}


char Get_Temp_reading(char ch)
{
	char temp=0;
	unsigned int ADC_Value=0,Reading_MV=0;
	ADC_Value=ADC_Get_reading_mv(ch);

	Reading_MV=ADC_Value*4;
	temp=Reading_MV/10;



return temp;
}
