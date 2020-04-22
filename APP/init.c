/*
 * init.c
 *
 *  Created on: 5 Aug 2019
 *      Author: root
 */
#include"../main.h"


ret_state init_fun(void)
{

	unsigned char data1=0,data2=0,data3=0,data4=0,ERROR_ID,RAW_DATA1,RAW_DATA2,First_Reading=TRUE,Status=0;

	unsigned int CO2=0,TVOC=0;
	unsigned long int i=0,CO2_AVG;

	sei();

	DDRD |=(1<<PD5);

	EF_void_LCD_init();
	ESP_init();

	TWI_Init();

	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Init state");
	_delay_ms(2000);




	ESP_Echo_Enable(FALSE);

	ESP_Work_Mode(BOTH);


	ESP_Multiple_Connections_Enable(FALSE);

	ESP_transmission_Mode(NORMAL);


	//	if(ESP_check_connection()==FALSE)
	//	{
	//    ESP_connect_to_WIFI(WIFI_USER_NAME,WIFI_PASSWORD);
	//	}
	//
	//    ESP_OPEN_SOCKET(ThingSpeak_SERVER,ThingSpeak_PORT);
	//
	//    ESP_uploade_data(CO2);

	//    ESP_CLOSE_SOCKET();




	// read HW ID

	TWI_Start();
	TWI_SendData(0b10110110);
	TWI_SendData(0x20);
	TWI_Stop();

	TWI_Start();
	TWI_SendData(0b10110111);
	TWI_ReceiveData_NACK(&Status);
	TWI_Stop();

	_delay_ms(100);

	// read HW ID

	_delay_ms(1000);
	TWI_Start();
	TWI_SendData(0b10110110);
	TWI_SendData(0x00);
	TWI_Stop();

	TWI_Start();
	TWI_SendData(0b10110111);
	TWI_ReceiveData_NACK(&Status);
	TWI_Stop();

	_delay_ms(1000);




	TWI_Start();
	TWI_SendData(0b10110110);
	TWI_SendData(0xF4);
	TWI_Stop();



	_delay_ms(1000);

	TWI_Start();
	TWI_SendData(0b10110110);
	TWI_SendData(0x00);
	TWI_Stop();

	TWI_Start();
	TWI_SendData(0b10110111);
	TWI_ReceiveData_NACK(&Status);
	TWI_Stop();


	_delay_ms(1000);

	TWI_Start();
	TWI_SendData(0b10110110);
	TWI_SendData(0x01);
	TWI_SendData(0b00100000);
	TWI_Stop();


	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Start");
	while(1)
	{



		TWI_Start();
		TWI_SendData(0b10110110);
		TWI_SendData(0x00);
		TWI_Stop();

		TWI_Start();
		TWI_SendData(0b10110111);
		TWI_ReceiveData_NACK(&Status);
		TWI_Stop();



		if(Status==152)
		{
			CO2=0;
			data1=0;data2=0;data3=0;data4=0;

			//			_delay_ms(100);
			TWI_Start();
			TWI_SendData(0b10110110);
			TWI_SendData(0x02);
			TWI_Stop();

			TWI_Start();
			TWI_SendData(0b10110111);
			TWI_ReceiveData_ACK(&data1);
			TWI_ReceiveData_ACK(&data2);
			TWI_ReceiveData_ACK(&data3);
			TWI_ReceiveData_ACK(&data4);
			TWI_ReceiveData_ACK(&Status);
			TWI_ReceiveData_ACK(&ERROR_ID);
			TWI_ReceiveData_ACK(&RAW_DATA1);
			TWI_ReceiveData_NACK(&RAW_DATA2);

			TWI_Stop();

			CO2=data1*256;
			CO2+=data2;


			TVOC=data3*256;
			TVOC+=data4;

			EF_void_LCD_Clear_Screen();
			EF_void_LCD_print((unsigned char*)"CO2 = ");
			EF_void_LCD_print_Number(CO2);

			EF_void_LCD_Newline();
			EF_void_LCD_print((unsigned char*)"TVOC = ");
			EF_void_LCD_print_Number(TVOC);
			EF_void_LCD_print((unsigned char*)"   i:");
			EF_void_LCD_print_Number(i);

			CO2_AVG+=CO2;
			i++;

			if((i%90==0)&&(First_Reading==FALSE))
			{


				CO2=CO2_AVG/90;


				if(ESP_check_connection()==FALSE)
				{
					ESP_connect_to_WIFI(WIFI_USER_NAME,WIFI_PASSWORD);
				}

				ESP_OPEN_SOCKET(ThingSpeak_SERVER,ThingSpeak_PORT);

				ESP_uploade_data(CO2);



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
