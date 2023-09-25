#ifndef _RTC_
#define _RTC_
#include "I2C_interface.h"
#include <stdint.h>

#define RTC_ADDRESS 0b1101000 // DS1307 I2C address

void ReadTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);
void SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
uint8_t DS1307_Read(uint8_t address);
void DS1307_Write(uint8_t address, uint8_t data);


#endif