/*
 * Timer.c
 *
 *  Created on: 2011-9-21
 *      Author: YWQ
 */
#include "Global.h"
//#include "Action.h"


#define TIMER0_INTERRUPT_PRIORITY	3
#define TICK_RATE_HZ		1000		// 1000hz 1ms

unsigned long dwTickCount = 0x0;
void SetupTimer0Interrupt( void )
{
	/* Enable compare match timer 0. */
	MSTP( CMT0 ) = 0;

	/* Interrupt on compare match. */
	CMT0.CMCR.BIT.CMIE = 1;

	/* Set the compare match value. */
	CMT0.CMCOR = ( unsigned short ) ( ( ( PCLK_FREQUENCY / TICK_RATE_HZ ) -1 ) / 8 );

	/* Divide the PCLK by 8. */
	CMT0.CMCR.BIT.CKS = 0;

	/* Enable the interrupt... */
	IEN( CMT0,CMI0 ) = 1;

	/* ...and set its priority to the application defined kernel priority. */
	IPR( CMT0,CMI0 ) = TIMER0_INTERRUPT_PRIORITY;

	/* Start the timer. */
	CMT.CMSTR0.BIT.STR0 = 1;
}
/*-----------------------------------------------------------*/
extern void TestSend(void);
extern unsigned long dwAutoStepResetDlay;
#pragma interrupt ( Timer0TickISR( vect = VECT( CMT0,CMI0 ), enable ) )
void Timer0TickISR( void )
{
	dwTickCount++;
	MSecondtime++;
	Secondtime++;
	if(Secondtime>=60*1000)
	{
		Secondtime=0;
		Mintuetime+=1;
	}
	if(cEnableRxDelay) cEnableRxDelay--;
	if(bTxEnd == 1)
	{
		if(SCI6.SSR.BIT.TEND == 1)
		{
			bTxEnd = 0;
			Enableb485Rx();
//			SCI0_RxIntEn();
		}
	}
	if(NextDlay) NextDlay--;
	if(ServorDlay) ServorDlay--;
	if(NextStepDlay) NextStepDlay--;
	if(RstPphlDlay)RstPphlDlay--;
        if (dwAutoStepResetDlay)dwAutoStepResetDlay--;
      
        if (StarFilterTime) StarFilterTime--;
	if(KeyDelay)KeyDelay--;
	TimerPulseStart();
}

#define CPLRunLED()	PORT0.DR.BYTE ^= 0x01
#define BLINKTIME 100

unsigned long dwBlinkCount = 0;
void BlinkRunLED(void)
{
//	b100ms = 0;
	if(dwBlinkCount < dwTickCount)
	{
//		b100ms = 1;
		dwBlinkCount = dwTickCount + BLINKTIME;
		CPLRunLED();
	//	PORTC.DR.BYTE ^= 0xF0;
//          TestSend();
	}
}
