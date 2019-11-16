/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corp. and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corp. and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORP. NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THE THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/

/*********************************************************************************
FILE NAME      FlashSerial.c
DESCRIPTION:  This code acts as an interface to an external serial flash device.
The specific device tested is an Atmel 26F081A. This module relies upon having a
lower level interface to the MCU specific spi port. The functionality of this module
is independent of target MCU and only depends on the protocol of the Serial Flash.

Copyright   : 2007 Renesas Electronics Corporation.
All Rights Reserved
**********************************************************************************/
/**********************************************************************************
Revision History
DD.MM.YYYY OSO-UID Description
05.16.2007 RTA-JMB First Release
**********************************************************************************/
/**********************************************************************************
System Includes
***********************************************************************************/


/**********************************************************************************
User Includes
***********************************************************************************/
#include "SPIFlash.h"
#include "spi.h"
#include <string.h>

#define BASESIZE	256
#define PAGESIZE	4096

void WriteProtect (void);
void WriteUnprotect (void);
unsigned char comm;
/* ************************* Global variables ********************************/

/*****************************************************************************
Name:    WriteEnable
Arguments: none
Returns: none
Description: Performs a write enable command
*****************************************************************************/
static void WriteEnable (void)
{
  /* send write enable command */
  const unsigned char command = 0x6;

  /* Initialize peripheral for SPI */
  SPI_open();

  SPI_send_receive(&command, NULL, 1 );

  /* close peripheral for SPI */
  SPI_close();
}


/*****************************************************************************
Name:    WriteProtect
Arguments: None
Returns:  None
Description: Sets the Status Register Write Disable (SRWD) bit.
             Setting this bit locks the status register from being rewritten
       if the Write Protect pin is high.  If the pin is low, then the
       status register can be changed.
             You must set/clear the Block Protect Bits at this time too.

*****************************************************************************/
void WriteProtect (void)
{
  unsigned char command[3];

  /* send write enable command */
  WriteEnable();

  /* Initialize peripheral for SPI */
  SPI_open();

  /*  This section writes data.  The first character is the write command */
  command[0] = 0x1;
  command[1] = 0x02;
  command[2] = 0x0;
  SPI_send_receive(command, NULL, 3 );

  /* close peripheral for SPI */
  SPI_close();
}

/*****************************************************************************
Name:    WriteUnprotect
Arguments: None
Returns:  None
Description: Clears the Status Register Write Disable (SRWD) bit, if the Write
             Protect pin is high.
             Clearing this bit unlocks the status register for rewriting.
       The Write Protect pin must be high to clear the SRWD bit.
             You can set/clear the Block Protect Bits at this time too.

*****************************************************************************/
void WriteUnprotect (void)
{
  unsigned char command[3];

  /* send write enable command */
  WriteEnable();

  /* Initialize peripheral for SPI */
  SPI_open();

  /*  This section writes data.  The first character is the write command */
  command[0] = 0x1;
  command[1] = 0x80;
  command[1] = 0x0;
  SPI_send_receive(command, NULL, 3 );

  /* close peripheral for SPI */
  SPI_close();
}

/*****************************************************************************
Name:    FlashEraseSector
Arguments: Address: address of sector to erase
            size: 0=4K, 1=32K, 2=64K, 3 = chip
Returns: Success/Failure: 0=success, not 0= failure
Description: Performs a 4k erase at address
*****************************************************************************/
static const unsigned char erase_commands[]={0x20, 0x52, 0xD8, 0xC7};
unsigned char FlashErase (const unsigned long address, const unsigned char size)
{
  unsigned char command[4];
  /* allow memory to be modified */
  //WriteUnprotect();
  /* send write enable command */
  WriteEnable();
  /* Initialize peripheral for SPI */
  SPI_open();

  /* 4k erase command */
  command[0] = erase_commands[size];
  command[1] = (unsigned char)(address >> 16);
  command[2] = (unsigned char)(address >>  8);
  command[3] = (unsigned char)(address >>  0);
  SPI_send_receive(command, NULL, 4 );
  /* close peripheral for SPI */
  SPI_close();

  /* protect memory from modification */
// WriteProtect();
  /* check status to make sure previous operation completed */
  while ((FlashReadStatus()& FLASH_BSY) == FLASH_BSY) 
  ;
  return(0);
}

/*****************************************************************************
Name:    FlashWriteData
Arguments: address: Target address to write to.
            data: Location to retrieve data to write.
            size: Amount of data to write.
Returns: Success/Failure: 0=success, not 0= failure
Description: Writes data to the external flash (up to 256 bytes)
*****************************************************************************/
unsigned char FlashWriteData (unsigned long address, unsigned char const *data, unsigned long size)
{
  unsigned char command[6];
  /* allow memory to be modified */
  //WriteUnprotect();
    /* send write enable command */
    WriteEnable();
    /*  This section writes data.  The first character is the write command */
    SPI_open();
    command[0] = 0x02;
    command[1] = (unsigned char)(address >> 16);
    command[2] = (unsigned char)(address >>  8);
    command[3] = (unsigned char)(address >>  0);
   SPI_send_receive(command, NULL, 4 );

   SPI_send_receive(data, NULL, size);    
  /* protect memory from modification */
  SPI_close();
  //WriteProtect();
   comm=FlashReadStatus();
   /* check status to make sure previous operation completed */
  while ((FlashReadStatus()& FLASH_BSY) == FLASH_BSY)
  ;
  return(0);
}

/*****************************************************************************
Name:    FlashReadData
Arguments: address: Target address to read from.
            data: Location to place read data.
            size: Amount of data to read.
Returns: Success/Failure: 0=success, not 0= failure
Description: Performs a read of the external flash to specified buffer.
*****************************************************************************/
unsigned char FlashReadData (const unsigned long address, unsigned char *data, const unsigned long size)
{
  unsigned char command[4];

  /* Initialize peripheral for SPI */
  SPI_open();

  /*  This section reads back data.  The first character is the read command */
  command[0] = 0x3;
  command[1] = (unsigned char)(address >> 16);
  command[2] = (unsigned char)(address >>  8);
  command[3] = (unsigned char)(address >>  0);
  SPI_send_receive(command, NULL, 4 );

  SPI_send_receive( NULL, data, size );

  /* close peripheral for SPI */
  SPI_close();
  return(0);
}

/*****************************************************************************
Name:    FlashReadStatus
Arguments: None
Returns:  status response
Description: Reads flash status register and returns.
*****************************************************************************/
unsigned char FlashReadStatus (void)
{
  unsigned char command;

  /* Initialize peripheral for SPI */
  SPI_open();

  command = 0x05;
  SPI_send_receive( &command, NULL, 1);
  SPI_send_receive( NULL, &command, 1);

  /* close peripheral for SPI */
  SPI_close();

  return(command);
}
/*****************************************************************************
读取页数据
*****************************************************************************/
void ReadPage (unsigned long ReadAddr, unsigned short *pBuffer)
{
	unsigned short i;
	unsigned char bufftmp[BASESIZE];
	unsigned long addrtmp;
	addrtmp=(ReadAddr/PAGESIZE)*PAGESIZE;
	for(i=0;i<PAGESIZE/BASESIZE;i++)
	{
		FlashReadData(addrtmp+i*BASESIZE, bufftmp, BASESIZE);
		memcpy(pBuffer+i*(BASESIZE/2),bufftmp,BASESIZE);
	}
}
/*****************************************************************************
写入页数据
*****************************************************************************/
unsigned short ProgramPage (unsigned long WriteAddr, unsigned short *pBuffer)
{
	unsigned short i;
	unsigned char bufftmp[BASESIZE];
	unsigned long addrtmp;
	addrtmp=(WriteAddr/PAGESIZE)*PAGESIZE;
	for(i=0;i<PAGESIZE/BASESIZE;i++)
	{
		memcpy(bufftmp,pBuffer+i*(BASESIZE/2),BASESIZE);
		FlashWriteData(addrtmp+i*BASESIZE, bufftmp, BASESIZE);		
	}
	return (0);
}
/*****************************************************************************
擦除页数据
*****************************************************************************/
unsigned short EraseSector (unsigned long BlockAddr)
{
	unsigned long addrtmp;
	addrtmp=(BlockAddr/PAGESIZE)*PAGESIZE;
	FlashErase(addrtmp, 0);
	return (0);
}
/*****************************************************************************
CRC校验
*****************************************************************************/
/*CRC 表格*/
static unsigned char  crc_table_hi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};
//
static unsigned char crc_table_lo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40

};
/**
 * 校验CRC
 * 
 * @Author LXZ (2016/5/26)
 * 
 * @param src 
 * @param length 
 * 
 * @return unsigned short 
 */
 //
static unsigned short crc_calc(void *src, int length) {
    unsigned char lo = 0xff, hi = 0xff;
    unsigned char index = 0;
    unsigned char *ptr = (unsigned char *)src;

    while (length > 0) {
        length--;
        index = hi ^ (*ptr);
        hi = lo ^ crc_table_hi[index];
        lo = crc_table_lo[index];
        ptr++;
    }
    return 0x0100 * lo + hi;
}
/*****************************************************************************
带备份的的Flash写
*****************************************************************************/
unsigned char BackupProgramPage(unsigned long WriteAddr, unsigned short *pBuffer)
{
	unsigned char Flag=1;
	unsigned short crctmp1;
	pBuffer[2046]=0xa5a5;
	crctmp1 = crc_calc(pBuffer, PAGESIZE - 2);
	pBuffer[2047]=crctmp1;
	EraseSector(WriteAddr);
	ProgramPage(WriteAddr, pBuffer);
	ReadPage(WriteAddr, pBuffer);
	crctmp1 = crc_calc(pBuffer, PAGESIZE );
	if((crctmp1!=0)||(pBuffer[2045]==0xffff))
	{
		Flag=0;
	}
	else
	{
		EraseSector(WriteAddr+4096);
		ProgramPage(WriteAddr+4096, pBuffer);
		ReadPage(WriteAddr+4096, pBuffer);
		crctmp1 = crc_calc(pBuffer, PAGESIZE);
		if(crctmp1!=0)
		{			
			Flag=0;
		}
	}
	return Flag;	
}
/*****************************************************************************
带备份的的Flash读
*****************************************************************************/
unsigned char BackupReadPage (unsigned long ReadAddr, unsigned short *pBuffer)
{
	unsigned char Flag=1;
	unsigned short crctmp1;
	ReadPage(ReadAddr, pBuffer);
	crctmp1 = crc_calc(pBuffer, PAGESIZE);
	if(((crctmp1!=0)&&(pBuffer[2046]!=0xa5a5))||(pBuffer[2045]==0xffff))
	{
		ReadPage(ReadAddr+4096, pBuffer);
		crctmp1 = crc_calc(pBuffer, PAGESIZE);
		if(crctmp1!=0)
		{
			Flag=0;
		}
		else
		{
			EraseSector(ReadAddr);
			ProgramPage(ReadAddr, pBuffer);
		}
	}
	else if((crctmp1==0)&&(pBuffer[2046]==0xa5a5))
	{
		EraseSector(ReadAddr+4096);
		ProgramPage(ReadAddr+4096, pBuffer);
	}
	return Flag;	
}