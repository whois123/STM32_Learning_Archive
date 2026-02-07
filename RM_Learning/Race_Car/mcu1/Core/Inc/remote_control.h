#include "main.h"

#ifndef __RREMOTE_CONTRAOL_H
#define __RREMOTE_CONTRAOL_H

#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
typedef struct
{
	int16_t ch1;
	int16_t ch2;
	int16_t ch3;
	int16_t ch4;

	uint8_t switch_left;
	uint8_t switch_right;

	struct
	{
		int16_t x;
		int16_t y;
		int16_t z;

		uint8_t press_left;
		uint8_t press_right;
	}mouse;
	
	uint16_t key_code;   
	
}RC_Type;

void Callback_RC_Handle(RC_Type *rc, uint8_t *buff);
	

#endif



