#ifndef SPIFLASH_H
#define SPIFLASH_H

#define   FLASH_BSY    0x01
#define   FLASH_RDY    0x01
#define   FLASH_WEL    0x02
#define   FLASH_SWP    0x0C
#define   FLASH_WPP    0x10
#define   FLASH_EPE    0x20
#define   FLASH_SPM    0x40
#define   FLASH_SPRL   0x80

extern unsigned char FlashErase (const unsigned long address, const unsigned char size);
extern unsigned char FlashReadData (const unsigned long address, unsigned char *data, const unsigned long size);
extern unsigned char FlashWriteData (unsigned long address, unsigned char const *data, unsigned long size);
extern unsigned char FlashReadStatus (void);

extern void ReadPage (unsigned long ReadAddr, unsigned short *pBuffer);
extern unsigned short ProgramPage (unsigned long WriteAddr, unsigned short *pBuffer);
extern unsigned short EraseSector (unsigned long BlockAddr);
extern unsigned char BackupProgramPage(unsigned long WriteAddr, unsigned short *pBuffer);
extern unsigned char BackupReadPage (unsigned long ReadAddr, unsigned short *pBuffer);
#endif 