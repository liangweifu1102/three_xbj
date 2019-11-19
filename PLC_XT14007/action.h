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
    long	XAxisPLimit; 		//X÷·∏∫º´œﬁŒª	//20
    long	XAxisNLimit; 		//X÷·∏∫º´œﬁŒª	//22
    long	YAxisPLimit; 		//X÷·∏∫º´œﬁŒª	//24
    long	YAxisNLimit; 		//X÷·∏∫º´œﬁŒª	//26
    long	ZAxisPLimit; 		//X÷·∏∫º´œﬁŒª	//28
    long	ZAxisNLimit; 		//X÷·∏∫º´œﬁŒª	//30
    long	UAxisPLimit; 		//X÷·∏∫º´œﬁŒª	//32
    long	UAxisNLimit; 		//X÷·∏∫º´œﬁŒª	//34
    unsigned short XAxisAlarmDir;//36 X÷·±®æØµÁ∆Ω 0 «≥£ø™1 «≥£±’
    unsigned short YAxisAlarmDir;//37 Y÷·±®æØµÁ∆Ω 0 «≥£ø™1 «≥£±’
    long        x_drill1_dis;    //38   –ﬁ±ﬂ‘≠µ„
    long        dill_origin_dis1;//40    //Èì£ËæπÂéüÁÇπ
    long        x_drill2_dis;    //42 ◊Íø◊‘≠µ„
    long        dill_origin_dis2; //44◊µ   //ÊßΩÂéüÁÇπ
    unsigned short DebugSwitch;  //46
    unsigned short XAxisZeroSpeed;//47
    unsigned short YAxisZeroSpeed;//48
    unsigned short XAxisAutoZero;      //49
    unsigned short YAxisAutoZero;      //50
    unsigned short ZAxisAlarmDir;//51 Z÷·±®æØµÁ∆Ω 0 «≥£ø™1 «≥£±’
    unsigned short ZAxisZeroSpeed;//52
    unsigned short ZAxisAutoZero;//53
    unsigned long juliao_length;//54   æ‚¡œ≥§∂»
    unsigned long juliao_depth;//56   æ‚¡œ…Ó∂»
    unsigned short res[2];//58 2∏ˆŒ¥”√µƒ
    unsigned short Slot_Orign[20];//60  ≤€÷–≤€∆µ„
    unsigned short Slot_Length[20];//80  ≤€÷–≤€≥§∂»  “—¬˙
}FactoryParamStrct;

typedef struct _UserParamStrct_
{
    long   TrimingLength;    //100 –ﬁ±ﬂ≥§∂»
    long   TrimingDeepth;    //102
    unsigned short  WorksDeltaSite[20]; //104 æ‡0µ„æ‡¿Î		
    unsigned short  WorksLength[20];    //124 ≥§∂»£¨≤ªŒ™0µƒ ±∫Ú «≤€	
    unsigned short  WorksDepth[20];     //144 …Ó∂», ≤ªƒ‹Œ™0	
    unsigned short  res[6];//
    long            StopperShift;       //170 µµŒˆ∆´“∆
    unsigned short  MillingCycleTime;   //172 œ≥≤€‘≤’˚ ±º‰	
    unsigned short  WorkMode;           //173 π§◊˜ƒ£ Ω   
    unsigned short  PressValveOpenTime;  //174  —π¡œ¥Úø™ ±º‰
    unsigned short  PressValveCloseTime;  //175  —π¡œπÿ±’ ±º‰
    unsigned short  xb_motor_start_time; //176  œ≥µÁª˙∆Ù∂Ø ±º‰
    unsigned short  xc_motor_start_time;//177    ◊ÍµÁª˙∆Ù∂Ø ±º‰
    unsigned short  DrillCycleTime;    //178  ◊Í‘≤’˚ ±º‰
    unsigned short  DrillKnifeOrign;   //179 ◊Íµ∂‘≠µ„
    unsigned short  MillingKnifeOrign; //180 œ≥µ∂‘≠µ„
    unsigned short  DrillHoleOrign;    //181 ◊Íø◊‘≠µ„
    long            ObjectLength;      //182 π§º˛≥§∂»
    long            MiddlePoint;       //184÷–º‰µ„Œª÷√
    long            HeaderLength;      //186»•Õ∑≥§∂»
    long            EndHearLength;     //188»•Õ∑≥§∂»
    unsigned short  MillingInplcaeTime;//190 œ≥µ∂«∞Ω¯µΩŒª∫Ûµ»¥˝ ±º‰
    unsigned short  MillingLockerTime;  //191 œ≥µ∂«∞Ω¯µΩŒª∫Ûµ»¥˝ ±º‰
    unsigned short  MillingUnLockerTime;//192 œ≥µ∂«∞Ω¯µΩŒª∫Ûµ»¥˝ ±º‰
    unsigned short  x_idl_speed;      //193 XÁ©∫
    
    unsigned short  y_idl_speed;    //194 YÁ©∫
    
    unsigned short  x_work_speed;       //195 xÂ∑•
 
    unsigned short  y_work_speed;     //196yÂ∑•
    
    unsigned short  z_work_speed;       //197 zÂ∑•
 
    unsigned short  z_idl_speed;      //198 ZÁ©∫
    
    unsigned short x_acc_time;     //199
    unsigned short x_dec_time;     //200
    unsigned short no_work_time;   //201

    unsigned short  TrimingRadius;      //202 –ﬁ±ﬂµ∂÷±æ∂
    unsigned short  DrillKnifeLength;//203
    unsigned short  TrimingKnifeRadius;//204
    unsigned short  res1[15];//
    unsigned short  Slot_Depth[20];//220  ≤€÷–≤€…Ó∂»∂»  “—¬˙

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
	unsigned short ZMoveDist;      //247
	unsigned short ZMotorSpeed;	   //248
	unsigned short UCirclingPulse; //249	
	unsigned short UMoveDist;      //250
	unsigned short UMotorSpeed;    //251
    unsigned short mode_lift;      //252
    unsigned short mode_right;     //253
    unsigned short xb_one_feed;    //254
    unsigned short xc_one_feed;    //255
}MortorParamStrct;

typedef struct{
    unsigned short testdata[10];   //400
    
}TestData_str;

typedef struct _PowerDownSaveStrct_   //‰∏éÈÄö‰ø°Êó†ÂÖ≥
{
	long ZDistance;
	unsigned short CrcDate;
}PowerDownSaveStrct;

#pragma packoption

typedef enum _EParaAddr_
{
    SYSTERMADDR  = 0,   //œµÕ≥≤Œ ˝
    FACTORYADDR	= 20,
    USERADDR    	= 100,    //X÷·µ±«∞Œª÷√
    MORTORADD     	= 240,    //Y÷·µ±«∞Œª÷√
    EPABUTT
}EParaAddr;

extern WORD_BITS RunAtcion;
#define	   bRBOrigin    RunAtcion.bits.b0	
#define	   NoAlarm	RunAtcion.bits.b1	
#define    bAutoStart   RunAtcion.bits.b2
#define    bFengchiFlag RunAtcion.bits.b3
#define    bAutoStop	RunAtcion.bits.b4

//∂®“Â÷· ˝£ª
#define AxisNum		3
//∂®“Â≤ΩΩ¯À≈∑˛
#define X_Axis_SV	1
#define Y_Axis_SV	1
#define Z_Axis_SV	1
#define U_Axis_SV	0
//ªÿ¡„ÀŸ∂»
#define X_Origin_Speed  300
#define Y_Origin_Speed  300
#define Z_Origin_Speed  300
#define U_Origin_Speed  300
//M0~M31Œ™œµÕ≥”¶”√
#define  bRunning		M00 //‘À––÷–
#define  bStart			M01 //∆Ù∂Ø
#define  bResume		M02	//∏¥Œª÷–	
#define  bRest			M03 //∏¥Œª
#define  bStop			M04 //Õ£÷π
#define  bClean			M05 //≤˙¡ø«Â¡„
#define  RDMachParam	M06	//ª÷∏¥Œ™≥ˆ≥ß≤Œ ˝
#define  WRMachParam	M07 //…Ë÷√Œ™≥ˆ≥ß≤Œ ˝
#define  bReadParam   	M08 //∂¡»°≤Œ ˝
#define  bWriteParam  	M09 //–¥≤Œ ˝
#define  bDotMVST		M10 //µ„∂Ø
#define  bZDotMVST		M11 //µ„∂Ø
#define  read_success	M12 //“ª¥Œ£¨¡¨–¯
#define  write_success  M13 //“ª¥Œ£¨¡¨–¯
#define  feed_xb	    M14
#define  clear_param    M15
#define  feed_xc        M16

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

#define bCurrentMode       M52 // 0   ÷∂Ø  1 ◊º±∏◊¥Ã¨
#define bCurrentMode_ST    M53

#define bTrimingSelect          M54   //–ﬁ±ﬂπ§◊˜
#define bTrimingSelect_ST       M55   //–ﬁ±ﬂπ§◊˜
#define bDrillingSelect         M56   //æ‚¡œπ§◊˜
#define bDrillingSelect_ST      M57
#define bFirstWorkSelect         M58   // 0  œ»–ﬁ∫Û◊Í 1 œ»◊Í∫Û–ﬁ
#define bFirstWorkSelect_ST      M59

#define MillingMotor_ST           M60  //œ≥µÁª˙
#define DrillMotor_ST             M61  //œ≥µÁª˙
#define StopperValve_ST           M67  //µµ¡œ
#define PressValve_ST             M68  //—π¡œ

#define EMG_STOP			X01 //º±Õ£
#define AUTORUN_IN			X00 //∆Ù∂Ø
#define OLDAUTORUN_IN			OldX00 //∆Ù∂Ø


//#define YALIANG_LMT		X03
//#define YALIANG_ORIGIN	X04
#define AXIS_DEC			1

#define MillingMotorAlarm        X05  //œ≥µ∂π˝‘ÿ
#define DrillMotorAlarm          X06  //◊Íµ∂π˝‘ÿ
#define GasSgn                   !X07  //∆¯—π≤ªπª
#define AutoModeSgn              M52  //◊‘∂Ø–≈∫≈
#define AutoModeSgnOld              OldX02  //◊‘∂Ø–≈∫≈
#define StopperLmt               X16  //µµ¡œœ¬œﬁŒª
#define StopperOrign             X15  //µµ¡œ…œœﬁŒª
#define MillingLmt               X13  //œ≥µ∂«∞Ω¯
#define MillingOrign             X14  //œ≥µ∂∫ÛÕÀ
#define DrillingLmt              X04// X17 //◊ÍœﬁŒª
#define DrillingOrign            X03//    X20 //◊Í‘≠µ„
#define OilSgn                   X10
#define	 U_SAlarm_In		 X34

//M160~M192Œ™ ‰»ÎŒªœ‘ æ
#define X_Origin			I011
#define Y_Origin			I013
#define Z_Origin			I003

#define U_Origin			X37

#define X_HLMTP_IN			X12
#define Y_HLMTP_IN			X14
#define Z_HLMTP_IN			X04

#define U_HLMTP_IN			X35

#define	 X_SAlarm_In		X27
#define	 Y_SAlarm_In		X26
#define	 Z_SAlarm_In		X25


#define MillingMotor             Y00  //œ≥µÁª˙
#define DrillMotor               Y01  //œ≥µÁª˙
#define StopperValve             Y07  //µµ¡œ
#define PressValve               Y10  //—π¡œ

#define MillingValve             Y11  //œ≥µ∂«∞Ω¯
#define MillingValveLocker       Y12  //œ≥µ∂«∞Ω¯À¯Œª
#define DrillValve               Y13  //◊Íµ∂∑ß


//∂®“Â≥›¬÷±∂ ˝
#define  XAxisConst		100//461
#define  YAxisConst		100//521
#define  UseAxisNum		1   //‘À”√÷· ˝¡ø

#define  SERVORDLY	      2000;   

//#define bAlarmFlag      M50


#define TrimingSoftOrign  800
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

extern unsigned char OnceOnpowerFLG,NOAirFLG;	//µ⁄“ª¥Œ…œµÁ±Í÷æ
extern unsigned char RebackXYFLG;
extern unsigned short	ServorDlay;
extern unsigned short   RstPphlDlay; //∏¥ŒªÕ‚…Ë—” ±

extern long dwRealPosi,cSetPulse;
extern unsigned short XGearRatio,YGearRatio,ZGearRatio,UGearRatio;	//µÁ◊”¥À¬÷±»
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
