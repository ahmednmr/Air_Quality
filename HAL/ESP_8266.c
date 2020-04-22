/*
 * ESP_8266.c
 *
 *  Created on: Apr 21, 2020
 *      Author: embeddedfab
 */
#include"ESP_8266.h"

//for interrupt

#define DEFAULT_BUFFER_SIZE 60
char  Rec_Data[DEFAULT_BUFFER_SIZE];
char  Counter=0;


void ESP_init(void)
{
	init_UART();
	Set_Call_Back_fun(REC_from_interrupt);
	Clear_REC_Buffer();

}

void ESP_Echo_Enable(BOOLEAN Choose)
{
	if(Choose==TRUE)
	{
		UART_SEND_string("ATE1\r\n");
	}

	else if(Choose==FALSE)
	{
		UART_SEND_string( "ATE0\r\n");
	}

	while(!((Check_Respond("\r\nOK\r\n"))||(Check_Respond("ATE0\r\r\n\r\nOK\r\n"))))
	{
		_delay_ms(1);
	}

#if	Enable_LCD_debug
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"ESP EChO ");
	EF_void_LCD_print_Number(Choose);
	_delay_ms(2000);
#endif
}


void ESP_Work_Mode(U8_t work_mode)
{
	if(work_mode==CLIENT)
	{
		UART_SEND_string( "AT+CWMODE=1\r\n");
	}
	else if(work_mode==SERVER)
	{
		UART_SEND_string( "AT+CWMODE=2\r\n");
	}
	else if(work_mode==BOTH)
	{
		UART_SEND_string( "AT+CWMODE=3\r\n");
	}

	while(!Check_Respond("\r\nOK\r\n"))
	{
		_delay_ms(1);
	}
#if	Enable_LCD_debug
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"ESP Work Mode");
	EF_void_LCD_print_Number(work_mode);
	_delay_ms(2000);
#endif


}


void ESP_Multiple_Connections_Enable(BOOLEAN Choose)
{

	if(Choose==TRUE)
	{
		UART_SEND_string( "AT+CIPMUX=1\r\n");
	}
	else if(Choose==FALSE)
	{
		UART_SEND_string( "AT+CIPMUX=0\r\n");
	}

	while(!Check_Respond("\r\nOK\r\n"))
	{
		_delay_ms(1);
	}
#if	Enable_LCD_debug
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Multiple Connections");
	EF_void_LCD_print_Number(Choose);
	_delay_ms(2000);
#endif


}


void ESP_transmission_Mode(U8_t transmission_Mode)
{

	if(transmission_Mode==NORMAL)
	{
		UART_SEND_string( "AT+CIPMODE=0\r\n");
	}
	else if(transmission_Mode==TRANSPARENT)
	{
		UART_SEND_string( "AT+CIPMODE=1\r\n");
	}

	while(!Check_Respond("\r\nOK\r\n"))
	{
		_delay_ms(1);

	}
#if	Enable_LCD_debug
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"transmission Mode");
	EF_void_LCD_print_Number(transmission_Mode);
	_delay_ms(2000);
#endif

}


BOOLEAN ESP_check_connection(void)
{

	UART_SEND_string( "AT+CIPSTATUS\r\n");

	while(!Check_Word_in_Respond("STATUS"))
	{
		_delay_ms(1);
	}

	_delay_ms(50);

	if(Check_Respond(":2\r\n"))
	{
		Clear_REC_Buffer();
		return TRUE;
	}
	else
	{
		Clear_REC_Buffer();
		return FALSE;
	}


}


void ESP_connect_to_WIFI(char* USER_NAME,char* PASSWORD)
{

	UART_SEND_string( "AT+CWJAP=\"");
	UART_SEND_string( USER_NAME);
	UART_SEND_string( "\",\"");
	UART_SEND_string( PASSWORD);
	UART_SEND_string( "\"\r\n");



	while(!((Check_Respond("WIFI DISCONNECT\r\nWIFI CONNECTED\r\nWIFI GOT IP\r\n\r\nOK\r\n"))||(Check_Respond("WIFI CONNECTED\r\nWIFI GOT IP\r\n\r\nOK\r\n"))||Check_Respond("\r\nOK\r\n")))
	{
		_delay_ms(1);

	}

#if	Enable_LCD_debug
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Connect to Wifi");
	_delay_ms(2000);
#endif



}

void  ESP_OPEN_SOCKET(char* SERVER_IP,char* SERVER_PORT)
{

	UART_SEND_string( "AT+CIPSTART=\"TCP\",\"");
	UART_SEND_string( SERVER_IP);
	UART_SEND_string( "\",");
	UART_SEND_string( SERVER_PORT);
	UART_SEND_string( "\r\n");

	while(!Check_Respond("CONNECT\r\n\r\nOK\r\n"))
	{
		_delay_ms(1);
	}

#if	Enable_LCD_debug
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Connect to");
	EF_void_LCD_Newline();
	EF_void_LCD_print((unsigned char*)"Server");
	_delay_ms(2000);
#endif




}


void ESP_uploade_data(unsigned int data)
{
	char api_buffer[50]={0},send_length_buffer[20]={0},api_length=0;


	sprintf(api_buffer, "GET /update?api_key=SD5OBD49N5H4O8RY&field2=%d\r\n", data);

	api_length=strlen(api_buffer);

	sprintf(send_length_buffer, "AT+CIPSEND=%d\r\n", api_length);


	UART_SEND_string( send_length_buffer);

	while(!Check_Respond("\r\nOK\r\n> "))
	{
		_delay_ms(1);
	}

	UART_SEND_string( api_buffer);

	while(!Check_Word_in_Respond("+IPD"))
	{
		_delay_ms(1);
	}

	_delay_ms(500);
	Clear_REC_Buffer();

#if	Enable_LCD_debug
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Done UPloading");
	_delay_ms(2000);
#endif


}


void ESP_CLOSE_SOCKET(void)
{
	UART_SEND_string( "AT+CIPCLOSE=0\r\n");
	while(!Check_Respond("\r\nOK\r\n"))
	{
		_delay_ms(1);

	}

#if	Enable_LCD_debug
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print((unsigned char*)"Socket Closed");
	_delay_ms(2000);
#endif



}





char Check_Respond(char * Expected_Respond)
{
	char Respond_Length=0;

	Respond_Length=strlen(Expected_Respond);

	if(strncmp(Rec_Data,Expected_Respond, Respond_Length)==0)
	{
		Clear_REC_Buffer();
		return TRUE;
	}
	return FALSE;


}


char Check_Word_in_Respond(char * Word)
{


	if(strstr(Rec_Data,Word) != 0)
	{
		Clear_REC_Buffer();
		return TRUE;
	}

	return FALSE;
}

void Clear_REC_Buffer(void)
{
	Counter=0;
	memset(Rec_Data,0,DEFAULT_BUFFER_SIZE);
}

void REC_from_interrupt(void)
{

	uint8_t oldsrg = SREG;
	cli();
	Rec_Data[Counter] = UDR;
	Counter++;
	if(Counter == DEFAULT_BUFFER_SIZE){
		Counter = 0; //pointer = 0;
	}
	SREG = oldsrg;



}
