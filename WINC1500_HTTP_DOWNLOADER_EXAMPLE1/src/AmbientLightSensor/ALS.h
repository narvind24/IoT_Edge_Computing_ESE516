/*
 * ALS.h
 *
 * Created: 5/7/2022 11:44:07 PM
 *  Author: gopik
 */ 


#ifndef ALS_H_
#define ALS_H_

/* Includes																*/
/************************************************************************/

#include "asf.h"
#include "main.h"
#include "I2cDriver/I2cDriver.h"
#include "SerialConsole.h"

/* Macros																*/
/************************************************************************/

#define VEML6030_I2CADDR_DEFAULT	0x48	///< VEML6030 I2C address with ADDR high
#define VEML6030_ALS_CONF_0			0x00	///< ALS gain, integration time, interrupt, and shutdown
#define VEML6030_ALS				0x04	///< ALS data
#define VEML6030_WHITE				0x05	///< WHITE data
#define VEML6030_TIMEOUT			100
#define VEML6030_DELAY				0

/* Variables															*/
/************************************************************************/

typedef struct {
	float luxVal;
	float whiteVal;
}alsData;

/* Function Prototypes                                                  */
/************************************************************************/

int32_t alsInit(void);
int32_t alsWriteRegister(uint8_t registerAddress, uint16_t data);
int32_t alsReadRegister(uint8_t registerAddress, uint8_t *data, uint8_t length);
int alsGetVal(alsData *data);


#endif /* ALS_H_ */