#define F_CPU 8000000

#include <util/delay.h>
#include "STDTYPE.h"
#include "UTILS.h"
#include "DIO_interface.h"
#include "LCD_Interface.h"
#include "SPI_interface.h"
#include "SEGMENTS.h"

int main(void)
{
    // Initialize SPI as a master (You may want to change this to SPI_INIT_SLAVE() if this is meant to be the slave)
    SPI_INIT_SLAVE();

    /*LCD */
    // Configure ports and pins for LCD
    DIO_SetPortDirection(Port_C, Port_output);
    DIO_SetPinDirection(Port_B, Pin_0, output);
    DIO_SetPinDirection(Port_B, Pin_1, output);
    DIO_SetPinDirection(Port_B, Pin_2, output);
    DIO_SetPortDirection(SegmentsPort, Port_output);
    DIO_SetPortDirection(CommonPort, Port_output);
    LCD_Init();

    u8 SPI_DATA = 0;
    while (1)
    {
        // Receive data from the master via SPI
        SPI_DATA = SPI_TR_RC(0xff);
        if (SPI_DATA == 't') // If received data is for time
        {
            GOTOXY(1, 0);
            LCD_String("Time : ");
            LCD_voidSendNumber(SPI_TR_RC(0xff));
            LCD_Send_Data(' ');
            LCD_voidSendNumber(SPI_TR_RC(0xff));
            LCD_Send_Data(' ');
            LCD_voidSendNumber(SPI_TR_RC(0xff));
            _delay_ms(100);
            LCD_Clear();
            // SEG_displayTime(SegmentsPort, CommonPort, time[0], time[1], time[2]);
        }
        else if (SPI_DATA == 'n') // If received data indicates a user is entering
        {
            LCD_Clear();
            GOTOXY(0, 0);
            LCD_String("Welcome USER : ");

            // Receive and display the user data from the master
            LCD_Send_Data(SPI_TR_RC(0xff));
            _delay_ms(100);
        }
        else if (SPI_DATA == 'x') // If received data indicates a user is exiting
        {
            LCD_Clear();
            GOTOXY(0, 0);
            LCD_String("BYE USER : ");

            // Receive and display the user data from the master
            LCD_Send_Data(SPI_TR_RC(0xff));
            _delay_ms(100);
        }
    }
}
