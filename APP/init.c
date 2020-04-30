/*
 * init.c
 *
 *  Created on: 5 Aug 2019
 *      Author: root
 */
#include"../main.h"

unsigned int value;

ret_state init_fun(void)
{

	sei();

	DDRD |=(1<<PD5);
	PORTD &=~(1<<PD5);
	EF_void_LCD_init();
	temp_sensor_init();
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"done init LCD");
	_delay_ms(400);

	CS811_init();
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"done init CS811");
	_delay_ms(400);


	spechial_timer_init();
	timer_create(server_update_timer_ID,server_update_timer_time_OUT);
	timer_start(server_update_timer_ID);
	timer_create(update_screen_timer_ID,update_screen_timer_time_OUT);
	timer_start(update_screen_timer_ID);




	ESP_init();
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"done init ESP");
	_delay_ms(400);



	//	    ESP_OPEN_SOCKET(ThingSpeak_SERVER,ThingSpeak_PORT);
	//
	//	    ESP_uploade_data(430);

	//	    ESP_CLOSE_SOCKET();


	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Init Done");
	_delay_ms(2000);



	return ret_operation;
}

