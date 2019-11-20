#ifndef AUTORUNPROC_H
#define AUTORUNPROC_H
#define STARTSPD	10
#define NSTEPDLAY  3
#define ACCTIME	10
#define XCONCMP	50

#define MODEXIUB  1
#define MODEXICAO 2

#define bWorkMode1 M90
#define bWorkMode2 M91
#define bWorkMode3 M93
#define MOTOR_SWITCH__TIME 500
extern unsigned char motor_run_flg;
extern char curDrillIndex;
extern unsigned char cAlarmFlag;
extern unsigned char cRunStep,cSlot2Step;
extern unsigned short NextDlay;
extern unsigned short NextStepDlay;
extern unsigned char  VerDrillNum,HorDrillNum;
extern unsigned long  PicFCDist;
extern unsigned long  PicSetionNum;
extern void AutoRun(void);
extern void aotu_run(void);

#endif
