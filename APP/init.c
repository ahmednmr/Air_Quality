/*
 * init.c
 *
 *  Created on: 5 Aug 2019
 *      Author: root
 */
#include"../main.h"


ret_state init_fun(void)
{

	char data1=0,data2=0,data3=0,data4=0,Status=0,First_Reading=TRUE;
	unsigned int CO2=0,TVOC=0;
	unsigned long int i=0,CO2_AVG;
	DDRD |=(1<<PD5);
	UART_INIT();
	EF_void_LCD_init();


	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Init state");
	_delay_ms(2000);

	EF_void_I2C_Init();



	EF_void_UART_SendString((U8_t *)"ATE1\r\n");
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Enable EChO");
	_delay_ms(3000);

	EF_void_UART_SendString((U8_t *)"AT+CWMODE=3\r\n");
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"ESP as Client");
	_delay_ms(3000);

	EF_void_UART_SendString((U8_t *)"AT+CIPMUX=0\r\n");
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Single Channel");
	_delay_ms(3000);

	EF_void_UART_SendString((U8_t *)"AT+CIPMODE=0\r\n");
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Normal Mode");
	_delay_ms(3000);

	EF_void_UART_SendString((U8_t *)"AT+CWJAP_DEF=\"ahmed\",\"135792468\"\r\n");
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Connect to Wifi");
	_delay_ms(3000);
	_delay_ms(3000);
	_delay_ms(3000);
	_delay_ms(3000);




	_delay_ms(1000);
	EF_void_I2C_Start();
	EF_void_I2C_Write(Sensor_Write_ADD);
	EF_void_I2C_Write(Status_Register);
	EF_void_I2C_Stop();

	EF_void_I2C_Start();
	EF_void_I2C_Write(Sensor_Read_ADD);
	Status=EF_U8_I2C_Read_Byte(0);
	EF_void_I2C_Stop();

	_delay_ms(100);

	EF_void_I2C_Start();
	EF_void_I2C_Write(Sensor_Write_ADD);
	EF_void_I2C_Write(APP_Start);
	EF_void_I2C_Stop();

	_delay_ms(100);
	EF_void_I2C_Start();
	EF_void_I2C_Write(Sensor_Write_ADD);
	EF_void_I2C_Write(Measurment_Mode_Register);
	EF_void_I2C_Write(0b00100000);
	EF_void_I2C_Stop();


	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Start");
	while(1)
	{



		EF_void_I2C_Start();
		EF_void_I2C_Write(Sensor_Write_ADD);
		EF_void_I2C_Write(Status_Register);
		EF_void_I2C_Stop();

		EF_void_I2C_Start();
		EF_void_I2C_Write(Sensor_Read_ADD);
		Status=EF_U8_I2C_Read_Byte(0);
		EF_void_I2C_Stop();

		if(Status==152)
		{

			EF_void_LCD_Clear_Screen();
			EF_void_I2C_Start();
			EF_void_I2C_Write(Sensor_Write_ADD);
			EF_void_I2C_Write(AlG_Result_Register);
			EF_void_I2C_Stop();

			EF_void_I2C_Start();
			EF_void_I2C_Write(Sensor_Read_ADD);
			data1=EF_U8_I2C_Read_Byte(1);
			data2=EF_U8_I2C_Read_Byte(1);
			data3=EF_U8_I2C_Read_Byte(1);
			data4=EF_U8_I2C_Read_Byte(1);
			Status=EF_U8_I2C_Read_Byte(0);

			EF_void_I2C_Stop();




			CO2=data1*256;
			CO2+=data2;


			TVOC=data3*256;
			TVOC+=data4;


			EF_void_LCD_print((unsigned char*)"CO2 = ");
			EF_void_LCD_print_Number(CO2);

			EF_void_LCD_Newline();
			EF_void_LCD_print((unsigned char*)"TVOC = ");
			EF_void_LCD_print_Number(TVOC);
			EF_void_LCD_print((unsigned char*)"   i:");
			EF_void_LCD_print_Number(i);

			CO2_AVG+=CO2;
			i++;

			if((i%360==0)&&(First_Reading==FALSE))
			{
				EF_void_UART_SendString((U8_t *)"AT+CWJAP_DEF=\"ahmed\",\"135792468\"\r\n");
				EF_void_LCD_Clear_Screen();
				EF_void_LCD_print((unsigned char*)"Connect to Wifi");
				_delay_ms(3000);
				_delay_ms(3000);
				_delay_ms(3000);
				_delay_ms(3000);



				EF_void_UART_SendString((U8_t *)"AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
				EF_void_LCD_Clear_Screen();
				EF_void_LCD_print((unsigned char*)"Connect to");
				EF_void_LCD_Newline();
				EF_void_LCD_print((unsigned char*)"ThingSpeak");
				_delay_ms(4000);


				EF_void_UART_SendString((U8_t *)"AT+CIPSEND=50\r\n");
				EF_void_LCD_Clear_Screen();
				EF_void_LCD_print((unsigned char*)"Uploading Data");

				_delay_ms(3000);

				CO2=CO2_AVG/360;

				EF_void_UART_SendString((U8_t *)"GET /update?api_key=SD5OBD49N5H4O8RY&field2=");
				EF_void_UART_Send_CO2(CO2);
				EF_void_UART_SendString((U8_t *)"\r\n");

				EF_void_LCD_Clear_Screen();
				EF_void_LCD_print((unsigned char*)"Done UPloading");
				_delay_ms(3000);

				i=0;
				CO2_AVG=0;
			}

			if(First_Reading==TRUE)
			{
				EF_void_LCD_Clear_Screen();
				EF_void_LCD_print((unsigned char*)"Not Ready Yet");
				EF_void_LCD_Newline();
				EF_void_LCD_print((unsigned char*)"Please Wait  ");
				EF_void_LCD_print_Number(4-i);
				if(i>=4)
				{
					i=0;
					CO2_AVG=0;
					First_Reading=FALSE;
					EF_void_LCD_Clear_Screen();
					EF_void_LCD_print((unsigned char*)"Ready");
				}

			}



		}



		_delay_ms(2000);





	}









	return ret_operation;
}
