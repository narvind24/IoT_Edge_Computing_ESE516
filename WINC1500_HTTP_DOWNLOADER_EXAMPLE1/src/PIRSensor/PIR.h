/*
 * PIR.h
 *
 * Created: 5/8/2022 8:20:20 PM
 *  Author: gopik
 */ 


#ifndef PIR_H_
#define PIR_H_

#define PIR_INPUT_PIN PIN_PB02
#include <asf.h>

void PIR_init();
bool PIR_check();

#endif /* PIR_H_ */