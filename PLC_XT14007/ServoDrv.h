#ifndef TWOAXISCTRL_H_
#define TWOAXISCTRL_H_
#define		X_AXIS		0x01
#define		Y_AXIS		0x02
#define		Z_AXIS		0x04
#define		U_AXIS		0x08
#define 	RATIO	100
#define     CURVEACC		1

#define XAxis_PWMInit()	MTU7_PWMInit()
#define YAxis_PWMInit()	MTU8_PWMInit()
#define ZAxis_PWMInit()	MTU9_PWMInit()
#define UAxis_PWMInit()	MTU10_PWMInit()

#define MTU7_PWMProc()    	XPwmInterruptProgram()
#define MTU8_PWMProc()    	YPwmInterruptProgram()
#define MTU9_PWMProc()    ZPwmInterruptProgram()
#define MTU10_PWMProc()   	UPwmInterruptProgram()

#define  XAxis_TCNT		MTU7.TCNT
#define  YAxis_TCNT   		MTU8.TCNT
#define  ZAxis_TCNT		MTU9.TCNT
#define  UAxis_TCNT		MTU10.TCNT

#define     X_TGRA		MTU7.TGRA
#define     X_TGRB 		MTU7.TGRB

#define     Y_TGRA		MTU8.TGRA
#define     Y_TGRB 		MTU8.TGRB

#define     Z_TGRA		MTU9.TGRA
#define     Z_TGRB 		MTU9.TGRB

#define     U_TGRA		MTU10.TGRA
#define     U_TGRB 		MTU10.TGRB

#pragma pack
typedef struct _RunSpeedStrct_
{
	unsigned long	StartSpeed;
	unsigned long	OverSpeed;
	unsigned long	AccSpdTime;
	unsigned long	DecSpdTime;
	unsigned long   CurSpeed;
	unsigned long   MaxSpeed;

}RunSpeedStrct;
#define ACCDEC_BUF_SIZE	1000
typedef struct _SpeedPusleStrct_
{
	unsigned short	AccStepPulse[ACCDEC_BUF_SIZE];
	unsigned short   AccStep;
	unsigned short	AccStepTime;
	unsigned short   AccSetcionNum;
	unsigned long    AccDotDistance;
	unsigned short	DecStepPulse[ACCDEC_BUF_SIZE];
	unsigned short   DecStep;
	unsigned short   DecStepTime;
	unsigned short   DecSetcionNum;
	unsigned long    DecDotDistance;
	unsigned long    ContSpeed;

}SpeedPusleStrct;
#pragma packoption
extern WORD_BITS cAxisState;
extern WORD_BITS XAxis_RR2,YAxis_RR2,ZAxis_RR2,UAxis_RR2;
//RR0
//为0表示驱动结束，为1表示正在驱动；
#define  X_DRV			cAxisState.bits.b0
#define  Y_DRV			cAxisState.bits.b1
#define  Z_DRV			cAxisState.bits.b2
#define  U_DRV			cAxisState.bits.b3


#define	 X_SLMTP		XAxis_RR2.bits.b0
#define	 X_SLMTN		XAxis_RR2.bits.b1
#define	 X_ALARM		XAxis_RR2.bits.b4
#define	 X_EMG			XAxis_RR2.bits.b5

#define	 Y_SLMTP		YAxis_RR2.bits.b0
#define	 Y_SLMTN		YAxis_RR2.bits.b1
#define	 Y_ALARM		YAxis_RR2.bits.b4
#define	 Y_EMG			YAxis_RR2.bits.b5

#define	 Z_SLMTP		ZAxis_RR2.bits.b0
#define	 Z_SLMTN		ZAxis_RR2.bits.b1
#define	 Z_ALARM		ZAxis_RR2.bits.b4
#define	 Z_EMG			ZAxis_RR2.bits.b5

#define	 U_SLMTP		UAxis_RR2.bits.b0
#define	 U_SLMTN		UAxis_RR2.bits.b1
#define	 U_ALARM		UAxis_RR2.bits.b4
#define	 U_EMG			UAxis_RR2.bits.b5

extern WORD_BITS XAxis_Ctrl,YAxis_Ctrl,ZAxis_Ctrl,UAxis_Ctrl;
#define X_Dir			XAxis_Ctrl.bits.b0  //电机方向
#define X_Cnter			XAxis_Ctrl.bits.b1  //设定距离一点
#define X_Frecy			XAxis_Ctrl.bits.b2  //频率设置
#define X_ACC			XAxis_Ctrl.bits.b3  //加速
#define X_DeC			XAxis_Ctrl.bits.b4  //减速
#define X_CRun			XAxis_Ctrl.bits.b5  //电动
#define X_DStop			XAxis_Ctrl.bits.b6  //减速
#define X_PStart		XAxis_Ctrl.bits.b7  //脉冲计数开始
#define X_LimitDec		XAxis_Ctrl.bits.b8  //硬件限位停止方式
#define X_ALARMOC		XAxis_Ctrl.bits.b9  //驱动器故障电平有效方式
#define X_SLMTNEN		XAxis_Ctrl.bits.b10 //软件负限位使能
#define X_SLMTPEN		XAxis_Ctrl.bits.b11 //软件正限位使能
#define X_ALARMEN		XAxis_Ctrl.bits.b12 //驱动器故障使能
#define X_ARMStop		XAxis_Ctrl.bits.b13 //告警停止方式
#define X_LimitStop		XAxis_Ctrl.bits.b14 //X轴回零停止
#define X_HLimitFlg		XAxis_Ctrl.bits.b15

#define Y_Dir			YAxis_Ctrl.bits.b0
#define Y_Cnter			YAxis_Ctrl.bits.b1
#define Y_Frecy			YAxis_Ctrl.bits.b2
#define Y_ACC			YAxis_Ctrl.bits.b3
#define Y_DeC			YAxis_Ctrl.bits.b4
#define Y_CRun			YAxis_Ctrl.bits.b5
#define Y_DStop			YAxis_Ctrl.bits.b6
#define Y_PStart		YAxis_Ctrl.bits.b7
#define Y_LimitDec		YAxis_Ctrl.bits.b8
#define Y_ALARMOC		YAxis_Ctrl.bits.b9
#define Y_SLMTNEN		YAxis_Ctrl.bits.b10
#define Y_SLMTPEN		YAxis_Ctrl.bits.b11
#define Y_ALARMEN		YAxis_Ctrl.bits.b12
#define Y_ArMStop		YAxis_Ctrl.bits.b13
#define Y_LimitStop		YAxis_Ctrl.bits.b14 
#define Y_HLimitFlg		YAxis_Ctrl.bits.b15

#define Z_Dir			ZAxis_Ctrl.bits.b0
#define Z_Cnter			ZAxis_Ctrl.bits.b1
#define Z_Frecy			ZAxis_Ctrl.bits.b2
#define Z_ACC			ZAxis_Ctrl.bits.b3
#define Z_DeC			ZAxis_Ctrl.bits.b4
#define Z_CRun			ZAxis_Ctrl.bits.b5
#define Z_DStop			ZAxis_Ctrl.bits.b6
#define Z_PStart		ZAxis_Ctrl.bits.b7
#define Z_LimitDec		ZAxis_Ctrl.bits.b8
#define Z_ALARMOC		ZAxis_Ctrl.bits.b9
#define Z_SLMTNEN		ZAxis_Ctrl.bits.b10
#define Z_SLMTPEN		ZAxis_Ctrl.bits.b11
#define Z_ALARMEN		ZAxis_Ctrl.bits.b12
#define Z_ArMStop		ZAxis_Ctrl.bits.b13
#define Z_LimitStop		ZAxis_Ctrl.bits.b14 
#define Z_HLimitFlg		ZAxis_Ctrl.bits.b15

#define U_Dir			UAxis_Ctrl.bits.b0  //电机方向
#define U_Cnter			UAxis_Ctrl.bits.b1  //设定距离一点
#define U_Frecy			UAxis_Ctrl.bits.b2  //频率设置
#define U_ACC			UAxis_Ctrl.bits.b3  //加速
#define U_DeC			UAxis_Ctrl.bits.b4  //减速
#define U_CRun			UAxis_Ctrl.bits.b5  //电动
#define U_DStop			UAxis_Ctrl.bits.b6  //减速
#define U_PStart		UAxis_Ctrl.bits.b7  //脉冲计数开始
#define U_LimitDec		UAxis_Ctrl.bits.b8  //硬件限位停止方式
#define U_ALARMOC		UAxis_Ctrl.bits.b9  //驱动器故障电平有效方式
#define U_SLMTNEN		UAxis_Ctrl.bits.b10 //软件负限位使能
#define U_SLMTPEN		UAxis_Ctrl.bits.b11 //软件正限位使能
#define U_ALARMEN		UAxis_Ctrl.bits.b12 //驱动器故障使能
#define U_ARMStop		UAxis_Ctrl.bits.b13 //告警停止方式
#define U_LimitStop	UAxis_Ctrl.bits.b14 //X轴回零停止
#define U_HLimitFlg	UAxis_Ctrl.bits.b15

extern WORD_BITS HardLimit,ServoAlarm;
#define	 X_HLMTP		HardLimit.bits.b0
#define	 X_HLMTN		HardLimit.bits.b1
#define	 Y_HLMTP		HardLimit.bits.b2
#define	 Y_HLMTN		HardLimit.bits.b3
#define	 Z_HLMTP		HardLimit.bits.b4
#define	 Z_HLMTN		HardLimit.bits.b5
#define	 U_HLMTP		HardLimit.bits.b6
#define	 U_HLMTN		HardLimit.bits.b7

#define	 X_SAlarmIn		ServoAlarm.bits.b0
#define	 Y_SAlarmIn		ServoAlarm.bits.b1
#define	 Z_SAlarmIn		ServoAlarm.bits.b2
#define	 U_SAlarmIn		ServoAlarm.bits.b3

extern long X_DistanceCount,Y_DistanceCount,Z_DistanceCount,U_DistanceCount;
extern unsigned long XPluseMoveCount,YPluseMoveCount,ZPluseMoveCount,UPluseMoveCount;
extern unsigned long XPluseDecCount,YPluseDecCount,ZPluseDecCount,UPluseDecCount;
extern SpeedPusleStrct XCurSpeedPusel;
extern SpeedPusleStrct YCurSpeedPusel;
extern SpeedPusleStrct ZCurSpeedPusel;
extern SpeedPusleStrct UCurSpeedPusel;
extern RunSpeedStrct   X_CurSpeed,Y_CurSpeed,Z_CurSpeed,U_CurSpeed;
extern unsigned short X_AccStep,X_DecStep;
extern unsigned short Y_AccStep,Y_DecStep;
extern unsigned short Z_AccStep,Z_DecStep;
extern unsigned short U_AccStep,U_DecStep;
extern unsigned short XPwmStepcounter,YPwmStepcounter,ZPwmStepcounter,UPwmStepcounter;
extern unsigned short XSpeedRatio,YSpeedRatio,ZSpeedRatio,USpeedRatio;//速度比率

extern void ResetServoDrv(unsigned short axis);
extern void MV_Set_Range(unsigned short axis,int wdata);
extern void MV_Set_Acc(unsigned short axis,unsigned short wdata);
extern void MV_Set_Dec(unsigned short axis,unsigned short wdata);
extern void MV_Set_Startv(unsigned short axis,unsigned short wdata);
extern void MV_Set_Speed(unsigned short axis,unsigned short wdata);
extern void MV_Pmov(unsigned short axis,int wdata);
extern void MV_Continue_Move(unsigned short axis,unsigned short dir);
extern void MV_Set_Command_Pos(unsigned short axis,int wdata);
extern long MV_Get_Command_Pos(unsigned short axis);
extern void MV_Dec_Stop(unsigned short axis);
extern void MV_Sudden_Stop(unsigned short axis);
extern void MV_Limit_Stop(unsigned short axis);
extern void MV_Set_Pulse(unsigned short axis,int wdata);
extern void MV_Set_Command_SlMTP(unsigned short axis,int wdata);
extern void MV_Set_Command_SlMTN(unsigned short axis,int wdata);
extern void CalAccDecSpeed(unsigned long Pulsemov,RunSpeedStrct currunspeed,SpeedPusleStrct *curspeedpusel);
extern void CalDecStop(RunSpeedStrct currunspeed,SpeedPusleStrct *curspeedpusel);
extern void CalAccRun(RunSpeedStrct currunspeed,SpeedPusleStrct *curspeedpusel);
extern void X_Pulse_Start();
extern void Y_Pulse_Start();
extern void Z_Pulse_Start();
extern void U_Pulse_Start();

extern void X_Pulse_Stop();
extern void Y_Pulse_Stop();
extern void Z_Pulse_Stop();
extern void U_Pulse_Stop();

extern void XPwmInterruptProgram(void);
extern void YPwmInterruptProgram(void);
extern void ZPwmInterruptProgram(void);
extern void UPwmInterruptProgram(void);

extern void XAxisHLimitProc(void);
extern void YAxisHLimitProc(void);
extern void ZAxisHLimitProc(void);
extern void UAxisHLimitProc(void);

extern void XAxisDrvArmProc(void);
extern void YAxisDrvArmProc(void);
extern void ZAxisDrvArmProc(void);
extern void UAxisDrvArmProc(void);

extern void ServoDrvProct(void);
extern void TimerPulseStart(void);
#endif
