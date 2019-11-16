/*
 * inout.h
 *
 *  Created on: 2011-9-24
 *      Author: lenovo
 */

#ifndef INOUT_H_
#define INOUT_H_

typedef union
{
    unsigned char Val;
	struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
    } bits;

} BYTE_BITS;

typedef union
{
    unsigned char Val;
	struct
    {
        unsigned char Tb0:2;
        unsigned char Tb1:2;
        unsigned char Tb2:2;
        unsigned char Tb3:2;
    } tobits;

} BYTE_TOBITS;

typedef union
{
	unsigned short Val;
	unsigned char v[2];
    struct
    {
		unsigned char LB;
		unsigned char HB;
    } byte;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
    } bits;
} WORD_BITS;

typedef union
{
	unsigned short Val;
 	unsigned char v[2];
    struct
    {
 		unsigned char LB;
 		unsigned char HB;
    } byte;
} WORD_VAL;


#define		I000			PORT0.PORT.BIT.B1
#define		I001			PORT0.PORT.BIT.B2
#define		I002			PORT0.PORT.BIT.B3
#define		I003			PORT0.PORT.BIT.B5
#define		I004			PORT0.PORT.BIT.B7
#define		I005			PORT4.PORT.BIT.B0
#define		I006			PORT4.PORT.BIT.B1
#define		I007			PORT4.PORT.BIT.B2
#define		I010			PORT4.PORT.BIT.B3
#define		I011			PORT4.PORT.BIT.B4
#define		I012			PORT4.PORT.BIT.B5
#define		I013			PORT9.PORT.BIT.B0
#define		I014			PORT9.PORT.BIT.B1
#define		I015			PORT9.PORT.BIT.B2
#define		I016			PORT9.PORT.BIT.B3
#define		I017			PORTD.PORT.BIT.B0

#define		I020			PORTD.PORT.BIT.B1
#define		I021			PORTD.PORT.BIT.B2
#define		I022			PORTD.PORT.BIT.B3
#define		I023			PORTD.PORT.BIT.B4
#define		I024			PORTD.PORT.BIT.B5
#define		I025			PORTD.PORT.BIT.B6
#define		I026			PORTE.PORT.BIT.B4
#define		I027			PORTE.PORT.BIT.B5

#define		I030			PORTE.PORT.BIT.B6
#define		I031			PORTE.PORT.BIT.B7
#define		I032		0
#define		I033		0
#define		I034		0
#define		I035		0
#define		I036		0
#define		I037		0

extern  WORD_BITS cInputVal1,cOldInputVal1;
extern  WORD_BITS cInputVal2,cOldInputVal2;
#define cInputX00_X17	cInputVal1.Val
#define X00		cInputVal1.bits.b0
#define X01		cInputVal1.bits.b1
#define X02		cInputVal1.bits.b2
#define X03		cInputVal1.bits.b3
#define X04		cInputVal1.bits.b4
#define X05		cInputVal1.bits.b5
#define X06		cInputVal1.bits.b6
#define X07		cInputVal1.bits.b7
#define X10		cInputVal1.bits.b8
#define X11		cInputVal1.bits.b9
#define X12		cInputVal1.bits.b10
#define X13		cInputVal1.bits.b11
#define X14		cInputVal1.bits.b12
#define X15		cInputVal1.bits.b13
#define X16		cInputVal1.bits.b14
#define X17		cInputVal1.bits.b15

#define cInputX20_X37	cInputVal2.Val
#define X20		cInputVal2.bits.b0
#define X21		cInputVal2.bits.b1
#define X22		cInputVal2.bits.b2
#define X23		cInputVal2.bits.b3
#define X24		cInputVal2.bits.b4
#define X25		cInputVal2.bits.b5
#define X26		cInputVal2.bits.b6
#define X27		cInputVal2.bits.b7
#define X30		cInputVal2.bits.b8
#define X31		cInputVal2.bits.b9
#define X32		cInputVal2.bits.b10
#define X33		cInputVal2.bits.b11
#define X34		cInputVal2.bits.b12
#define X35		cInputVal2.bits.b13
#define X36		cInputVal2.bits.b14
#define X37		cInputVal2.bits.b15

#define cOldInputX00_X17	cOldInputVal1.Val
#define OldX00	cOldInputVal1.bits.b0
#define OldX01	cOldInputVal1.bits.b1
#define OldX02	cOldInputVal1.bits.b2
#define OldX03	cOldInputVal1.bits.b3
#define OldX04	cOldInputVal1.bits.b4
#define OldX05	cOldInputVal1.bits.b5
#define OldX06	cOldInputVal1.bits.b6
#define OldX07	cOldInputVal1.bits.b7
#define OldX10	cOldInputVal1.bits.b8
#define OldX11	cOldInputVal1.bits.b9
#define OldX12	cOldInputVal1.bits.b10
#define OldX13	cOldInputVal1.bits.b11
#define OldX14	cOldInputVal1.bits.b12
#define OldX15	cOldInputVal1.bits.b13
#define OldX16	cOldInputVal1.bits.b14
#define OldX17	cOldInputVal1.bits.b15

#define cOldInputX20_X37	cOldInputVal2.Val
#define OldX20	cOldInputVal2.bits.b0
#define OldX21	cOldInputVal2.bits.b1
#define OldX22	cOldInputVal2.bits.b2
#define OldX23	cOldInputVal2.bits.b3
#define OldX24	cOldInputVal2.bits.b4
#define OldX25	cOldInputVal2.bits.b5
#define OldX26	cOldInputVal2.bits.b6
#define OldX27	cOldInputVal2.bits.b7
#define OldX30	cOldInputVal2.bits.b8
#define OldX31	cOldInputVal2.bits.b9
#define OldX32	cOldInputVal2.bits.b10
#define OldX33	cOldInputVal2.bits.b11
#define OldX34	cOldInputVal2.bits.b12
#define OldX35	cOldInputVal2.bits.b13
#define OldX36	cOldInputVal2.bits.b14
#define OldX37	cOldInputVal2.bits.b15

#define		OUT00			PORT2.DR.BIT.B4
#define		OUT01			PORT2.DR.BIT.B3
#define		OUT02			PORT2.DR.BIT.B2
#define		OUT03			PORT2.DR.BIT.B1
#define		OUT04			PORT2.DR.BIT.B0
#define		OUT05			PORT1.DR.BIT.B7
#define		OUT06			PORT1.DR.BIT.B6
#define		OUT07			PORT1.DR.BIT.B5
#define		OUT10			PORT1.DR.BIT.B4
#define		OUT11			PORT5.DR.BIT.B6
#define		OUT12			PORT5.DR.BIT.B5
#define		OUT13			PORT5.DR.BIT.B4
#define		OUT14			PORT5.DR.BIT.B2
#define		OUT15			PORT5.DR.BIT.B1
#define		OUT16			PORT5.DR.BIT.B0
#define		OUT17			PORTC.DR.BIT.B3

#define		OUT20			PORT7.DR.BIT.B7
#define		OUT21			PORT7.DR.BIT.B6
#define		OUT22			PORTC.DR.BIT.B2
#define		OUT23			PORT7.DR.BIT.B5
#define		OUT24			PORTA.DR.BIT.B1//SON1
#define		OUT25			PORTA.DR.BIT.B2//SON2
#define		OUT26			PORTA.DR.BIT.B0//SON3
#define		OUT27			PORT6.DR.BIT.B7//SON4

#define		OUT30			PORTA.DR.BIT.B7
#define		OUT31			PORTA.DR.BIT.B6
#define		OUT32			PORTA.DR.BIT.B5
#define		OUT33			PORTA.DR.BIT.B4

extern WORD_BITS cOutputVal1,cOutputVal2;
#define Y00		cOutputVal1.bits.b0
#define Y01		cOutputVal1.bits.b1
#define Y02		cOutputVal1.bits.b2
#define Y03		cOutputVal1.bits.b3
#define Y04		cOutputVal1.bits.b4
#define Y05		cOutputVal1.bits.b5
#define Y06		cOutputVal1.bits.b6
#define Y07		cOutputVal1.bits.b7
#define Y10		cOutputVal1.bits.b8
#define Y11		cOutputVal1.bits.b9
#define Y12		cOutputVal1.bits.b10
#define Y13		cOutputVal1.bits.b11
#define Y14		cOutputVal1.bits.b12
#define Y15		cOutputVal1.bits.b13
#define Y16		cOutputVal1.bits.b14
#define Y17		cOutputVal1.bits.b15

#define Y20		cOutputVal2.bits.b0
#define Y21		cOutputVal2.bits.b1
#define Y22		cOutputVal2.bits.b2
#define Y23		cOutputVal2.bits.b3
#define Y24		cOutputVal2.bits.b4
#define Y25		cOutputVal2.bits.b5
#define Y26		cOutputVal2.bits.b6
#define Y27		cOutputVal2.bits.b7
#define Y30		cOutputVal2.bits.b8
#define Y31		cOutputVal2.bits.b9
#define Y32		cOutputVal2.bits.b10
#define Y33		cOutputVal2.bits.b11
#define Y34		cOutputVal2.bits.b12
#define Y35		cOutputVal2.bits.b13
#define Y36		cOutputVal2.bits.b14
#define Y37		cOutputVal2.bits.b15

extern unsigned char InputFiltering[40];		//输入滤波寄存器
#define FILTERTIME_P		4			//正滤波次数
#define FILTERTIME_N		1			//负滤波次数
extern void ReadInput(void);
extern void TestOutput(void);
extern void WriteOutput(void);

#endif /* INOUT_H_ */
