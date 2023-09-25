
#ifndef _SEG_
#define _SEG_
#include "DIO_interface.h"
#include "UTILS.h"
#include "STDTYPE.h"
#define SegmentsPort Port_A
#define CommonPort Port_D
extern const u8 segmentPins[];

// Define pins for selecting the common cathode of each display
extern const u8 digitPins[];

extern const u8 digitPatterns[];

void SEG_Display(u8 PORT, u8 num);
void SEG_displayTime(u8 segmentPort, u8 commonPort, u8 hours, u8 minutes, u8 seconds);
#endif