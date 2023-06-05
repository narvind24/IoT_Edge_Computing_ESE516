/*
 * led.c
 *
 * Created: 5/8/2022 9:19:00 PM
 *  Author: gopik
 */ 
#include "led.h"

void led_init()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(STREETLIGHT_PIN, &config_port_pin);
	
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(REPAIRLIGHT_PIN, &config_port_pin);
}

void streetLightStateChange(bool val)
{
	if (port_pin_get_output_level(REPAIRLIGHT_PIN) == false)
	{
		if (val)
		{
			port_pin_set_output_level(STREETLIGHT_PIN, true);
		}
		else
		{
			port_pin_set_output_level(STREETLIGHT_PIN, false);
		}
	}
	else
	{
		port_pin_set_output_level(STREETLIGHT_PIN, false);
	}
}

void repairLightStateChange(bool val)
{
	if (val)
	{
		port_pin_set_output_level(REPAIRLIGHT_PIN, true);
	}
	else
	{
		port_pin_set_output_level(REPAIRLIGHT_PIN, false);
	}
}