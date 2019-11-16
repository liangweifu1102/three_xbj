/***********************************************************************/
/*                                                                     */
/*  FILE        :hwsetup.c                                             */
/*  DATE        :Sat, Oct 02, 2010                                     */
/*  DESCRIPTION :Hardware Setup file                                   */
/*  CPU TYPE    :RX62N                                                 */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.53).    */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
/************************************************************************
*
* Device     : RX/RX600/RX62N
*
* File Name  : hwsetup.c
*
* Abstract   : Hardware Setup file.
*
* History    : 1.00  (2010-03-05)  [Hardware Manual Revision : 0.50]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2009 Renesas Electronics Corporation.
* and Renesas Solutions Corporation. All rights reserved.
*
************************************************************************/

#include "Global.h"

extern void SetupTimer0Interrupt( void );

void HardwareSetup(void)
{
   /*
   Clock Description              Frequency
   ----------------------------------------
   Input Clock Frequency..............11.0592MHz
   Internal Clock Frequency..........ICLK * 8 MHz
   Peripheral Clock Frequency.........ICLK * 4 MHz
   External Bus Clock Frequency.......ICLK * 4 MHz
    */

  /* Configure SCKCR based on header request */
  {
    uint32_t sckcr = 0;
    sckcr += (ICLK_MUL==8) ? (0ul << 24) : (ICLK_MUL==4) ? (1ul << 24) : (ICLK_MUL==2)? (2ul << 24) : (1ul << 24);
    sckcr += (BCLK_MUL==8) ? (0ul << 16) : (BCLK_MUL==4) ? (1ul << 16) : (BCLK_MUL==2)? (2ul << 16) : (1ul << 16);
    sckcr += (PCLK_MUL==8) ? (0ul <<  8) : (PCLK_MUL==4) ? (1ul <<  8) : (PCLK_MUL==2)? (2ul <<  8) : (1ul <<  8);
    SYSTEM.SCKCR.LONG = sckcr;
  }


 /*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *    IN1  XXX   IN2  XXX  IN3   IN4   IN5   IN6
 * DDR   0     0    0	   0	 0    0      0	   0		 
 */
	PORT0.DDR.BYTE = 0x01;		
	PORT0.DR.BYTE = 0x01;		
	PORT0.ICR.BYTE = 0xae;		

 /*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *    TXD2    RXD2    R/T2   R/T1   SDA   SCL   XXX   XXX
 * DDR   0     0     0	   0	 1     1    0	   0
*/
	PORT1.DDR.BYTE = 0xfc;		
	PORT1.DR.BYTE = 0xfc;		
	PORT1.ICR.BYTE = 0x00;
	PORT1.ODR.BYTE=0x0c;

 /*	  Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *    TCK  TXD0 MTKBA   MTKAA    MTKDA   MTKCA RXD   TXD
 * DDR   0     0    0	   0	 0    1      0	   0 
 */
	PORT2.DDR.BYTE = 0x3f;
	PORT2.DR.BYTE = 0x1f;	
	PORT2.ICR.BYTE = 0x00;	

/*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *    XXX   XXX    NC   NC   IN7  IN10    NC    NC	
 * DDR   0     0    0	   0	 0      1   0	   0	
*/
	PORT3.DDR.BYTE = 0x00;	
	PORT3.DR.BYTE = 0x00;	
	PORT3.ICR.BYTE = 0x00;	
        
/*	Bit7  Bit6  Bit5     Bit4  Bit3     Bit2    Bit1    Bit0
 *    INt1   INt2  IN31 INT32 IN33 IN34 IN35   IN0	
 * DDR   0     0    0	      0	    0         0       0     0	
*/
	PORT4.DDR.BYTE = 0x0;	
	PORT4.DR.BYTE = 0x0;	
	PORT4.ICR.BYTE = 0xff;	

/*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *    XXX  IN11    IN12   IN13   IN14   RD    IN15    WR	
 * DDR   0     0    0   0	 0    1	    0	   1	
*/
	PORT5.DDR.BYTE = 0x77;		
	PORT5.DR.BYTE = 0x77;		
	PORT5.ICR.BYTE = 0x00;		

/*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *    NC    NC   NC  NC CS312 NC NC NC	
 * DDR   0     0    0 	   1	 1    1	      1	   1	
*/
	PORT6.DDR.BYTE = 0x00;		
	PORT6.DR.BYTE = 0x0;		
	PORT6.ICR.BYTE = 0xff;		

/*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *    IN17    IN20    IN21   IN22 IN23    IN26   A_RST2   NC   NC	
 * DDR   0     0    0	   0	 0    1	      1	   0	
*/
	PORT7.DDR.BYTE = 0xe0;		
	PORT7.DR.BYTE = 0xe0;		
	PORT7.ICR.BYTE = 0x07;		

/*    Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *     XXX  XXX  XXX  XXX  DR2I PUS1I DR1I  PUS1I	
 * DDR   0     0    0	   0	 0	1   1   1	 
*/
	PORT8.DDR.BYTE = 0x00;		
	PORT8.DR.BYTE = 0x00;		
	PORT8.ICR.BYTE = 0xff;		

/*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *      XXX   XXX   XXX   XXX   P93  P92 CS_OuT   IN30	
 * DDR   0     0    0	   0	 0   0	    0	   0	
*/
	PORT9.DDR.BYTE = 0x00;		
	PORT9.DR.BYTE = 0x00;		
	PORT9.ICR.BYTE = 0x0f;		

/*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *    NC   NC    NC    A4    A3    A2    A1    NC	
 * DDR  1     1	    1	  1	1     1	    1	  1		 
*/
	PORTA.DDR.BYTE = 0xf8;		
	PORTA.DR.BYTE = 0xf8;		
	PORTA.ICR.BYTE = 0x07;		
//	PORTA.PCR.BYTE = 0xff;		

/*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *    IN27 RUN  CLK   SON1  A_RST1    SON2   NC    NC
 * DDR  0     0    0	  0	 0   0	    1	  1		
*/
	PORTB.DDR.BYTE = 0x33;		
	PORTB.DR.BYTE = 0x33;		
	PORTB.ICR.BYTE = 0x00;		
//	PORTB.PCR.BYTE = 0xff;		

/*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *    MISO MOSI   TCK   SSL0   IN16   IN21   IN24  IN25	
 * DDR  0     0	    1	  1	 0   0	    0  0		
*/
	PORTC.DDR.BYTE = 0xdc;		
	PORTC.DR.BYTE = 0x0c;		
	PORTC.ICR.BYTE = 0x00;		
//	PORTC.PCR.BYTE = 0xff;		

/*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *      D7    D6    D5    D4    D3    D2    D1    D0		
 * DDR  0     0	    0	  0	0     0	    0	  0	 
*/
	PORTD.DDR.BYTE = 0x00;		
	PORTD.DR.BYTE = 0x00;		
	PORTD.ICR.BYTE = 0xff;		
//	PORTD.PCR.BYTE = 0xff;		

/*	Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
 *      D15   D14   D13   D12   D11   D10   D9    D8		
 * DDR  0     0	    0	  0	 0    0	    0	  0		
*/
	PORTE.DDR.BYTE = 0x00;		
	PORTE.DR.BYTE = 0x00;		
	PORTE.ICR.BYTE = 0xff;		
//	PORTE.PCR.BYTE = 0xff;		
        
#if EX_BUS_EN
	/* turn on external address and data bus */
	SYSTEM.SYSCR0.WORD = 0x5A03;   /* enable the external bus...must also set key and internal ROME bit */

	IOPORT.PF0CSE.BYTE = 0x00;     /* Disable CS0-CS7 */
	IOPORT.PF1CSS.BYTE = 0x00;     /* SELECT CS4--CS7 OUT PIN */
	IOPORT.PF2CSS.BYTE = 0x00;     /* SELECT CS0--CS3 OUT PIN */
	IOPORT.PF3BUS.BYTE = 0x00;     /* Enable A16-A21 */
	IOPORT.PF4BUS.BYTE = 0x01;     /* Enable A0-A15 */
	IOPORT.PF5BUS.BYTE = 0x10;     /* Enable D8-D15 select A16.A -- A19.A*/
	IOPORT.PF6BUS.BYTE = 0x00;     /* Disable SDRAM pins */
//	SYSTEM.SYSCR0.BIT.EXBE = 0x01;
	{ uint32_t delay = 100*100; while (--delay > 0); } /* delay at least 100uS after SDCLK active */
#endif

#if CS0_USE
  /* configure CS0 */
  BSC.CS0MOD.BIT.WRMOD = 1;       /* use single write control */

  /* enable CS0 space as 16 bit memory space */
  BSC.CS0CR.WORD = 1 + (CS0_DATA_SIZE << 4);

  /* 恢复周期设定寄存�? */
  BSC.CS0REC.WORD = CS0_RRCV + (CS0_WRCV << 8);

  /* 等待控制寄存�? */
  BSC.CS0WCR1.LONG = CS0_CSPWWAIT + (CS0_CSPRWAIT << 8)
					 + (CS0_CSWWAIT << 16) + (CS0_CSRWAIT << 24);

  /* 等待控制寄存�? */
  BSC.CS0WCR2.LONG = CS0_CSROFF + (CS0_CSWOFF << 4)
					 + (CS0_WDOFF << 8) + (CS0_RDON << 16)
					 + (CS0_WRON << 20) + (CS0_WDON << 24)
					 + (CS0_CSON << 28);

  IOPORT.PF2CSS.BIT.CS0S = 0;     /* set CS0-A as active  P60*/
  IOPORT.PF0CSE.BIT.CS0E = 1;     /* enable CS1 pin */
#endif


#if CS1_USE
  /* configure CS1 */
  BSC.CS1MOD.BIT.WRMOD = 0;       /* 字节选通模�?*/

  /* enable CS1 space as 8 bit memory space */
  BSC.CS1CR.WORD = 1 + (CS1_DATA_SIZE << 4);

  /* 恢复周期设定寄存�? */
  BSC.CS1REC.WORD = CS1_RRCV + (CS1_WRCV << 8);

  /* 等待控制寄存�? */
  BSC.CS1WCR1.LONG = CS1_CSPWWAIT + (CS1_CSPRWAIT << 8)
					 + (CS1_CSWWAIT << 16) + (CS1_CSRWAIT << 24);

  /* 等待控制寄存�? */
  BSC.CS1WCR2.LONG = CS1_CSROFF + (CS1_CSWOFF << 4)
					 + (CS1_WDOFF << 8) + (CS1_RDON << 16)
					 + (CS1_WRON << 20) + (CS1_WDON << 24)
					 + (CS1_CSON << 28);

  IOPORT.PF2CSS.BIT.CS1S = 0;     /* set CS1-A as active  P61*/
  IOPORT.PF0CSE.BIT.CS1E = 1;     /* enable CS1 pin */
#endif

#if CS2_USE
  /* configure CS2 */
  BSC.CS2MOD.BIT.WRMOD = 1;       /* use single write control */

  /* enable CS2 space as 16 bit memory space */
  BSC.CS2CR.WORD = 1 + (CS2_DATA_SIZE << 4);

  /* 恢复周期设定寄存�? */
  BSC.CS2REC.WORD = CS2_RRCV + (CS2_WRCV << 8);

  /* 等待控制寄存�? */
  BSC.CS2WCR1.LONG = CS2_CSPWWAIT + (CS2_CSPRWAIT << 8)
					 + (CS2_CSWWAIT << 16) + (CS2_CSRWAIT << 24);

  /* 等待控制寄存�? */
  BSC.CS2WCR2.LONG = CS2_CSROFF + (CS2_CSWOFF << 4)
					 + (CS2_WDOFF << 8) + (CS2_RDON << 16)
					 + (CS2_WRON << 20) + (CS2_WDON << 24)
					 + (CS2_CSON << 28);

  IOPORT.PF2CSS.BIT.CS2S = 0;     /* set CS2-A as active  P61*/
  IOPORT.PF0CSE.BIT.CS2E = 1;     /* enable CS2 pin */
#endif

#if CS3_USE
  /* configure CS3 */
  BSC.CS3MOD.BIT.WRMOD = 1;       /* use single write control */

  /* enable CS3 space as 16 bit memory space */
  BSC.CS3CR.WORD = 1 + (CS3_DATA_SIZE << 4);

  /* 恢复周期设定寄存�? */
  BSC.CS3REC.WORD = CS3_RRCV + (CS3_WRCV << 8);

  /* 等待控制寄存�? */
  BSC.CS3WCR1.LONG = CS3_CSPWWAIT + (CS3_CSPRWAIT << 8)
					 + (CS3_CSWWAIT << 16) + (CS3_CSRWAIT << 24);

  /* 等待控制寄存�? */
  BSC.CS3WCR2.LONG = CS3_CSROFF + (CS3_CSWOFF << 4)
					 + (CS3_WDOFF << 8) + (CS3_RDON << 16)
					 + (CS3_WRON << 20) + (CS3_WDON << 24)
					 + (CS3_CSON << 28);

  IOPORT.PF2CSS.BIT.CS3S = 0;     /* set CS3-A as active  P63*/
  IOPORT.PF0CSE.BIT.CS3E = 1;     /* enable CS3 pin */
#endif

#if CS4_USE
  /* configure CS4 */
  BSC.CS4MOD.BIT.WRMOD = 1;       /* use single write control */

  /* enable CS4 space as 16 bit memory space */
  BSC.CS4CR.WORD = 1 + (CS4_DATA_SIZE << 4);

  /* 恢复周期设定寄存�? */
  BSC.CS4REC.WORD = CS4_RRCV + (CS4_WRCV << 8);

  /* 等待控制寄存�? */
  BSC.CS4WCR1.LONG = CS4_CSPWWAIT + (CS4_CSPRWAIT << 8)
					 + (CS4_CSWWAIT << 16) + (CS4_CSRWAIT << 24);

  /* 等待控制寄存�? */
  BSC.CS4WCR2.LONG = CS4_CSROFF + (CS4_CSWOFF << 4)
					 + (CS4_WDOFF << 8) + (CS4_RDON << 16)
					 + (CS4_WRON << 20) + (CS4_WDON << 24)
					 + (CS4_CSON << 28);

  IOPORT.PF1CSS.BIT.CS4S = 0;     /* set CS4-A as active  P64*/
  IOPORT.PF0CSE.BIT.CS4E = 1;     /* enable CS4 pin */
#endif

#if CS5_USE
  /* configure CS5 */
  BSC.CS5MOD.BIT.WRMOD = 1;       /* use single write control */

  /* enable CS5 space as 16 bit memory space */
  BSC.CS5CR.WORD = 1 + (CS5_DATA_SIZE << 4);

  /* 恢复周期设定寄存�? */
  BSC.CS5REC.WORD = CS5_RRCV + (CS5_WRCV << 8);

  /* 等待控制寄存�? */
  BSC.CS5WCR1.LONG = CS5_CSPWWAIT + (CS5_CSPRWAIT << 8)
					 + (CS5_CSWWAIT << 16) + (CS5_CSRWAIT << 24);

  /* 等待控制寄存�? */
  BSC.CS5WCR2.LONG = CS5_CSROFF + (CS5_CSWOFF << 4)
					 + (CS5_WDOFF << 8) + (CS5_RDON << 16)
					 + (CS5_WRON << 20) + (CS5_WDON << 24)
					 + (CS5_CSON << 28);

  IOPORT.PF1CSS.BIT.CS5S = 0;     /* set CS5-A as active  P65*/
  IOPORT.PF0CSE.BIT.CS5E = 1;     /* enable CS5 pin */
#endif

#if CS6_USE
  /* configure CS6 */
  BSC.CS6MOD.BIT.WRMOD = 1;       /* use single write control */

  /* enable CS6 space as 16 bit memory space */
  BSC.CS6CR.WORD = 1 + (CS6_DATA_SIZE << 4);

  /* 恢复周期设定寄存�? */
  BSC.CS6REC.WORD = CS6_RRCV + (CS6_WRCV << 8);

  /* 等待控制寄存�? */
  BSC.CS6WCR1.LONG = CS6_CSPWWAIT + (CS6_CSPRWAIT << 8)
					 + (CS6_CSWWAIT << 16) + (CS6_CSRWAIT << 24);

  /* 等待控制寄存�? */
  BSC.CS6WCR2.LONG = CS6_CSROFF + (CS6_CSWOFF << 4)
					 + (CS6_WDOFF << 8) + (CS6_RDON << 16)
					 + (CS6_WRON << 20) + (CS6_WDON << 24)
					 + (CS6_CSON << 28);

  IOPORT.PF1CSS.BIT.CS6S = 0;     /* set CS6-A as active  P66*/
  IOPORT.PF0CSE.BIT.CS6E = 1;     /* enable CS6 pin */
#endif

#if CS7_USE
  /* configure CS7 */
  BSC.CS7MOD.BIT.WRMOD = 1;       /* use single write control */

  /* enable CS7 space as 16 bit memory space */
  BSC.CS7CR.WORD = 1 + (CS7_DATA_SIZE << 4);

  /* 恢复周期设定寄存�? */
  BSC.CS7REC.WORD = CS7_RRCV + (CS7_WRCV << 8);

  /* 等待控制寄存�? */
  BSC.CS7WCR1.LONG = CS7_CSPWWAIT + (CS7_CSPRWAIT << 8)
					 + (CS7_CSWWAIT << 16) + (CS7_CSRWAIT << 24);

  /* 等待控制寄存�? */
  BSC.CS7WCR2.LONG = CS7_CSROFF + (CS7_CSWOFF << 4)
					 + (CS7_WDOFF << 8) + (CS7_RDON << 16)
					 + (CS7_WRON << 20) + (CS7_WDON << 24)
					 + (CS7_CSON << 28);

  IOPORT.PF1CSS.BIT.CS7S = 0;     /* set CS7-A as active  P67*/
  IOPORT.PF0CSE.BIT.CS7E = 1;     /* enable CS7 pin */
#endif

#if SDRAM_USE

  BSC.SDIR.WORD = 0x00F0;         /* SDRAM initialization...AutoRefresh interval=3 cycles, Precharge cycles count=3cycles, 15 times */
  BSC.SDICR.BIT.INIRQ = 1;        /* starte SDRAM initialization */
  while(BSC.SDSR.BIT.INIST == 1);  /* wait for initialization complete */

  BSC.SDCMOD.BIT.EMODE = 0;       /* set endian to little */
  BSC.SDCCR.BIT.BSIZE = 0;        /* set SDRAM to 16bit access */
  BSC.SDMOD.WORD = 0x0220;        /* Set write single location, CL=2 */
  BSC.SDRFCR.BIT.REFW = 5-1;      /* set refresh cycle count to 5 */
  BSC.SDRFCR.BIT.RFC = 720-1;     /* set refresh period to 720 clock cycles (15uS at 48Mhz) */
  BSC.SDTR.LONG = 0x000002;       /* set RAS=1, RCD=1, RP=1, WR=1, CL=2, cycles */
  BSC.SDADR.BIT.MXC = 1;          /* set shift to 9 bits (for 8Mx16 SDRAM) */
  BSC.SDRFEN.BIT.RFEN = 1;        /* enable auto refresh */
  BSC.SDCCR.BIT.EXENB = 1;        /* enable SDRAM operation...this should be last operation */
#endif

	//初始化定时器0比较中断
	SetupTimer0Interrupt();
	UartInit(BAUD_FREQ);
}


