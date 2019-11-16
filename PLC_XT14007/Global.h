#ifndef GLOBAL_H
#define GLOBAL_H

/* Typedef fundemental data types that may change between compilers/families */
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* Include the MCU sfr definitions */
#include "iodefine.h"
#include "Inout.h"
#include "PWM.h"
#include "ServoDrv.h" 
#include "Uart.h"
#include "modusASC.h"
#include "I2c_24c04.h"
#include "Action.h"
#include "MenInit.h"
#include "ManualProc.h"
#include "AutoRunProc.h"
#include "SPIFlash.h"

#define XCW    0 // Զ��ԭ��
#define XCCW    1 // ����ԭ��
#define YCW    0 // ����ԭ��
#define YCCW    1 // Զ��ԭ��
#define ZCW    0 // ����ԭ��
#define ZCCW    1 // Զ��ԭ��

/* Include platform level hardware definitions */
#ifdef MEM_DECL
#define EXTERN
#else
#define EXTERN extern
#endif

//This segment should not be modified
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL    ((void *)0)
#endif



// CPU Clk Frequency define
#define		XTAL_FREQUENCY (11059200L)
#define		ICLK_MUL (8)
#define		PCLK_MUL (4)
#define		BCLK_MUL (2)
#define		ICLK_FREQUENCY (XTAL_FREQUENCY * ICLK_MUL)
#define		PCLK_FREQUENCY (XTAL_FREQUENCY * PCLK_MUL)
#define		BCLK_FREQUENCY (XTAL_FREQUENCY * BCLK_MUL)

// MCX312,MCX314  Frequency define
#define 	MAINFREQ		8000000


#define		EX_BUS_EN	(0)
#define		CS0_USE (0)
#define		CS1_USE (0)
#define		CS2_USE (0)
#define		CS3_USE (0)
#define		CS4_USE (0)
#define		CS5_USE (0)
#define		CS6_USE (0)
#define		CS7_USE (0)
#define		CS0_DATA_SIZE (0)	// 0-16bit,1-32bit,2-8bit
#define		CS1_DATA_SIZE (2)	// 0-16bit,1-32bit,2-8bit
#define		CS2_DATA_SIZE (0)	// 0-16bit,1-32bit,2-8bit
#define		CS3_DATA_SIZE (0)	// 0-16bit,1-32bit,2-8bit
#define		CS4_DATA_SIZE (0)	// 0-16bit,1-32bit,2-8bit
#define		CS5_DATA_SIZE (0)	// 0-16bit,1-32bit,2-8bit
#define		CS6_DATA_SIZE (0)	// 0-16bit,1-32bit,2-8bit
#define		CS7_DATA_SIZE (0)	// 0-16bit,1-32bit,2-8bit
#define		CS0_RRCV (0)		// 读恢复周期设定  0-15周期
#define		CS1_RRCV (0)		// 读恢复周期设定  0-15周期
#define		CS2_RRCV (2)		// 读恢复周期设定  0-15周期
#define		CS3_RRCV (0)		// 读恢复周期设定  0-15周期
#define		CS4_RRCV (0)		// 读恢复周期设定  0-15周期
#define		CS5_RRCV (0)		// 读恢复周期设定  0-15周期
#define		CS6_RRCV (0)		// 读恢复周期设定  0-15周期
#define		CS7_RRCV (0)		// 读恢复周期设定  0-15周期
#define		CS0_WRCV (0)		// 写恢复周期设定  0-15周期
#define		CS1_WRCV (0)		// 写恢复周期设定  0-15周期
#define		CS2_WRCV (2)		// 写恢复周期设定  0-15周期
#define		CS3_WRCV (0)		// 写恢复周期设定  0-15周期
#define		CS4_WRCV (0)		// 写恢复周期设定  0-15周期
#define		CS5_WRCV (0)		// 写恢复周期设定  0-15周期
#define		CS6_WRCV (0)		// 写恢复周期设定  0-15周期
#define		CS7_WRCV (0)		// 写恢复周期设定  0-15周期

#define		CS0_CSPWWAIT (0)	// 设置写页面等待周期  0-7
#define		CS1_CSPWWAIT (0)	// 设置写页面等待周期  0-7
#define		CS2_CSPWWAIT (0)	// 设置写页面等待周期  0-7
#define		CS3_CSPWWAIT (0)	// 设置写页面等待周期  0-7
#define		CS4_CSPWWAIT (0)	// 设置写页面等待周期  0-7
#define		CS5_CSPWWAIT (0)	// 设置写页面等待周期  0-7
#define		CS6_CSPWWAIT (0)	// 设置写页面等待周期  0-7
#define		CS7_CSPWWAIT (0)	// 设置写页面等待周期  0-7

#define		CS0_CSPRWAIT (0)	// 设置读页面等待周期  0-7
#define		CS1_CSPRWAIT (0)	// 设置读页面等待周期  0-7
#define		CS2_CSPRWAIT (0)	// 设置读页面等待周期  0-7
#define		CS3_CSPRWAIT (0)	// 设置读页面等待周期  0-7
#define		CS4_CSPRWAIT (0)	// 设置读页面等待周期  0-7
#define		CS5_CSPRWAIT (0)	// 设置读页面等待周期  0-7
#define		CS6_CSPRWAIT (0)	// 设置读页面等待周期  0-7
#define		CS7_CSPRWAIT (0)	// 设置读页面等待周期  0-7

#define		CS0_CSWWAIT (3)		// 设置正常写等待周期  0-31
#define		CS1_CSWWAIT (3)		// 设置正常写等待周期  0-31
#define		CS2_CSWWAIT (5)		// 设置正常写等待周期  0-31
#define		CS3_CSWWAIT (5)		// 设置正常写等待周期  0-31
#define		CS4_CSWWAIT (5)		// 设置正常写等待周期  0-31
#define		CS5_CSWWAIT (3)		// 设置正常写等待周期  0-31
#define		CS6_CSWWAIT (3)		// 设置正常写等待周期  0-31
#define		CS7_CSWWAIT (3)		// 设置正常写等待周期  0-31

#define		CS0_CSRWAIT (3)		// 设置正常读等待周期  0-31
#define		CS1_CSRWAIT (3)		// 设置正常读等待周期  0-31
#define		CS2_CSRWAIT (5)		// 设置正常读等待周期  0-31
#define		CS3_CSRWAIT (5)		// 设置正常读等待周期  0-31
#define		CS4_CSRWAIT (5)		// 设置正常读等待周期  0-31
#define		CS5_CSRWAIT (3)		// 设置正常读等待周期  0-31
#define		CS6_CSRWAIT (3)		// 设置正常读等待周期  0-31
#define		CS7_CSRWAIT (3)		// 设置正常读等待周期  0-31

#define		CS0_CSROFF (1)		// 设置读取时的CS延长周期  0-7
#define		CS1_CSROFF (1)		// 设置读取时的CS延长周期  0-7
#define		CS2_CSROFF (1)		// 设置读取时的CS延长周期  0-7
#define		CS3_CSROFF (1)		// 设置读取时的CS延长周期  0-7
#define		CS4_CSROFF (1)		// 设置读取时的CS延长周期  0-7
#define		CS5_CSROFF (1)		// 设置读取时的CS延长周期  0-7
#define		CS6_CSROFF (1)		// 设置读取时的CS延长周期  0-7
#define		CS7_CSROFF (1)		// 设置读取时的CS延长周期  0-7

#define		CS0_CSWOFF (1)		// 设置写入时的CS延长周期  0-7
#define		CS1_CSWOFF (1)		// 设置写入时的CS延长周期  0-7
#define		CS2_CSWOFF (1)		// 设置写入时的CS延长周期  0-7
#define		CS3_CSWOFF (1)		// 设置写入时的CS延长周期  0-7
#define		CS4_CSWOFF (1)		// 设置写入时的CS延长周期  0-7
#define		CS5_CSWOFF (1)		// 设置写入时的CS延长周期  0-7
#define		CS6_CSWOFF (1)		// 设置写入时的CS延长周期  0-7
#define		CS7_CSWOFF (1)		// 设置写入时的CS延长周期  0-7

#define		CS0_WDOFF (0)		// 设置写数据的输出延长周期  0-7
#define		CS1_WDOFF (1)		// 设置写数据的输出延长周期  0-7
#define		CS2_WDOFF (1)		// 设置写数据的输出延长周期  0-7
#define		CS3_WDOFF (1)		// 设置写数据的输出延长周期  0-7
#define		CS4_WDOFF (1)		// 设置写数据的输出延长周期  0-7
#define		CS5_WDOFF (0)		// 设置写数据的输出延长周期  0-7
#define		CS6_WDOFF (0)		// 设置写数据的输出延长周期  0-7
#define		CS7_WDOFF (0)		// 设置写数据的输出延长周期  0-7

#define		CS0_RDON (2)		// 设置RD有效等待周期  0-7
#define		CS1_RDON (2)		// 设置RD有效等待周期  0-7
#define		CS2_RDON (2)		// 设置RD有效等待周期  0-7
#define		CS3_RDON (2)		// 设置RD有效等待周期  0-7
#define		CS4_RDON (2)		// 设置RD有效等待周期  0-7
#define		CS5_RDON (2)		// 设置RD有效等待周期  0-7
#define		CS6_RDON (2)		// 设置RD有效等待周期  0-7
#define		CS7_RDON (2)		// 设置RD有效等待周期  0-7

#define		CS0_WRON (3)		// 设置WR有效等待周期  0-7
#define		CS1_WRON (3)		// 设置WR有效等待周期  0-7
#define		CS2_WRON (3)		// 设置WR有效等待周期  0-7
#define		CS3_WRON (3)		// 设置WR有效等待周期  0-7
#define		CS4_WRON (3)		// 设置WR有效等待周期  0-7
#define		CS5_WRON (3)		// 设置WR有效等待周期  0-7
#define		CS6_WRON (3)		// 设置WR有效等待周期  0-7
#define		CS7_WRON (3)		// 设置WR有效等待周期  0-7

#define		CS0_WDON (2)		// 设置写数据的输出等待周期  0-7
#define		CS1_WDON (2)		// 设置写数据的输出等待周期  0-7
#define		CS2_WDON (2)		// 设置写数据的输出等待周期  0-7
#define		CS3_WDON (2)		// 设置写数据的输出等待周期  0-7
#define		CS4_WDON (2)		// 设置写数据的输出等待周期  0-7
#define		CS5_WDON (2)		// 设置写数据的输出等待周期  0-7
#define		CS6_WDON (2)		// 设置写数据的输出等待周期  0-7
#define		CS7_WDON (2)		// 设置写数据的输出等待周期  0-7

#define		CS0_CSON (1)		// 设置CS有效等待周期  0-7
#define		CS1_CSON (1)		// 设置CS有效等待周期  0-7
#define		CS2_CSON (1)		// 设置CS有效等待周期  0-7
#define		CS3_CSON (1)		// 设置CS有效等待周期  0-7
#define		CS4_CSON (1)		// 设置CS有效等待周期  0-7
#define		CS5_CSON (1)		// 设置CS有效等待周期  0-7
#define		CS6_CSON (1)		// 设置CS有效等待周期  0-7
#define		CS7_CSON (1)		// 设置CS有效等待周期  0-7

/* convert 'a' to a string */
#define TO_STR1(a) #a
#define TO_STR(a) TO_STR1(a)

/* Define Pin Macros to ease implementation (secondary macros _1, _2 used for expansion ONLY */
#define CAT(a,b) a ## b
#define MERGE2(a,b) CAT(a,b)

/* Set signal DDR to output */
#ifdef __RX600
#define DDRo2(port,pin) MERGE2(PORT,port) ## MERGE2(.DDR.BIT.B,pin) = 1;
#define DDRi2(port,pin) MERGE2(PORT,port) ## MERGE2(.DDR.BIT.B,pin) = 0;
#define PINo2(port,pin) MERGE2(PORT,port) ## MERGE2(.DR.BIT.B,pin)
#define PINi2(port,pin) MERGE2(PORT,port) ## MERGE2(.PORT.BIT.B,pin)
#define ICRi2(port,pin) MERGE2(PORT,port) ## MERGE2(.ICR.BIT.B,pin)
#else
/* memory for DDR shadowing...used by DDR_xxxx Macros */
EXTERN unsigned char P1DDRS, P2DDRS, P3DDRS, P4DDRS, P5DDRS, P6DDRS, P8DDRS, PADDRS, PBDDRS, PCDDRS,PDDDRS, PEDDRS, PFDDRS,  PGDDRS, PHDDRS, PIDDRS, PJDDRS, PKDDRS, PLDDRS, PMDDRS;

#define DDRo2(port,pin) ( ## MERGE2(P,port) ## .DDR = (unsigned char)( ## MERGE2(P,MERGE2(port,DDRS)) |= (1 << pin)))
#define DDRi2(port,pin) ( ## MERGE2(P,port) ## .DDR = (unsigned char)( ## MERGE2(P,MERGE2(port,DDRS)) &= ~(1 << pin)))
#define PINo2(port,pin) MERGE2(P,port) ## MERGE2(.DR.BIT.B,pin)
#define PINi2(port,pin) MERGE2(P,port) ## MERGE2(.PORT.BIT.B,pin)
#define ICRi2(port,pin) MERGE2(P,port) ## MERGE2(.ICR.BIT.B,pin)
#endif

#define DDRo(signal) DDRo2(signal##_PORT, signal##_PIN)

/* Set signal DDR to input */
#define DDRi(signal) DDRi2(signal##_PORT, signal##_PIN)

/* Write signal level (for output) */
#define PINo(signal) PINo2(signal##_PORT, signal##_PIN)

/* Read signal level (for input) */
#define PINi(signal) PINi2(signal##_PORT, signal##_PIN)

/* Signals buffer control (for inputs) */
#define ICRi(signal) ICRi2(signal##_PORT, signal##_PIN)

#define size_ra(ra) (sizeof(ra)/sizeof(ra[0]))

/* macros to allow easy access to new style ICU bits and IODEFINE macros */
#define _ICU2_(func,unit_channel) _##func(unit_channel)
#define _ICU_(func,irq) _ICU2_(func, MERGE2(irq ## _UNIT, MERGE2(_,irq ## _CHANNEL)))


#define M8D_CS1(adr)  (*((volatile unsigned char  *) (0x07000000+(adr))))
#define M16D(adr) (*((volatile unsigned short *) (adr)))
//#define M16D_CS2(adr) (*((volatile unsigned short *) (0x06000000+(adr))))
#define M16D_CS3(adr) (*((volatile unsigned short *) (0x05000000+(adr))))
#define M16D_CS4(adr) (*((volatile unsigned short *) (0x04000000+(adr))))




#define		OUTEN			PORTA.DR.BIT.B3
// Timer.c
extern unsigned long dwTickCount;


#endif
