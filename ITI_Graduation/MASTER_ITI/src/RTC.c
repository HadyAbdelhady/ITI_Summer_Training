#include "RTC.h"
void DS1307_Write(uint8_t address, uint8_t data)
{
    I2C_VoidStartCondition();
    I2C_VoidSetSlaveAddress_Operation(RTC_ADDRESS, TWI_WRITE);
    I2C_VoidMasterWriteData(address);
    I2C_VoidMasterWriteData(data);
    I2C_VoidMasterStopCondition();
}
uint8_t DS1307_Read(uint8_t address)
{
    uint8_t data;
    I2C_VoidStartCondition();
    I2C_VoidSetSlaveAddress_Operation(RTC_ADDRESS, TWI_WRITE);
    I2C_VoidMasterWriteData(address);
    I2C_VoidStartCondition();
    I2C_VoidSetSlaveAddress_Operation(RTC_ADDRESS, TWI_READ);
    I2C_VoidMasterReadData(&data); // Pass a pointer to the data variable
    I2C_VoidMasterStopCondition();
    return data;
}

void SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    DS1307_Write(0x00, seconds);
    DS1307_Write(0x01, minutes);
    DS1307_Write(0x02, hours);
}
void ReadTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds)
{
    *seconds = DS1307_Read(0x00);
    *minutes = DS1307_Read(0x01);
    *hours = DS1307_Read(0x02);
    if ((*seconds) >= 60)
    {
        (*minutes)++;
        (*seconds) = 0;
    }
    if ((*minutes) >= 60)
    {
        (*hours)++;
        (*minutes) = 0;
    }
    if ((*hours) >= 24)
    {
        (*hours) = 0;
        (*minutes) = 0;
        (*seconds) = 0;
    }
    SetTime(*hours, *minutes, *seconds);
}