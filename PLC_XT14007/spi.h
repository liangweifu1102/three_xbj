/******************************************************************************
* DISCLAIMER
* Please refer to http://www.renesas.com/disclaimer
******************************************************************************/
#ifndef NULL
#define NULL	0
#endif

/*****************************************************************************
Name:    SPI_open
Arguments:  None
Returns:  None
Description: Configure uart0 for SPI, Mode 3, assert slave select
*****************************************************************************/
void SPI_open(void);

/*****************************************************************************
Name:    SPI_close
Arguments:  None
Returns:  None
Description: Disable UART 0 for SPI and disable slave select
*****************************************************************************/
void SPI_close(void);

/*****************************************************************************
Name:        SPI_send_receive
Arguments:
      pSrc - pointer to data buffer with data to be transmitted.
      pDest - pointer to location to put the received data (can be same as pSrc if desired)
      usBytes - number of bytes to be sent/received
Returns:     none
Description: Performs SPI transfers. The slave_select of the device is brought
             low prior to the serial data transfers and brought high afterwards.
*****************************************************************************/
void SPI_send_receive(unsigned char const *pSrc, unsigned char *pDest, unsigned long usBytes );
