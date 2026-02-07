#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"

void Encoder_Init(void);
void Encoder_Update(void);

extern int16_t Encoder_Result[4];
extern int16_t Real_Speed[4]; 

#endif
