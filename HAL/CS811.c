/*
 * CS811.c
 *
 *  Created on: Mar 16, 2020
 *      Author: embeddedfab
 */

#include"CS811.h"




void CS811_init(void)
{
	unsigned char Status=0;
	TWI_Init();

	if (read_HW_ID ())
	{

		Status=Read_Status_Register();

		EF_void_LCD_Clear_Screen();
		EF_void_LCD_print((unsigned char*)"Status");
		EF_void_LCD_print_Number(Status);
		_delay_ms(400);


		APP_start();

		Status=Read_Status_Register();

		EF_void_LCD_Clear_Screen();
		EF_void_LCD_print((unsigned char*)"Status");
		EF_void_LCD_print_Number(Status);
		_delay_ms(400);


		 Measurment_Mode_set();




	}



}

void APP_start(void)
{

	TWI_Start();
	TWI_SendData(Sensor_Write_ADD);
	TWI_SendData(APP_Start);
	TWI_Stop();

#if	Enable_CS811_debug

	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"app start ");   //send APP Start
	_delay_ms(1000);

#endif
}


BOOLEAN read_HW_ID (void)
{
	unsigned char HW_ID=0;
	// read HW ID  //it should be 129

	TWI_Start();
	TWI_SendData(Sensor_Write_ADD);
	TWI_SendData(0x20);
	TWI_Stop();
	TWI_Start();
	TWI_SendData(Sensor_Read_ADD);
	TWI_ReceiveData_NACK(&HW_ID);
	TWI_Stop();
	_delay_ms(100);


#if	Enable_CS811_debug

	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"H.W ID Reading ");
	EF_void_LCD_print_Number(HW_ID);
	_delay_ms(1000);

#endif

	if (HW_ID==129)
	{
		return TRUE;
	}


	return FALSE;
}
unsigned char Read_Status_Register(void)
{
	unsigned char Status=0;

	TWI_Start();
	TWI_SendData(Sensor_Write_ADD);
	TWI_SendData(Status_Register);
	TWI_Stop();
	TWI_Start();
	TWI_SendData(Sensor_Read_ADD);
	TWI_ReceiveData_NACK(&Status);
	TWI_Stop();

#if	Enable_CS811_debug

//	EF_void_LCD_Clear_Screen();
//	EF_void_LCD_print((unsigned char*)"Status");
//	EF_void_LCD_print_Number(Status);
//	_delay_ms(100);

#endif

	return Status;
}



void Measurment_Mode_set(void)
{
	TWI_Start();
	TWI_SendData(Sensor_Write_ADD);
	TWI_SendData(Measurment_Mode_Register);
	TWI_SendData(0b00100000);               //sample Every 10 seconds
	TWI_Stop();

}



void CS811_CO2_TVOC_Reading(CS811_sensor* my_CS811)
{
	unsigned char ERROR_ID,RAW_DATA1,RAW_DATA2,Status=0;

	unsigned int CO2=0,TVOC=0;

//			_delay_ms(100);
TWI_Start();
TWI_SendData(Sensor_Write_ADD);
TWI_SendData(AlG_Result_Register);
TWI_Stop();

TWI_Start();
TWI_SendData(Sensor_Read_ADD);
TWI_ReceiveData_ACK((unsigned char *)&CO2);
CO2<<=8;
TWI_ReceiveData_ACK((unsigned char *)&CO2);
TWI_ReceiveData_ACK((unsigned char *)&TVOC);
TVOC<<=8;
TWI_ReceiveData_ACK((unsigned char *)&TVOC);
TWI_ReceiveData_ACK(&Status);
TWI_ReceiveData_ACK(&ERROR_ID);
TWI_ReceiveData_ACK(&RAW_DATA1);
TWI_ReceiveData_NACK(&RAW_DATA2);

TWI_Stop();


my_CS811->CO2=CO2;
my_CS811->TVOC=TVOC;


#if	Enable_CS811_debug

//	EF_void_LCD_Clear_Screen();
//	EF_void_LCD_print((unsigned char*)"CS811_CO2_TVOC_Reading");
//	_delay_ms(400);

#endif

}

