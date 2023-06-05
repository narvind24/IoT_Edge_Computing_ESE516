/*
 * SHTC3.c
 *
 * Created: 5/7/2022 10:25:50 PM
 *  Author: gopik
 */ 
#include "TempSensor/SHTC3.h"

/* I2C Config															*/
/************************************************************************/

I2C_Data shtc3Data = {
	.address = SHTC3_ADDR
};

/* Function Defintion															*/
/************************************************************************/

static int32_t shtc3WriteRegister(uint8_t *buffer, uint16_t length)
{
	shtc3Data.lenOut = length;
	shtc3Data.msgOut = buffer;
	shtc3Data.msgIn = NULL;
	shtc3Data.lenIn = 0;
	int32_t result = I2cWriteDataWait(&shtc3Data, SHTC3_TIMEOUT);
	return result;
}

static int32_t shtc3ReadRegister(uint8_t *buffer, uint16_t length)
{
	shtc3Data.lenOut = length;
	shtc3Data.msgOut = buffer;
	shtc3Data.msgIn = readBuffer;
	shtc3Data.lenIn = READ_BUFFER_LEN;
	int32_t result = I2cReadDataWait(&shtc3Data, SHTC3_DELAY, SHTC3_TIMEOUT);
	return result;
}

int32_t commFunction()
{
	int32_t error = ERROR_NONE;
	
	error = shtc3WriteRegister(wakeWriteBuffer, WRITE_BUFFER_LEN);
	if(error){return error;}
	
	error = shtc3ReadRegister(measureWriteBuffer, WRITE_BUFFER_LEN);
	if(error){return error;}
	
	shtc3ReadRegister(sleepWriteBuffer, WRITE_BUFFER_LEN);
	return error;
}

bool getTempAndHum(uint16_t *buffer)
{
	int32_t error;
	error = commFunction();
	if(error){goto errorHandle;}
			
	humidity = (readBuffer[0] << 8) | readBuffer[1] ;
	temp = (readBuffer[3] << 8) | readBuffer[4] ;

	buffer[0] = 100 * humidity/65536;
	buffer[1] = -45 +175 * temp/65536;
	return true;
	
	errorHandle:
	
	buffer[0] = 0;
	buffer[1] = 0;
	return false;
	
}