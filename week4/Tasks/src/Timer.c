
/******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "Timer.h"

/******************************************************************************
 *                               GLOBAL & EXTERN VARIABLES                     *
 *******************************************************************************/
Ptr_Func CALLBACK_OVER_FLOW;
Ptr_Func CALLBACK_COMPARE;
uint8_t Over_Flow_Number = 0,PWM_Over_Flow_Number=0;
uint8_t CMP_Number = 0,PWM_Compare_Number=0;
Timer_Config_t *Global_configuartion;
/******************************************************************************
 *								 APIS IMPLEMENTATION			              *
 *******************************************************************************/

E_STATUS_t TIMER0_Init(Timer_Config_t *configuartion)
{
	E_STATUS_t Value = E_OK;
	if (NULL_PTR == configuartion)
	{
		Value = E_NOK;
	}
	else
	{
		Global_configuartion = configuartion;
		if ((Global_configuartion->mode == Normal) || (Global_configuartion->mode == CTC) ||
			(Global_configuartion->PWM0_MODE == Phase_Correct_PWM ) ||
			(Global_configuartion->PWM0_MODE == Fast_PWM))
		{
			TCCR0 |= Global_configuartion->mode;
		}
		else
		{
			Value = E_NOK;
		}
		if ((Global_configuartion->CLK >= NO_CLK_SRC) && (Global_configuartion->CLK <= EXT_CLK_RISING))
		{
			TCCR0 |= Global_configuartion->CLK;
		}
		else
		{
			Value = E_NOK;
		}
		if ((Global_configuartion->Compare == OCIE_DISABLE) || (Global_configuartion->Compare == OCIE_ENABLE))
		{
			TIMSK |= Global_configuartion->Compare;
		}
		else
		{
			Value = E_NOK;
		}
		if ((Global_configuartion->Overflow == TOIE_DISABLE) || (Global_configuartion->Overflow == TOIE_ENABLE))
		{
			TIMSK |= Global_configuartion->Overflow;
		}
		// Initialize PWM if applicable
		if ((Global_configuartion->PWM0_MODE == Phase_Correct_PWM) || (Global_configuartion->PWM0_MODE == Fast_PWM))
		{
			TIMER0_Init_PWM(Global_configuartion);
		}
		else
		{
			Value = E_NOK;
		}
	}
	return Value;
}

E_STATUS_t TIMER0_Stop()
{
	E_STATUS_t Value = E_OK;
	TCCR0 &= NO_CLK_SRC;
	return Value;
}

/*Does the TCNT0 counter start from TCNT0's value and count up to the overflow value?
Yes.
Does the Timer/Counter 0 count from 0 to OCR0 value in CTC mode?
Yes.*/

E_STATUS_t TIMER0_GetCompare(unsigned char *TicksNumber)
{
	/*The Output Compare Register contains an 8-bit value that is continuously compared with the
	counter value (TCNT0). A match can be used to generate an output compare interrupt, or to
	generate a waveform output on the OC0 pin*/
	E_STATUS_t Value = E_OK;
	*TicksNumber = OCR0;
	return Value;
}

E_STATUS_t TIMER0_SetCompare(uint8_t uint8_t_TicksNumber)
{
	E_STATUS_t Value = E_OK;
	OCR0 = uint8_t_TicksNumber;
	return Value;
}

E_STATUS_t TIMER0_GetCounter(unsigned char *TicksNumber)
{
	E_STATUS_t Value = E_OK;
	*TicksNumber = TCNT0;
	return Value;
}
E_STATUS_t TIMER0_SetCounter(uint8_t uint8_t_TicksNumber)
{
	E_STATUS_t Value = E_OK;
	TCNT0 = uint8_t_TicksNumber;
	return Value;
}

E_STATUS_t TIMER0_GetOverflow(unsigned char *TicksNumber)
{
	E_STATUS_t Value = E_OK;
	*TicksNumber = Over_Flow_Number;
	return Value;
}

E_STATUS_t TIMER0_SetOverflow(uint64_t uint8_t_TicksNumber)
{
	E_STATUS_t Value = E_OK;
	Over_Flow_Number = uint8_t_TicksNumber;
	return Value;
}

void TIMER0_CALLBACK_Overflow_INTERRUPT(Ptr_Func callback)
{
	CALLBACK_OVER_FLOW = callback;
}
void TIMER0_CALLBACK_CompareMatch_INTERRUPT(Ptr_Func callback)
{
	CALLBACK_COMPARE = callback;
}

// Initialize Timer0 PWM settings
void TIMER0_Init_PWM(Timer_Config_t *TIM0_Config)
{
	// Set Fast PWM mode
	if (TIM0_Config->PWM0_MODE == Fast_PWM)
	{
		// Set WGM00 and WGM01 bits to enable Fast PWM mode
		SET_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);
	}
	// Set Phase Correct PWM mode
	else if (TIM0_Config->PWM0_MODE == Phase_Correct_PWM)
	{
		// Clear WGM00 and set WGM01 bit to enable Phase Correct PWM mode
		CLR_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);
	}

	// Set PWM output state
	if (TIM0_Config->PWM0_STATE == PWM0_STATE_NON_INVERTING)
	{
		SET_BIT(TCCR0, COM00);
		CLR_BIT(TCCR0, COM01);
	}
	else if (TIM0_Config->PWM0_STATE == PWM0_STATE_INVERTING)
	{
		SET_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
	}
}

void PWM0_SetDutyCycleValue(uint8_t DutyCycle)
{
	uint8_t Compare_Value = (DutyCycle / 100.0) * 255;
	TIMER0_SetCompare(Compare_Value);
}
void WDT_OFF(void)
{
	WDTCR |= (1 << WDTOE) | (1 << WDE);
	WDTCR = 0x00;
}
// use WDT_TimeOut_t
void WDT_ON(uint8_t time)
{
	SET_BIT(WDTCR, time);
}

// void __vector_11(void) __attribute__((signal));
// void __vector_11(void)
// {
// 	Over_Flow_Number++;
// 	CALLBACK_OVER_FLOW();
// }

// void __vector_10(void) __attribute__((signal));
// void __vector_10(void)
// {
// 	CMP_Number++;
// 	CALLBACK_COMPARE();
// }