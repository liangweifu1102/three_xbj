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
    long	XAxisPLimit; 		//X�Ḻ����λ	//20
    long	XAxisNLimit; 		//X�Ḻ����λ	//22
    long	YAxisPLimit; 		//X�Ḻ����λ	//24
    long	YAxisNLimit; 		//X�Ḻ����λ	//26
    long	ZAxisPLimit; 		//X�Ḻ����λ	//28
    long	ZAxisNLimit; 		//X�Ḻ����λ	//30
    long	UAxisPLimit; 		//X�Ḻ����λ	//32
    long	UAxisNLimit; 		//X�Ḻ����λ	//34
    unsigned short XAxisAlarmDir;//36 X�ᱨ����ƽ 0�ǳ���1�ǳ���
    unsigned short YAxisAlarmDir;//37 Y�ᱨ����ƽ 0�ǳ���1�ǳ���
    long        TrimingSiteOrign;//38   �ޱ�ԭ��
    long        TrimingDeepthOrign;//40 �ޱ����ԭ��
    long        DrillSiteOrign;    //42 ���ԭ��
    long        DrillDeepthOrign;  //44 ������ԭ��
    unsigned short DebugSwitch;//46
    unsigned short XAxisZeroSpeed;//47
    unsigned short YAxisZeroSpeed;//48
    unsigned short XAxisAutoZero;      //49
    unsigned short YAxisAutoZero;      //50
    unsigned short ZAxisAlarmDir;//51 Z�ᱨ����ƽ 0�ǳ���1�ǳ���
    unsigned short ZAxisZeroSpeed;//52
    unsigned short ZAxisAutoZero;//53
    unsigned long juliao_length;//54   ���ϳ���
    unsigned long juliao_depth;//56   �������
    unsigned short res[2];//58 2��δ�õ�
    unsigned short Slot_Orign[20];//60  ���в����
    unsigned short Slot_Length[20];//80  ���в۳���  ����
}FactoryParamStrct;

typedef struct _UserParamStrct_
{
        long   TrimingLength; //100 �ޱ߳���
	long   TrimingDeepth;
	unsigned short  WorksDeltaSite[20]; //104 ��0�����		
	unsigned short  WorksLength[20];    //124 ���ȣ���Ϊ0��ʱ���ǲ�	
	unsigned short  WorksDepth[20];     //144 ���, ����Ϊ0	
        unsigned short  res[6];//
        long            StopperShift;       //170 ����ƫ��
        unsigned short  MillingCycleTime;   //172 ϳ��Բ��ʱ��	
        unsigned short  WorkMode;           //173 ����ģʽ   
        unsigned short  PressValveOpenTime;  //174  ѹ�ϴ�ʱ��
        unsigned short  PressValveCloseTime;  //175  ѹ�Ϲر�ʱ��
        unsigned short  MillingMotorStartTime; //176  ϳ�������ʱ��
        unsigned short  DrillMotorStartTime;//177    ��������ʱ��
        unsigned short  DrillCycleTime;    //178  ��Բ��ʱ��
        unsigned short  DrillKnifeOrign;   //179 �굶ԭ��
        unsigned short  MillingKnifeOrign; //180 ϳ��ԭ��
        unsigned short  DrillHoleOrign;    //181 ���ԭ��
        long            ObjectLength;      //182 ��������
        long            MiddlePoint;       //184�м��λ��
        long            HeaderLength;      //186ȥͷ����
        long            EndHearLength;     //188ȥͷ����
        unsigned short  MillingInplcaeTime;//190 ϳ��ǰ����λ��ȴ�ʱ��
        unsigned short  MillingLockerTime;  //191 ϳ��ǰ����λ��ȴ�ʱ��
        unsigned short  MillingUnLockerTime;//192 ϳ��ǰ����λ��ȴ�ʱ��
        unsigned short  SiteIdleSpeed;      //193 λ�ÿ����ٶ� 
        unsigned short  DeepthIdleSpeed;    //194 ��ȿ����ٶ� 
        unsigned short  TrimingSpeed;       //195 �ޱ��ٶ� 
        unsigned short  DrillFeedSpeed;         //196 ���ٶ� 
        unsigned short  MillingSpeed;       //197 ���ٶ� 
        unsigned short  MillingRadius;      //198 ��ֱ��
        unsigned short  MillingFeed;        //199 �۽���
        unsigned short  MillingFeedSpeed;   //200 ��ǰ�����ٶ� 
        unsigned short  TrimingFeedSpeed;   //201 �ޱ߽����ٶ� 
        unsigned short  TrimingRadius;      //202 �ޱߵ�ֱ��
        unsigned short  DrillKnifeLength;//203
        unsigned short  TrimingKnifeRadius;//204
        unsigned short  res1[15];//
        unsigned short  Slot_Depth[20];//220  ���в���ȶ�  ����

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

typedef struct _PowerDownSaveStrct_   //与通信无关
{
	long ZDistance;
	unsigned short CrcDate;
}PowerDownSaveStrct;

#pragma packoption

typedef enum _EParaAddr_
{
    SYSTERMADDR  = 0,   //ϵͳ����
    FACTORYADDR	= 20,
    USERADDR    	= 100,    //X�ᵱǰλ��
    MORTORADD     	= 240,    //Y�ᵱǰλ��
    EPABUTT
}EParaAddr;

extern WORD_BITS RunAtcion;
#define	   bRBOrigin    RunAtcion.bits.b0	
#define	   NoAlarm	RunAtcion.bits.b1	
#define    bAutoStart   RunAtcion.bits.b2
#define    bFengchiFlag RunAtcion.bits.b3
#define    bAutoStop	RunAtcion.bits.b4

//����������
#define AxisNum		3
//���岽���ŷ�
#define X_Axis_SV	1
#define Y_Axis_SV	1
#define Z_Axis_SV	1
#define U_Axis_SV	0
//�����ٶ�
#define X_Origin_Speed  300
#define Y_Origin_Speed  300
#define Z_Origin_Speed  300
#define U_Origin_Speed  300
//M0~M31ΪϵͳӦ��
#define  bRunning		M00 //������
#define  bStart			M01 //����
#define  bResume		M02	//��λ��	
#define  bRest			M03 //��λ
#define  bStop			M04 //ֹͣ
#define  bClean			M05 //��������
#define  RDMachParam	M06	//�ָ�Ϊ��������
#define  WRMachParam	M07 //����Ϊ��������
#define  bReadParam   	M08 //��ȡ����
#define  bWriteParam  	M09 //д����
#define  bDotMVST		M10 //�㶯
#define  bZDotMVST		M11 //�㶯
#define  read_success	M12 //һ�Σ�����
#define  write_success  M13 //һ�Σ�����
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

#define bCurrentMode       M52 // 0  �ֶ�  1 ׼��״̬
#define bCurrentMode_ST    M53

#define bTrimingSelect          M54   //�ޱ߹���
#define bTrimingSelect_ST       M55   //�ޱ߹���
#define bDrillingSelect         M56   //���Ϲ���
#define bDrillingSelect_ST      M57
#define bFirstWorkSelect         M58   // 0  ���޺��� 1 �������
#define bFirstWorkSelect_ST      M59

#define MillingMotor_ST           M60  //ϳ���
#define DrillMotor_ST             M61  //ϳ���
#define StopperValve_ST           M67  //����
#define PressValve_ST             M68  //ѹ��

#define EMG_STOP			X01 //��ͣ
#define AUTORUN_IN			X00 //����
#define OLDAUTORUN_IN			OldX00 //����


//#define YALIANG_LMT		X03
//#define YALIANG_ORIGIN	X04
#define AXIS_DEC			1

#define MillingMotorAlarm        X05  //ϳ������
#define DrillMotorAlarm          X06  //�굶����
#define GasSgn                   !X07  //��ѹ����
#define AutoModeSgn              M52  //�Զ��ź�
#define AutoModeSgnOld              OldX02  //�Զ��ź�
#define StopperLmt               X16  //��������λ
#define StopperOrign             X15  //��������λ
#define MillingLmt               X13  //ϳ��ǰ��
#define MillingOrign             X14  //ϳ������
#define DrillingLmt              X04// X17 //����λ
#define DrillingOrign            X03//    X20 //��ԭ��
#define OilSgn                   X10
#define	 U_SAlarm_In		X34

//M160~M192Ϊ����λ��ʾ
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


#define MillingMotor             Y00  //ϳ���
#define DrillMotor               Y01  //ϳ���
#define StopperValve             Y07  //����
#define PressValve               Y10  //ѹ��

#define MillingValve             Y11  //ϳ��ǰ��
#define MillingValveLocker       Y12  //ϳ��ǰ����λ
#define DrillValve               Y13  //�굶��


//������ֱ���
#define  XAxisConst		100//461
#define  YAxisConst		100//521
#define  UseAxisNum		1   //����������

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

extern unsigned char OnceOnpowerFLG,NOAirFLG;	//��һ���ϵ��־
extern unsigned char RebackXYFLG;
extern unsigned short	ServorDlay;
extern unsigned short   RstPphlDlay; //��λ������ʱ

extern long dwRealPosi,cSetPulse;
extern unsigned short XGearRatio,YGearRatio,ZGearRatio,UGearRatio;	//���Ӵ��ֱ�
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
