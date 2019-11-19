#include "Global.h"
WORD_BITS cAxisManuRunState;

unsigned short ManuSpeed;
unsigned char cXRstStep,cYRstStep,cZRstStep,cURstStep;
unsigned char cXResumStep,cYResumStep,cZResumStep,cUResumStep;
unsigned char XManulDir,YManulDir,ZManulDir,UManulDir;
unsigned char XLDec = 0, XRDec = 0;
unsigned char YLDec = 0, YRDec = 0;
unsigned char ZLDec = 0, ZRDec = 0;
unsigned char ULDec = 0, URDec = 0;

unsigned short ManualSpeed;
unsigned long ZDotDistance;
unsigned long XDotDistance;
unsigned long YDotDistance;

void ManualProc_XAxis(void);
void ManualProc_YAxis(void);
void ManualProc_ZAxis(void);
void ManualProc_UAxis(void);
void ManualProc_IO(void);
void RebackXaxisOrign(void);
void RebackYaxisOrign(void);
void RebackZaxisOrign(void);
void RebackUaxisOrign(void);
/************************************************/
/*
手动操作

*/
/************************************************/
void ManualAction(void)
{
   //if ((!bRunning) && (!bRBOrigin) && (!bResume) && (!AutoModeSgn))
   {
      ManualProc_XAxis();
      ManualProc_YAxis();
      ManualProc_ZAxis();
      //ManualProc_UAxis();
      ManualProc_IO();
   }
}
/************************************************/
/*
X轴手动-水平排，水平钻
*/
/************************************************/
void ManualProc_XAxis(void)
{
   unsigned long  Speedtmp;
   long Distancetmp;
   Speedtmp = SystemParam->ManuSpeed;
   Distancetmp = SystemParam->DotDistance;
   if (bMVXn) XManulDir = 0;
   if (bMVXp) XManulDir = 1;
   if (!bRBOrigin && !bXRst)
   {
      if (bDotMVST) //寸动
      {
         if ((!X_Dotting) && (!X_DRV))
         {
            if (bMVXn && !X_HLMTN && !X_SLMTN)
            {
               X_Dotting = 1;
               /*if((OnceOnpowerFLG==0)&&(SystemParam->XDistance<Distancetmp))
                               Distancetmp=SystemParam->XDistance;*/
               //设定X轴
               MV_Set_Startv(X_AXIS, 10);
               MV_Set_Speed(X_AXIS, Speedtmp);
               cSetPulse = -PositionToPluse(X_AXIS, Distancetmp);
               MV_Pmov(X_AXIS, cSetPulse);
               bMVXn = 0;
               XManulDir = 0;
            }
            else if (bMVXp && !X_HLMTP && !X_SLMTP)
            {
               X_Dotting = 1;
               /*if((OnceOnpowerFLG==0)&&((SystemParam->XDistance+Distancetmp)>FactoryParam->XAxisPLimit))
               {
                       Distancetmp=(FactoryParam->XAxisPLimit-SystemParam->XDistance);
               }*/
               //设定X轴
               MV_Set_Startv(X_AXIS, 10);
               MV_Set_Speed(X_AXIS, Speedtmp);
               cSetPulse = PositionToPluse(X_AXIS, Distancetmp);
               MV_Pmov(X_AXIS, cSetPulse);
               bMVXp = 0;
               XManulDir = 1;
            }
         }
         if (!X_DRV)
         {
            X_Dotting = 0;
         }
      }
      else
      {
      #if 0
         if ((OnceOnpowerFLG == 0) && (bMVXn || bMVXp))
         {
            if ((XManulDir == 0) && (SystemParam->XDistance <= 100) && (XLDec == 0))
            {
               bMVXn = 0;
               XLDec = 1;
               MV_Dec_Stop(X_AXIS);
            }

            if ((XManulDir == 1) && ((FactoryParam->XAxisPLimit - SystemParam->XDistance) <= 100) && (XRDec == 0))
            {
               bMVXp = 0;
               XRDec = 1;
               MV_Dec_Stop(X_AXIS);
            }
         }
         if ((XManulDir == 0) && (XLDec == 1) && (!X_DRV))
         {
            MV_Set_Speed(X_AXIS, 300);
            cSetPulse = SystemParam->XDistance;
            cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
            if (cSetPulse > 0) MV_Pmov(X_AXIS, -cSetPulse);
            XLDec = 2;
         }
         else if ((XLDec == 2) && (!X_DRV))
         {
            XLDec = 0;
         }
         if ((XManulDir == 1) && (XRDec == 1) && (!X_DRV))
         {
            MV_Set_Speed(X_AXIS, 300);
            cSetPulse = FactoryParam->XAxisPLimit - SystemParam->XDistance;
            cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
            if (cSetPulse > 0) MV_Pmov(X_AXIS, cSetPulse);
            XRDec = 2;
         }
         else if ((XRDec == 2) && (!X_DRV))
         {
            XRDec = 0;
         }
         #endif
         if (!X_DRV && !X_Dotting)
         {
            if (bMVXn && !X_HLMTN && !X_SLMTN && !X_Origin)
            {
               X_Dotting = 1;
               XRDec = 0;
               MV_Set_Startv(X_AXIS, 1);
               MV_Set_Speed(X_AXIS, Speedtmp);
               MV_Continue_Move(X_AXIS, 1);
               XManulDir = 0;
            }
            else if (bMVXp && !X_HLMTP && !X_SLMTP)
            {

               X_Dotting = 1;
               XLDec = 0;
               MV_Set_Startv(X_AXIS, 1);
               MV_Set_Speed(X_AXIS, Speedtmp);
               MV_Continue_Move(X_AXIS, XCW);//0);
               XManulDir = 1;
            }

         }
         if (X_Dotting && !(bMVXn || bMVXp))
         {
            X_Dotting = 0;
            MV_Dec_Stop(X_AXIS);

         }
      }
   }
}
/************************************************/
/*
Y轴手动-垂直1钻

*/
/************************************************/
void ManualProc_YAxis(void)
{
   unsigned long  Speedtmp;
   long Distancetmp;
   Speedtmp = SystemParam->ManuSpeed;
   Distancetmp = SystemParam->DotDistance;
   if (bMVYn) YManulDir = 0;
   if (bMVYp) YManulDir = 1;
   if (!bRBOrigin && !bYRst)
   {
      if (bDotMVST)
      {
         if (!Y_Dotting && (!Y_DRV))
         {
            if (bMVYn && !Y_HLMTN && !Y_SLMTN && !Y_Origin)
            {
               Y_Dotting = 1;

               //设定X轴
               MV_Set_Startv(Y_AXIS, 10);
               MV_Set_Speed(Y_AXIS, Speedtmp);

               cSetPulse = -PositionToPluse(Y_AXIS, Distancetmp);
               MV_Pmov(Y_AXIS, cSetPulse);
               bMVYn = 0;
               YManulDir = 0;
            }
            else if (bMVYp && !Y_HLMTP && !Y_SLMTP)
            {
               Y_Dotting = 1;
               //设定X轴
               MV_Set_Startv(Y_AXIS, 10);
               MV_Set_Speed(Y_AXIS, Speedtmp);

               cSetPulse = PositionToPluse(Y_AXIS, Distancetmp);
               MV_Pmov(Y_AXIS, cSetPulse);
               bMVYp = 0;
               YManulDir = 1;
            }
         }
         if (!Y_DRV)
         {
            Y_Dotting = 0;
         }
      }
      else
      {
         if (!Y_DRV && !Y_Dotting)
         {
            if (bMVYn && !Y_HLMTN && !Y_SLMTN && !Y_Origin)
            {
               Y_Dotting = 1;
               YRDec = 0;
               MV_Set_Startv(Y_AXIS, 10);
               MV_Set_Speed(Y_AXIS, Speedtmp);
               MV_Continue_Move(Y_AXIS, YCW);// 1);
               YManulDir = 0;
            }
            else if (bMVYp && !Y_HLMTP && !Y_SLMTP)
            {
               Y_Dotting = 1;
               YLDec = 0;
               if (YRDec == 1) Speedtmp = 10;
               MV_Set_Startv(Y_AXIS, 10);
               MV_Set_Speed(Y_AXIS, Speedtmp);
               MV_Continue_Move(Y_AXIS, YCCW);// 0);
               YManulDir = 1;
            }
         }
         if (Y_Dotting && (!(bMVYn || bMVYp)))
         {
            Y_Dotting = 0;
            MV_Dec_Stop(Y_AXIS);
         }
      }
   }
}
/************************************************/
/*
Z轴手动 垂直2钻孔
*/
/************************************************/
void ManualProc_ZAxis(void)
{
   unsigned long  Speedtmp;
   long Distancetmp;
   Speedtmp = SystemParam->ManuSpeed;
   Distancetmp = SystemParam->DotDistance;
   
   if (bMVZn) ZManulDir = 0;
   if (bMVZp) ZManulDir = 1;
   if (!bRBOrigin && !bZRst)
   {
      if (bDotMVST)
      {
         if (!Z_Dotting && (!Z_DRV))
         {
            if (bMVZn && !Z_HLMTN && !Z_SLMTN)
            {
               Z_Dotting = 1;
               //设定X轴
               MV_Set_Startv(Z_AXIS, 10);
               MV_Set_Speed(Z_AXIS, Speedtmp);
               cSetPulse = -(Distancetmp * ZGearRatio);
               MV_Pmov(Z_AXIS, cSetPulse);
               bMVZn = 0;
               ZManulDir = 0;

            }
            else if (bMVZp && !Z_HLMTP && !Z_SLMTP)
            {
               Z_Dotting = 1;
               //设定X轴
               MV_Set_Startv(Z_AXIS, 10);
               MV_Set_Speed(Z_AXIS, Speedtmp);
               cSetPulse = (Distancetmp * ZGearRatio);
               MV_Pmov(Z_AXIS, cSetPulse);
               bMVZp = 0;
               ZManulDir = 1;
            }
         }
         if (!Z_DRV)
         {
            Z_Dotting = 0;
         }
      }
      else
      {
         if (!Z_DRV && !Z_Dotting)
         {
            if (bMVZn && !Z_HLMTN && !Z_SLMTN && !Z_Origin)
            {
               Z_Dotting = 1;
               ZRDec = 0;
               MV_Set_Startv(Z_AXIS, 10);
               MV_Set_Speed(Z_AXIS, Speedtmp);
               MV_Continue_Move(Z_AXIS, ZCW);// 1);
               ZManulDir = 0;
            }
            else if (bMVZp && !Z_HLMTP && !Z_SLMTP)
            {
               Z_Dotting = 1;
               ZLDec = 0;
               MV_Set_Startv(Z_AXIS, 10);
               MV_Set_Speed(Z_AXIS, Speedtmp);
               MV_Continue_Move(Z_AXIS, ZCCW);// 0);
               ZManulDir = 1;
            }
         }
         if (Z_Dotting && (!(bMVZn || bMVZp)))
         {
            Z_Dotting = 0;
            MV_Dec_Stop(Z_AXIS);
         }
      }
   }
}
/************************************************/
/*
U轴手动  垂直3钻孔
*/
/************************************************/
void ManualProc_UAxis(void)
{
   unsigned long  Speedtmp;
   long Distancetmp;
   Speedtmp = SystemParam->ManuSpeed;
   Distancetmp = SystemParam->DotDistance;
   if (bMVUn) UManulDir = 0;
   if (bMVUp) UManulDir = 1;
   if (!bRBOrigin && !bURst)
   {
      if (bDotMVST)
      {
         if (!U_Dotting && (!U_DRV))
         {
            if (bMVUn && !U_HLMTN && !U_SLMTN)
            {
               U_Dotting = 1;
               if ((OnceOnpowerFLG == 0) && (SystemParam->UDistance < Distancetmp)) Distancetmp = SystemParam->UDistance;
               //设定X轴
               MV_Set_Startv(U_AXIS, 10);
               MV_Set_Speed(U_AXIS, Speedtmp);
               cSetPulse = -(Distancetmp * UGearRatio);
               MV_Pmov(U_AXIS, cSetPulse);
               bMVUn = 0;
               UManulDir = 0;
            }
            else if (bMVUp && !U_HLMTP && !U_SLMTP)
            {
               U_Dotting = 1;
               if ((OnceOnpowerFLG == 0) && ((SystemParam->UDistance + Distancetmp) > FactoryParam->UAxisPLimit))
               {
                  Distancetmp = (FactoryParam->UAxisPLimit - SystemParam->UDistance);
               }
               //设定X轴
               MV_Set_Startv(U_AXIS, 10);
               MV_Set_Speed(U_AXIS, Speedtmp);
               cSetPulse = (Distancetmp * UGearRatio);
               MV_Pmov(U_AXIS, cSetPulse);
               bMVUp = 0;
               UManulDir = 1;
            }
         }
         if (!U_DRV)
         {
            U_Dotting = 0;
         }
      }
      else
      {
         if ((OnceOnpowerFLG == 0) && (bMVUn || bMVUp))
         {
            if ((UManulDir == 0) && (SystemParam->UDistance <= 100) && (ULDec == 0))
            {
               bMVUn = 0;
               ULDec = 1;
               MV_Dec_Stop(U_AXIS);
            }
            if ((UManulDir == 1) && ((FactoryParam->UAxisPLimit - SystemParam->UDistance) <= 100) && (URDec == 0))
            {
               bMVUp = 0;
               URDec = 1;
               MV_Dec_Stop(U_AXIS);
            }
         }
         if ((UManulDir == 0) && (ULDec == 1) && (!U_DRV))
         {
            MV_Set_Speed(U_AXIS, 300);
            cSetPulse = SystemParam->UDistance;
            cSetPulse *= UGearRatio;
            if (cSetPulse > 0) MV_Pmov(U_AXIS, -cSetPulse);
            ULDec = 2;
         }
         else if ((ULDec == 2) && (!U_DRV))
         {
            ULDec = 0;
         }
         if ((UManulDir == 1) && (URDec == 1) && (!U_DRV))
         {
            MV_Set_Speed(U_AXIS, 300);
            cSetPulse = FactoryParam->UAxisPLimit - SystemParam->UDistance;
            cSetPulse *= UGearRatio;
            if (cSetPulse > 0) MV_Pmov(U_AXIS, cSetPulse);
            URDec = 2;
         }
         else if ((URDec == 2) && (!U_DRV))
         {
            URDec = 0;
         }
         if (!U_DRV && !U_Dotting)
         {
            if (bMVUn && !U_HLMTN && !U_SLMTN)
            {
               U_Dotting = 1;
               URDec = 0;
               MV_Set_Startv(U_AXIS, 10);
               MV_Set_Speed(U_AXIS, Speedtmp);
               MV_Continue_Move(U_AXIS, 1);
               UManulDir = 0;
            }
            else if (bMVUp && !U_HLMTP && !U_SLMTP)
            {
               U_Dotting = 1;
               ULDec = 0;
               if (URDec == 1) Speedtmp = 10;
               MV_Set_Startv(U_AXIS, 10);
               MV_Set_Speed(U_AXIS, Speedtmp);
               MV_Continue_Move(U_AXIS, 0);
               UManulDir = 1;
            }
         }
         if (U_Dotting && (!(bMVUn || bMVUp)))
         {
            ULDec = 0;
            URDec = 0;
            U_Dotting = 0;
            MV_Dec_Stop(U_AXIS);
         }
         if (OnceOnpowerFLG == 0)
         {
            if ((XManulDir == 0) && (SystemParam->UDistance <= 0))
            {
               bMVUn = 0;
               U_Dotting = 0;
               MV_Sudden_Stop(U_AXIS);
            }
         }
      }
   }
}

/************************************************/
/*
IO手动

*/
/************************************************/
void ManualProc_IO(void)
{
   if (MillingMotor_ST)
   {
      MillingMotor_ST = 0;
      Y00 = ~Y00;
   }
   if (DrillMotor_ST)
   {
      DrillMotor_ST = 0;
      Y01 = ~Y01;
   }
   #if 0
   if (M62)
   {
      M62 = 0;
      Y02 = ~Y02;
   }
   if (M63)
   {
      M63 = 0;
      Y03 = ~Y03;
   }
   if (M64)
   {
      M64 = 0;
      Y04 = ~Y04;
   }
   if (M65)
   {
      M65 = 0;
      Y05 = ~Y05;
   }
   if (M66)
   {
      M66 = 0;
      Y06 = ~Y06;
   }
   #endif
   if (M67)
   {
      M67 = 0;
      //if (!Y11 && !Y13 && MillingOrign && DrillingOrign && !MillingLmt && !DrillingLmt)
      {
         Y07 = ~Y07;
      }
   }
   if (PressValve_ST)
   {
      PressValve_ST = 0;

      Y10 = ~Y10;

   }
   if (M69)
   {
      M69 = 0;
      if (!Y07)
      {
         Y11 = ~Y11;
      }
   }
   if (M70)
   {
      M70 = 0;
      Y12 = ~Y12;
   }
   if (M71)
   {
      M71 = 0;
      if (!Y07)
      {
         Y13 = ~Y13;
      }
   }
   if (M72)
   {
      M72 = 0;
      Y14 = ~Y14;
   }
   if (M73)
   {
      M73 = 0;
      Y15 = ~Y15;
   }
   if (M74)
   {
      M74 = 0;
      Y16 = ~Y16;
   }
   if (M75)
   {
      M75 = 0;
      Y17 = ~Y17;
      Y25 = ~Y25;
      Y26 = ~Y26;
   }
   if (M76)
   {
      M76 = 0;
      Y20 = ~Y20;
   }
   if (M77)
   {
      M77 = 0;
      Y21 = ~Y21;
   }
   if (M78)
   {
      M78 = 0;
      Y22 = ~Y22;
   }
   if (M79)
   {
      M79 = 0;
      Y23 = ~Y23;
   }
   if (M80)
   {
      M80 = 0;
      Y24 = ~Y24;
   }
   if (M81)
   {
      M81 = 0;
      Y25 = ~Y25;
   }
}
/************************************************/
/*
XY轴回零

*/
/************************************************/
void RebackOrigin(void)
{
   long PosLimit, NegLimit;
   if (bRBOrigin)
   {
      X_SLMTNEN=0;
      Y_SLMTNEN=0;
      Z_SLMTNEN=0;
      RebackXaxisOrign();
      RebackYaxisOrign();
      RebackZaxisOrign();
      if (!(bXRst || bYRst || bZRst) && !(X_DRV || Y_DRV || Z_DRV))
      {
         
         NegLimit = PositionToPluse(X_AXIS, FactoryParam->XAxisNLimit);
         PosLimit = PositionToPluse(X_AXIS, FactoryParam->XAxisPLimit);
         MV_Set_Command_SlMTN(X_AXIS, NegLimit);
         MV_Set_Command_SlMTP(X_AXIS, PosLimit);
         NegLimit = PositionToPluse(Y_AXIS, FactoryParam->YAxisNLimit);
         PosLimit = PositionToPluse(Y_AXIS, FactoryParam->YAxisPLimit);
         MV_Set_Command_SlMTN(Y_AXIS, NegLimit);
         MV_Set_Command_SlMTP(Y_AXIS, PosLimit);
         NegLimit = PositionToPluse(Z_AXIS, FactoryParam->ZAxisNLimit);
         PosLimit = PositionToPluse(Z_AXIS, FactoryParam->ZAxisPLimit);
         MV_Set_Command_SlMTN(Z_AXIS, NegLimit);
         MV_Set_Command_SlMTP(Z_AXIS, PosLimit);
      }
   }
   if (bXoriginST)
   {
      RebackXaxisOrign();
      if (!(bXRst) && !(X_DRV))
      {
         bXoriginST = 0;
      }
   }
   if (bYoriginST)
   {
      RebackYaxisOrign();
      if (!(bYRst) && !(Y_DRV))
      {
         bYoriginST = 0;
      }
   }
   if (bZoriginST)
   {
      RebackZaxisOrign();
      if (!(bZRst) && !(Z_DRV))
      {
         bZoriginST = 0;
      }
   }
   if (bUoriginST)
   {
      RebackUaxisOrign();
      if (!(bURst) && !(U_DRV))
      {
         bUoriginST = 0;
      }
   }
}
/************************************************/
/*
X轴回原点

*/
/************************************************/
void RebackXaxisOrign(void)
{
   if (cXRstStep == 1)
   {
      if (X_Origin || X_HLMTN || X_SLMTN)
      {
         cXRstStep = 3;
         MV_Set_Startv(X_AXIS, 10);
         MV_Set_Speed(X_AXIS, 100);
         MV_Continue_Move(X_AXIS, XCW);
      }
      else
      {
         /*
              if(!AXIS_DEC)
              {
                      MV_Set_Startv(X_AXIS,10);
                      MV_Set_Speed(X_AXIS,FactoryParam->OriginHighSp);
                      MV_Continue_Move(X_AXIS,1);
                      cXRstStep = 7;
              }
              else
                 */
         {
            MV_Set_Acc(X_AXIS, 300);
            MV_Set_Dec(X_AXIS, 300);
            MV_Set_Startv(X_AXIS, 10);
            MV_Set_Speed(X_AXIS, FactoryParam->XAxisZeroSpeed);
            MV_Continue_Move(X_AXIS, XCCW);
            cXRstStep = 20;
         }
      }
   }
   else if ((cXRstStep == 2) && X_Origin)
   {
      cXRstStep = 3;
   }
   else if ((cXRstStep == 3) && !X_Origin)
   {
      cXRstStep = 4;
      MV_Dec_Stop(X_AXIS);
   }
   else if ((cXRstStep == 4) && !X_DRV)
   {
      cXRstStep = 5;
      MV_Set_Startv(X_AXIS, 10);
      MV_Set_Speed(X_AXIS, 100);
      MV_Continue_Move(X_AXIS, XCCW);
   }
   else if ((cXRstStep == 5) && X_Origin)
   {
      cXRstStep = 6;
      MV_Dec_Stop(X_AXIS);
      //MV_Limit_Stop(X_AXIS);
   }
   else if ((cXRstStep == 6) && !X_DRV)
   {
      cXRstStep = 11;//10;
   }
   else if ((cXRstStep == 7) && (AXIS_DEC))
   {
      cXRstStep = 8;
      MV_Dec_Stop(X_AXIS);
   }
   else if ((cXRstStep == 8) && !X_DRV)
   {
      cXRstStep = 1;
   }
   else if ((cXRstStep == 10) && !X_DRV)
   {
      cSetPulse = -50;
      cSetPulse *= XGearRatio;
      MV_Set_Startv(X_AXIS, 10);
      MV_Set_Speed(X_AXIS, 100);
      MV_Pmov(X_AXIS, cSetPulse);
      cXRstStep = 11;
   }
   else if ((cXRstStep == 11) && !X_DRV)
   {
      bXRst = 0;
      cXRstStep = 0;
      MV_Set_Command_Pos(X_AXIS, 0);
   }
   else if ((cXRstStep == 20) && X_Origin)
   {
      cXRstStep = 21;
      MV_Dec_Stop(X_AXIS);
   }
   else if ((cXRstStep == 21) && !X_DRV)
   {
      cXRstStep = 1;
   }
}
/************************************************/
/*
Y轴回原点

*/
/************************************************/
void RebackYaxisOrign(void)
{
   if (cYRstStep == 1)
   {
      if (Y_Origin || Y_HLMTN || Y_SLMTN)
      {
         cYRstStep = 3;
         MV_Set_Startv(Y_AXIS, 10);
         MV_Set_Speed(Y_AXIS, 10);
         MV_Continue_Move(Y_AXIS, YCCW);
      }
      else
      {
         cYRstStep = 7;
         MV_Set_Startv(Y_AXIS, 10);
         MV_Set_Speed(Y_AXIS, FactoryParam->YAxisZeroSpeed);
         MV_Continue_Move(Y_AXIS, YCW);
      }
   }
   else if ((cYRstStep == 2) && Y_Origin)
   {
      cYRstStep = 3;
   }
   else if ((cYRstStep == 3) && !Y_Origin)
   {
      cYRstStep = 4;
      MV_Dec_Stop(Y_AXIS);
   }
   else if ((cYRstStep == 4) && !Y_DRV)
   {
      cYRstStep = 5;
      MV_Set_Startv(Y_AXIS, 10);
      MV_Set_Speed(Y_AXIS, 10);
      MV_Continue_Move(Y_AXIS, YCW);// 1);
   }
   else if ((cYRstStep == 5) && Y_Origin)
   {
      cYRstStep = 6;
      MV_Limit_Stop(Y_AXIS);
   }
   else if ((cYRstStep == 6) && !Y_DRV)
   {
      cYRstStep = 10;
   }
   else if ((cYRstStep == 7) && (Y_Origin || Y_HLMTN))
   {
      cYRstStep = 8;
      MV_Dec_Stop(Y_AXIS);
   }
   else if ((cYRstStep == 8) && !Y_DRV)
   {
      cYRstStep = 1;
   }
   else if ((cYRstStep == 10) && !Y_DRV)
   {
      cSetPulse = -50;
      cSetPulse *= YGearRatio;
      MV_Set_Startv(Y_AXIS, 5);
      MV_Set_Speed(Y_AXIS, 10);
      MV_Pmov(Y_AXIS, cSetPulse);
      cYRstStep = 11;
   }
   else if ((cYRstStep == 11) && !Y_DRV)
   {
      bYRst = 0;
      cYRstStep = 0;
      MV_Set_Command_Pos(Y_AXIS, 0);
   }
}
/************************************************/
/*
Z轴回原点

*/
/************************************************/
void RebackZaxisOrign(void)
{
   if (cZRstStep == 1)
   {
      if (Z_Origin || Z_HLMTN || Z_SLMTN)
      {
         cZRstStep = 3;
         MV_Set_Startv(Z_AXIS, 10);
         MV_Set_Speed(Z_AXIS, 10);
         MV_Continue_Move(Z_AXIS, ZCCW);// 0);
      }
      else
      {
         cZRstStep = 7;
         MV_Set_Startv(Z_AXIS, 10);
         MV_Set_Speed(Z_AXIS, FactoryParam->ZAxisZeroSpeed);
         MV_Continue_Move(Z_AXIS, ZCW);// 1);
      }
   }
   else if ((cZRstStep == 2) && Z_Origin)
   {
      cZRstStep = 3;
   }
   else if ((cZRstStep == 3) && !Z_Origin)
   {
      cZRstStep = 4;
      MV_Dec_Stop(Z_AXIS);
   }
   else if ((cZRstStep == 4) && !Z_DRV)
   {
      cZRstStep = 5;
      MV_Set_Startv(Z_AXIS, 10);
      MV_Set_Speed(Z_AXIS, 10);
      MV_Continue_Move(Z_AXIS, ZCW);// 1);
   }
   else if ((cZRstStep == 5) && Z_Origin)
   {
      cZRstStep = 6;
      MV_Limit_Stop(Z_AXIS);
   }
   else if ((cZRstStep == 6) && !Z_DRV)
   {
      cZRstStep = 10;
   }
   else if ((cZRstStep == 7) && (Z_Origin || Z_HLMTN))
   {
      cZRstStep = 8;
      MV_Dec_Stop(Z_AXIS);
   }
   else if ((cZRstStep == 8) && !Z_DRV)
   {
      cZRstStep = 1;
   }
   else if ((cZRstStep == 10) && !Z_DRV)
   {
      cSetPulse = -50;
      cSetPulse *= ZGearRatio;
      MV_Set_Startv(Z_AXIS, 5);
      MV_Set_Speed(Z_AXIS, 10);
      MV_Pmov(Z_AXIS, cSetPulse);
      cZRstStep = 11;
   }
   else if ((cZRstStep == 11) && !Z_DRV)
   {
      bZRst = 0;
      cZRstStep = 0;
      MV_Set_Command_Pos(Z_AXIS, 0);
   }
}
/************************************************/
/*
U轴回原点

*/
/************************************************/
void RebackUaxisOrign(void)
{
   if (cURstStep == 1)
   {
      if (U_Origin || U_HLMTN)
      {
         cURstStep = 3;
         MV_Set_Startv(U_AXIS, 10);
         MV_Set_Speed(U_AXIS, 10);
         MV_Continue_Move(U_AXIS, 0);
      }
      else
      {
         cURstStep = 7;
         MV_Set_Startv(U_AXIS, 10);
         MV_Set_Speed(U_AXIS, U_Origin_Speed);
         MV_Continue_Move(U_AXIS, 1);
      }
   }
   else if ((cURstStep == 2) && U_Origin)
   {
      cURstStep = 3;
   }
   else if ((cURstStep == 3) && !U_Origin)
   {
      cURstStep = 4;
      MV_Dec_Stop(U_AXIS);
   }
   else if ((cURstStep == 4) && !U_DRV)
   {
      cURstStep = 5;
      MV_Set_Startv(U_AXIS, 10);
      MV_Set_Speed(U_AXIS, 10);
      MV_Continue_Move(U_AXIS, 1);
   }
   else if ((cURstStep == 5) && U_Origin)
   {
      cURstStep = 6;
      MV_Limit_Stop(U_AXIS);
   }
   else if ((cURstStep == 6) && !U_DRV)
   {
      cURstStep = 10;
   }
   else if ((cURstStep == 7) && (U_Origin || U_HLMTN))
   {
      cURstStep = 8;
      MV_Dec_Stop(U_AXIS);
   }
   else if ((cURstStep == 8) && !U_DRV)
   {
      cURstStep = 1;
   }
   else if ((cURstStep == 10) && !U_DRV)
   {
      cSetPulse = -50;
      cSetPulse *= UGearRatio;
      MV_Set_Startv(U_AXIS, 5);
      MV_Set_Speed(U_AXIS, 10);
      MV_Pmov(U_AXIS, cSetPulse);
      cURstStep = 11;
   }
   else if ((cURstStep == 11) && !U_DRV)
   {
      bURst = 0;
      cURstStep = 0;
      MV_Set_Command_Pos(U_AXIS, 0);
   }
}

