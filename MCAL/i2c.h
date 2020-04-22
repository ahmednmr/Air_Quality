/*
 * i2c.h
 *
 *  Created on: Mar 25, 2019
 *      Author: Nmr
 */

#ifndef I2C_H_
#define I2C_H_


#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

void TWI_Init(void);
void TWI_Start(void);
void TWI_SendAddress(unsigned char address);
void TWI_SendData(unsigned char data);
void TWI_ReceiveData_ACK(unsigned char * pu8RxData);
void TWI_ReceiveData_NACK(unsigned char * pu8RxData);
void TWI_Stop(void);
unsigned char  TWI_Read8(unsigned char DeviceAdd, unsigned char memory_location);
unsigned char TWI_Read16(unsigned char DeviceAdd,unsigned char memory_location);
void  TWI_Write8(unsigned char DeviceAdd, unsigned char memory_location, unsigned char DataByte);


#endif /* I2C_H_ */
