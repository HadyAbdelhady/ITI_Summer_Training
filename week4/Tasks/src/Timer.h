#ifndef TIMER
#define TIMER

/******************************************************************************
*                               INCLUDES			                          *
// *******************************************************************************/
#include <stdint.h>
#include "Bit_Math.h"

/******************************************************************************
 *					Typedef-Defines-ENUMS	                				  *
 *******************************************************************************/

typedef void (*Ptr_Func)(void);
#define NULL_PTR ((void *)(0))

// TIMSK: (Timer/Counter Interrupt Mask Register)
typedef enum
{
    TOIE0 = 0, // Bit 0 – TOIE0: Timer/Counter0 Overflow Interrupt Enable
    OCIE0,     // Bit 1 – OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
    TOIE1,
    OCIE1B,
    OCIE1A,
    TICIE1,
    TOIE2,
    OCIE2 = 7
} TIMER0_TIMSK_PINs_E;

// TCCR0 (Timer/Counter Control Register)
typedef enum
{
    CS00 = 0,
    CS01,
    CS02,
    WGM01,   // Bit 3 – WGM01:0: Waveform Generation Mode
    COM00,   // Bit 4 – COM00: Compare Match Output Mode
    COM01,   // Bit 5 – COM01: Compare Match Output Mode
    WGM00,   // Bit 6 – WGM01:0: Waveform Generation Mode
    FOC0 = 7 // Bit 7 – FOC0: Force Output Compare
} TIMER0_TCCR0_PINs_E;

// TIFR:  Timer/Counter Interrupt Flag Register
typedef enum
{
    TOV0 = 0, // • Bit 0 – TOV0: Timer/Counter0 Overflow Flag
    OCF0,     // • Bit 1 – OCF0: Output Compare Flag 0
    TOV1,
    OCF1B,
    OCF1A,
    ICF1,
    TOV2,
    OCF2 = 7
} TIMER0_TIFR_PINs_E;
typedef enum
{
    Normal,
    CTC = 0x08
} Timer_Modes_t;

/*• Bit 0 – TOIE0: Timer/Counter0 Overflow Interrupt Enable
When the TOIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
Timer/Counter0 Overflow interrupt is enabled.*/
typedef enum
{
    TOIE_DISABLE,
    TOIE_ENABLE
} TOIE_t;

/*• Bit 1 – OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
When the OCIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
Timer/Counter0 Compare Match interrupt is enabled.*/
typedef enum
{
    OCIE_DISABLE,
    OCIE_ENABLE = 0x02
} OCIE_t;

typedef unsigned char E_STATUS_t;
#define E_OK (E_STATUS_t)(0)
#define E_NOK (E_STATUS_t)(1)

typedef enum
{
    NO_CLK_SRC,
    NO_PRESCALING,
    PRESCALING_CLK8,
    PRESCALING_CLK64,
    PRESCALING_CLK256,
    PRESCALING_CLK1024,
    EXT_CLK_FALLING,
    EXT_CLK_RISING,
} TIMER_CLOCK_t;
typedef enum {
	PWM0_STATE_Disable,
	PWM0_STATE_INVERTING,
	PWM0_STATE_NON_INVERTING
} PWM0_STATE_t;
typedef enum
{
	Fast_PWM = 0x40,
	Phase_Correct_PWM = 0x08
} PWM_Modes_t;
/******************************************************************************
 *									STRUCT	                				  *
 *******************************************************************************/

typedef struct
{
    Timer_Modes_t mode;
    TOIE_t Overflow;
    OCIE_t Compare;
    TIMER_CLOCK_t CLK;
    PWM_Modes_t PWM0_MODE;
    PWM0_STATE_t PWM0_STATE;  
} Timer_Config_t;

//******************************************************************
/*************************       MACROS        *******************
******************************************************************/

// TCCR0: FOC0 WGM00 COM01 COM00 WGM01 CS02 CS01 CS00
#define TCCR0 *((volatile uint8_t *)0x53)
// TCNT0: Timer/Counter0 (8 Bits)
#define TCNT0 *((volatile uint8_t *)0x52)
// OCR0: Timer/Counter0 Output Compare Register
#define OCR0 *((volatile uint8_t *)0x5C)
// TIMSK: OCIE2 TOIE2 TICIE1 OCIE1A OCIE1B TOIE1 OCIE0 TOIE0
#define TIMSK *((volatile uint8_t *)0x59)
// TIFR: OCF2 TOV2 ICF1 OCF1A OCF1B TOV1 OCF0 TOV0
#define TIFR *((volatile uint8_t *)0x58)

#define SREG *((volatile uint8_t *)0x5F)
#define SREG_BIT7 7

//---------------------------------------
//@ref TIMER0_OCMIE_Define
//---------------------------------------
// TIMSK: Bit 1 – OCIE0:(Timer/Counter0) Output Compare Match Interrupt Enable
#define OCMIE0_Disable ~((uint8_t)(1 << OCIE0))
#define OCMIE0_Enable (uint8_t)(1 << OCIE0)

//---------------------------------------
//@ref TIMER0_TOVIE_Define
//---------------------------------------
// TIMSK: Bit 0 – TOIE0: Timer/Counter0 Overflow Interrupt Enable
#define TOVIE0_Disable ~((uint8_t)(1 << TOIE0))
#define TOVIE0_Enable (uint8_t)(1 << TOIE0)

#define WDTCR *((volatile uint8_t *)0x41)

typedef enum
{
    TimeOut_16ms,
    TimeOut_32ms,
    TimeOut_65ms,
    TimeOut_130ms,
    TimeOut_260ms,
    TimeOut_520ms,
    TimeOut_1s,
    TimeOut_2s,
} WDT_TimeOut_t;
// Bit 3 – WDE: Watchdog Enable
#define WDE (uint8_t)3
// Bit 4 – WDTOE: Watchdog Turn-off Enable
#define WDTOE (uint8_t)4

/******************************************************************************
 *									APIS				                      *
 *******************************************************************************/

E_STATUS_t TIMER0_Init(Timer_Config_t *configuartion);
E_STATUS_t TIMER0_Stop();

E_STATUS_t TIMER0_GetCompare(unsigned char *TicksNumber);
E_STATUS_t TIMER0_SetCompare(uint8_t uint8_t_TicksNumber);

E_STATUS_t TIMER0_GetCounter(unsigned char *TicksNumber);
E_STATUS_t TIMER0_SetCounter(uint8_t uint8_t_TicksNumber);

E_STATUS_t TIMER0_GetOverflow(unsigned char *TicksNumber);
E_STATUS_t TIMER0_SetOverflow(uint64_t uint8_t_TicksNumber);

void TIMER0_CALLBACK_Overflow_INTERRUPT(Ptr_Func callback);
void TIMER0_CALLBACK_CompareMatch_INTERRUPT(Ptr_Func callback);

void PWM0_SetDutyCycleValue(uint8_t DutyCycle);
void TIMER0_Init_PWM(Timer_Config_t *TIM0_Config);

void WDT_ON(uint8_t time);
void WDT_OFF(void);

#endif