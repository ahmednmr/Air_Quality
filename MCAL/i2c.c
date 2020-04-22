/*
 * i2c.c
 *
 *  Created on: Mar 25, 2019
 *      Author: Nmr
 */
#include<avr/io.h>
#include<avr/delay.h>
#include"i2c.h"


void TWI_Init(void)
{

//	TWCR = 0;
//	TWBR= TWBR_val;

TWSR=0;
TWBR=0x47;             //50khz
TWCR=0x04;


}


void TWI_Start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); 	//Send START condition
	while (!(TWCR & (1<<TWINT)) );   		//Wait for TWINT flag set. This indicates that the

	}



void TWI_SendAddress(unsigned char address)
{


	TWDR = address;
	TWCR = (1<<TWINT)|(1<<TWEN);	   //Load SLA_W into TWDR Register. Clear TWINT bit
                                     	//in TWCR to start transmission of address

	while (!(TWCR & (1<<TWINT)));   		//Wait for TWINT flag set. This indicates that the

}

void TWI_SendData(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) |(1<<TWEN);	   //Load SLA_W into TWDR Register. Clear TWINT bit
	                                   //in TWCR to start transmission of data

	while (!(TWCR & (1<<TWINT)));   		//Wait for TWINT flag set. This indicates that the

	}

void TWI_ReceiveData_ACK(unsigned char * pu8RxData)
{


	*pu8RxData =0;

	TWCR = (1<<TWEA)|(1<<TWINT)|(1<<TWEN);

	while (!(TWCR & (1<<TWINT)));		//Wait for TWINT flag set. This indicates that the

	*pu8RxData = TWDR;

}


void TWI_ReceiveData_NACK(unsigned char * pu8RxData)
{

	TWCR = (1<<TWINT)|(1<<TWEN);


	while (!(TWCR & (1<<TWINT)));   		//Wait for TWINT flag set. This indicates that the
	*pu8RxData = TWDR;


}

void TWI_Stop(void)
{
	TWCR =  (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);	  //Transmit STOP condition
}




unsigned char  TWI_Read8(unsigned char DeviceAdd, unsigned char memory_location)
{
	uint8_t DataByte = 0;

	TWI_Start();                      /* Send Start Bit 						 */
	TWI_SendData(DeviceAdd);         /* Send Slave address with Operation Write */
	TWI_SendData(memory_location);       /* Send Memory Location Address 			 */
	TWI_Start();                      /* Send Restart Bit 						 */
	TWI_SendData(DeviceAdd | 1);     /* Send Slave address with Operation read  */
	TWI_ReceiveData_NACK(&DataByte);
	TWI_Stop();

	return DataByte;

}

unsigned char TWI_Read16(unsigned char DeviceAdd,unsigned char memory_location)
{
	uint16_t u16Data = 0;
	uint8_t u8Data = 0;

	TWI_Start();                      /* Send Start Bit 						 */
	TWI_SendData(DeviceAdd);         /* Send Slave address with Operation Write */
	TWI_SendData(memory_location);       /* Send Memory Location Address 			 */
	TWI_Start();                      /* Send Restart Bit 						 */
	TWI_SendData(DeviceAdd | 1);     /* Send Slave address with Operation read  */
	TWI_ReceiveData_ACK(&u8Data);  //read 2 or 3 bytes ?
	u16Data = u8Data<<8;
	TWI_ReceiveData_NACK(&u8Data);
	TWI_Stop();

	u16Data |= u8Data;
	return u16Data;

}

void  TWI_Write8(unsigned char DeviceAdd, unsigned char memory_location, unsigned char DataByte)
{
	TWI_Start();                      /* Send Start Bit 						 */
	TWI_SendData(DeviceAdd);         /* Send Slave address with Operation Write */
	TWI_SendData(memory_location);       /* Send Memory Location Address 			 */
	TWI_SendData(DataByte);
	TWI_Stop();

}
