/*
 * modusASC.h
 *
 *  Created on: 2011-10-14
 *      Author: lenovo
 */

#ifndef MODUSASC_H_
#define MODUSASC_H_

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long  uint32;
//typedef unsigned int   BOOL;

#define MB_NO_ERR					0x00
#define ILLEGAL_FUNCTION			0x01
#define ILLEGAL_DATA_ADDR			0x02
#define ILLEGAL_DATA_VALUE			0x03
#define SLAVE_DEVICE_FAILURE		0x04
#define ACKNOWLEDGE					0x05
#define SLAVE_DEVICE_BUSY			0x06
#define MEMORY_PARITY_ERR			0x08
#define GATEWAY_PATH_UNABLE			0x0A
#define GATEWAY_TARGET_DEV_FAIL		0x0B

#define MB_FUN_NOT_DEF				0x80
#define MB_MASTER_BUSY				0x81
#define MB_MASTER_IDLE				0x82
#define MB_RESPONSE_TIME_OUT		0x82
#define MB_PARAMETER_ERR			0x83

#define MEMSIZE		512
extern BYTE_BITS cMidleCoil[50];
extern unsigned short cDataArea[MEMSIZE];

#define	M00		cMidleCoil[0].bits.b0
#define	M01		cMidleCoil[0].bits.b1
#define	M02		cMidleCoil[0].bits.b2
#define	M03		cMidleCoil[0].bits.b3
#define	M04		cMidleCoil[0].bits.b4
#define	M05		cMidleCoil[0].bits.b5
#define	M06		cMidleCoil[0].bits.b6
#define	M07		cMidleCoil[0].bits.b7

#define	M08		cMidleCoil[1].bits.b0
#define	M09		cMidleCoil[1].bits.b1
#define	M10		cMidleCoil[1].bits.b2
#define	M11		cMidleCoil[1].bits.b3
#define	M12		cMidleCoil[1].bits.b4
#define	M13		cMidleCoil[1].bits.b5
#define	M14		cMidleCoil[1].bits.b6
#define	M15		cMidleCoil[1].bits.b7

#define	M16		cMidleCoil[2].bits.b0
#define	M17		cMidleCoil[2].bits.b1
#define	M18		cMidleCoil[2].bits.b2
#define	M19		cMidleCoil[2].bits.b3
#define	M20		cMidleCoil[2].bits.b4
#define	M21		cMidleCoil[2].bits.b5
#define	M22		cMidleCoil[2].bits.b6
#define	M23		cMidleCoil[2].bits.b7

#define	M24		cMidleCoil[3].bits.b0
#define	M25		cMidleCoil[3].bits.b1
#define	M26		cMidleCoil[3].bits.b2
#define	M27		cMidleCoil[3].bits.b3
#define	M28		cMidleCoil[3].bits.b4
#define	M29		cMidleCoil[3].bits.b5
#define	M30		cMidleCoil[3].bits.b6
#define	M31		cMidleCoil[3].bits.b7

#define	M32		cMidleCoil[4].bits.b0
#define	M33		cMidleCoil[4].bits.b1
#define	M34		cMidleCoil[4].bits.b2
#define	M35		cMidleCoil[4].bits.b3
#define	M36		cMidleCoil[4].bits.b4
#define	M37		cMidleCoil[4].bits.b5
#define	M38		cMidleCoil[4].bits.b6
#define	M39		cMidleCoil[4].bits.b7

#define	M40		cMidleCoil[5].bits.b0
#define	M41		cMidleCoil[5].bits.b1
#define	M42		cMidleCoil[5].bits.b2
#define	M43		cMidleCoil[5].bits.b3
#define	M44		cMidleCoil[5].bits.b4
#define	M45		cMidleCoil[5].bits.b5
#define	M46		cMidleCoil[5].bits.b6
#define	M47		cMidleCoil[5].bits.b7

#define	M48		cMidleCoil[6].bits.b0
#define	M49		cMidleCoil[6].bits.b1
#define	M50		cMidleCoil[6].bits.b2
#define	M51		cMidleCoil[6].bits.b3
#define	M52		cMidleCoil[6].bits.b4
#define	M53		cMidleCoil[6].bits.b5
#define	M54		cMidleCoil[6].bits.b6
#define	M55		cMidleCoil[6].bits.b7

#define	M56		cMidleCoil[7].bits.b0
#define	M57		cMidleCoil[7].bits.b1
#define	M58		cMidleCoil[7].bits.b2
#define	M59		cMidleCoil[7].bits.b3
#define	M60		cMidleCoil[7].bits.b4
#define	M61		cMidleCoil[7].bits.b5
#define	M62		cMidleCoil[7].bits.b6
#define	M63		cMidleCoil[7].bits.b7

#define	M64		cMidleCoil[8].bits.b0
#define	M65		cMidleCoil[8].bits.b1
#define	M66		cMidleCoil[8].bits.b2
#define	M67		cMidleCoil[8].bits.b3
#define	M68		cMidleCoil[8].bits.b4
#define	M69		cMidleCoil[8].bits.b5
#define	M70		cMidleCoil[8].bits.b6
#define	M71		cMidleCoil[8].bits.b7

#define	M72		cMidleCoil[9].bits.b0
#define	M73		cMidleCoil[9].bits.b1
#define	M74		cMidleCoil[9].bits.b2
#define	M75		cMidleCoil[9].bits.b3
#define	M76		cMidleCoil[9].bits.b4
#define	M77		cMidleCoil[9].bits.b5
#define	M78		cMidleCoil[9].bits.b6
#define	M79		cMidleCoil[9].bits.b7

#define	M80		cMidleCoil[10].bits.b0
#define	M81		cMidleCoil[10].bits.b1
#define	M82		cMidleCoil[10].bits.b2
#define	M83		cMidleCoil[10].bits.b3
#define	M84		cMidleCoil[10].bits.b4
#define	M85		cMidleCoil[10].bits.b5
#define	M86		cMidleCoil[10].bits.b6
#define	M87		cMidleCoil[10].bits.b7

#define	M88		cMidleCoil[11].bits.b0
#define	M89		cMidleCoil[11].bits.b1
#define	M90		cMidleCoil[11].bits.b2
#define	M91		cMidleCoil[11].bits.b3
#define	M92		cMidleCoil[11].bits.b4
#define	M93		cMidleCoil[11].bits.b5
#define	M94		cMidleCoil[11].bits.b6
#define	M95		cMidleCoil[11].bits.b7

#define	M96			cMidleCoil[12].bits.b0
#define	M97			cMidleCoil[12].bits.b1
#define	M98			cMidleCoil[12].bits.b2
#define	M99			cMidleCoil[12].bits.b3
#define	M100		cMidleCoil[12].bits.b4
#define	M101		cMidleCoil[12].bits.b5
#define	M102		cMidleCoil[12].bits.b6
#define	M103		cMidleCoil[12].bits.b7

#define	M104		cMidleCoil[13].bits.b0
#define	M105		cMidleCoil[13].bits.b1
#define	M106		cMidleCoil[13].bits.b2
#define	M107		cMidleCoil[13].bits.b3
#define	M108		cMidleCoil[13].bits.b4
#define	M109		cMidleCoil[13].bits.b5
#define	M110		cMidleCoil[13].bits.b6
#define	M111		cMidleCoil[13].bits.b7

#define	M112		cMidleCoil[14].bits.b0
#define	M113		cMidleCoil[14].bits.b1
#define	M114		cMidleCoil[14].bits.b2
#define	M115		cMidleCoil[14].bits.b3
#define	M116		cMidleCoil[14].bits.b4
#define	M117		cMidleCoil[14].bits.b5
#define	M118		cMidleCoil[14].bits.b6
#define	M119		cMidleCoil[14].bits.b7

#define	M120		cMidleCoil[15].bits.b0
#define	M121		cMidleCoil[15].bits.b1
#define	M122		cMidleCoil[15].bits.b2
#define	M123		cMidleCoil[15].bits.b3
#define	M124		cMidleCoil[15].bits.b4
#define	M125		cMidleCoil[15].bits.b5
#define	M126		cMidleCoil[15].bits.b6
#define	M127		cMidleCoil[15].bits.b7



#define	M128		cMidleCoil[16].bits.b0
#define	M129		cMidleCoil[16].bits.b1
#define	M130		cMidleCoil[16].bits.b2
#define	M131		cMidleCoil[16].bits.b3
#define	M132		cMidleCoil[16].bits.b4
#define	M133		cMidleCoil[16].bits.b5
#define	M134		cMidleCoil[16].bits.b6
#define	M135		cMidleCoil[16].bits.b7

#define	M136		cMidleCoil[17].bits.b0
#define	M137		cMidleCoil[17].bits.b1
#define	M138		cMidleCoil[17].bits.b2
#define	M139		cMidleCoil[17].bits.b3
#define	M140		cMidleCoil[17].bits.b4
#define	M141		cMidleCoil[17].bits.b5
#define	M142		cMidleCoil[17].bits.b6
#define	M143		cMidleCoil[17].bits.b7

#define	M144		cMidleCoil[18].bits.b0
#define	M145		cMidleCoil[18].bits.b1
#define	M146		cMidleCoil[18].bits.b2
#define	M147		cMidleCoil[18].bits.b3
#define	M148		cMidleCoil[18].bits.b4
#define	M149		cMidleCoil[18].bits.b5
#define	M150		cMidleCoil[18].bits.b6
#define	M151		cMidleCoil[18].bits.b7

#define	M152		cMidleCoil[19].bits.b0
#define	M153		cMidleCoil[19].bits.b1
#define	M154		cMidleCoil[19].bits.b2
#define	M155		cMidleCoil[19].bits.b3
#define	M156		cMidleCoil[19].bits.b4
#define	M157		cMidleCoil[19].bits.b5
#define	M158		cMidleCoil[19].bits.b6
#define	M159		cMidleCoil[19].bits.b7

#define	M160		cMidleCoil[20].bits.b0
#define	M161		cMidleCoil[20].bits.b1
#define	M162		cMidleCoil[20].bits.b2
#define	M163		cMidleCoil[20].bits.b3
#define	M164		cMidleCoil[20].bits.b4
#define	M165		cMidleCoil[20].bits.b5
#define	M166		cMidleCoil[20].bits.b6
#define	M167		cMidleCoil[20].bits.b7

#define	M168		cMidleCoil[21].bits.b0
#define	M169		cMidleCoil[21].bits.b1
#define	M170		cMidleCoil[21].bits.b2
#define	M171		cMidleCoil[21].bits.b3
#define	M172		cMidleCoil[21].bits.b4
#define	M173		cMidleCoil[21].bits.b5
#define	M174		cMidleCoil[21].bits.b6
#define	M175		cMidleCoil[21].bits.b7

#define	M256		cMidleCoil[32].bits.b0
#define	M257		cMidleCoil[32].bits.b1
#define	M258		cMidleCoil[32].bits.b2
#define	M259		cMidleCoil[32].bits.b3
#define	M260		cMidleCoil[32].bits.b4
#define	M261		cMidleCoil[32].bits.b5
#define	M262		cMidleCoil[32].bits.b6
#define	M263		cMidleCoil[32].bits.b7

//extern uint8 Modbus_CRC16(uint8 *Buff_addr,uint16 len);
extern uint8  CheckReceiveSum(void);
extern void CheckReceData(void);
extern void ReadCoil(void);
extern void ReadRegister(void);
extern void WriteCoil(void);
extern void WriteRegister(void);
extern void WriteMulRegister(void);
extern void TouchCommOK(void);




#endif /* MODUSASC_H_ */
