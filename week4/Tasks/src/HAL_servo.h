
#ifndef HAL_SERVO_SERVO_INTERFACE_H_
#define HAL_SERVO_SERVO_INTERFACE_H_

#include <stdint.h>
#include "Timer.h"
void Servo_VoidInit(Timer_Config_t *TIM0_Config);
void Servo_VoidDegree(uint8_t Copy_u8Degree);

uint16_t Servo_uint16_tGetTicks(void);

void Servo_VoidReset(void);

#endif /* HAL_SERVO_SERVO_INTERFACE_H_ */