#ifndef ACTION_H
#define ACTION_H
#pragma pack

typedef struct _SystemParamStrct_
{
    long	XDistance;      //0		
    long	YDistance;	//2/
    long	ZDistance;	//4// 		
    long	UDistance;	//6//
    unsigned long  Proctotal;//8//
    unsigned short ManuSpeed;//10
    unsigned short DotDistance;//11
    unsigned short AlarmCode;//12
    unsigned short RunState; //13
    unsigned short ReadNum;	  //14
    unsigned short WriteNum; //15
    unsigned short DrillIdleSpeed; //16
    unsigned short IdleSpeed;  //17
    unsigned short MillingWorkSpeed;//18
    unsigned short DrillWorkSpeed;//19

}SystemParamStrct;
typedef struct _FactoryParamStrct_
{
    long	XAxisPLimit; 		//X轴负极限位	//20
    long	XAxisNLimit; 		//X轴负极限位	//22
    long	YAxisPLimit; 		//X轴负极限位	//24
    long	YAxisNLimit; 		//X轴负极限位	//26
    long	ZAxisPLimit; 		//X轴负极限位	//28
    long	ZAxisNLimit; 		//X轴负极限位	//30
    long	UAxisPLimit; 		//X轴负极限位	//32
    long	UAxisNLimit; 		//X轴负极限位	//34
    unsigned short XAxisAlarmDir;//36 X轴报警电平 0是常开1是常闭
    unsigned short YAxisAlarmDir;//37 Y轴报警电平 0是常开1是常闭
    long        TrimingSiteOrign;//38   修边原点
    long        TrimingDeepthOrign;//40 修边深度原点
    long        DrillSiteOrign;    //42 钻孔原点
    long        DrillDeepthOrign;  //44 钻孔深度原点
    unsigned short DebugSwitch;//46
    unsigned short XAxisZeroSpeed;//47
    unsigned short YAxisZeroSpeed;//48
    unsigned short XAxisAutoZero;      //49
    unsigned short YAxisAutoZero;      //50
    unsigned short ZAxisAlarmDir;//51 Z轴报警电平 0是常开1是常闭
    unsigned short ZAxisZeroSpeed;//52
    unsigned short ZAxisAutoZero;//53
    unsigned long juliao_length;//54   锯料长度
    unsigned long juliao_depth;//56   锯料深度
    unsigned short res[2];//58 2个未用的
    unsigned short Slot_Orign[20];//60  槽中槽起点
    unsigned short Slot_Length[20];//80  槽中槽长度  已满
}FactoryParamStrct;

typedef struct _UserParamStrct_
{
        long   TrimingLength; //100 修边长度
	long   TrimingDeepth;
	unsigned short  WorksDeltaSite[20]; //104 距0点距离		
	unsigned short  WorksLength[20];    //124 长度，不为0的时候是槽	
	unsigned short  WorksDepth[20];     //144 深度, 不能为0	
        unsigned short  res[6];//
        long            StopperShift;       //170 档析偏移
        unsigned short  MillingCycleTime;   //172 铣槽圆整时间	
        unsigned short  WorkMode;           //173 工作模式   
        unsigned short  PressValveOpenTime;  //174  压料打开时间
        unsigned short  PressValveCloseTime;  //175  压料关闭时间
        unsigned short  MillingMotorStartTime; //176  铣电机启动时间
        unsigned short  DrillMotorStartTime;//177    钻电机启动时间
        unsigned short  DrillCycleTime;    //178  钻圆整时间
        unsigned short  DrillKnifeOrign;   //179 钻刀原点
        unsigned short  MillingKnifeOrign; //180 铣刀原点
        unsigned short  DrillHoleOrign;    //181 钻孔原点
        long            ObjectLength;      //182 工件长度
        long            MiddlePoint;       //184中间点位置
        long            HeaderLength;      //186去头长度
        long            EndHearLength;     //188去头长度
        unsigned short  MillingInplcaeTime;//190 铣刀前进到位后等待时间
        unsigned short  MillingLockerTime;  //191 铣刀前进到位后等待时间
        unsigned short  MillingUnLockerTime;//192 铣刀前进到位后等待时间
        unsigned short  SiteIdleSpeed;      //193 位置空走速度 
        unsigned short  DeepthIdleSpeed;    //194 深度空走速度 
        unsigned short  TrimingSpeed;       //195 修编速度 
        unsigned short  DrillFeedSpeed;         //196 钻速度 
        unsigned short  MillingSpeed;       //197 槽速度 
        unsigned short  MillingRadius;      //198 刀直径
        unsigned short  MillingFeed;        //199 槽进给
        unsigned short  MillingFeedSpeed;   //200 槽前进给速度 
        unsigned short  TrimingFeedSpeed;   //201 修边进给速度 
        unsigned short  TrimingRadius;      //202 修边刀直径
        unsigned short  DrillKnifeLength;//203
        unsigned short  TrimingKnifeRadius;//204
        unsigned short  res1[15];//
        unsigned short  Slot_Depth[20];//220  槽中槽深度度  已满

}UserParamStrct;

typedef struct _MortorParamStrct_
{
	unsigned short XCirclingPulse; //240
	unsigned short XMoveDist;      //241
	unsigned short XMotorSpeed;    //242
	unsigned short YCirclingPulse; //243
	unsigned short YMoveDist;      //244
	unsigned short YMotorSpeed;    //245
	unsigned short ZCirclingPulse; //246
	unsigned short ZMoveDist;//247
	unsigned short ZMotorSpeed;	
	unsigned short UCirclingPulse;	
	unsigned short UMoveDist;
	unsigned short UMotorSpeed;
}MortorParamStrct;

typedef struct{
    unsigned short testdata[10];   //400
    
}TestData_str;

typedef struct _PowerDownSaveStrct_   //涓庨�氫俊鏃犲叧
{
	long ZDistance;
	unsigned short CrcDate;
}PowerDownSaveStrct;

#pragma packoption

typedef enum _EParaAddr_
{
    SYSTERMADDR  = 0,   //系统参数
    FACTORYADDR	= 20,
    USERADDR    	= 100,    //X轴当前位置
    MORTORADD     	= 240,    //Y轴当前位置
    EPABUTT
}EParaAddr;

extern WORD_BITS RunAtcion;
#define	   bRBOrigin    RunAtcion.bits.b0	
#define	   NoAlarm	RunAtcion.bits.b1	
#define    bAutoStart   RunAtcion.bits.b2
#define    bFengchiFlag RunAtcion.bits.b3
#define    bAutoStop	RunAtcion.bits.b4

//定义轴数；
#define AxisNum		3
//定义步进伺服
#define X_Axis_SV	1
#define Y_Axis_SV	1
#define Z_Axis_SV	1
#define U_Axis_SV	0
//回零速度
#define X_Origin_Speed  300
#define Y_Origin_Speed  300
#define Z_Origin_Speed  300
#define U_Origin_Speed  300
//M0~M31为系统应用
#define  bRunning		M00 //运行中
#define  bStart			M01 //启动
#define  bResume		M02	//复位中	
#define  bRest			M03 //复位
#define  bStop			M04 //停止
#define  bClean			M05 //产量清零
#define  RDMachParam	M06	//恢复为出厂参数
#define  WRMachParam	M07 //设置为出厂参数
#define  bReadParam   	M08 //读取参数
#define  bWriteParam  	M09 //写参数
#define  bDotMVST		M10 //点动
#define  bZDotMVST		M11 //点动
#define  read_success	M12 //一次，连续
#define  write_success  M13 //一次，连续
#define  bTest			M14
#define  clear_param    M15

#define  bRunDIST_St	M20
#define  bRunDIST		M21

#define bModel1			M22
#define bModel2			M23
#define bModel3			M24
#define bModel4			M25

#define  bMVXp			M32  
#define  bMVXn			M33
#define  bMVYp			M34 
#define  bMVYn			M35  
#define  bMVZp			M36
#define  bMVZn			M37
#define  bMVUp			M38
#define  bMVUn			M39
#define  bXoriginST	M40
#define  bXorigin		M41
#define  bYoriginST	M42
#define  bYorigin		M43
#define  bZoriginST	M44
#define  bZorigin		M45
#define  bUoriginST	M46
#define  bUorigin		M47

#define bFirstWorkDisp_ST      M51
#define bAlarmCode27           M52
#define bAlarmCode29           M53

#define bCurrentMode       M52 // 0  手动  1 准备状态
#define bCurrentMode_ST    M53

#define bTrimingSelect          M54   //修边工作
#define bTrimingSelect_ST       M55   //修边工作
#define bDrillingSelect         M56   //锯料工作
#define bDrillingSelect_ST      M57
#define bFirstWorkSelect         M58   // 0  先修后钻 1 先钻后修
#define bFirstWorkSelect_ST      M59

#define MillingMotor_ST           M60  //铣电机
#define DrillMotor_ST             M61  //铣电机
#define StopperValve_ST           M67  //档料
#define PressValve_ST             M68  //压料

#define EMG_STOP			X01 //急停
#define AUTORUN_IN			X00 //启动
#define OLDAUTORUN_IN			OldX00 //启动


//#define YALIANG_LMT		X03
//#define YALIANG_ORIGIN	X04
#define AXIS_DEC			1

#define MillingMotorAlarm        X05  //铣刀过载
#define DrillMotorAlarm          X06  //钻刀过载
#define GasSgn                   !X07  //气压不够
#define AutoModeSgn              M52  //自动信号
#define AutoModeSgnOld              OldX02  //自动信号
#define StopperLmt               X16  //档料下限位
#define StopperOrign             X15  //档料上限位
#define MillingLmt               X13  //铣刀前进
#define MillingOrign             X14  //铣刀后退
#define DrillingLmt              X04// X17 //钻限位
#define DrillingOrign            X03//    X20 //钻原点
#define OilSgn                   X10
#define	 U_SAlarm_In		X34

//M160~M192为输入位显示
#define X_Origin			I011
#define Y_Origin			I003
#define Z_Origin			I014
#define U_Origin			X37

#define X_HLMTP_IN			X12
#define Y_HLMTP_IN			X04
#define Z_HLMTP_IN			X13
#define U_HLMTP_IN			X35

#define	 X_SAlarm_In		X27
#define	 Y_SAlarm_In		X26
#define	 Z_SAlarm_In		X25


#define MillingMotor             Y00  //铣电机
#define DrillMotor               Y01  //铣电机
#define StopperValve             Y07  //档料
#define PressValve               Y10  //压料

#define MillingValve             Y11  //铣刀前进
#define MillingValveLocker       Y12  //铣刀前进锁位
#define DrillValve               Y13  //钻刀阀


//定义齿轮倍数
#define  XAxisConst		100//461
#define  YAxisConst		100//521
#define  UseAxisNum		1   //运用轴数量

#define  SERVORDLY	      2000;   

//#define bAlarmFlag      M50


#define TrimingSoftOrign  FactoryParam->TrimingDeepthOrign - (UserParam->TrimingRadius / 2) - UserParam->StopperShift
#define DrillingSoftOrign  FactoryParam->DrillDeepthOrign - UserParam->DrillKnifeLength - UserParam->StopperShift

extern unsigned short    PreMenuSel;
extern unsigned short   PreWorkMode;
extern unsigned short   PreDrillkMode;
extern unsigned short   PreDrillDist;
extern unsigned long    Secondtime;
extern unsigned long    Mintuetime;
extern unsigned long    PrevMintuetime;
extern unsigned short   PrevShouqian1;
extern unsigned short   PrevShouqian2;
extern unsigned short   Shouqian1Flag;
extern unsigned short 	MSecondtime;

extern unsigned char OnceOnpowerFLG,NOAirFLG;	//第一次上电标志
extern unsigned char RebackXYFLG;
extern unsigned short	ServorDlay;
extern unsigned short   RstPphlDlay; //复位外设延时

extern long dwRealPosi,cSetPulse;
extern unsigned short XGearRatio,YGearRatio,ZGearRatio,UGearRatio;	//电子此轮比
extern SystemParamStrct *SystemParam;
extern FactoryParamStrct *FactoryParam;
extern MortorParamStrct *MotroParam;
extern UserParamStrct *UserParam;
extern TestData_str *TestData;
extern PowerDownSaveStrct CurDistanceSave;
extern unsigned short StarFilterTime;
extern unsigned short KeyDelay;
extern void ServoInit(void);
extern void Action(void);
extern void CalGearRatio(void);
extern void ResetPeripheral(void);
//extern void PowerDownSave(void);
//extern unsigned char PowerDownLoad (void);
long PluseToPosition(char axis, long p);
long PositionToPluse(char axis, long p);
extern unsigned char bOldX00;
extern char cAutoResetStep;
#endif 
