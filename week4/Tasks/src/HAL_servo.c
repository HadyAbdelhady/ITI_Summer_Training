#include <HAL_servo.h>
uint16_t Ticks = 0;

void Servo_VoidInit(Timer_Config_t *TIM0_Config)
{
    TIMER0_Init_PWM(TIM0_Config);
    TIMER0_SetOverflow(20000);
}

void Servo_VoidDegree(uint8_t Copy_uint8_tDegree)
{
    if (Copy_uint8_tDegree > 180)
        Copy_uint8_tDegree = 180;
    uint32_t Ton = (1 / 180.0) * Copy_uint8_tDegree + 1;
    Ticks = Ton * 1000;
    TIMER0_SetCompare(Ticks);
}

void Servo_VoidReset(void)
{
    TIMER0_SetCompare(0);
}

uint16_t Servo_uint16_tGetTicks(void)
{
    return Ticks;
}