/*
 * ESP_8266.h
 *
 *  Created on: Apr 21, 2020
 *      Author: embeddedfab
 */

#ifndef HAL_ESP_8266_H_
#define HAL_ESP_8266_H_


#include "../MCAL/UART.h"
#include "EF_LCD.h"
#include <util/delay.h>
#include <string.h>
#include<stdio.h>

#define Enable_LCD_debug     0

#define WIFI_USER_NAME "B68L-73EE"// "ahmed"//
#define WIFI_PASSWORD    "7BF3260E"//"135792468"//

#define ThingSpeak_SERVER      "api.thingspeak.com"
#define ThingSpeak_PORT			"80"


#define CLIENT   		 1
#define SERVER   		 2
#define BOTH     		 3

#define NORMAL    	     0
#define TRANSPARENT 	 1

void ESP_init(void);
void ESP_Echo_Enable(BOOLEAN Choose);
void ESP_Work_Mode(U8_t work_mode);
void ESP_Multiple_Connections_Enable(BOOLEAN Choose);
void ESP_transmission_Mode(U8_t transmission_Mode);
BOOLEAN ESP_check_connection(void);
void ESP_connect_to_WIFI(char* USER_NAME,char* PASSWORD);

void  ESP_OPEN_SOCKET(char* SERVER_IP,char* SERVER_PORT);
void ESP_uploade_data(unsigned int data);
void ESP_CLOSE_SOCKET(void);

char Check_Respond(char * Expected_Respond);
char Check_Word_in_Respond(char * Word);
void Clear_REC_Buffer(void);

void REC_from_interrupt(void);

#endif /* HAL_ESP_8266_H_ */
