
#include "Global.h"                     
#define  FM_SCLK_SET 	PORT1.DR.BIT.B2= 1
#define  FM_SDA_SET  	PORT1.DR.BIT.B3 = 1
#define  FM_SDA_IN	 	PORT1.DR.BIT.B3 = 1
#define  FM_SDA_OUT		PORT1.DR.BIT.B3 = 1

#define  FM_SCLK_CLR 	PORT1.DR.BIT.B2= 0
#define  FM_SDA_CLR  	PORT1.DR.BIT.B3 = 0

#define  FM_SDA     (PORT1.PORT.BIT.B3)
unsigned int regtemp;

#define DELAYTIME 20

void i2c_Delay(void);
void Stop(void);
void Start(void);
void NoAck(void);
unsigned char ReadByte24C04(void);
void WriteByte24C04(unsigned char value);

void i2c_Delay(void)
{
	unsigned char j;
    for(j = 0; j < DELAYTIME; j++);
	
}

void Stop(void)
{
    FM_SCLK_CLR;
    i2c_Delay();
	FM_SDA_OUT;
    FM_SDA_CLR;
    i2c_Delay();
	FM_SCLK_SET;
    i2c_Delay();
    FM_SDA_SET;
    i2c_Delay();
    FM_SCLK_CLR;
}

void Start(void)
{
    FM_SCLK_CLR;
    FM_SDA_OUT;
    FM_SDA_SET;
    i2c_Delay();
    FM_SCLK_SET;
    i2c_Delay();
    FM_SDA_CLR;
    i2c_Delay();
    FM_SCLK_CLR;
    i2c_Delay();
    FM_SDA_SET;
}

void NoAck(void)
{ 
	
    FM_SCLK_CLR;
    FM_SDA_OUT;    
    FM_SDA_SET;    
    i2c_Delay();
	FM_SCLK_SET;
    i2c_Delay();
    FM_SCLK_CLR;
    i2c_Delay();
}

unsigned char Read24C04(unsigned short addr)
{
	unsigned char dat=0;

	if(addr<=0xff)
	{
		Start();
		WriteByte24C04(0xa0);
		WriteByte24C04(addr);

		Start();
		WriteByte24C04(0xa1);
		dat = ReadByte24C04();
		NoAck();
		Stop();
	}
	else if((addr>0xff)&&(addr<=0x01ff))
	{
		Start();
		WriteByte24C04(0xa2);
		WriteByte24C04(addr-0x100);

		Start();
		WriteByte24C04(0xa3);
		dat = ReadByte24C04();
		NoAck();
		Stop();
	}
    return dat;
}

unsigned char ReadByte24C04(void)
{
    unsigned char i,value = 0;

	FM_SDA_IN;
	FM_SCLK_CLR;
    for(i = 0; i < 8; i++)
    {
        value <<= 1;
        FM_SCLK_SET;
	    i2c_Delay();
        if(FM_SDA != 0)
            value |= 0x1;
	    i2c_Delay();
		FM_SCLK_CLR;
	    i2c_Delay();
    }
    return value;
}

void Write24C04(unsigned short addr,unsigned char dat)
{                                                  
	Start();
	if(addr<=0xff)
	{
		WriteByte24C04(0xa0);
   		WriteByte24C04(addr);
		WriteByte24C04(dat);
	}
	else if((addr>0xff)&&(addr<=0x01ff))
	{
		WriteByte24C04(0xa2);
   		WriteByte24C04(addr-0x100);
		WriteByte24C04(dat);
	}
    Stop();
}

void WriteByte24C04(unsigned char value)
{
    unsigned int i;

	FM_SDA_OUT;
    for(i = 0; i < 8; i++)
    {
        FM_SCLK_CLR;
	    i2c_Delay();
        if(value & 0x80)
            FM_SDA_SET;
        else
            FM_SDA_CLR;
        value <<= 1;
        FM_SCLK_SET;
	    i2c_Delay();
    }
    FM_SCLK_CLR;
    i2c_Delay();
	FM_SDA_IN;
    FM_SDA_SET;
    i2c_Delay();
	FM_SCLK_SET;
    i2c_Delay();
    FM_SCLK_CLR;
    i2c_Delay();
    i = 5000;
    while(i > 0)
    {
        if(FM_SDA != 0)
            break;
        i--;
    }
}                               
