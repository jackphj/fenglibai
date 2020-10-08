#ifndef	__SERVO_H
#define __SERVO_H

#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"
#include "uart_handler.h"

#define frontalKp 30
#define frontalKi 30

#define profileKp 30
#define profileKi 30

#define sl 37.5
#define ll 20.5+37.5



int setZero(void);
void PIDtoPosition(uint8_t* position);

#endif
