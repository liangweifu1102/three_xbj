#include "Global.h"
/********************************************************************
MTU7脉冲输出初始化
 *******************************************************************/
void MTU7_PWMInit(void)
{
	MSTP(MTU7) = 0;
	
	/* TCNT3 stop */
	MTUB.TSTR.BIT.CST1 =0;

	MTU7.TCR.BYTE = 0x20;

	/* TCNT4 synchronization */
	MTUB.TSYR.BIT.SYNC1 = 0;
	
	/* TCNT10 initialize */
	MTU7.TCNT = 0x0000;
	/* Synchronous Clear */

	/* MTIOC3A output initial output is 1 */
	MTU7.TIOR.BYTE = 0x61;

	/* Set TGRA3 */
	MTU7.TGRA = 11059;
	/* Set TGRB3 */
	MTU7.TGRB = 5529;
	/* Set TGRC3 */
//	MTU8.TGRC = 11059;

//	MTU8.TBTM.BYTE = 0x01;

		/* ---- Timer interrupt enable register setting ---- */
    MTU7.TIER.BYTE = 0x01;         /* The interrupt request (TGIA) by TGFA bit is enabled */
	/* initial interrupt */
	IEN(MTU7,TGIA7) = 0;
	IR(MTU7,TGIA7)  = 0;
	IPR(MTU7,TGIA7) = 18;
	IEN(MTU7,TGIA7) = 1;

	/* MTU7 pwm mode1 */
	MTU7.TMDR.BYTE = 0x02;

	/* MTU7 Start */
	MTUB.TSTR.BIT.CST1 =0;
		
}
/********************************************************************
MTU8脉冲输出初始化
 *******************************************************************/
void MTU8_PWMInit(void)
{
	MSTP(MTU8) = 0;
	
	/* TCNT3 stop */
	MTUB.TSTR.BIT.CST2 =0;
//	MTUA.TSTR.BIT.CST3 =0;

	MTU8.TCR.BYTE = 0x20;

	/* TCNT4 synchronization */
	MTUB.TSYR.BIT.SYNC2 = 0;
	
	/* TCNT10 initialize */
	MTU8.TCNT = 0x0000;
	/* Synchronous Clear */

	/* MTIOC3A output initial output is 1 */
	MTU8.TIOR.BYTE = 0x61;

	/* Set TGRA3 */
	MTU8.TGRA = 11059;
	/* Set TGRB3 */
	MTU8.TGRB = 5529;
	/* Set TGRC3 */

		/* ---- Timer interrupt enable register setting ---- */
    MTU8.TIER.BYTE = 0x01;         /* The interrupt request (TGIA) by TGFA bit is enabled */
	/* initial interrupt */
	IEN(MTU8,TGIA8) = 0;
	IR(MTU8,TGIA8)  = 0;
	IPR(MTU8,TGIA8) = 17;
	IEN(MTU8,TGIA8) = 1;

	/* MTU8 pwm mode1 */
	MTU8.TMDR.BYTE = 0x02;

	/* MTU3 Start */
	MTUB.TSTR.BIT.CST2 =0;
		
}
/********************************************************************
MTU4脉冲输出初始化
 *******************************************************************/
void MTU10_PWMInit(void)
{
	MSTP(MTU10) = 0;
	
	/* TCNT3 stop */
	MTUB.TSTR.BIT.CST4 =0;

	MTU10.TCR.BYTE = 0x20;

	/* TCNT4 synchronization */
	MTUB.TSYR.BIT.SYNC4 = 0;
	
	/* TCNT10 initialize */
	MTU10.TCNT = 0x0000;
	/* Synchronous Clear */

	/* MTIOC10A output initial output is 1 */
	MTU10.TIORH.BYTE = 0x61;

	/* Set TGRA3 */
	MTU10.TGRA = 11059;
	/* Set TGRB3 */
	MTU10.TGRB = 5529;
	/* Set TGRC3 */
	MTU10.TGRC = 11059;

	MTU10.TBTM.BYTE = 0x01;

		/* ---- Timer interrupt enable register setting ---- */
    MTU10.TIER.BYTE = 0x01;         /* The interrupt request (TGIA) by TGFA bit is enabled */
	/* initial interrupt */
	IEN(MTU10,TGIA10) = 0;
	IR(MTU10,TGIA10)  = 0;
	IPR(MTU10,TGIA10) = 10;
	IEN(MTU10,TGIA10) = 1;

	/* MTU3 pwm mode1 */
	MTU10.TMDR.BYTE = 0x12;

	MTUB.TOER.BIT.OE4A = 1;
	MTUB.TSTR.BIT.CST4 =0;
			
}
/********************************************************************
MTU9脉冲输出初始化
 *******************************************************************/
void MTU9_PWMInit(void)
{
//	IOPORT.PFCMTU.BIT.MTUS4 = 1;

	MSTP(MTU9) = 0;
	
	/* TCNT4 stop */
//	MTUB.TSTR.BYTE = 0;

	MTUB.TSTR.BIT.CST3 =0;

	MTU9.TCR.BYTE = 0x20;

	/* TCNT3 synchronization */
	MTUB.TSYR.BIT.SYNC4 = 0;
	
	/* TCNT3 initialize */
	MTU9.TCNT = 0x0000;
	/* Synchronous Clear */

	/* MTIOC4A-b output initial output is 1 */
	/* Output=0 Compare Match(TGRB3),Output=1 Compare Match(TGRA3) */
	MTU9.TIORH.BYTE = 0x61;

	/* Set TGRA4 */
	MTU9.TGRA = 11059;
	/* Set TGRB4 */
	MTU9.TGRB = 5529;
	/* Set TGRC4 */
	MTU9.TGRC = 11059;

	MTU9.TBTM.BYTE = 0x01;

		/* ---- Timer interrupt enable register setting ---- */
    MTU9.TIER.BYTE = 0x01;         /* The interrupt request (TGIA) by TGFA bit is enabled */
	/* initial interrupt */
	IEN(MTU9,TGIA9) = 0;
	IR(MTU9,TGIA9)  = 0;
	IPR(MTU9,TGIA9) = 12;
	IEN(MTU9,TGIA9) = 1;

	/* MTU9 pwm mode1 */
	MTU9.TMDR.BYTE = 0x02;

	/* MTU4 Start */
	MTUB.TSTR.BIT.CST3 =0;
		
}
/********************************************

MTU7-PWM脉冲输出中断程序

*********************************************/

#pragma interrupt ( MTU7_TGRA( vect = VECT( MTU7,TGIA7), enable ) )
void  MTU7_TGRA(void)
{	
	MTU7_PWMProc();
	
}
/********************************************

MTU8-PWM脉冲输出中断程序

*********************************************/
#pragma interrupt ( MTU8_TGRA( vect = VECT( MTU8,TGIA8), enable ) )
void  MTU8_TGRA(void)
{	
	MTU8_PWMProc();	
}
/********************************************

MTU10-PWM脉冲输出中断程序

*********************************************/

#pragma interrupt ( MTU10_TGRA( vect = VECT( MTU10,TGIA10), enable ) )
void  MTU10_TGRA(void)
{	
	MTU10_PWMProc();	
	
}
/********************************************

MTU9-PWM脉冲输出中断程序

*********************************************/
#pragma interrupt ( MTU9_TGRA( vect = VECT( MTU9,TGIA9), enable ) )
void  MTU9_TGRA(void)
{ 
	MTU9_PWMProc();	
}


