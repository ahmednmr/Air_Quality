/*
 * operation.c
 *
 *  Created on: 5 Aug 2019
 *      Author: root
 */

#include"../main.h"

CS811_sensor my_CS811;

unsigned char First_Reading=TRUE,Status=0,temp_value;

unsigned long int CO2_reading_numbers,CO2_AVG,TVOC_reading_numbers,TVOC_AVG;
current_uploade CurrentUploade =TEMP_uploade;


ret_state operation_fun(void)
{


	Status=Read_Status_Register();


	if(Status==152)
	{
		CS811_CO2_TVOC_Reading(&my_CS811);

		if(my_CS811.CO2!=0)
		{
			CO2_AVG+=my_CS811.CO2;
			CO2_reading_numbers++;
		}
		if(my_CS811.TVOC!=0)
		{
			TVOC_AVG+=my_CS811.TVOC;
			TVOC_reading_numbers++;
		}

	}



	if(timer_check(update_screen_timer_ID))
	{

		temp_value=Get_Temp_reading(1);

		EF_void_LCD_Clear_Screen();
		EF_void_LCD_print((unsigned char*)"CO2");
		EF_void_LCD_goto(1,7);
		EF_void_LCD_print((unsigned char*)"TVOC");
		EF_void_LCD_goto(1,13);
		EF_void_LCD_print((unsigned char*)"Temp");
		EF_void_LCD_Newline();
		EF_void_LCD_print_Number(my_CS811.CO2);
		EF_void_LCD_goto(2,7);
		EF_void_LCD_print_Number(my_CS811.TVOC);
		EF_void_LCD_goto(2,13);
		EF_void_LCD_print_Number(temp_value);



		timer_reset(update_screen_timer_ID);
	}








	if(timer_check(server_update_timer_ID))
	{


		PORTD |=(1<<PD5);               //buzzer on
		_delay_ms(500);
		PORTD &=~(1<<PD5);              //buzzer off

		my_CS811.CO2=CO2_AVG/CO2_reading_numbers;
		my_CS811.TVOC=TVOC_AVG/TVOC_reading_numbers;
		CO2_reading_numbers=0;
		CO2_AVG=0;
		TVOC_reading_numbers=0;
		TVOC_AVG=0;


		if(CurrentUploade==TEMP_uploade)
		{
			ESP_uploade_data(1,temp_value);
			CurrentUploade =CO2_uploade;
		}
		else if(CurrentUploade==CO2_uploade)
		{
			ESP_uploade_data(2,my_CS811.CO2);
			CurrentUploade =TVOC_uploade;
		}
		else if(CurrentUploade==TVOC_uploade)
		{
			ESP_uploade_data(3,my_CS811.TVOC);
			CurrentUploade =TEMP_uploade;
		}

		timer_reset(server_update_timer_ID);
	}


	return ret_operation;
}
