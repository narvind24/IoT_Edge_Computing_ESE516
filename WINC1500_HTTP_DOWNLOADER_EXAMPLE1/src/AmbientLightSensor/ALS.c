/*
 * ALS.c
 *
 * Created: 5/7/2022 11:43:55 PM
 *  Author: gopik
 */ 
#include "ALS.h"

I2C_Data veml6030Data;

int32_t alsInit(void)
{
	int32_t error = ERROR_NONE;
	error = alsWriteRegister(VEML6030_ALS_CONF_0, 0x1040);
	delay_ms(5);
	return error;
}

int32_t alsWriteRegister(uint8_t registerAddress, uint16_t data)
{
	uint8_t readData;
	int32_t error = ERROR_NONE;
	uint8_t msg[3] = {registerAddress, data&0xFF, data>>8};
		
	veml6030Data.address = VEML6030_I2CADDR_DEFAULT;
	veml6030Data.msgOut = &msg;
	veml6030Data.lenOut = 3;
	veml6030Data.msgIn = &readData;
	veml6030Data.lenIn = 0;
	error = I2cWriteDataWait(&veml6030Data, VEML6030_TIMEOUT);
	return error;
}

int32_t alsReadRegister(uint8_t registerAddress, uint8_t *data, uint8_t length)
{
	int32_t error = ERROR_NONE;
	uint8_t msg = registerAddress;
	veml6030Data.address = VEML6030_I2CADDR_DEFAULT;
	veml6030Data.msgOut = &msg;
	veml6030Data.lenOut = 1;
	veml6030Data.msgIn = data;
	veml6030Data.lenIn = length;
	error = I2cReadDataWaitNoStop(&veml6030Data, 0, 100);
	return error;
}

int alsGetVal(alsData *data)
{
	int32_t error = ERROR_NONE;
	uint8_t buffer[2];
	
	error = alsReadRegister(VEML6030_ALS, &buffer, 2);
	if (error != ERROR_NONE) return error;
	data->luxVal = (buffer[0] | (buffer[1] << 8))*0.2304;
	
	error = alsReadRegister(VEML6030_WHITE, &buffer, 2);
	if (error != ERROR_NONE) return error;
	data->whiteVal = (buffer[0] | (buffer[1] << 8))*0.2304;
	
	return error;
}
