/*
 * CS811.h
 *
 *  Created on: Mar 16, 2020
 *      Author: embeddedfab
 */

#ifndef HAL_CS811_H_
#define HAL_CS811_H_

#include"../MCAL/i2c.h"
#include"../HAL/EF_LCD.h"
#include<util/delay.h>

#define Enable_CS811_debug      TRUE

#define Sensor_Write_ADD         0xB6
#define Sensor_Read_ADD          0xB7

#define Status_Register          0x00
#define Measurment_Mode_Register 0x01
#define AlG_Result_Register      0x02
#define APP_Start                0xF4


typedef struct my_struct
{
	unsigned int  CO2;
	unsigned int  TVOC;

}CS811_sensor;

void CS811_init(void);
unsigned char Read_Status_Register(void);
void APP_start(void);
BOOLEAN read_HW_ID (void);
void Measurment_Mode_set(void);
void CS811_CO2_TVOC_Reading(CS811_sensor* my_CS811);




#endif /* HAL_CS811_H_ */
