#include "SEGMENTS.h"
#include "DIO_interface.h"
#include <util/delay.h>

#include "DIO_private.h"
const u8 common_pins[] = {1, 2, 4, 8, 16, 32};
const u8 digitPatterns[] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111	// 9
};
void SEG_Display(u8 PORT, u8 num)
{
	DIO_SetPortValue(PORT, digitPatterns[num]);
}

void SEG_displayTime(u8 segmentPort, u8 commonPort, u8 hours, u8 minutes, u8 seconds)
{
	for (u8 i = 0; i < 6; i++)
	{
		for (u8 j = 0; j < 100; j++)
		{ // Set the common pin high based on the current segment
			DIO_SetPinValue(commonPort, common_pins[i], HIGH);

			// Display the corresponding digit based on the segment
			switch (i)
			{
			case 0:
				SEG_Display(segmentPort, (hours / 10));
				break; // Display hours (tens digit)
			case 1:
				SEG_Display(segmentPort, (hours % 10));
				break; // Display hours (ones digit)
			case 2:
				SEG_Display(segmentPort, (minutes / 10));
				break; // Display minutes (tens digit)
			case 3:
				SEG_Display(segmentPort, (minutes % 10));
				break; // Display minutes (ones digit)
			case 4:
				SEG_Display(segmentPort, (seconds / 10));
				break; // Display seconds (tens digit)
			case 5:
				SEG_Display(segmentPort, (seconds % 10));
				break; // Display seconds (ones digit)
			}
			// Set the common pin low after displaying the digit
			DIO_SetPinValue(commonPort, common_pins[i], LOW);
		}
	}
}