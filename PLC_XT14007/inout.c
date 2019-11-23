/*
 * inout.c
 *
 *  Created on: 2011-9-24
 *      Author: lenovo
 */
#include "Global.h"
WORD_BITS cInputVal1,cOldInputVal1;
WORD_BITS cInputVal2,cOldInputVal2;
WORD_BITS cOutputVal1;
WORD_BITS cOutputVal2;
unsigned char InputFiltering[40];				//ÊäÈëÂË²¨¼Ä´æÆ÷

void ReadInput(void)
{	
	if(I000)
	{
		InputFiltering[0]++;
		if(InputFiltering[0]>=FILTERTIME_P)
		{
			InputFiltering[0]=FILTERTIME_P;
			OldX00=X00;
			X00=1;
		}
	}
	else
	{
		if(InputFiltering[0])
		{
			InputFiltering[0]--;
		}
		if(InputFiltering[0]<=FILTERTIME_N)
		{
			InputFiltering[0]=0;
			OldX00=X00;
			X00=0;
		}
	}
	//
	if(I001)
	{
		InputFiltering[1]++;
		if(InputFiltering[1]>=FILTERTIME_P)
		{
			InputFiltering[1]=FILTERTIME_P;
			OldX01=X01;
			X01=1;
		}
	}
	else
	{
		if(InputFiltering[1])
		{
			InputFiltering[1]--;
		}
		if(InputFiltering[1]<=FILTERTIME_N)
		{
			InputFiltering[1]=0;
			OldX01=X01;
			X01=0;
		}
	}
	//
	if(I002)
	{
		InputFiltering[2]++;
		if(InputFiltering[2]>=FILTERTIME_P)
		{
			InputFiltering[2]=FILTERTIME_P;
			OldX02=X02;
			X02=1;
		}
	}
	else
	{
		if(InputFiltering[2])
		{
			InputFiltering[2]--;
		}
		if(InputFiltering[2]<=FILTERTIME_N)
		{
			InputFiltering[2]=0;
			OldX02=X02;
			X02=0;
		}
	}
	//
	if(I003)
	{
		InputFiltering[3]++;
		if(InputFiltering[3]>=FILTERTIME_P)
		{
			InputFiltering[3]=FILTERTIME_P;
			OldX03=X03;
			X03=1;
		}
	}
	else
	{
		if(InputFiltering[3])
		{
			InputFiltering[3]--;
		}
		if(InputFiltering[3]<=FILTERTIME_N)
		{
			InputFiltering[3]=0;
			OldX03=X03;
			X03=0;
		}
	}
	//
	if(I004)
	{
		InputFiltering[4]++;
		if(InputFiltering[4]>=FILTERTIME_P)
		{
			InputFiltering[4]=FILTERTIME_P;
			OldX04=X04;
			X04=1;
		}
	}
	else
	{
		if(InputFiltering[4])
		{
			InputFiltering[4]--;
		}
		if(InputFiltering[4]<=FILTERTIME_N)
		{
			InputFiltering[4]=0;
			OldX04=X04;
			X04=0;
		}
	}
	//
	if(I005)
	{
		InputFiltering[5]++;
		if(InputFiltering[5]>=FILTERTIME_P)
		{
			InputFiltering[5]=FILTERTIME_P;
			OldX05=X05;
			X05=1;
		}
	}
	else
	{
		if(InputFiltering[5])
		{
			InputFiltering[5]--;
		}
		if(InputFiltering[5]<=FILTERTIME_N)
		{
			InputFiltering[5]=0;
			OldX05=X05;
			X05=0;
		}
	}
	//
	if(I006)
	{
		InputFiltering[6]++;
		if(InputFiltering[6]>=FILTERTIME_P)
		{
			InputFiltering[6]=FILTERTIME_P;
			OldX06=X06;
			X06=1;
		}
	}
	else
	{
		if(InputFiltering[6])
		{
			InputFiltering[6]--;
		}
		if(InputFiltering[6]<=FILTERTIME_N)
		{
			InputFiltering[6]=0;
			OldX06=X06;
			X06=0;
		}
	}
	//
	if(I007)
	{
		InputFiltering[7]++;
		if(InputFiltering[7]>=FILTERTIME_P)
		{
			InputFiltering[7]=FILTERTIME_P;
			OldX07=X07;
			X07=1;
		}
	}
	else
	{
		if(InputFiltering[7])
		{
			InputFiltering[7]--;
		}
		if(InputFiltering[7]<=FILTERTIME_N)
		{
			InputFiltering[7]=0;
			OldX07=X07;
			X07=0;
		}
	}
	//
	if(I010)
	{
		InputFiltering[10]++;
		if(InputFiltering[10]>=FILTERTIME_P)
		{
			InputFiltering[10]=FILTERTIME_P;
			OldX10=X10;
			X10=1;
		}
	}
	else
	{
		if(InputFiltering[10])
		{
			InputFiltering[10]--;
		}
		if(InputFiltering[10]<=FILTERTIME_N)
		{
			InputFiltering[10]=0;
			OldX10=X10;
			X10=0;
		}
	}
	//
	if(I011)
	{
		InputFiltering[11]++;
		if(InputFiltering[11]>=FILTERTIME_P)
		{
			InputFiltering[11]=FILTERTIME_P;
			OldX11=X11;
			X11=1;
		}
	}
	else
	{
		if(InputFiltering[11])
		{
			InputFiltering[11]--;
		}
		if(InputFiltering[11]<=FILTERTIME_N)
		{
			InputFiltering[11]=0;
			OldX11=X11;
			X11=0;
		}
	}
	//
	if(I012)
	{
		InputFiltering[12]++;
		if(InputFiltering[12]>=FILTERTIME_P)
		{
			InputFiltering[12]=FILTERTIME_P;
			OldX12=X12;
			X12=1;
		}
	}
	else
	{
		if(InputFiltering[12])
		{
			InputFiltering[12]--;
		}
		if(InputFiltering[12]<=FILTERTIME_N)
		{
			InputFiltering[12]=0;
			OldX12=X12;
			X12=0;
		}
	}
	//
	if(I013)
	{
		InputFiltering[13]++;
		if(InputFiltering[13]>=FILTERTIME_P)
		{
			InputFiltering[13]=FILTERTIME_P;
			OldX13=X13;
			X13=1;
		}
	}
	else
	{
		if(InputFiltering[13])
		{
			InputFiltering[13]--;
		}
		if(InputFiltering[13]<=FILTERTIME_N)
		{
			InputFiltering[13]=0;
			OldX13=X13;
			X13=0;
		}
	}
	//
	if(I014)
	{
		InputFiltering[14]++;
		if(InputFiltering[14]>=FILTERTIME_P)
		{
			InputFiltering[14]=FILTERTIME_P;
			OldX14=X14;
			X14=1;
		}
	}
	else
	{
		if(InputFiltering[14])
		{
			InputFiltering[14]--;
		}
		if(InputFiltering[14]<=FILTERTIME_N)
		{
			InputFiltering[14]=0;
			OldX14=X14;
			X14=0;
		}
	}
	//
	if(I015)
	{
		InputFiltering[15]++;
		if(InputFiltering[15]>=FILTERTIME_P)
		{
			InputFiltering[15]=FILTERTIME_P;
			OldX15=X15;
			X15=1;
		}
	}
	else
	{
		if(InputFiltering[15])
		{
			InputFiltering[15]--;
		}
		if(InputFiltering[15]<=FILTERTIME_N)
		{
			InputFiltering[15]=0;
			OldX15=X15;
			X15=0;
		}
	}
	if(I016)
	{
		InputFiltering[16]++;
		if(InputFiltering[16]>=FILTERTIME_P)
		{
			InputFiltering[16]=FILTERTIME_P;
			OldX16=X16;
			X16=1;
		}
	}
	else
	{
		if(InputFiltering[16])
		{
			InputFiltering[16]--;
		}
		if(InputFiltering[16]<=FILTERTIME_N)
		{
			InputFiltering[16]=0;
			OldX16=X16;
			X16=0;
		}
	}
	//
	if(I017)
	{
		InputFiltering[17]++;
		if(InputFiltering[17]>=FILTERTIME_P)
		{
			InputFiltering[17]=FILTERTIME_P;
			OldX17=X17;
			X17=1;
		}
	}
	else
	{
		if(InputFiltering[17])
		{
			InputFiltering[17]--;
		}
		if(InputFiltering[17]<=FILTERTIME_N)
		{
			InputFiltering[17]=0;
			OldX17=X17;
			X17=0;
		}
	}
	if(I020)
	{
		InputFiltering[20]++;
		if(InputFiltering[20]>=FILTERTIME_P)
		{
			InputFiltering[20]=FILTERTIME_P;
			OldX20=X20;
			X20=1;
		}
	}
	else
	{
		if(InputFiltering[20])
		{
			InputFiltering[20]--;
		}
		if(InputFiltering[20]<=FILTERTIME_N)
		{
			InputFiltering[20]=0;
			OldX20=X20;
			X20=0;
		}
	}
	//
	if(I021)
	{
		InputFiltering[21]++;
		if(InputFiltering[21]>=FILTERTIME_P)
		{
			InputFiltering[21]=FILTERTIME_P;
			OldX21=X21;
			X21=1;
		}
	}
	else
	{
		if(InputFiltering[21])
		{
			InputFiltering[21]--;
		}
		if(InputFiltering[21]<=FILTERTIME_N)
		{
			InputFiltering[21]=0;
			OldX21=X21;
			X21=0;
		}
	}
	//
	if(I022)
	{
		InputFiltering[22]++;
		if(InputFiltering[22]>=FILTERTIME_P)
		{
			InputFiltering[22]=FILTERTIME_P;
			OldX22=X22;
			X22=1;
		}
	}
	else
	{
		if(InputFiltering[22])
		{
			InputFiltering[22]--;
		}
		if(InputFiltering[22]<=FILTERTIME_N)
		{
			InputFiltering[22]=0;
			OldX22=X22;
			X22=0;
		}
	}
	//
	if(I023)
	{
		InputFiltering[23]++;
		if(InputFiltering[23]>=FILTERTIME_P)
		{
			InputFiltering[23]=FILTERTIME_P;
			OldX23=X23;
			X23=1;
		}
	}
	else
	{
		if(InputFiltering[23])
		{
			InputFiltering[23]--;
		}
		if(InputFiltering[23]<=FILTERTIME_N)
		{
			InputFiltering[23]=0;
			OldX23=X23;
			X23=0;
		}
	}
	//
	if(I024)
	{
		InputFiltering[24]++;
		if(InputFiltering[24]>=FILTERTIME_P)
		{
			InputFiltering[24]=FILTERTIME_P;
			OldX24=X24;
			X24=1;
		}
	}
	else
	{
		if(InputFiltering[24])
		{
			InputFiltering[24]--;
		}
		if(InputFiltering[24]<=FILTERTIME_N)
		{
			InputFiltering[24]=0;
			OldX24=X24;
			X24=0;
		}
	}
	//
	if(I025)
	{
		InputFiltering[25]++;
		if(InputFiltering[25]>=FILTERTIME_P)
		{
			InputFiltering[25]=FILTERTIME_P;
			OldX25=X25;
			X25=1;
		}
	}
	else
	{
		if(InputFiltering[25])
		{
			InputFiltering[25]--;
		}
		if(InputFiltering[25]<=FILTERTIME_N)
		{
			InputFiltering[25]=0;
			OldX25=X25;
			X25=0;
		}
	}
	//
	if(I026)
	{
		InputFiltering[26]++;
		if(InputFiltering[26]>=FILTERTIME_P)
		{
			InputFiltering[26]=FILTERTIME_P;
			OldX26=X26;
			X26=1;
		}
	}
	else
	{
		if(InputFiltering[26])
		{
			InputFiltering[26]--;
		}
		if(InputFiltering[26]<=FILTERTIME_N)
		{
			InputFiltering[26]=0;
			OldX26=X26;
			X26=0;
		}
	}
	//
	if(I027)
	{
		InputFiltering[27]++;
		if(InputFiltering[27]>=FILTERTIME_P)
		{
			InputFiltering[27]=FILTERTIME_P;
			OldX27=X27;
			X27=1;
		}
	}
	else
	{
		if(InputFiltering[27])
		{
			InputFiltering[27]--;
		}
		if(InputFiltering[27]<=FILTERTIME_N)
		{
			InputFiltering[27]=0;
			OldX27=X27;
			X27=0;
		}
	}
	//
	if(I030)
	{
		InputFiltering[30]++;
		if(InputFiltering[30]>=FILTERTIME_P)
		{
			InputFiltering[30]=FILTERTIME_P;
			OldX30=X30;
			X30=1;
		}
	}
	else
	{
		if(InputFiltering[30])
		{
			InputFiltering[30]--;
		}
		if(InputFiltering[30]<=FILTERTIME_N)
		{
			InputFiltering[30]=0;
			OldX30=X30;
			X30=0;
		}
	}
	//
	if(I031)
	{
		InputFiltering[31]++;
		if(InputFiltering[31]>=FILTERTIME_P)
		{
			InputFiltering[31]=FILTERTIME_P;
			OldX31=X31;
			X31=1;
		}
	}
	else
	{
		if(InputFiltering[31])
		{
			InputFiltering[31]--;
		}
		if(InputFiltering[31]<=FILTERTIME_N)
		{
			InputFiltering[31]=0;
			OldX31=X31;
			X31=0;
		}
	}
	//
	if(I032)
	{
		InputFiltering[32]++;
		if(InputFiltering[32]>=FILTERTIME_P)
		{
			InputFiltering[32]=FILTERTIME_P;
			OldX32=X32;
			X32=1;
		}
	}
	else
	{
		if(InputFiltering[32])
		{
			InputFiltering[32]--;
		}
		if(InputFiltering[32]<=FILTERTIME_N)
		{
			InputFiltering[32]=0;
			OldX32=X32;
			X32=0;
		}
	}
	//
	if(I033)
	{
		InputFiltering[33]++;
		if(InputFiltering[33]>=FILTERTIME_P)
		{
			InputFiltering[33]=FILTERTIME_P;
			OldX33=X33;
			X33=1;
		}
	}
	else
	{
		if(InputFiltering[33])
		{
			InputFiltering[33]--;
		}
		if(InputFiltering[33]<=FILTERTIME_N)
		{
			InputFiltering[33]=0;
			OldX33=X33;
			X33=0;
		}
	}
	//
	if(I034)
	{
		InputFiltering[34]++;
		if(InputFiltering[34]>=FILTERTIME_P)
		{
			InputFiltering[34]=FILTERTIME_P;
			OldX34=X34;
			X34=1;
		}
	}
	else
	{
		if(InputFiltering[34])
		{
			InputFiltering[34]--;
		}
		if(InputFiltering[34]<=FILTERTIME_N)
		{
			InputFiltering[34]=0;
			OldX14=X34;
			X34=0;
		}
	}
	//
	if(I035)
	{
		InputFiltering[35]++;
		if(InputFiltering[35]>=FILTERTIME_P)
		{
			InputFiltering[35]=FILTERTIME_P;
			OldX35=X35;
			X35=1;
		}
	}
	else
	{
		if(InputFiltering[35])
		{
			InputFiltering[35]--;
		}
		if(InputFiltering[35]<=FILTERTIME_N)
		{
			InputFiltering[35]=0;
			OldX35=X35;
			X35=0;
		}
	}
	if(I036)
	{
		InputFiltering[36]++;
		if(InputFiltering[36]>=FILTERTIME_P)
		{
			InputFiltering[36]=FILTERTIME_P;
			OldX36=X36;
			X36=1;
		}
	}
	else
	{
		if(InputFiltering[36])
		{
			InputFiltering[36]--;
		}
		if(InputFiltering[36]<=FILTERTIME_N)
		{
			InputFiltering[36]=0;
			OldX36=X36;
			X36=0;
		}
	}
	//
	if(I037)
	{
		InputFiltering[37]++;
		if(InputFiltering[37]>=FILTERTIME_P)
		{
			InputFiltering[37]=FILTERTIME_P;
			OldX37=X37;
			X37=1;
		}
	}
	else
	{
		if(InputFiltering[37])
		{
			InputFiltering[37]--;
		}
		if(InputFiltering[37]<=FILTERTIME_N)
		{
			InputFiltering[37]=0;
			OldX37=X37;
			X37=0;
		}
	}
}
void TestOutput(void)
{
  static unsigned long dwOutTime = 0;
  static unsigned short temp = 0;

  if(dwTickCount > dwOutTime)
  {
    dwOutTime = dwTickCount + 500;
	cOutputVal1.Val=0;
	cOutputVal2.Val=0;
    if(temp++ > 24)
      temp = 0;
  }
  if((cInputX00_X17 == 0)&&(cInputX20_X37==0))
  {    
    switch(temp)
    {
    case 0:
		cOutputVal1.Val=0xffff;
		cOutputVal2.Val=0xffff;
		break;
    case 1:
		Y00=1;
		break;
    case 2:
		Y01 = 1;
		break;
    case 3:
		Y02 = 1;
		break;
    case 4:
		Y03 = 1;
		break;
    case 5:
		Y04 = 1;
		break;
    case 6:
		Y05 = 1;
		break;
    case 7:
		Y06 = 1;
        break;
    case 8:
        Y07 = 1;
		break;
    case 9:
		Y10 = 1;
		break;
    case 10:
		Y11 = 1;
		break;
    case 11:
		Y12 = 1;
        break;
    case 12:
		Y13 = 1;
        break;
    case 13:
		Y14 = 1;
		break;
    case 14:
		Y15 = 1;
		break;
    case 15:
		Y16 = 1;
		break;
    case 16:
		Y17 = 1;
		break;
	case 17:
		Y20 = 1;
		break;
    case 18:
		Y21 = 1;
		break;
    case 19:
		Y22 = 1;
		break;
    case 20:
		Y23 = 1;
		break;
	case 21:
		Y24 = 1;
		break;
    case 22:
		Y25 = 1;
		break;
	case 23:
		Y26 = 1;
		break;
    case 24:
		Y27 = 1;
		break;
    default:
		break;
    }
  }
  else
  {
    if(X00)
      Y00 = 1;
    if(X01)
      Y01 = 1;
    if(X02)
      Y02 = 1;
    if(X03)
      Y03 = 1;
    if(X04)
      Y04 = 1;
    if(X05)
      Y05 = 1;
    if(X06)
      Y06 = 1;
    if(X07)
      Y07 = 1;
    if(X10)
      Y10 = 1;
    if(X11)
      Y11 = 1;
    if(X12)
      Y12 = 1;
    if(X13)
      Y13 = 1;
    if(X14)
      Y14 = 1;
    if(X15)
      Y15 = 1;
    if(X16)
      Y16 = 1;
    if(X17)
      Y17 = 1;  
	if(X20)
      Y20 = 1;
    if(X21)
      Y21 = 1;
    if(X22)
      Y22 = 1;
    if(X23)
      Y23 = 1; 
	if(X24){
      Y24 = 1;
	  Y26=  1;}
    if(X25){
      Y25 = 1;
	  Y27=1;}
  }
}

void selset_mode(void)
{
	if (MotroParam->mode_lift == MODEXIUB)
   {
	   if (MotroParam->mode_right == MODEXIUB)
	   {
		   Y02 = Y14 | Y15;
		   Y03 = 0;
	   }
	   else if (MotroParam->mode_right == MODEXICAO)
	   {
		   Y02 = Y14;
		   Y03 = Y15;
	   }
	}
	else if (MotroParam->mode_lift == MODEXICAO)
	{
		if (MotroParam->mode_right == MODEXIUB)
		{
			Y02 = Y15;
			Y03 = Y14;
		}
		else if (MotroParam->mode_right == MODEXICAO)
		{
			Y02 = 0;
			Y03 = Y14 | Y15;
		}
	}
	else
	{
		if (MotroParam->mode_right == MODEXIUB)
		{
			Y02 = Y15;
			Y03 = 0;
		}
		else if (MotroParam->mode_right == MODEXICAO)
		{
			Y02 = 0;
			Y03 = Y15;
		}
	}

}

void WriteOutput(void)
{
    selset_mode();
	OUT00 = !Y00;	
	OUT01 = !Y01;	
	OUT02 = !Y02;	
	OUT03 = !Y03;	
	OUT04 = !Y04;	
	OUT05 = !Y05;	
	OUT06 = !Y06;
	OUT07 = !Y07;

	OUT10 = Y10;	
	OUT11 = !Y11;	
	OUT12 = !Y12;	
	OUT13 = !Y13;	
	OUT14 = !Y14;	
	OUT15 = !Y15;	
	OUT16 = !Y16;
	OUT17 = !Y17;

	OUT20 = !Y20;	
	OUT21 = !Y21;	
	OUT22 = !Y22;	
	OUT23 = !Y23;	
	OUT24 = !Y24;	
	OUT25 = !Y25;	
	OUT26 = !Y26;
	OUT27 = !Y27;
}

