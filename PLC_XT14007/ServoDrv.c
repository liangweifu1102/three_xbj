#include "Global.h"

WORD_BITS cAxisState;
WORD_BITS XAxis_RR2,YAxis_RR2,ZAxis_RR2,UAxis_RR2;
WORD_BITS XAxis_Ctrl,YAxis_Ctrl,ZAxis_Ctrl,UAxis_Ctrl;
WORD_BITS HardLimit,ServoAlarm;

long X_DistanceCount,Y_DistanceCount,Z_DistanceCount,U_DistanceCount;
unsigned long XPluseMoveCount,YPluseMoveCount,ZPluseMoveCount,UPluseMoveCount;
unsigned long XPluseDecCount,YPluseDecCount,ZPluseDecCount,UPluseDecCount;
SpeedPusleStrct XCurSpeedPusel;
SpeedPusleStrct YCurSpeedPusel;
SpeedPusleStrct ZCurSpeedPusel;
SpeedPusleStrct UCurSpeedPusel;
RunSpeedStrct   X_CurSpeed,Y_CurSpeed,Z_CurSpeed,U_CurSpeed;
unsigned short X_AccStep,X_DecStep;
unsigned short Y_AccStep,Y_DecStep;
unsigned short Z_AccStep,Z_DecStep;
unsigned short U_AccStep,U_DecStep;
unsigned short XPwmStepcounter,YPwmStepcounter,ZPwmStepcounter,UPwmStepcounter;
unsigned char  X_Pulse_StartFlg,Y_Pulse_StartFlg,Z_Pulse_StartFlg,U_Pulse_StartFlg;
unsigned short XSpeedRatio,YSpeedRatio,ZSpeedRatio,USpeedRatio;//速度比率
unsigned long XPluseMoveDist,YPluseMoveDist,ZPluseMoveDist,UPluseMoveDist;
long	XSoftLinitNeg, XSoftLinitPos;
long	YSoftLinitNeg, YSoftLinitPos;
long	ZSoftLinitNeg, ZSoftLinitPos;
long	USoftLinitNeg, USoftLinitPos;
/************************************************/
/*
复位伺服驱动寄存器

*/
/************************************************/
void ResetServoDrv(unsigned short axis)
{
	cAxisState.Val=0;
	HardLimit.Val=0;
	ServoAlarm.Val=0;
	if(axis==X_AXIS)
	{
		XAxis_PWMInit();
		XAxis_RR2.Val=0;
		XAxis_Ctrl.Val=0;
		memset(&XCurSpeedPusel,0,sizeof(SpeedPusleStrct));
		memset(&X_CurSpeed,0,sizeof(RunSpeedStrct));
		X_AccStep=0;
		X_DecStep=0;
		XPluseMoveCount=0;
		XPluseMoveDist=0;
		XSoftLinitNeg=0;
		XSoftLinitPos=0;	
		XPluseDecCount=0;
		X_Pulse_StartFlg=0;
		XPwmStepcounter=0;
		XSpeedRatio=100;
	}
	else if(axis==Y_AXIS)
	{
		YAxis_PWMInit();
		YAxis_RR2.Val=0;
		YAxis_Ctrl.Val=0;
		memset(&YCurSpeedPusel,0,sizeof(SpeedPusleStrct));
		memset(&Y_CurSpeed,0,sizeof(RunSpeedStrct));
		Y_AccStep=0;
		Y_DecStep=0;
		YPluseMoveCount=0;
		YPluseMoveDist=0;
		YSoftLinitNeg=0;
		YSoftLinitPos=0;	
		YPluseDecCount=0;
		Y_Pulse_StartFlg=0;
		YPwmStepcounter=0;
		YSpeedRatio=100;
	}
	else if(axis==Z_AXIS)
	{
		ZAxis_PWMInit();
		ZAxis_RR2.Val=0;
		ZAxis_Ctrl.Val=0;
		memset(&ZCurSpeedPusel,0,sizeof(SpeedPusleStrct));
		memset(&Z_CurSpeed,0,sizeof(RunSpeedStrct));
		Z_AccStep=0;
		Z_DecStep=0;
		ZPluseMoveCount=0;
		ZPluseMoveDist=0;
		ZSoftLinitNeg=0;
		ZSoftLinitPos=0;	
		ZPluseDecCount=0;
		Z_Pulse_StartFlg=0;
		ZPwmStepcounter=0;
		ZSpeedRatio=100;
	}
	else if(axis==U_AXIS)
	{
		UAxis_PWMInit();
		UAxis_RR2.Val=0;
		UAxis_Ctrl.Val=0;
		memset(&UCurSpeedPusel,0,sizeof(SpeedPusleStrct));
		memset(&U_CurSpeed,0,sizeof(RunSpeedStrct));
		U_AccStep=0;
		U_DecStep=0;
		UPluseMoveCount=0;
		UPluseMoveDist=0;
		USoftLinitNeg=0;
		USoftLinitPos=0;	
		UPluseDecCount=0;
		U_Pulse_StartFlg=0;
		UPwmStepcounter=0;
		USpeedRatio=100;
	}
	YAxis_PWMInit();
}
/************************************************/
/*
设置频率

*/
/************************************************/
void MV_Set_Range(unsigned short axis,int wdata)
{
	axis=axis;
	wdata=wdata;
}
/************************************************/
/*
设置加速度

*/
/************************************************/
void MV_Set_Acc(unsigned short axis,unsigned short wdata)
{
	if(axis==X_AXIS)
	{
		X_CurSpeed.AccSpdTime=wdata;		
	}
	else if(axis==Y_AXIS)
	{
		Y_CurSpeed.AccSpdTime=wdata;	
	}
	else if(axis==Z_AXIS)
	{
		Z_CurSpeed.AccSpdTime=wdata;	
	}
	else if(axis==U_AXIS)
	{
		U_CurSpeed.AccSpdTime=wdata;	
	}
}
/************************************************/
/*
设置减速度

*/
/************************************************/
void MV_Set_Dec(unsigned short axis,unsigned short wdata)
{
	if(axis==X_AXIS)
	{
		X_CurSpeed.DecSpdTime=wdata;		
	}
	else if(axis==Y_AXIS)
	{
		Y_CurSpeed.DecSpdTime=wdata;	
	}
	else if(axis==Z_AXIS)
	{
		Z_CurSpeed.DecSpdTime=wdata;	
	}
	else if(axis==U_AXIS)
	{
		U_CurSpeed.DecSpdTime=wdata;	
	}
}
/************************************************/
/*
设置减起始速度

*/
/************************************************/
void MV_Set_Startv(unsigned short axis,unsigned short wdata)
{
	if(axis==X_AXIS)
	{
		X_CurSpeed.StartSpeed=wdata;	
		X_CurSpeed.OverSpeed=wdata;
	}
	else if(axis==Y_AXIS)
	{
		Y_CurSpeed.StartSpeed=wdata;	
		Y_CurSpeed.OverSpeed=wdata;
	}
	else if(axis==Z_AXIS)
	{
		Z_CurSpeed.StartSpeed=wdata;
		Z_CurSpeed.OverSpeed=wdata;
	}
	else if(axis==U_AXIS)
	{
		U_CurSpeed.StartSpeed=wdata;
		U_CurSpeed.OverSpeed=wdata;
	}
}
/************************************************/
/*
设置减当前速度

*/
/************************************************/
void MV_Set_Speed(unsigned short axis,unsigned short wdata)
{
	if(axis==X_AXIS)
	{
		X_CurSpeed.CurSpeed=(wdata*XSpeedRatio)/100;		
	}
	else if(axis==Y_AXIS)
	{
		Y_CurSpeed.CurSpeed=(wdata*YSpeedRatio)/100;	
	}
	else if(axis==Z_AXIS)
	{
		Z_CurSpeed.CurSpeed=(wdata*ZSpeedRatio)/100;	
	}
	else if(axis==U_AXIS)
	{
		U_CurSpeed.CurSpeed=(wdata*USpeedRatio)/100;	
	}
}
/************************************************/
/*
设置移动相对位置

*/
/************************************************/
void MV_Pmov(unsigned short axis,int wdata)
{
	unsigned long pulsemov;
	if(wdata>=0) pulsemov=wdata;else pulsemov=0-wdata;
	if(axis==X_AXIS)
	{
		if(wdata>=0) 
		{
			X_Dir=0;
			DR_CW_X();
		}
		else
		{
			X_Dir=1;
			DR_CCW_X();
		}
		if((X_CurSpeed.CurSpeed!=0)&&(pulsemov!=0))//速度不为零，距离不为零移动
		{
			CalAccDecSpeed(pulsemov,X_CurSpeed,&XCurSpeedPusel);
			XPluseMoveDist=pulsemov;
			/* Set TGRB3 */
			X_TGRB = XCurSpeedPusel.AccStepPulse[0]/2;
			/* Set TGRC3 */
			X_TGRA = XCurSpeedPusel.AccStepPulse[0];
			X_Cnter=1;
			X_Pulse_Start();	
		}
	
	}
	else if(axis==Y_AXIS)
	{
		if(wdata<0) 
		{
			Y_Dir=0;
			DR_CW_Y();
		}
		else
		{
			Y_Dir=1;
			DR_CCW_Y();
		}
		if((Y_CurSpeed.CurSpeed!=0)&&(pulsemov!=0))//速度不为零，距离不为零移动
		{
			CalAccDecSpeed(pulsemov,Y_CurSpeed,&YCurSpeedPusel);
			YPluseMoveDist=pulsemov;
			/* Set TGRB3 */
			Y_TGRB = YCurSpeedPusel.AccStepPulse[0]/2;
			/* Set TGRC3 */
			Y_TGRA = YCurSpeedPusel.AccStepPulse[0];
			Y_Cnter=1;
			Y_Pulse_Start();	
		}
	}
	else if(axis==Z_AXIS)
	{
		if(wdata<0) 
		{
			Z_Dir=0;
			DR_CW_Z();
		}
		else
		{
			Z_Dir=1;
			DR_CCW_Z();
		}
		if((Z_CurSpeed.CurSpeed!=0)&&(pulsemov!=0))//速度不为零，距离不为零移动
		{
			CalAccDecSpeed(pulsemov,Z_CurSpeed,&ZCurSpeedPusel);
			ZPluseMoveDist=pulsemov;
			/* Set TGRA3 */
			Z_TGRA = ZCurSpeedPusel.AccStepPulse[0];
			/* Set TGRB3 */
			Z_TGRB = ZCurSpeedPusel.AccStepPulse[0]/2;
			Z_Cnter=1;
			Z_Pulse_Start();	
		}
	}
	else if(axis==U_AXIS)
	{
		if(wdata>=0) 
		{
			U_Dir=0;
			DR_CW_U();
		}
		else
		{
			U_Dir=1;
			DR_CCW_U();
		}
		if((U_CurSpeed.CurSpeed!=0)&&(pulsemov!=0))//速度不为零，距离不为零移动
		{
			CalAccDecSpeed(pulsemov,U_CurSpeed,&UCurSpeedPusel);
			UPluseMoveDist=pulsemov;
			/* Set TGRA3 */
			U_TGRA = UCurSpeedPusel.AccStepPulse[0];
			/* Set TGRB3 */
			U_TGRB = UCurSpeedPusel.AccStepPulse[0]/2;
			U_Cnter=1;
			U_Pulse_Start();	
		}
	}
}
/************************************************/
/*
连续移动

*/
/************************************************/
void MV_Continue_Move(unsigned short axis,unsigned short dir)
{
	if(axis==X_AXIS)
	{
		if((dir==0)&&(!X_SLMTP)&&(!X_HLMTP)&&(!X_ALARM)) 
		{
			X_Dir=0;			
			DR_CW_X();
			X_Cnter=0;
			X_CRun=1;
			if(X_CurSpeed.CurSpeed!=0)
			{
				CalDecStop(X_CurSpeed, &XCurSpeedPusel);
				CalAccRun(X_CurSpeed, &XCurSpeedPusel);
				X_TGRB= XCurSpeedPusel.AccStepPulse[0]/2;
				X_TGRA= XCurSpeedPusel.AccStepPulse[0];
				X_Pulse_Start();
			}	
		}
		else if((dir==1)&&(!X_SLMTN)&&(!X_HLMTN)&&(!X_ALARM)) 
		{
			X_Dir=1;
			DR_CCW_X();
			X_Cnter=0;
			X_CRun=1;
			if(X_CurSpeed.CurSpeed!=0)
			{
				CalDecStop(X_CurSpeed, &XCurSpeedPusel);
				CalAccRun(X_CurSpeed, &XCurSpeedPusel);
				X_TGRB = XCurSpeedPusel.AccStepPulse[0]/2;
				X_TGRA = XCurSpeedPusel.AccStepPulse[0];
				X_Pulse_Start();
			}	
		}	
		
	}
	else if(axis==Y_AXIS)
	{
		if((dir==0)&&(!Y_SLMTN)&&(!Y_HLMTN)&&(!Y_ALARM)) 
		{
			Y_Dir=0;			
			DR_CW_Y();
			Y_Cnter=0;
			Y_CRun=1;
			if(Y_CurSpeed.CurSpeed!=0)
			{
				CalDecStop(Y_CurSpeed, &YCurSpeedPusel);
				CalAccRun(Y_CurSpeed, &YCurSpeedPusel);				
				Y_TGRB = YCurSpeedPusel.AccStepPulse[0]/2;
				Y_TGRA = YCurSpeedPusel.AccStepPulse[0];
				Y_Pulse_Start();
			}	
		}
		else if((dir==1)&&(!Y_SLMTP)&&(!Y_HLMTP)&&(!Y_ALARM)) 
		{
			Y_Dir=1;
			DR_CCW_Y();
			Y_Cnter=0;
			Y_CRun=1;
			if(Y_CurSpeed.CurSpeed!=0)
			{
				CalDecStop(Y_CurSpeed, &YCurSpeedPusel);
				CalAccRun(Y_CurSpeed, &YCurSpeedPusel);
				Y_TGRB = YCurSpeedPusel.AccStepPulse[0]/2;
				Y_TGRA = YCurSpeedPusel.AccStepPulse[0];
				Y_Pulse_Start();
			}	
		}
	}
	else if(axis==Z_AXIS)
	{
		if((dir==0)&&(!Z_SLMTN)&&(!Z_HLMTN)&&(!Z_ALARM)) 
		{
			Z_Dir=0;			
			DR_CW_Z();
			Z_Cnter=0;
			Z_CRun=1;
			if(Z_CurSpeed.CurSpeed!=0)
			{
				CalDecStop(Z_CurSpeed, &ZCurSpeedPusel);
				CalAccRun(Z_CurSpeed, &ZCurSpeedPusel);
				Z_TGRA = ZCurSpeedPusel.AccStepPulse[0];
				Z_TGRB = ZCurSpeedPusel.AccStepPulse[0]/2;
				Z_Pulse_Start();
			}	
		}
		else if((dir==1)&&(!Z_SLMTP)&&(!Z_HLMTP)&&(!Z_ALARM)) 
		{
			Z_Dir=1;
			DR_CCW_Z();
			Z_Cnter=0;
			Z_CRun=1;
			if(Z_CurSpeed.CurSpeed!=0)
			{
				CalDecStop(Z_CurSpeed, &ZCurSpeedPusel);
				CalAccRun(Z_CurSpeed, &ZCurSpeedPusel);
				Z_TGRA = ZCurSpeedPusel.AccStepPulse[0];
				Z_TGRB = ZCurSpeedPusel.AccStepPulse[0]/2;
				Z_Pulse_Start();
			}	
		}
	}
	else if(axis==U_AXIS)
	{
		if((dir==0)&&(!U_SLMTP)&&(!U_HLMTP)&&(!U_ALARM)) 
		{
			U_Dir=0;			
			DR_CW_U();
			U_Cnter=0;
			U_CRun=1;
			if(U_CurSpeed.CurSpeed!=0)
			{
				CalDecStop(U_CurSpeed, &UCurSpeedPusel);
				CalAccRun(U_CurSpeed, &UCurSpeedPusel);
				U_TGRA = UCurSpeedPusel.AccStepPulse[0];
				U_TGRB = UCurSpeedPusel.AccStepPulse[0]/2;
				U_Pulse_Start();
			}	
		}
		else if((dir==1)&&(!U_SLMTN)&&(!U_HLMTN)&&(!U_ALARM)) 
		{
			U_Dir=1;
			DR_CCW_U();
			U_Cnter=0;
			U_CRun=1;
			if(U_CurSpeed.CurSpeed!=0)
			{
				CalDecStop(U_CurSpeed, &UCurSpeedPusel);
				CalAccRun(U_CurSpeed, &UCurSpeedPusel);
				U_TGRA = UCurSpeedPusel.AccStepPulse[0];
				U_TGRB = UCurSpeedPusel.AccStepPulse[0]/2;
				U_Pulse_Start();
			}	
		}
	}
}	
/************************************************/
/*
设置当前位置

*/
/************************************************/
void MV_Set_Command_Pos(unsigned short axis,int wdata)
{
	if(axis==X_AXIS)
	{
		X_DistanceCount=wdata;		
	}
	else if(axis==Y_AXIS)
	{
		Y_DistanceCount=wdata;
	}
	else if(axis==Z_AXIS)
	{
		Z_DistanceCount=wdata;
	}
	else if(axis==U_AXIS)
	{
		U_DistanceCount=wdata;
	}
}
/************************************************/
/*
获取当前位置

*/
/************************************************/
long MV_Get_Command_Pos(unsigned short axis)
{
	long pos;
	if(axis==X_AXIS)
	{
		pos=X_DistanceCount;		
	}
	else if(axis==Y_AXIS)
	{
		pos=Y_DistanceCount;
	}
	else if(axis==Z_AXIS)
	{
		pos=Z_DistanceCount;
	}
	else if(axis==U_AXIS)
	{
		pos=U_DistanceCount;
	}
	return(pos);
}
/************************************************/
/*
减速停止
*/
/************************************************/
void MV_Dec_Stop(unsigned short axis)
{
	unsigned short curspeedtmp;
	if(axis==X_AXIS)
	{
		curspeedtmp=X_TGRA;
		X_CurSpeed.CurSpeed=PCLK_FREQUENCY/curspeedtmp;
		X_CurSpeed.CurSpeed/=100;
		CalDecStop(X_CurSpeed, &XCurSpeedPusel);
		if(X_DRV)
		{
			if((X_Pulse_StartFlg==1)&&!X_PStart)
			{
				X_DRV=0;
				X_Pulse_StartFlg=0;
				X_DecStep=0;
				X_Cnter=0;
				X_CRun=0;
				X_DStop=0;
				X_LimitStop=0;
				XPluseDecCount=0;
			}
			if((X_Pulse_StartFlg==0)&&X_PStart&&!X_DStop)
			{
				X_DecStep=1;
				X_Cnter=0;
				X_CRun=0;
				X_DStop=1;
				X_LimitStop=0;
				XPluseDecCount=0;
			}
		}
	}
	else if(axis==Y_AXIS)
	{
		curspeedtmp=Y_TGRA;
		Y_CurSpeed.CurSpeed=PCLK_FREQUENCY/curspeedtmp;
		Y_CurSpeed.CurSpeed/=100;
		CalDecStop(Y_CurSpeed, &YCurSpeedPusel);
		if(Y_DRV)
		{
			if((Y_Pulse_StartFlg==1)&&!Y_PStart)
			{
				Y_DRV=0;
				Y_Pulse_StartFlg=0;
				Y_DecStep=0;
				Y_Cnter=0;
				Y_CRun=0;
				Y_DStop=0;
				Y_LimitStop=0;
				YPluseDecCount=0;
			}
			if((Y_Pulse_StartFlg==0)&&Y_PStart&&!Y_DStop)
			{
				Y_DecStep=1;
				Y_Cnter=0;
				Y_CRun=0;
				Y_DStop=1;			
				Y_LimitStop=0;
				YPluseDecCount=0;
			}

		}
	}	
	else if(axis==Z_AXIS)
	{
		curspeedtmp=Z_TGRA;
		Z_CurSpeed.CurSpeed=PCLK_FREQUENCY/curspeedtmp;
		Z_CurSpeed.CurSpeed/=100;
		CalDecStop(Z_CurSpeed, &ZCurSpeedPusel);
		if(Z_DRV)
		{
			if((Z_Pulse_StartFlg==1)&&!Z_PStart)
			{
				Z_DRV=0;
				Z_Pulse_StartFlg=0;
				Z_DecStep=0;
				Z_Cnter=0;
				Z_CRun=0;
				Z_DStop=0;
				Z_LimitStop=0;
				ZPluseDecCount=0;
			}
			if((Z_Pulse_StartFlg==0)&&Z_PStart&&!Z_DStop)
			{
				Z_DecStep=1;
				Z_Cnter=0;
				Z_CRun=0;
				Z_DStop=1;			
				Z_LimitStop=0;
				ZPluseDecCount=0;
			}

		}
	}	
	else if(axis==U_AXIS)
	{
		curspeedtmp=U_TGRA;
		U_CurSpeed.CurSpeed=PCLK_FREQUENCY/curspeedtmp;
		U_CurSpeed.CurSpeed/=100;
		CalDecStop(U_CurSpeed, &UCurSpeedPusel);
		if(U_DRV)
		{
			if((U_Pulse_StartFlg==1)&&!U_PStart)
			{
				U_DRV=0;
				U_Pulse_StartFlg=0;
				U_DecStep=0;
				U_Cnter=0;
				U_CRun=0;
				U_DStop=0;
				U_LimitStop=0;
				UPluseDecCount=0;
			}
			if((U_Pulse_StartFlg==0)&&U_PStart&&!U_DStop)
			{
				U_DecStep=1;
				U_Cnter=0;
				U_CRun=0;
				U_DStop=1;			
				U_LimitStop=0;
				UPluseDecCount=0;
			}

		}
	}	
}
/************************************************/
/*
立即停止
*/
/************************************************/
void MV_Sudden_Stop(unsigned short axis)
{
	if(axis==X_AXIS)
	{
		X_Pulse_Stop();		
	}
	else if(axis==Y_AXIS)
	{
		Y_Pulse_Stop();
	}
	else if(axis==Z_AXIS)
	{
		Z_Pulse_Stop();
	}
	else if(axis==U_AXIS)
	{
		U_Pulse_Stop();
	}
}
/************************************************/
/*
限位停止
*/
/************************************************/
void MV_Limit_Stop(unsigned short axis)
{
	if(axis==X_AXIS)
	{
		X_DecStep=1;
		X_LimitStop=1;
		X_DStop=0;
		X_Cnter=0;
		X_CRun=0;
		XPluseDecCount=0;		
	}
	else if(axis==Y_AXIS)
	{
		Y_DecStep=1;
		Y_LimitStop=1;
		Y_DStop=0;
		Y_Cnter=0;
		Y_CRun=0;
		YPluseDecCount=0;	
	}
	else if(axis==Z_AXIS)
	{
		Z_DecStep=1;
		Z_LimitStop=1;
		Z_DStop=0;
		Z_Cnter=0;
		Z_CRun=0;
		ZPluseDecCount=0;	
	}
	else if(axis==U_AXIS)
	{
		U_DecStep=1;
		U_LimitStop=1;
		U_DStop=0;
		U_Cnter=0;
		U_CRun=0;
		UPluseDecCount=0;	
	}
}
/************************************************/
/*
移动脉冲数
*/
/************************************************/
void MV_Set_Pulse(unsigned short axis,int wdata)
{

}
/************************************************/
/*
设置软件限位
*/
/************************************************/
void MV_Set_Command_SlMTP(unsigned short axis,int wdata)
{
	if(axis==X_AXIS)
	{
		XSoftLinitPos=wdata;
		X_SLMTPEN=1;
	}
	else if(axis==Y_AXIS)
	{
		YSoftLinitPos=wdata;
		Y_SLMTPEN=1;
	}
	else if(axis==Z_AXIS)
	{
		ZSoftLinitPos=wdata;
		Z_SLMTPEN=1;
	}
	else if(axis==U_AXIS)
	{
		USoftLinitPos=wdata;
		U_SLMTPEN=1;
	}
}
/************************************************/
/*
设置软件限位
*/
/************************************************/
void MV_Set_Command_SlMTN(unsigned short axis,int wdata)
{
	if(axis==X_AXIS)
	{
		XSoftLinitNeg=wdata;
		X_SLMTNEN=1;
	}
	else if(axis==Y_AXIS)
	{
		YSoftLinitNeg=wdata;
		Y_SLMTNEN=1;
	}
	else if(axis==Z_AXIS)
	{
		ZSoftLinitNeg=wdata;
		Z_SLMTNEN=1;
	}
	else if(axis==U_AXIS)
	{
		USoftLinitNeg=wdata;
		U_SLMTNEN=1;
	}
}
/************************************************/
/*
计算加减速
*/
/************************************************/
#if CURVEACC 
void CalAccDecSpeed(unsigned long Pulsemov,RunSpeedStrct currunspeed,SpeedPusleStrct *curspeedpusel)
{
        unsigned long long Kacc;//加速度变化率
        unsigned long long Kdec;//减速度变化率
        unsigned long SAcc;//加速距离
        unsigned long SDec;//减速距离

        unsigned long caltmp;
        unsigned long accpulsetotal=0,decpulsetotal=0;
        unsigned short AccSecond,DecSecond;
        unsigned short i;
        unsigned long Acc_n_1,Acc_n;

        if(currunspeed.StartSpeed<10)
        {
                currunspeed.StartSpeed=10;
        }
        if(currunspeed.OverSpeed<10)
        {
                currunspeed.OverSpeed=10;
        }
        if(currunspeed.CurSpeed<10)
        {
                currunspeed.CurSpeed=10;
        }
        currunspeed.CurSpeed*=10;
        currunspeed.StartSpeed*=10;
        currunspeed.MaxSpeed*=10;
        currunspeed.OverSpeed*=10;
        //
        AccSecond=1+currunspeed.AccSpdTime/1000;
        DecSecond=1+currunspeed.DecSpdTime/1000;

        //S1为加速距离,S3为减速部分距离
        SAcc=(currunspeed.CurSpeed*currunspeed.AccSpdTime)/200+(currunspeed.StartSpeed*currunspeed.AccSpdTime)/100;
        SDec=(currunspeed.CurSpeed*currunspeed.DecSpdTime)/200+(currunspeed.OverSpeed*currunspeed.DecSpdTime)/100;

        while(SAcc+SDec>Pulsemov)
        {
            if(SAcc+SDec>Pulsemov)
            {
                currunspeed.CurSpeed=(currunspeed.CurSpeed*9)/10;
                if(currunspeed.CurSpeed<currunspeed.StartSpeed)break;
            }
            SAcc=(currunspeed.CurSpeed*currunspeed.AccSpdTime)/200+(currunspeed.StartSpeed*currunspeed.AccSpdTime)/100;
            SDec=(currunspeed.CurSpeed*currunspeed.DecSpdTime)/200+(currunspeed.OverSpeed*currunspeed.DecSpdTime)/100;

        }
        if(currunspeed.CurSpeed>currunspeed.StartSpeed)//计算出来的当前速度大于起始速度
        {
            Kacc=(4*(currunspeed.CurSpeed-currunspeed.StartSpeed))*1000/(currunspeed.AccSpdTime);
            Kacc=Kacc*1000/currunspeed.AccSpdTime;
            if(Kacc<1000)Kacc=1000;
            Kdec=(4*(currunspeed.CurSpeed-currunspeed.OverSpeed))*1000/(currunspeed.DecSpdTime);
            Kdec=Kdec*1000/currunspeed.DecSpdTime;
            if(Kdec<1000)Kdec=1000;
        }
        else
        {
             currunspeed.CurSpeed=currunspeed.StartSpeed;
             Kacc=0;
             Kdec=0;
        }
        curspeedpusel->ContSpeed=currunspeed.CurSpeed;
        //
        curspeedpusel->AccStepPulse[0]=currunspeed.StartSpeed;	//加速脉冲起始值
        curspeedpusel->DecStepPulse[0]=currunspeed.CurSpeed;     //减速脉冲起始值

        curspeedpusel->AccStep=currunspeed.AccSpdTime/AccSecond;
        curspeedpusel->DecStep=currunspeed.DecSpdTime/DecSecond;
        curspeedpusel->AccStepTime=AccSecond;
        curspeedpusel->DecStepTime=DecSecond;

        Acc_n_1=0;
        //计算加速部分的速度表
        for(i=1; i<1000; i++)
        {
            if(i>curspeedpusel->AccStep)
            {
                curspeedpusel->AccStepPulse[i]=currunspeed.CurSpeed;
            }
            else
            {
                if(i<=curspeedpusel->AccStep/2)
                {
                    Acc_n=Acc_n_1+(Kacc*AccSecond)/1000;
                   }
                else
                {
                    Acc_n=Acc_n_1-(Kacc*AccSecond)/1000;
                    if(i==curspeedpusel->AccStep)
                    {
                        Acc_n=0;
                    }
                }
                if(Acc_n!=0)
                {
                    if((i%2)==0)
                    {
                        curspeedpusel->AccStepPulse[i]=curspeedpusel->AccStepPulse[i-1]+((Acc_n+Acc_n_1)*AccSecond)/2000;
                    }
                    else
                    {
                        curspeedpusel->AccStepPulse[i]=curspeedpusel->AccStepPulse[i-1]+((Acc_n+Acc_n_1)*AccSecond)/2000+1;
                    }
                }
                else
                {
                    curspeedpusel->AccStepPulse[i]=curspeedpusel->AccStepPulse[i-1]+((Acc_n+Acc_n_1)*AccSecond)/2000;
                }
                if(curspeedpusel->AccStepPulse[i]>currunspeed.CurSpeed)
                {
                    curspeedpusel->AccStepPulse[i]=currunspeed.CurSpeed;
                    curspeedpusel->AccStep=i;
                }
                accpulsetotal+=curspeedpusel->AccStepPulse[i]*AccSecond;
                Acc_n_1=Acc_n;
             }
        }
        //计算减速部分的速度表
        curspeedpusel->DecStepPulse[0]=currunspeed.CurSpeed;
        Acc_n_1=0;
        for(i=1; i<1000; i++)
        {
            if(i>curspeedpusel->DecStep)
            {
                curspeedpusel->DecStepPulse[i]=currunspeed.OverSpeed;
            }
            else
            {
                if(i<=curspeedpusel->DecStep/2)
                {
                    Acc_n=Acc_n_1+(Kdec*AccSecond)/1000;
                }
                else
                {
                    Acc_n=Acc_n_1-(Kdec*AccSecond)/1000;
                    if(i==curspeedpusel->DecStep)
                    {
                        Acc_n=0;
                    }
                }
                if(Acc_n!=0)
                {
                    if((i%2)==0)
                    {
                        curspeedpusel->DecStepPulse[i]=curspeedpusel->DecStepPulse[i-1]-((Acc_n+Acc_n_1)*AccSecond)/2000;
                    }
                    else
                    {
                       curspeedpusel->DecStepPulse[i]=curspeedpusel->DecStepPulse[i-1]-((Acc_n+Acc_n_1)*AccSecond)/2000-1;
                    }
                }
                else
                {
                    curspeedpusel->DecStepPulse[i]=curspeedpusel->DecStepPulse[i-1]-((Acc_n+Acc_n_1)*AccSecond)/2000;
                }
                if(curspeedpusel->DecStepPulse[i]<currunspeed.OverSpeed)
                {
                      curspeedpusel->DecStepPulse[i]=currunspeed.OverSpeed;
                      curspeedpusel->DecStep=i;
                }
                decpulsetotal+=(curspeedpusel->DecStepPulse[i]*DecSecond);
                Acc_n_1=Acc_n;
            }
        }
        curspeedpusel->AccDotDistance=accpulsetotal/100;
        decpulsetotal=decpulsetotal/100;
        if(Pulsemov>decpulsetotal)
        {
                curspeedpusel->DecDotDistance=Pulsemov-decpulsetotal;
        }
        else
        {
                curspeedpusel->DecDotDistance=0;
        }
        for(i=0;i<1000;i++)
        {
            caltmp=curspeedpusel->AccStepPulse[i];
            caltmp=PCLK_FREQUENCY/caltmp;
            caltmp/=10;
            curspeedpusel->AccStepPulse[i]=caltmp;

            caltmp=curspeedpusel->DecStepPulse[i];
            caltmp=PCLK_FREQUENCY/caltmp;
            caltmp/=10;
            curspeedpusel->DecStepPulse[i]=caltmp;
        }
        caltmp=curspeedpusel->ContSpeed;
        caltmp=PCLK_FREQUENCY/caltmp;
        caltmp/=10;
        curspeedpusel->ContSpeed=caltmp;
}
#else
void CalAccDecSpeed(unsigned long Pulsemov,RunSpeedStrct currunspeed,SpeedPusleStrct *curspeedpusel)
{
	unsigned long caltmp;
	unsigned long accsteppulse,decsteppulse;
	unsigned long accpulsetotal,decpulsetotal;
	unsigned short AccSecond,DecSecond;
	unsigned short i;	
	unsigned short flag2=0;
	unsigned long  DecOverSpeed;
	memset(curspeedpusel,0,sizeof(SpeedPusleStrct));
	if(currunspeed.StartSpeed<10)
	{
		currunspeed.StartSpeed=10;
	}
	if(currunspeed.MaxSpeed<10)
	{
		currunspeed.MaxSpeed=10;
	}
	if(currunspeed.CurSpeed<10)
	{
		currunspeed.CurSpeed=10;
	}
	currunspeed.CurSpeed*=RATIO/10;
	currunspeed.StartSpeed*=RATIO/10;
	currunspeed.MaxSpeed*=RATIO/10;
	DecOverSpeed=10*RATIO/10;
	
	AccSecond=1+currunspeed.AccSpdTime/1000;
	DecSecond=1+currunspeed.DecSpdTime/1000;	
	if(currunspeed.CurSpeed<currunspeed.StartSpeed)//起始速度小于运行速度
	{
		currunspeed.CurSpeed=currunspeed.StartSpeed;
	}
	accsteppulse=(currunspeed.CurSpeed-currunspeed.StartSpeed);//加速脉冲数
	accsteppulse=(accsteppulse/currunspeed.AccSpdTime)*AccSecond;	 //加速步进脉冲值
	if(accsteppulse==0)
	{
		accsteppulse=1;
	}
	decsteppulse=(currunspeed.CurSpeed-DecOverSpeed);					//减速脉冲数量
	decsteppulse=(decsteppulse/currunspeed.DecSpdTime)*DecSecond;    //减速脉冲步进值
	if(decsteppulse==0)
	{
		decsteppulse=1;
	}

	curspeedpusel->AccStepPulse[0]=currunspeed.StartSpeed;	//加速脉冲起始值
	curspeedpusel->DecStepPulse[0]=currunspeed.CurSpeed;     //减速脉冲起始值
	for(i=1;i<ACCDEC_BUF_SIZE;i++)//加速赋值
	{
		curspeedpusel->AccStepPulse[i]=curspeedpusel->AccStepPulse[i-1]+accsteppulse;	
		curspeedpusel->DecStepPulse[i]=curspeedpusel->DecStepPulse[i-1]-decsteppulse;	
		if(curspeedpusel->AccStepPulse[i]>=currunspeed.CurSpeed)
		{
			curspeedpusel->AccStepPulse[i]=currunspeed.CurSpeed;			
		}		
		if(curspeedpusel->DecStepPulse[i]<=DecOverSpeed)
		{
			curspeedpusel->DecStepPulse[i]=DecOverSpeed;
		}
	}	
	for(i=0;i<ACCDEC_BUF_SIZE;i++)//加速赋值
	{		
		if(curspeedpusel->AccStepPulse[i]>=currunspeed.CurSpeed)
		{
			curspeedpusel->AccStepPulse[i]=currunspeed.CurSpeed;
			curspeedpusel->AccStep=i;
			break;			
		}
	}
	for(i=0;i<ACCDEC_BUF_SIZE;i++)//加减速赋值
	{		
		if(curspeedpusel->DecStepPulse[i]<=DecOverSpeed)
		{
			curspeedpusel->DecStepPulse[i]=DecOverSpeed;
			curspeedpusel->DecStep=i;
			break;
		}

	}	
	decpulsetotal=0;//(DecOverSpeed*DecSecond);
	accpulsetotal=0;//(currunspeed.StartSpeed*AccSecond);
	curspeedpusel->ContSpeed=currunspeed.CurSpeed;
	for(i=0;i<ACCDEC_BUF_SIZE;i++)//计算减速脉冲总数
	{
		if(i<curspeedpusel->AccStep) accpulsetotal+=(curspeedpusel->AccStepPulse[i]*AccSecond);
		if(i<=curspeedpusel->DecStep) decpulsetotal+=(curspeedpusel->DecStepPulse[i+1]*DecSecond);				
		if(2*(accpulsetotal+decpulsetotal)>=Pulsemov*100)
		{
			curspeedpusel->ContSpeed=curspeedpusel->AccStepPulse[i];
			curspeedpusel->AccStep=i;
			flag2=1;
			break;
		}
	}
	//accpulsetotal=(currunspeed.CurSpeed/2+currunspeed.StartSpeed/2)*currunspeed.AccSpdTime;
	//decpulsetotal=(currunspeed.CurSpeed/2+DecOverSpeed/2)*currunspeed.DecSpdTime;	
	decpulsetotal/=100;
	accpulsetotal/=100;
	
	if(flag2)//防止三角形
	{
		curspeedpusel->AccStepPulse[0]=currunspeed.StartSpeed;
		curspeedpusel->DecStepPulse[0]=curspeedpusel->ContSpeed;	
		for(i=1;i<ACCDEC_BUF_SIZE;i++)//加速赋值
		{
			curspeedpusel->AccStepPulse[i]=curspeedpusel->AccStepPulse[i-1]+accsteppulse;	
			curspeedpusel->DecStepPulse[i]=curspeedpusel->DecStepPulse[i-1]-decsteppulse;	
			if(curspeedpusel->AccStepPulse[i]>=curspeedpusel->ContSpeed)
			{
				curspeedpusel->AccStepPulse[i]=curspeedpusel->ContSpeed;			
			}		
			if(curspeedpusel->DecStepPulse[i]<=DecOverSpeed)
			{
				curspeedpusel->DecStepPulse[i]=DecOverSpeed;
			}
		}
		for(i=0;i<ACCDEC_BUF_SIZE;i++)//重新计算减速
		{			
			if(curspeedpusel->DecStepPulse[i]<=DecOverSpeed)
			{
				curspeedpusel->DecStepPulse[i]=DecOverSpeed;
				curspeedpusel->DecStep=i;
				break;
			}
		}
		for(i=0;i<ACCDEC_BUF_SIZE;i++)//加速赋值
		{			
			if(curspeedpusel->AccStepPulse[i]>=curspeedpusel->ContSpeed)
			{
				curspeedpusel->AccStep=i;
				break;				
			}
		}
		decpulsetotal=(DecOverSpeed*DecSecond);
		accpulsetotal=(currunspeed.StartSpeed*AccSecond);
		for(i=1;i<ACCDEC_BUF_SIZE;i++)//计算减速脉冲总数
		{
			if(i<curspeedpusel->AccStep) accpulsetotal+=(curspeedpusel->AccStepPulse[i]*AccSecond);
			if(i<=curspeedpusel->DecStep) decpulsetotal+=(curspeedpusel->DecStepPulse[i]*DecSecond);				
		}
		decpulsetotal/=100;
		accpulsetotal/=100;
	}
	for(i=0;i<ACCDEC_BUF_SIZE;i++)
	{
		caltmp=curspeedpusel->AccStepPulse[i];
		caltmp=PCLK_FREQUENCY/caltmp;
		caltmp/=10;
		curspeedpusel->AccStepPulse[i]=caltmp;
		
		caltmp=curspeedpusel->DecStepPulse[i];
		caltmp=PCLK_FREQUENCY/caltmp;
		caltmp/=10;
		curspeedpusel->DecStepPulse[i]=caltmp;
	}
	caltmp=curspeedpusel->ContSpeed;
	caltmp=PCLK_FREQUENCY/caltmp;
	caltmp/=10;
	curspeedpusel->ContSpeed=caltmp;
	curspeedpusel->AccDotDistance=accpulsetotal;
	if(Pulsemov>decpulsetotal)
	{
		curspeedpusel->DecDotDistance=Pulsemov-decpulsetotal;
	}
	else
	{
		curspeedpusel->DecDotDistance=0;
	}	
	curspeedpusel->AccStepTime=AccSecond;
	curspeedpusel->DecStepTime=DecSecond;
}
#endif
/************************************************/
/*
计算减速
*/
/************************************************/
#if CURVEACC
void CalDecStop(RunSpeedStrct currunspeed,SpeedPusleStrct *curspeedpusel)
{
        unsigned long long Kacc;//加速度变化率
        unsigned long long Kdec;//减速度变化率

        unsigned long caltmp;
        unsigned long decpulsetotal=0;
        unsigned short AccSecond,DecSecond;
        unsigned short i;
        unsigned long Acc_n_1,Acc_n;
        if(currunspeed.StartSpeed<10)
        {
                currunspeed.StartSpeed=10;
        }
        if(currunspeed.OverSpeed<10)
        {
                currunspeed.OverSpeed=10;
        }

        if(currunspeed.CurSpeed<10)
        {
                currunspeed.CurSpeed=10;
        }
        currunspeed.CurSpeed*=10;
        currunspeed.StartSpeed*=10;
        currunspeed.MaxSpeed*=10;
        currunspeed.OverSpeed*=10;
        //
        AccSecond=1+currunspeed.AccSpdTime/1000;
        DecSecond=1+currunspeed.DecSpdTime/1000;

        if(currunspeed.CurSpeed>currunspeed.StartSpeed)//计算出来的当前速度大于起始速度
        {
            Kacc=(4*(currunspeed.CurSpeed-currunspeed.StartSpeed))*1000/(currunspeed.AccSpdTime);
            Kacc=Kacc*1000/currunspeed.AccSpdTime;
            if(Kacc<1000)Kacc=1000;
            Kdec=(4*(currunspeed.CurSpeed-currunspeed.OverSpeed))*1000/(currunspeed.DecSpdTime);
            Kdec=Kdec*1000/currunspeed.DecSpdTime;
            if(Kdec<1000)Kdec=1000;
        }
        else
        {
             currunspeed.CurSpeed=currunspeed.StartSpeed;
             Kacc=0;
             Kdec=0;
        }
        curspeedpusel->ContSpeed=currunspeed.CurSpeed;
        //
        curspeedpusel->AccStepPulse[0]=currunspeed.StartSpeed;	//加速脉冲起始值
        curspeedpusel->DecStepPulse[0]=currunspeed.CurSpeed;     //减速脉冲起始值

        curspeedpusel->AccStep=currunspeed.AccSpdTime/AccSecond;
        curspeedpusel->DecStep=currunspeed.DecSpdTime/DecSecond;
        curspeedpusel->AccStepTime=AccSecond;
        curspeedpusel->DecStepTime=DecSecond;
        Acc_n_1=0;
        for(i=1; i<1000; i++)
        {
            if(i>curspeedpusel->DecStep)
            {
                curspeedpusel->DecStepPulse[i]=currunspeed.OverSpeed;
            }
            else
            {
                if(i<=curspeedpusel->DecStep/2)
                {
                    Acc_n=Acc_n_1+(Kdec*AccSecond)/1000;
                }
                else
                {
                    Acc_n=Acc_n_1-(Kdec*AccSecond)/1000;
                    if(i==curspeedpusel->DecStep)
                    {
                        Acc_n=0;
                    }
                }
                if(Acc_n!=0)
                {
                    if((i%2)==0)
                    {

                        curspeedpusel->DecStepPulse[i]=curspeedpusel->DecStepPulse[i-1]-((Acc_n+Acc_n_1)*AccSecond)/2000;
                    }
                    else
                    {

                       curspeedpusel->DecStepPulse[i]=curspeedpusel->DecStepPulse[i-1]-((Acc_n+Acc_n_1)*AccSecond)/2000-1;
                    }
                }
                else
                {

                    curspeedpusel->DecStepPulse[i]=curspeedpusel->DecStepPulse[i-1]-((Acc_n+Acc_n_1)*AccSecond)/2000;
                }
                if(curspeedpusel->DecStepPulse[i]<currunspeed.OverSpeed)
                {
                      curspeedpusel->DecStepPulse[i]=currunspeed.OverSpeed;
                      curspeedpusel->DecStep=i;
                }
                decpulsetotal+=(curspeedpusel->DecStepPulse[i]*DecSecond);
                Acc_n_1=Acc_n;
            }
        }
        for(i=0;i<1000;i++)
        {
            caltmp=curspeedpusel->DecStepPulse[i];
            caltmp=PCLK_FREQUENCY/caltmp;
            caltmp/=10;
            curspeedpusel->DecStepPulse[i]=caltmp;

        }
        caltmp=curspeedpusel->ContSpeed;
        caltmp=PCLK_FREQUENCY/caltmp;
        caltmp/=10;
        curspeedpusel->ContSpeed=caltmp;
}
#else
void CalDecStop(RunSpeedStrct currunspeed,SpeedPusleStrct *curspeedpusel)
{
	unsigned long caltmp;
	unsigned long decsteppulse;
	unsigned long decpulsetotal;
	unsigned short DecSecond;
	unsigned short i;	
	unsigned long  DecOverSpeed;
	unsigned long DecSpdTimetmp=0;
	if(currunspeed.StartSpeed<10)
	{
		currunspeed.StartSpeed=10;
	}
	if(currunspeed.MaxSpeed<10)
	{
		currunspeed.MaxSpeed=10;
	}
	if(currunspeed.CurSpeed<10)
	{
		currunspeed.CurSpeed=10;
	}
	currunspeed.CurSpeed*=RATIO/10;
	currunspeed.StartSpeed*=RATIO/10;
	currunspeed.MaxSpeed*=RATIO/10;
	DecOverSpeed=10*RATIO/10;
	DecSpdTimetmp=200;
	
	DecSecond=1+DecSpdTimetmp/1000;	
	if(currunspeed.CurSpeed<currunspeed.StartSpeed)//起始速度小于运行速度
	{
		currunspeed.CurSpeed=currunspeed.StartSpeed;
	}
	decsteppulse=(currunspeed.CurSpeed-DecOverSpeed);					//减速脉冲数量
	decsteppulse=(decsteppulse/DecSpdTimetmp)*DecSecond;    //减速脉冲步进值
	if(decsteppulse==0)
	{
		decsteppulse=1;
	}
	curspeedpusel->DecStepPulse[0]=currunspeed.CurSpeed;      //减速脉冲起始值
	for(i=1;i<ACCDEC_BUF_SIZE;i++)//加减速赋值
	{
		curspeedpusel->DecStepPulse[i]=curspeedpusel->DecStepPulse[i-1]-decsteppulse;	
		if(curspeedpusel->DecStepPulse[i]<=DecOverSpeed)
		{
			curspeedpusel->DecStepPulse[i]=DecOverSpeed;
		}

	}	
	decpulsetotal=0;
	for(i=1;i<ACCDEC_BUF_SIZE;i++)//计算减速脉冲总数
	{
		decpulsetotal+=(curspeedpusel->DecStepPulse[i]*DecSecond);		
		if(curspeedpusel->DecStepPulse[i]<=DecOverSpeed)
		{
			curspeedpusel->DecStep=i+20;
			break;
		}
	}
	for(i=0;i<ACCDEC_BUF_SIZE;i++)
	{
		caltmp=curspeedpusel->DecStepPulse[i];
		caltmp=PCLK_FREQUENCY/caltmp;
		caltmp/=10;
		curspeedpusel->DecStepPulse[i]=caltmp;
	}
	curspeedpusel->ContSpeed=currunspeed.CurSpeed;
	caltmp=curspeedpusel->ContSpeed;
	caltmp=PCLK_FREQUENCY/caltmp;
	caltmp/=10;
	curspeedpusel->ContSpeed=caltmp;
	curspeedpusel->DecStepTime=DecSecond;
	curspeedpusel->DecDotDistance=decpulsetotal;
}
#endif
/************************************************/
/*
计算加速
*/
/************************************************/
#if CURVEACC
void CalAccRun(RunSpeedStrct currunspeed,SpeedPusleStrct *curspeedpusel)
{
        unsigned long long Kacc;//加速度变化率
        unsigned long long Kdec;//减速度变化率

        unsigned long caltmp;
        unsigned long accpulsetotal=0;
        unsigned short AccSecond,DecSecond;
        unsigned short i;
        unsigned long Acc_n_1,Acc_n;
        if(currunspeed.StartSpeed<10)
        {
                currunspeed.StartSpeed=10;
        }
        if(currunspeed.OverSpeed<10)
        {
                currunspeed.OverSpeed=10;
        }
        if(currunspeed.CurSpeed<10)
        {
                currunspeed.CurSpeed=10;
        }
        currunspeed.CurSpeed*=10;
        currunspeed.StartSpeed*=10;
        currunspeed.MaxSpeed*=10;
        currunspeed.OverSpeed*=10;
        //
        AccSecond=1+currunspeed.AccSpdTime/1000;
        DecSecond=1+currunspeed.DecSpdTime/1000;

        if(currunspeed.CurSpeed>currunspeed.StartSpeed)//计算出来的当前速度大于起始速度
        {
            Kacc=(4*(currunspeed.CurSpeed-currunspeed.StartSpeed))*1000/(currunspeed.AccSpdTime);
            Kacc=Kacc*1000/currunspeed.AccSpdTime;
            if(Kacc<1000)Kacc=1000;
            Kdec=(4*(currunspeed.CurSpeed-currunspeed.OverSpeed))*1000/(currunspeed.DecSpdTime);
            Kdec=Kdec*1000/currunspeed.DecSpdTime;
            if(Kdec<1000)Kdec=1000;
        }
        else
        {
             currunspeed.CurSpeed=currunspeed.StartSpeed;
             Kacc=0;
             Kdec=0;
        }
        curspeedpusel->ContSpeed=currunspeed.CurSpeed;
        //
        curspeedpusel->AccStepPulse[0]=currunspeed.StartSpeed;	//加速脉冲起始值
        curspeedpusel->DecStepPulse[0]=currunspeed.CurSpeed;     //减速脉冲起始值

        curspeedpusel->AccStep=currunspeed.AccSpdTime/AccSecond;
        curspeedpusel->DecStep=currunspeed.DecSpdTime/DecSecond;
        curspeedpusel->AccStepTime=AccSecond;
        curspeedpusel->DecStepTime=DecSecond;
        Acc_n_1=0;
        //计算加速部分的速度表
        for(i=1; i<1000; i++)
        {
            if(i>curspeedpusel->AccStep)
            {
                curspeedpusel->AccStepPulse[i]=currunspeed.CurSpeed;
            }
            else
            {
                if(i<=curspeedpusel->AccStep/2)
                {
                    Acc_n=Acc_n_1+(Kacc*AccSecond)/1000;
                }
                else
                {
                    Acc_n=Acc_n_1-(Kacc*AccSecond)/1000;
                    if(i==curspeedpusel->AccStep)
                    {
                        Acc_n=0;
                    }
                }
                if(Acc_n!=0)
                {
                    if((i%2)==0)
                    {
                      curspeedpusel->AccStepPulse[i]=curspeedpusel->AccStepPulse[i-1]+((Acc_n+Acc_n_1)*AccSecond)/2000;
                    }
                    else
                    {
                        curspeedpusel->AccStepPulse[i]=curspeedpusel->AccStepPulse[i-1]+((Acc_n+Acc_n_1)*AccSecond)/2000+1;
                    }
                }
                else
                {
                    curspeedpusel->AccStepPulse[i]=curspeedpusel->AccStepPulse[i-1]+((Acc_n+Acc_n_1)*AccSecond)/2000;
                }
                if(curspeedpusel->AccStepPulse[i]>currunspeed.CurSpeed)
                {
                    curspeedpusel->AccStepPulse[i]=currunspeed.CurSpeed;
                    curspeedpusel->AccStep=i;
                }
                accpulsetotal+=curspeedpusel->AccStepPulse[i]*AccSecond;
                Acc_n_1=Acc_n;
             }
        }
        for(i=0;i<1000;i++)
        {
            caltmp=curspeedpusel->AccStepPulse[i];
            caltmp=PCLK_FREQUENCY/caltmp;
            caltmp/=10;
            curspeedpusel->AccStepPulse[i]=caltmp;
        }
        caltmp=curspeedpusel->ContSpeed;
        caltmp=PCLK_FREQUENCY/caltmp;
        caltmp/=10;
        curspeedpusel->ContSpeed=caltmp;
}
#else
void CalAccRun(RunSpeedStrct currunspeed,SpeedPusleStrct *curspeedpusel)
{
	unsigned long caltmp;
	unsigned long accsteppulse;
	unsigned long accpulsetotal;
	unsigned short AccSecond;
	unsigned short i;	
	if(currunspeed.StartSpeed<10)
	{
		currunspeed.StartSpeed=10;
	}
	if(currunspeed.MaxSpeed<10)
	{
		currunspeed.MaxSpeed=10;
	}
	if(currunspeed.CurSpeed<10)
	{
		currunspeed.CurSpeed=10;
	}
	currunspeed.CurSpeed*=RATIO/10;
	currunspeed.StartSpeed*=RATIO/10;
	currunspeed.MaxSpeed*=RATIO/10;
	
	AccSecond=1+currunspeed.AccSpdTime/1000;
	if(currunspeed.CurSpeed<currunspeed.StartSpeed)//起始速度小于运行速度
	{
		currunspeed.CurSpeed=currunspeed.StartSpeed;
	}
	accsteppulse=(currunspeed.CurSpeed-currunspeed.StartSpeed);//加速脉冲数
	accsteppulse=(accsteppulse/currunspeed.AccSpdTime)*AccSecond;	 //加速步进脉冲值
	if(accsteppulse==0)
	{
		accsteppulse=1;
	}
	curspeedpusel->AccStepPulse[0]=currunspeed.StartSpeed;	//加速脉冲起始值
	for(i=1;i<ACCDEC_BUF_SIZE;i++)//加减速赋值
	{
		curspeedpusel->AccStepPulse[i]=curspeedpusel->AccStepPulse[i-1]+accsteppulse;		
		if(curspeedpusel->AccStepPulse[i]>=currunspeed.CurSpeed)
		{
			curspeedpusel->AccStepPulse[i]=currunspeed.CurSpeed;
		}
	}	
	accpulsetotal=(currunspeed.StartSpeed*AccSecond)/100;
	for(i=1;i<ACCDEC_BUF_SIZE;i++)//计算加速脉冲总数
	{		
		accpulsetotal+=(curspeedpusel->AccStepPulse[i]*AccSecond)/100;			
		if(curspeedpusel->AccStepPulse[i]>=currunspeed.CurSpeed)
		{
			curspeedpusel->AccStep=i;	
			curspeedpusel->ContSpeed=currunspeed.CurSpeed;
			break;
		}

	}	
	for(i=0;i<ACCDEC_BUF_SIZE;i++)
	{
		caltmp=curspeedpusel->AccStepPulse[i];
		caltmp=PCLK_FREQUENCY/caltmp;
		caltmp/=10;
		curspeedpusel->AccStepPulse[i]=caltmp;
		
	}
	caltmp=curspeedpusel->ContSpeed;
	caltmp=PCLK_FREQUENCY/caltmp;
	caltmp/=10;
	curspeedpusel->ContSpeed=caltmp;
	curspeedpusel->AccDotDistance=accpulsetotal;
	curspeedpusel->AccStepTime=AccSecond;	
}
#endif
/************************************************/
/*
X轴脉冲启动
*/
/************************************************/
void X_Pulse_Start()
{	
	XPwmStepcounter=0;	
	X_Frecy=0;
	X_DRV=1;
	X_AccStep=0;
	X_DecStep=1;
	XPluseMoveCount=0;
	X_Pulse_StartFlg=1;
//	X_PStart=1;
//	X_AXIS_PULSE_ON();
}
/************************************************/
/*
Y轴脉冲启动
*/
/************************************************/
void Y_Pulse_Start()
{
	YPwmStepcounter=0;	
	Y_Frecy=0;
	Y_DRV=1;
	Y_AccStep=0;
	Y_DecStep=1;
	YPluseMoveCount=0;
	Y_Pulse_StartFlg=1;
//	Y_PStart=1;
//	Y_AXIS_PULSE_ON();
}
/************************************************/
/*
Z轴脉冲启动
*/
/************************************************/
void Z_Pulse_Start()
{
	ZPwmStepcounter=0;	
	Z_Frecy=0;
	Z_DRV=1;
	Z_AccStep=0;
	Z_DecStep=1;
	ZPluseMoveCount=0;
	Z_Pulse_StartFlg=1;
}
/************************************************/
/*
U轴脉冲启动
*/
/************************************************/
void U_Pulse_Start()
{
	UPwmStepcounter=0;	
	U_Frecy=0;
	U_DRV=1;
	U_AccStep=0;
	U_DecStep=1;
	UPluseMoveCount=0;
	U_Pulse_StartFlg=1;
}
/************************************************/
/*
X轴脉冲停止
*/
/************************************************/
void X_Pulse_Stop()
{
	X_PStart=0;
	XPwmStepcounter=0;
	XPluseDecCount=0;
	XPluseMoveDist=0;
	X_AccStep=0;
	X_DecStep=0;
	X_Frecy=0;
	X_Cnter=0;
	X_CRun=0;
	X_DStop=0;
	X_DRV=0;
	X_LimitStop=0;
	XPluseMoveCount=0;
	XAxis_TCNT = 0x0000;
	X_Pulse_StartFlg=0;
	X_AXIS_PULSE_OFF();
}
/************************************************/
/*
Y轴脉冲停止
*/
/************************************************/
void Y_Pulse_Stop()
{
	Y_PStart=0;
	YPwmStepcounter=0;
	YPluseDecCount=0;
	YPluseMoveDist=0;
	Y_AccStep=0;
	Y_DecStep=0;
	Y_Frecy=0;
	Y_Cnter=0;
	Y_CRun=0;
	Y_DStop=0;
	Y_DRV=0;
	Y_LimitStop=0;
	YPluseMoveCount=0;
	YAxis_TCNT = 0x0000;
	Y_Pulse_StartFlg=0;
	Y_AXIS_PULSE_OFF();
}
/************************************************/
/*
Z轴脉冲停止
*/
/************************************************/
void Z_Pulse_Stop()
{
	Z_PStart=0;
	ZPwmStepcounter=0;
	ZPluseDecCount=0;
	ZPluseMoveDist=0;
	Z_AccStep=0;
	Z_DecStep=0;
	Z_Frecy=0;
	Z_Cnter=0;
	Z_CRun=0;
	Z_DStop=0;
	Z_DRV=0;
	Z_LimitStop=0;
	ZPluseMoveCount=0;
	ZAxis_TCNT = 0x0000;
	Z_Pulse_StartFlg=0;
	Z_AXIS_PULSE_OFF();
}
/************************************************/
/*
U轴脉冲停止
*/
/************************************************/
void U_Pulse_Stop()
{
	U_PStart=0;
	UPwmStepcounter=0;
	UPluseDecCount=0;
	UPluseMoveDist=0;
	U_AccStep=0;
	U_DecStep=0;
	U_Frecy=0;
	U_Cnter=0;
	U_CRun=0;
	U_DStop=0;
	U_DRV=0;
	U_LimitStop=0;
	UPluseMoveCount=0;
	UAxis_TCNT = 0x0000;
	U_Pulse_StartFlg=0;
	U_AXIS_PULSE_OFF();
}
/************************************************/
/*
X轴软件限位
*/
/************************************************/
void XSoftLimitProc(void)
{
	//unsigned long pmov;
	if(X_SLMTNEN)//X轴负极限位
	{
           
		if(XSoftLinitNeg<X_DistanceCount)
		{
			X_SLMTN=0;
		}
		if((X_DistanceCount<XSoftLinitNeg)&&X_Dir)
		{			
			if(X_SLMTN==0)MV_Limit_Stop(X_AXIS);	
			X_SLMTN=1;
		}
                
	}
	else if(!X_SLMTNEN)
	{
		X_SLMTN=0;
	}
	if(X_SLMTPEN)//X轴正极极限位
	{
		if(XSoftLinitPos>X_DistanceCount)
		{
			X_SLMTP=0;
		}
		if((X_DistanceCount>XSoftLinitPos)&&!X_Dir)
		{			
			if(X_SLMTP==0)MV_Dec_Stop(X_AXIS);//MV_Limit_Stop(X_AXIS);	
			X_SLMTP=1;
		}
	}
	else if(!X_SLMTPEN)
	{
		X_SLMTP=0;
	}
}
/************************************************/
/*
Y轴软件限位
*/
/************************************************/
void YSoftLimitProc(void)
{
	//unsigned long pmov;
	if(Y_SLMTNEN)
	{
		if(YSoftLinitNeg<Y_DistanceCount)
		{
			Y_SLMTN=0;
		}
		if((Y_DistanceCount<YSoftLinitNeg)&&!Y_Dir)
		{			
			if(Y_SLMTN==0)MV_Limit_Stop(Y_AXIS);	
			Y_SLMTN=1;
		}
	}
	else if(!Y_SLMTNEN)
	{
		Y_SLMTN=0;
	}
	if(Y_SLMTPEN)//Y轴正极极限位
	{
		if(YSoftLinitPos>Y_DistanceCount)
		{
			Y_SLMTP=0;
		}
		if((Y_DistanceCount>YSoftLinitPos)&&Y_Dir)
		{			
			if(Y_SLMTP==0)MV_Limit_Stop(Y_AXIS);	
			Y_SLMTP=1;
		}
	}
	else if(!Y_SLMTPEN)
	{
		Y_SLMTP=0;
	}
}
/************************************************/
/*
Z轴软件限位
*/
/************************************************/
void ZSoftLimitProc(void)
{
	if(Z_SLMTNEN)
	{
		if(ZSoftLinitNeg<Z_DistanceCount)
		{
			Z_SLMTN=0;
		}
		if((Z_DistanceCount<ZSoftLinitNeg)&&!Z_Dir)
		{			
			if(Z_SLMTN==0)MV_Limit_Stop(Z_AXIS);	
			Z_SLMTN=1;
		}
	}
	else// if(!Z_SLMTNEN)
	{
		Z_SLMTN=0;
	}
	if(Z_SLMTPEN)//Y轴正极极限位
	{
		if(ZSoftLinitPos>Z_DistanceCount)
		{
			Z_SLMTP=0;
		}
		if((Z_DistanceCount>ZSoftLinitPos)&&Z_Dir)
		{			
			if(Z_SLMTP==0)MV_Limit_Stop(Z_AXIS);	
			Z_SLMTP=1;
		}
	}
	else if(!Z_SLMTPEN)
	{
		Z_SLMTP=0;
	}
}
/************************************************/
/*
U轴软件限位
*/
/************************************************/
void USoftLimitProc(void)
{
	//unsigned long pmov;
	if(U_SLMTNEN)
	{
		if(USoftLinitNeg<U_DistanceCount)
		{
			U_SLMTN=0;
		}
		if((U_DistanceCount<USoftLinitNeg)&&U_Dir)
		{			
			if(U_SLMTN==0)MV_Limit_Stop(U_AXIS);	
			U_SLMTN=1;
		}
	}
	else if(!U_SLMTNEN)
	{
		U_SLMTN=0;
	}
	if(U_SLMTPEN)//Y轴正极极限位
	{
		if(USoftLinitPos>U_DistanceCount)
		{
			U_SLMTP=0;
		}
		if((U_DistanceCount>USoftLinitPos)&&!U_Dir)
		{			
			if(U_SLMTP==0)MV_Limit_Stop(U_AXIS);	
			U_SLMTP=1;
		}
	}
	else if(!U_SLMTPEN)
	{
		U_SLMTP=0;
	}
}

extern void ServorHandler(void);
/************************************************/
/*
X轴脉冲程序
*/
/************************************************/
void XPwmInterruptProgram(void)
{
	//XAxisDrvArmProc();
	//XAxisHLimitProc();
	if(X_PStart)
	{
		if(X_Dir)X_DistanceCount--;else X_DistanceCount++;
		XSoftLimitProc();		
	}	
	if(X_Cnter)
	{
		XPluseMoveCount++;
		if(XPluseMoveCount<XCurSpeedPusel.AccDotDistance)//加速区
		{
			X_ACC=1;
			X_DeC=0;
			if(X_Frecy)		
			{
				X_TGRA = XCurSpeedPusel.AccStepPulse[X_AccStep];
				X_TGRB = XCurSpeedPusel.AccStepPulse[X_AccStep]/2;
				X_AccStep++;
				X_Frecy=0;		
			}
			
		}
		else if((XPluseMoveCount>=XCurSpeedPusel.AccDotDistance)
			  &&(XPluseMoveCount<XCurSpeedPusel.DecDotDistance))//匀速区
		{
			X_ACC=0;
			X_DeC=0;
			if(X_Frecy)
			{
				X_TGRA = XCurSpeedPusel.ContSpeed;
				X_TGRB = XCurSpeedPusel.ContSpeed/2;
				X_Frecy=0;		
			}
		}
		else if((XPluseMoveCount>=XCurSpeedPusel.DecDotDistance)//减速区
			  &&(XPluseMoveCount<XPluseMoveDist))
		{
			X_ACC=0;
			X_DeC=1;
			if(X_Frecy)
			{
				X_TGRA = XCurSpeedPusel.DecStepPulse[X_DecStep];
				X_TGRB = XCurSpeedPusel.DecStepPulse[X_DecStep]/2;
				X_Frecy=0;
				X_DecStep++;
			}
		}			  
		if(XPluseMoveCount>=XPluseMoveDist)//停止去
		{
			X_ACC=0;
			X_DeC=0;
			X_Pulse_Stop();
		}
	}
	else
	{
		if(X_CRun)//运行
		{				
			if(X_AccStep<=XCurSpeedPusel.AccStep)//加速去
			{
				X_ACC=1;
				if(X_Frecy)
				{
					X_TGRA = XCurSpeedPusel.AccStepPulse[X_AccStep];
					X_TGRB = XCurSpeedPusel.AccStepPulse[X_AccStep]/2;
					X_AccStep++;
					X_Frecy=0;	
				}
			}
			else//匀速区
			{
				X_TGRA = XCurSpeedPusel.ContSpeed;
				X_TGRB = XCurSpeedPusel.ContSpeed/2;
			}			
			
		}
		else if(X_DStop)
		{
			if(X_DecStep<=XCurSpeedPusel.DecStep)
			{
				if(X_Frecy)//减速区
				{	
					X_TGRA = XCurSpeedPusel.DecStepPulse[X_DecStep];
					X_TGRB = XCurSpeedPusel.DecStepPulse[X_DecStep]/2;
					X_DecStep++;
					X_Frecy=0;	
				}
			}
			else
			{
				X_Pulse_Stop();
			}
			//XPluseDecCount++;
			//if((XPluseDecCount>=10000)
			//  ||(XCurSpeedPusel.DecStepPulse[X_DecStep]<=XCurSpeedPusel.DecStepPulse[XCurSpeedPusel.DecStep]))
			//{
			//	XPluseDecCount=0;
			//	X_Pulse_Stop();
			//}
		}
		else if(X_LimitStop)//限位停止
		{
			if(X_DecStep<=XCurSpeedPusel.DecStep)
			{			
				X_TGRA = XCurSpeedPusel.DecStepPulse[X_DecStep];
				X_TGRB = XCurSpeedPusel.DecStepPulse[X_DecStep]/2;					
			}
			else
			{
				X_Pulse_Stop();
			}
			if(XCurSpeedPusel.DecStep>5)
			{
				X_DecStep+=XCurSpeedPusel.DecStep/5;
			}
			XPluseDecCount++;
			if(XPluseDecCount>=5)
			{
				XPluseDecCount=0;
				X_Pulse_Stop();
			}
		}

	}
        ServorHandler();
}
/************************************************/
/*
Y轴脉冲程序
*/
/************************************************/
void YPwmInterruptProgram(void)
{
	//YAxisDrvArmProc();
	//YAxisHLimitProc();
	if(Y_PStart)
	{
		if(Y_Dir)Y_DistanceCount++;else Y_DistanceCount--;
		YSoftLimitProc();		
	}	
	if(Y_Cnter)
	{
		YPluseMoveCount++;
		if(YPluseMoveCount<YCurSpeedPusel.AccDotDistance)//加速区
		{
			Y_ACC=1;
			Y_DeC=0;
			if(Y_Frecy)		
			{
				Y_TGRA = YCurSpeedPusel.AccStepPulse[Y_AccStep];
				Y_TGRB = YCurSpeedPusel.AccStepPulse[Y_AccStep]/2;
				Y_AccStep++;
				Y_Frecy=0;		
			}
			
		}
		else if((YPluseMoveCount>=YCurSpeedPusel.AccDotDistance)
			  &&(YPluseMoveCount<YCurSpeedPusel.DecDotDistance))//匀速区
		{
			Y_ACC=0;
			Y_DeC=0;
			if(Y_Frecy)
			{
				Y_TGRA = YCurSpeedPusel.ContSpeed;
				Y_TGRB = YCurSpeedPusel.ContSpeed/2;
				Y_Frecy=0;		
			}
		}
		else if((YPluseMoveCount>=YCurSpeedPusel.DecDotDistance)//减速区
			  &&(YPluseMoveCount<YPluseMoveDist))
		{
			Y_ACC=0;
			Y_DeC=1;
			if(Y_Frecy)
			{
				Y_TGRA = YCurSpeedPusel.DecStepPulse[Y_DecStep];
				Y_TGRB = YCurSpeedPusel.DecStepPulse[Y_DecStep]/2;
				Y_Frecy=0;
				Y_DecStep++;
			}
		}			  
		if(YPluseMoveCount>=YPluseMoveDist)//停止去
		{
			Y_ACC=0;
			Y_DeC=0;
			Y_Pulse_Stop();
		}
	}
	else
	{
		if(Y_CRun)//运行
		{				
			if(Y_AccStep<=YCurSpeedPusel.AccStep)//加速去
			{
				Y_ACC=1;
				if(Y_Frecy)
				{
					Y_TGRA = YCurSpeedPusel.AccStepPulse[Y_AccStep];
					Y_TGRB = YCurSpeedPusel.AccStepPulse[Y_AccStep]/2;
					Y_AccStep++;
					Y_Frecy=0;	
				}
			}
			else//匀速区
			{
				Y_TGRA = YCurSpeedPusel.ContSpeed;
				Y_TGRB = YCurSpeedPusel.ContSpeed/2;
			}			
			
		}
		else if(Y_DStop)
		{
			if(Y_DecStep<=YCurSpeedPusel.DecStep)
			{
				if(Y_Frecy)//减速区
				{	
					Y_TGRA = YCurSpeedPusel.DecStepPulse[Y_DecStep];
					Y_TGRB = YCurSpeedPusel.DecStepPulse[Y_DecStep]/2;
					Y_DecStep++;
					Y_Frecy=0;	
				}
			}
			else
			{
				Y_Pulse_Stop();
			}
			//YPluseDecCount++;
			//if((YPluseDecCount>=10000)
			//||(YCurSpeedPusel.DecStepPulse[Y_DecStep]<=YCurSpeedPusel.DecStepPulse[YCurSpeedPusel.DecStep]))
			//{
			//	YPluseDecCount=0;
			//	Y_Pulse_Stop();
			//}
		}
		else if(Y_LimitStop)//限位停止
		{
			if(Y_DecStep<=YCurSpeedPusel.DecStep)
			{			
				Y_TGRA = YCurSpeedPusel.DecStepPulse[Y_DecStep];
				Y_TGRB = YCurSpeedPusel.DecStepPulse[Y_DecStep]/2;					
			}
			else
			{
				Y_Pulse_Stop();
			}
			if(YCurSpeedPusel.DecStep>5)
			{
				Y_DecStep+=YCurSpeedPusel.DecStep/5;
			}
			YPluseDecCount++;
			if(YPluseDecCount>=5)
			{
				YPluseDecCount=0;
				Y_Pulse_Stop();
			}
		}

	}
}
/************************************************/
/*
Z轴脉冲程序
*/
/************************************************/
void ZPwmInterruptProgram(void)
{
	if(Z_PStart)
	{
		if(Z_Dir)Z_DistanceCount++;else Z_DistanceCount--;
		ZSoftLimitProc();		
	}	
	if(Z_Cnter)
	{
		ZPluseMoveCount++;
		if(ZPluseMoveCount<ZCurSpeedPusel.AccDotDistance)//加速区
		{
			Z_ACC=1;
			Z_DeC=0;
			if(Z_Frecy)		
			{
				Z_TGRA = ZCurSpeedPusel.AccStepPulse[Z_AccStep];
				Z_TGRB = ZCurSpeedPusel.AccStepPulse[Z_AccStep]/2;
				Z_AccStep++;
				Z_Frecy=0;		
			}
			
		}
		else if((ZPluseMoveCount>=ZCurSpeedPusel.AccDotDistance)
			  &&(ZPluseMoveCount<ZCurSpeedPusel.DecDotDistance))//匀速区
		{
			Z_ACC=0;
			Z_DeC=0;
			if(Z_Frecy)
			{
				Z_TGRA = ZCurSpeedPusel.ContSpeed;
				Z_TGRB = ZCurSpeedPusel.ContSpeed/2;
				Z_Frecy=0;		
			}
		}
		else if((ZPluseMoveCount>=ZCurSpeedPusel.DecDotDistance)//减速区
			  &&(ZPluseMoveCount<ZPluseMoveDist))
		{
			Z_ACC=0;
			Z_DeC=1;
			if(Z_Frecy)
			{
				Z_TGRA = ZCurSpeedPusel.DecStepPulse[Z_DecStep];
				Z_TGRB = ZCurSpeedPusel.DecStepPulse[Z_DecStep]/2;
				Z_Frecy=0;
				Z_DecStep++;
			}
		}			  
		if(ZPluseMoveCount>=ZPluseMoveDist)//停止去
		{
			Z_ACC=0;
			Z_DeC=0;
			Z_Pulse_Stop();
		}
	}
	else
	{
		if(Z_CRun)//运行
		{				
			if(Z_AccStep<=ZCurSpeedPusel.AccStep)//加速去
			{
				Z_ACC=1;
				if(Z_Frecy)
				{
					Z_TGRA = ZCurSpeedPusel.AccStepPulse[Z_AccStep];
					Z_TGRB = ZCurSpeedPusel.AccStepPulse[Z_AccStep]/2;
					Z_AccStep++;
					Z_Frecy=0;	
				}
			}
			else//匀速区
			{
				Z_TGRA = ZCurSpeedPusel.ContSpeed;
				Z_TGRB = ZCurSpeedPusel.ContSpeed/2;
			}			
			
		}
		else if(Z_DStop)
		{
			if(Z_DecStep<=ZCurSpeedPusel.DecStep)
			{
				if(Z_Frecy)//减速区
				{	
					Z_TGRA= ZCurSpeedPusel.DecStepPulse[Z_DecStep];
					Z_TGRB = ZCurSpeedPusel.DecStepPulse[Z_DecStep]/2;
					Z_DecStep++;
					Z_Frecy=0;	
				}
			}
			else
			{
				Z_Pulse_Stop();
			}
			//ZPluseDecCount++;
			//if((ZPluseDecCount>=10000)
			//||(ZCurSpeedPusel.DecStepPulse[Z_DecStep]<=ZCurSpeedPusel.DecStepPulse[ZCurSpeedPusel.DecStep]))
			//{
			//	ZPluseDecCount=0;
			//	Z_Pulse_Stop();
			//}
		}
		else if(Z_LimitStop)//限位停止
		{
			if(Z_DecStep<=ZCurSpeedPusel.DecStep)
			{			
				Z_TGRA = ZCurSpeedPusel.DecStepPulse[Z_DecStep];
				Z_TGRB = ZCurSpeedPusel.DecStepPulse[Z_DecStep]/2;					
			}
			else
			{
				Z_Pulse_Stop();
			}
			if(ZCurSpeedPusel.DecStep>5)
			{
				Z_DecStep+=ZCurSpeedPusel.DecStep/5;
			}
			ZPluseDecCount++;
			if(ZPluseDecCount>=5)
			{
				ZPluseDecCount=0;
				Z_Pulse_Stop();
			}
		}

	}
}
/************************************************/
/*
U轴脉冲程序
*/
/************************************************/
void UPwmInterruptProgram(void)
{
	if(U_PStart)
	{
		if(U_Dir)U_DistanceCount--;else U_DistanceCount++;
		USoftLimitProc();		
	}	
	if(U_Cnter)
	{
		UPluseMoveCount++;
		if(UPluseMoveCount<UCurSpeedPusel.AccDotDistance)//加速区
		{
			U_ACC=1;
			U_DeC=0;
			if(U_Frecy)		
			{
				U_TGRA = UCurSpeedPusel.AccStepPulse[U_AccStep];
				U_TGRB = UCurSpeedPusel.AccStepPulse[U_AccStep]/2;
				U_AccStep++;
				U_Frecy=0;		
			}
			
		}
		else if((UPluseMoveCount>=UCurSpeedPusel.AccDotDistance)
			  &&(UPluseMoveCount<UCurSpeedPusel.DecDotDistance))//匀速区
		{
			U_ACC=0;
			U_DeC=0;
			if(U_Frecy)
			{
				U_TGRA = UCurSpeedPusel.ContSpeed;
				U_TGRB = UCurSpeedPusel.ContSpeed/2;
				U_Frecy=0;		
			}
		}
		else if((UPluseMoveCount>=UCurSpeedPusel.DecDotDistance)//减速区
			  &&(UPluseMoveCount<UPluseMoveDist))
		{
			U_ACC=0;
			U_DeC=1;
			if(U_Frecy)
			{
				U_TGRA = UCurSpeedPusel.DecStepPulse[U_DecStep];
				U_TGRB = UCurSpeedPusel.DecStepPulse[U_DecStep]/2;
				U_Frecy=0;
				U_DecStep++;
			}
		}			  
		if(UPluseMoveCount>=UPluseMoveDist)//停止去
		{
			U_ACC=0;
			U_DeC=0;
			U_Pulse_Stop();
		}
	}
	else
	{
		if(U_CRun)//运行
		{				
			if(U_AccStep<=UCurSpeedPusel.AccStep)//加速去
			{
				U_ACC=1;
				if(U_Frecy)
				{
					U_TGRA = UCurSpeedPusel.AccStepPulse[U_AccStep];
					U_TGRB = UCurSpeedPusel.AccStepPulse[U_AccStep]/2;
					U_AccStep++;
					U_Frecy=0;	
				}
			}
			else//匀速区
			{
				U_TGRA = UCurSpeedPusel.ContSpeed;
				U_TGRB = UCurSpeedPusel.ContSpeed/2;
			}			
			
		}
		else if(U_DStop)
		{
			if(U_DecStep<=UCurSpeedPusel.DecStep)
			{
				if(U_Frecy)//减速区
				{	
					U_TGRA= UCurSpeedPusel.DecStepPulse[U_DecStep];
					U_TGRB = UCurSpeedPusel.DecStepPulse[U_DecStep]/2;
					U_DecStep++;
					U_Frecy=0;	
				}
			}
			else
			{
				U_Pulse_Stop();
			}
			UPluseDecCount++;
			if((UPluseDecCount>=10000)
			||(UCurSpeedPusel.DecStepPulse[U_DecStep]<=UCurSpeedPusel.DecStepPulse[UCurSpeedPusel.DecStep]))
			{
				UPluseDecCount=0;
				U_Pulse_Stop();
			}
		}
		else if(U_LimitStop)//限位停止
		{
			if(U_DecStep<=UCurSpeedPusel.DecStep)
			{			
				U_TGRA = UCurSpeedPusel.DecStepPulse[U_DecStep];
				U_TGRB = UCurSpeedPusel.DecStepPulse[U_DecStep]/2;					
			}
			else
			{
				U_Pulse_Stop();
			}
			if(UCurSpeedPusel.DecStep>5)
			{
				U_DecStep+=UCurSpeedPusel.DecStep/5;
			}
			UPluseDecCount++;
			if(UPluseDecCount>=5)
			{
				UPluseDecCount=0;
				U_Pulse_Stop();
			}
		}

	}
}

/************************************************/
/*
X轴硬件限位
*/
/************************************************/
void XAxisHLimitProc(void)
{
	if(X_HLMTN||X_HLMTP)
	{
		if(X_LimitDec)
		{
			MV_Sudden_Stop(X_AXIS);
		}
		else
		{
			if(X_HLimitFlg==0)MV_Limit_Stop(X_AXIS);
			X_HLimitFlg=1;
		}
	}
	else
	{
		X_HLimitFlg=0;
	}
}
/************************************************/
/*
Y轴硬件限位
*/
/************************************************/
void YAxisHLimitProc(void)
{
	if(Y_HLMTN||Y_HLMTP)
	{
		if(Y_LimitDec)
		{
			MV_Sudden_Stop(Y_AXIS);
		}
		else
		{
			if(Y_HLimitFlg==0)MV_Limit_Stop(Y_AXIS);
			Y_HLimitFlg=1;
		}
	}
	else
	{
		Y_HLimitFlg=0;
	}
}
/************************************************/
/*
Z轴硬件限位
*/
/************************************************/
void ZAxisHLimitProc(void)
{
	if(Z_HLMTN||Z_HLMTP)
	{
		if(Z_LimitDec)
		{
			MV_Sudden_Stop(Z_AXIS);
		}
		else
		{
			if(Z_HLimitFlg==0)MV_Limit_Stop(Z_AXIS);
			Z_HLimitFlg=1;
		}
	}
	else
	{
		Z_HLimitFlg=0;
	}
}
/************************************************/
/*
U轴硬件限位
*/
/************************************************/
void UAxisHLimitProc(void)
{
	if(U_HLMTN||U_HLMTP)
	{
		if(U_LimitDec)
		{
			MV_Sudden_Stop(U_AXIS);
		}
		else
		{
			if(U_HLimitFlg==0)MV_Limit_Stop(U_AXIS);
			U_HLimitFlg=1;
		}
	}
	else
	{
		U_HLimitFlg=0;
	}
}
/************************************************/
/*
X轴驱动器告警
*/
/************************************************/
void XAxisDrvArmProc(void)
{
	if(X_ALARMEN)
	{
		if(X_SAlarmIn)
		{
			X_ALARM=1;
			MV_Sudden_Stop(X_AXIS);
		}
		else
		{
			X_ALARM=0;
		}
	}
	else
	{
		X_ALARM=0;
	}
}
/************************************************/
/*
Y轴驱动器告警
*/
/************************************************/
void YAxisDrvArmProc(void)
{
	if(Y_ALARMEN)
	{
		if(Y_SAlarmIn)
		{
			Y_ALARM=1;
			MV_Sudden_Stop(Y_AXIS);
		}
		else
		{
			Y_ALARM=0;
		}
	}
	else
	{
		Y_ALARM=0;
	}
}
/************************************************/
/*
Z轴驱动器告警
*/
/************************************************/
void ZAxisDrvArmProc(void)
{
	if(Z_ALARMEN)
	{
		if(Z_SAlarmIn)
		{
			Z_ALARM=1;
			MV_Sudden_Stop(Z_AXIS);
		}
		else
		{
			Z_ALARM=0;
		}
	}
	else
	{
		Z_ALARM=0;
	}
}
/************************************************/
/*
U轴驱动器告警
*/
/************************************************/
void UAxisDrvArmProc(void)
{
	if(U_ALARMEN)
	{
		if(U_SAlarmIn)
		{
			U_ALARM=1;
			MV_Sudden_Stop(U_AXIS);
		}
		else
		{
			U_ALARM=0;
		}
	}
	else
	{
		U_ALARM=0;
	}
}
/************************************************/
/*
驱动器保护
*/
/************************************************/
void ServoDrvProct(void)
{
	if(AxisNum>0)
	{
		XAxisDrvArmProc();
		//XAxisHLimitProc();
		//XSoftLimitProc();	
	}
	if(AxisNum>1)
	{
		YAxisDrvArmProc();
		//YAxisHLimitProc();
		//YSoftLimitProc();	
	}
	if(AxisNum>2)
	{
		ZAxisDrvArmProc();
		//ZAxisHLimitProc();
		//ZSoftLimitProc();	
	}
	if(AxisNum>3)
	{
		UAxisDrvArmProc();
		UAxisHLimitProc();
		//USoftLimitProc();
	}	
}
/************************************************/
/*
定时启动发送脉冲
*/
/************************************************/
void TimerPulseStart(void)
{
	if(X_Pulse_StartFlg)
	{
		X_Pulse_StartFlg=0;
		X_PStart=1;
		X_AXIS_PULSE_ON();
	}
	if(Y_Pulse_StartFlg)
	{
		Y_Pulse_StartFlg=0;
		Y_PStart=1;
		Y_AXIS_PULSE_ON();
	}
	if(Z_Pulse_StartFlg)
	{
		Z_Pulse_StartFlg=0;
		Z_PStart=1;
		Z_AXIS_PULSE_ON();
	}
	if(U_Pulse_StartFlg)
	{
		U_Pulse_StartFlg=0;
		U_PStart=1;
		U_AXIS_PULSE_ON();
	}
	if(X_PStart)
	{
		if(X_CRun||X_ACC)
		{
			XPwmStepcounter++;
			if(XPwmStepcounter>=XCurSpeedPusel.AccStepTime)
			{	
				X_Frecy=1;				
			}
		}
		if(X_DeC||X_DStop)
		{
			XPwmStepcounter++;
			if(XPwmStepcounter>=XCurSpeedPusel.DecStepTime)
			{	
				X_Frecy=1;
			}
		}		
	}
	if(Y_PStart)
	{
		if(Y_CRun||Y_ACC)
		{
			YPwmStepcounter++;
			if(YPwmStepcounter>=YCurSpeedPusel.AccStepTime)
			{	
				Y_Frecy=1;				
			}
		}
		if(Y_DeC||Y_DStop)
		{
			YPwmStepcounter++;
			if(YPwmStepcounter>=YCurSpeedPusel.DecStepTime)
			{	
				Y_Frecy=1;
			}
		}		
	}
	if(Z_PStart)
	{
		if(Z_CRun||Z_ACC)
		{
			ZPwmStepcounter++;
			if(ZPwmStepcounter>=ZCurSpeedPusel.AccStepTime)
			{	
				Z_Frecy=1;				
			}
		}
		if(Z_DeC||Z_DStop)
		{
			ZPwmStepcounter++;
			if(ZPwmStepcounter>=ZCurSpeedPusel.DecStepTime)
			{	
				Z_Frecy=1;
			}
		}		
	}
	if(U_PStart)
	{
		if(U_CRun||U_ACC)
		{
			UPwmStepcounter++;
			if(UPwmStepcounter>=UCurSpeedPusel.AccStepTime)
			{	
				U_Frecy=1;				
			}
		}
		if(U_DeC||U_DStop)
		{
			UPwmStepcounter++;
			if(UPwmStepcounter>=UCurSpeedPusel.DecStepTime)
			{	
				U_Frecy=1;
			}
		}		
	}
}

