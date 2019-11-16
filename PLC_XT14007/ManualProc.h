#ifndef ManualProc_H
#define ManualProc_H

extern WORD_BITS cAxisManuRunState;
#define  X_Dotting		cAxisManuRunState.bits.b0
#define  Y_Dotting		cAxisManuRunState.bits.b1
#define  Z_Dotting		cAxisManuRunState.bits.b2
#define  U_Dotting		cAxisManuRunState.bits.b3
#define  bXRst			cAxisManuRunState.bits.b8
#define  bYRst			cAxisManuRunState.bits.b9
#define  bZRst			cAxisManuRunState.bits.b10
#define  bURst			cAxisManuRunState.bits.b11

extern unsigned short ManuSpeed;
extern unsigned char cXRstStep,cYRstStep,cZRstStep,cURstStep;
extern unsigned char cXResumStep,cYResumStep,cZResumStep,cUResumStep;
extern unsigned char XManulDir,YManulDir,ZManulDir,UManulDir;
extern unsigned char XLDec,XRDec;
extern unsigned char YLDec,YRDec;
extern unsigned char ZLDec,ZRDec;
extern unsigned char ULDec,URDec;

extern unsigned short ManualSpeed;
extern unsigned long ZDotDistance;
extern unsigned long XDotDistance;
extern unsigned long YDotDistance;

extern void ManualAction(void);
extern void RebackOrigin(void);
extern  void ManualProc_XAxis(void);
extern  void ManualProc_YAxis(void);
extern  void ManualProc_ZAxis(void);
extern  void ManualProc_UAxis(void);
#endif
