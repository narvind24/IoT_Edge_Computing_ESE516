/*
 * PIR.c
 *
 * Created: 5/8/2022 8:19:50 PM
 *  Author: gopik
 */ 
#include "PIR.h"

void PIR_init()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(PIR_INPUT_PIN, &config_port_pin);
}

bool PIR_check()
{
	bool var;
	var = port_pin_get_input_level(PIR_INPUT_PIN);
	if (var)
	{
		return true;
	}
	return false;
}