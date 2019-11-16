/*
 * uart.h
 *
 *  Created on: 2011-9-28
 *      Author: lenovo
 */

#ifndef UART_H_
#define UART_H_

#define UART0_USE	(0)
#define UART1_USE	(0)
#define UART2_USE	(0)
#define UART3_USE	(0)
#define UART5_USE	(0)
#define UART6_USE	(1)

#define BAUD_FREQ	9600

#define RX_STATE_SD1	':'
#define RX_STATE_END1	0x0d
#define RX_STATE_END2	0x0a
#define	TX_STATE_SD1	':'
#define TX_STATE_END1	0x0d
#define TX_STATE_END2	0x0a

#define RX_START		0
#define RX_END1			1
#define RX_END2			2



#define Enableb485Tx()	PORT2.DR.BIT.B5 = 1
#define Enableb485Rx()	PORT2.DR.BIT.B5 = 0

//#define Enableb485Tx_Uart1()	PORT2.DR.BIT.B5 = 1
//#define Enableb485Rx_Uart1()	PORT2.DR.BIT.B5 = 0


#define		RX_BUFFER_NUM  256
#define		TX_BUFFER_NUM  256

typedef struct
{
	unsigned short cRxTimeOut;
	unsigned short cRxOK;
	unsigned short TxLen;
	unsigned short TxPosi;
	unsigned short RxPosi;
	unsigned char RxBuf[RX_BUFFER_NUM];
	unsigned char TxBuf[TX_BUFFER_NUM];
} SCI0DataInfo;

extern SCI0DataInfo SCI0Data;
extern unsigned short bTxEnd,bTxEnd_Uart1;
extern unsigned short cTxOKTimer;
extern unsigned short cEnableRxDelay;

extern void UartInit(unsigned int  baud_rate);
extern void SCI6_TxIntDis (void);
extern void SCI6_TxIntEn (void);
extern void SCI6_RxIntDis (void);
extern void SCI6_RxIntEn (void);
extern void  SCI6_TxStart (void);
extern void	SendBackRxBuf(void);
#endif /* UART_H_ */
