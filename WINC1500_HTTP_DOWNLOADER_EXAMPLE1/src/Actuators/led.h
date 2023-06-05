/*
 * led.h
 *
 * Created: 5/8/2022 9:19:07 PM
 *  Author: gopik
 */ 


#ifndef LED_H_
#define LED_H_

#define STREETLIGHT_PIN PIN_PA10
#define REPAIRLIGHT_PIN PIN_PA11
#include <asf.h>

void led_init();
void streetLightStateChange(bool state);
void repairLightStateChange(bool state);

#endif /* LED_H_ */