/*
 * SHTC3.h
 *
 * Created: 5/7/2022 9:34:30 PM
 *  Author: gopik
 */ 


#ifndef SHTC3_H_
#define SHTC3_H_

/* Includes															*/
/************************************************************************/

#include <errno.h>
#include "asf.h"
#include "main.h"
#include "SerialConsole/SerialConsole.h"
#include "I2cDriver/I2cDriver.h"

/* Variables															*/
/************************************************************************/
uint16_t temp;
uint16_t humidity;

/* Macros																*/
/************************************************************************/

#define WRITE_BUFFER_LEN 2
#define READ_BUFFER_LEN 6
#define SHTC3_ADDR 0x70
#define SHTC3_DELAY 210/portTICK_PERIOD_MS
#define SHTC3_TIMEOUT 10

/* Buffer Init															*/
/************************************************************************/

static uint8_t wakeWriteBuffer[WRITE_BUFFER_LEN] = {0x35, 0x17};
static uint8_t measureWriteBuffer[WRITE_BUFFER_LEN] = {0x58, 0xE0};
static uint8_t sleepWriteBuffer[WRITE_BUFFER_LEN] = {0xB0, 0x98};
uint8_t readBuffer[READ_BUFFER_LEN];

/* Function Prototypes                                                  */
/************************************************************************/

static int32_t shtc3WriteRegister(uint8_t *buffer, uint16_t length);
static int32_t shtc3ReadRegister(uint8_t *buffer, uint16_t length);
int32_t commFunction();
bool getTempAndHum(uint16_t *buffer);

#endif /* SHTC3_H_ */