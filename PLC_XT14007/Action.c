#include "Global.h"

WORD_BITS RunAtcion;

unsigned short    PreMenuSel;
unsigned char cResumeStep;      //∏¥πÈ≤Ω÷Ë
unsigned char OnceOnpowerFLG,NOAirFLG;  //µ⁄“ª¥Œ…œµÁ±Í÷æ
unsigned char RebackXYFLG;
unsigned short	ServorDlay;
unsigned short   RstPphlDlay; //∏¥ŒªÕ‚…Ë—” ±
unsigned short   PreWorkMode;
unsigned short   PreDrillkMode;
unsigned short   PreDrillDist;
unsigned long    Secondtime;
unsigned long    Mintuetime;
unsigned long    PrevMintuetime;
unsigned short   PrevShouqian1;
unsigned short   PrevShouqian2;
unsigned short   Shouqian1Flag;
unsigned short FlashbufTmp[4096/2];
unsigned short MSecondtime;
unsigned short StarFilterTime;
unsigned short KeyDelay;

long dwRealPosi,cSetPulse;
unsigned short XGearRatio,YGearRatio,ZGearRatio,UGearRatio;     //µÁ◊”¥À¬÷±»
SystemParamStrct *SystemParam;
FactoryParamStrct *FactoryParam;
MortorParamStrct *MotroParam;
UserParamStrct *UserParam;
TestData_str *TestData;
PowerDownSaveStrct CurDistanceSave;

unsigned long gas_alarm_delay;
unsigned long oil_alarm_delay;

unsigned short cRunDistStep;
void ReadRobotCurrent(void);
void KeyBoardProc(void);
void UserKeyBoardProc(void);
void ResumeLocation(void);
void SaveResumeLct(void);
void OncePowerResume(void);
void AlarmProtect(void);
void SaveSetParamToFlash(void);
void StopAxis(void);
//void  RunDistProc(void);

//◊‘∂Øπ§◊˜ƒ£ Ω≥ı ºªØ◊¥Ã¨
char cAutoResetStep = 0;
//◊‘∂Øπ§◊˜ƒ£ Ωµ»¥˝—” ±
unsigned long dwAutoStepResetDlay = 0;


/************************************************/
/*
∂Ø◊˜‘À––

*/
/************************************************/
void Action(void)
{
   OncePowerResume();
   ReadRobotCurrent();
   ManualAction();
   aotu_run();
   KeyBoardProc();
   ResumeLocation();
   RebackOrigin();
   AlarmProtect();
   SaveSetParamToFlash();
}
/*****************************/
/*
  Ëá™Âä®ËøêË°åÁ®ãÂ∫è
*/
/************************************************/
/*
µ±«∞¡Ω÷·◊¥Ã¨

*/
/************************************************/
void ReadRobotCurrent(void)
{
   //static unsigned long dwReadPosiCount = 0;
   SystemParam->XDistance = PluseToPosition(X_AXIS, MV_Get_Command_Pos(X_AXIS));  //∂¡µ±«∞X÷·Œª÷√
   SystemParam->YDistance = PluseToPosition(Y_AXIS, MV_Get_Command_Pos(Y_AXIS));  //∂¡µ±«∞Y÷·Œª÷√
   SystemParam->ZDistance = PluseToPosition(Z_AXIS, MV_Get_Command_Pos(Z_AXIS));  //∂¡µ±«∞Z÷·Œª÷√
//   SystemParam->UDistance = MV_Get_Command_Pos(U_AXIS) / UGearRatio;  //∂¡µ±«∞U÷·Œª÷√

   cMidleCoil[20].Val = cInputVal1.v[0];
   cMidleCoil[21].Val = cInputVal1.v[1];
   cMidleCoil[22].Val = cInputVal2.v[0];
   cMidleCoil[23].Val = cInputVal2.v[1];

   cMidleCoil[30].Val = cOutputVal1.v[0];;
   cMidleCoil[30 + 1].Val = cOutputVal1.v[1];
   cMidleCoil[30 + 2].Val = cOutputVal2.v[0];
   cMidleCoil[30 + 3].Val = cOutputVal2.v[1];

   X_HLMTP = X_HLMTP_IN;
   Y_HLMTP = Y_HLMTP_IN;
   Z_HLMTP = Z_HLMTP_IN;
   U_HLMTP = 0; //U_HLMTP_IN;

   X_SAlarmIn = X_SAlarm_In != FactoryParam->XAxisAlarmDir;
   Y_SAlarmIn = Y_SAlarm_In != FactoryParam->YAxisAlarmDir;
   Z_SAlarmIn = Z_SAlarm_In != FactoryParam->ZAxisAlarmDir;;
   U_SAlarmIn = 0;//!U_SAlarm_In;


   //SystemParam->Proctotal = cRunStep;
}

unsigned char bOldX00;
/************************************************/
/*
∞¥º¸¥¶¿Ì

*/
/************************************************/
void KeyBoardProc(void)
{
   unsigned char buffer[4], i;

   if ((bStart) || (X00 && bOldX00 == 0) && ready_state) //∆Ù∂Ø
   {
      bStart = 0;
      if ((!bRunning) && (!bRBOrigin) && (!bResume) && (SystemParam->AlarmCode == 0))
      {
         ResetPeripheral();
         bAlarmCode29 = 0;
       //  if (!bCurrentMode)  SystemParam->AlarmCode = 21;
       //  if (!bTrimingSelect && !bDrillingSelect) SystemParam->AlarmCode = 26;
        // if (!StopperLmt) SystemParam->AlarmCode = 22;
        // if (!MillingOrign) SystemParam->AlarmCode = 23;
        // if (!DrillingOrign) SystemParam->AlarmCode = 25;

         if (SystemParam->AlarmCode == 0)
         {
            bRunning = 1;
            cRunStep = 1;
         }

      }
   }
   if (ready)
   {
      ready=0;
      ready_state = ~ready_state;
      Y07 = ready_state;
   }
   /*
   if (X03)
   {
      MillingMotor = 1;
   }
   if (X04)
   {
      MillingMotor = 0;
   }
   */
   bOldX00 = X00;
   if (AutoModeSgn && SystemParam->AlarmCode == 21) SystemParam->AlarmCode = 0;
   if (StopperOrign && SystemParam->AlarmCode == 22) SystemParam->AlarmCode = 0;
   //if (MillingOrign && SystemParam->AlarmCode == 23) SystemParam->AlarmCode = 0;
   //if (DrillingOrign && SystemParam->AlarmCode == 25) SystemParam->AlarmCode = 0;
   if ((M54 || M56) && SystemParam->AlarmCode == 26) SystemParam->AlarmCode = 0;
   if (MillingMotor && SystemParam->AlarmCode == 24) SystemParam->AlarmCode = 0;

   if (bStop || EMG_STOP) //Õ£÷π
   {
        bStop = 0;
        cAlarmFlag = 1;
        if(SystemParam->AlarmCode == 8)
            SystemParam->AlarmCode = 0;

   }

    if(cAlarmFlag > 0)
    {
        cAlarmFlag= 0;

      motor_run_flg = 0;
      cResumeStep=0;
      bRBOrigin = 0;
      bAutoStart = 0;
      bAutoStop = 0;
      bXRst = 0;
      bYRst = 0;
      bZRst = 0;
      bURst = 0;
      bResume = 0;
      bRunning = 0;
      bDotMVST = 0;
      //bZDotMVST = 0;
      cRunStep = 0;

      bRunDIST_St = 0;
      cRunDistStep = 0;

      cOutputVal1.Val = 0;

      cAutoResetStep = 0;
      M52 = 0;
      ResetPeripheral();
      StopAxis();
    }
   
   if ((bRest) && !bResume) //∏¥Œª
   {
      bRest = 0;
      bRunning = 0;
      bResume = 1;
      bCurrentMode = 0;
      cResumeStep = 1;

      bAlarmCode29 = 0;
   }
   if (bXorigin && !bXoriginST) //X÷·ªÿ¡„
   {
      bXorigin = 0;
      bXoriginST = 1;
      bXRst = 1;
      cXRstStep = 1;
   }
   if (bYorigin && !bYoriginST) //Y÷·ªÿ¡„
   {
      bYorigin = 0;
      bYoriginST = 1;
      bYRst = 1;
      cYRstStep = 1;
   }
   if (bZorigin && !bZoriginST) //Y÷·ªÿ¡„
   {
      bZorigin = 0;
      bZoriginST = 1;
      bZRst = 1;
      cZRstStep = 1;
   }
   if (bUorigin && !bUoriginST) //X÷·ªÿ¡„
   {
      bUorigin = 0;
      bUoriginST = 1;
      bURst = 1;
      cURstStep = 1;
   }
   if (bClean)
   {
      bClean = 0;
      SystemParam->Proctotal = 0;
      memcpy(buffer, &SystemParam->Proctotal, 4);
      for (i = 0; i < 4; i++)
      {
         Write24C04((16 + i), buffer[i]);
      }
   }

}
/************************************************/
/*
”√ªß∞¥º¸≥Ã–Ú

*/
/************************************************/
void UserKeyBoardProc(void)
{


}
/************************************************/
/*
∏¥πÈ

*/
/************************************************/
void ResumeLocation(void)
{

   TestData->testdata[0]=cResumeStep;
   //TestData->testdata[1]=cResumeStep;
   if (bResume)
   {
      if (cResumeStep == 1)
      {
         MV_Dec_Stop(X_AXIS);
         MV_Dec_Stop(Y_AXIS);
         MV_Dec_Stop(Z_AXIS);
         cResumeStep = 2;
      }
      else if ((cResumeStep == 2) && (RstPphlDlay == 0))
      {
         cOutputVal1.Val=0;  //ÂÖ≥Èó≠ÊâÄÊúâËæìÂá∫
         cResumeStep = 3;
      }
      else if ((cResumeStep == 3))
      {
         if (OnceOnpowerFLG)
         {
            bRBOrigin = 1;
            bYRst = 1;
            bZRst = 1;
            bXRst = 0;
            cXRstStep = 0;
            cYRstStep = 1;
            cZRstStep = 1;
            cResumeStep = 10;
         }
         else
         {
            cResumeStep=4;
         }
      }
      else if (cResumeStep == 4)
      {
         MV_Set_Startv(Y_AXIS, 10);
         MV_Set_Speed(Y_AXIS, FactoryParam->YAxisZeroSpeed);
         dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
         cSetPulse = 0 - dwRealPosi;
         MV_Pmov(Y_AXIS, cSetPulse);

         MV_Set_Startv(Z_AXIS, 10);
         MV_Set_Speed(Z_AXIS, FactoryParam->ZAxisZeroSpeed);
         dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
         cSetPulse = 0 - dwRealPosi;
         MV_Pmov(Z_AXIS, cSetPulse);

         cResumeStep = 5;
      }
      else if (cResumeStep == 5 && !(Y_DRV) && !Z_DRV)
      {
         MV_Set_Startv(X_AXIS, 10);
         MV_Set_Speed(X_AXIS, FactoryParam->YAxisZeroSpeed);
         dwRealPosi = MV_Get_Command_Pos(X_AXIS);
         cSetPulse = 0 - dwRealPosi;
         MV_Pmov(X_AXIS, cSetPulse);
         cResumeStep = 6;
      }
      else if ((cResumeStep == 6) && !(X_DRV))
      {
         cResumeStep = 12;
      }
      else if ((cResumeStep == 10) && !(Y_DRV || Z_DRV) && !(bYRst || bZRst))
      {
         bXRst = 1;
         cXRstStep = 1;
         cResumeStep = 11;
      }
      else if ((cResumeStep == 11) && !(X_DRV) && !(bXRst))
      {
         bRBOrigin = 0;
         cResumeStep = 12;
      }
      else if ((cResumeStep == 12) && !(X_DRV))
      {
         OnceOnpowerFLG = 0;
         ready_state=0;
         cResumeStep = 0;
         bResume = 0;
      }
   }
}
/************************************************/
/*
±£¥Ê∏¥πÈ

*/
/************************************************/
void SaveResumeLct(void)
{

}
/************************************************/
/*
…œµÁΩœµ∂

*/
/************************************************/
void OncePowerResume(void)
{
   if (OnceOnpowerFLG)
   {
      if (SystemParam->AlarmCode == 0) SystemParam->AlarmCode = 1;
      bRunning = 0;
   }
   else
   {
      if (SystemParam->AlarmCode == 1) SystemParam->AlarmCode = 0;
   }
}
static unsigned long alarmTick1 = 0;
static unsigned long alarmTick2 = 0;
static unsigned long alarmTick3 = 0;
static unsigned long alarmTick4 = 0;
/************************************************/
/*
∏ÊæØ±£ª§

*/
/************************************************/
void AlarmProtect(void)
{
   if (AxisNum > 0)
   {
      /*if(X_HLMTN)
      {	
              SystemParam->AlarmCode=3;
              if(bRunning)
              {
                      bRunning=0;
                      MV_Dec_Stop(X_AXIS);
                      cRunStep=0;
              }
      } 
      */
      if (X_HLMTP)
      {
         SystemParam->AlarmCode = 4;
         if (bRunning)
         {
            bRunning = 0;
            MV_Dec_Stop(X_AXIS);
            cRunStep = 0;
         }
      }
      if (X_SLMTN)
      {
         SystemParam->AlarmCode = 11;
         if (bRunning)
         {
            bRunning = 0;
            //bStop = 1;
            MV_Dec_Stop(X_AXIS);
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 11) SystemParam->AlarmCode = 0;
      }
      if (X_SLMTP)
      {
         SystemParam->AlarmCode = 12;
         if (bRunning)
         {
            bRunning = 0;
            //bStop = 1;
            MV_Dec_Stop(X_AXIS);
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 12) SystemParam->AlarmCode = 0;
      }
      if (X_ALARM)
      {
         SystemParam->AlarmCode = 19;
         if (bRunning)
         {
            bRunning = 0;
            MV_Dec_Stop(X_AXIS);
            cOutputVal1.Val=0;  //ÂÖ≥Èó≠ÊâÄÊúâËæìÂá∫
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 19) SystemParam->AlarmCode = 0;
      }
   }
   if (AxisNum > 1)
   {
      
      /*if(Y_HLMTN)
      {	
              SystemParam->AlarmCode=5;
              if(bRunning)
              {
                      bRunning=0;
                      MV_Dec_Stop(Y_AXIS);
                      cRunStep=0;
              }
      }*/ 
      
      if(Y_HLMTP)
      {
          SystemParam->AlarmCode=5;
          if(bRunning)
          {
              bRunning=0;
              MV_Dec_Stop(Y_AXIS);
              cRunStep=0;
          }
      }
      if (Y_SLMTN)
      {
         SystemParam->AlarmCode = 13;
         if (bRunning)
         {
            bRunning = 0;
            bStop = 1;
            MV_Dec_Stop(Y_AXIS);
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 13) 
            SystemParam->AlarmCode = 0;
      }
      if (Y_SLMTP)
      {
         SystemParam->AlarmCode = 14;
         if (bRunning)
         {
            bRunning = 0;
            bStop = 1;
            MV_Dec_Stop(Y_AXIS);
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 14) SystemParam->AlarmCode = 0;
      }
      if (Y_ALARM)
      {
         SystemParam->AlarmCode = 20;
         if (bRunning)
         {
            bRunning = 0;
            MV_Dec_Stop(Y_AXIS);
            cOutputVal1.Val=0;  //ÂÖ≥Èó≠ÊâÄÊúâËæìÂá∫
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 20) SystemParam->AlarmCode = 0;
      }
   }
   if (AxisNum > 2)
   {
      /*if(Z_HLMTN)
      {	
              SystemParam->AlarmCode=7;
              if(bRunning)
              {
                      bRunning=0;
                      MV_Dec_Stop(Z_AXIS);
                      cRunStep=0;
              }
      }*/
      if(Z_HLMTP)
      {
          SystemParam->AlarmCode=6;
          if(bRunning)
          {
              bRunning=0;
              MV_Dec_Stop(Z_AXIS);
              cRunStep=0;
          }
      }
      if (Z_SLMTP)
      {
         SystemParam->AlarmCode = 16;
         if (bRunning)
         {
            bRunning = 0;
            MV_Dec_Stop(Z_AXIS);
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 16) 
            SystemParam->AlarmCode = 0;
      }
      if (Z_SLMTN)
      {
         SystemParam->AlarmCode = 15;
         if (bRunning)
         {
            MV_Dec_Stop(Z_AXIS);
            bRunning = 0;
            bStop = 1; 
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 15) 
            SystemParam->AlarmCode = 0;
      }
      if (Z_ALARM)
      {
         SystemParam->AlarmCode = 17;
         if (bRunning)
         {
            bRunning = 0;
            bStop = 1;
            MV_Dec_Stop(Z_AXIS);
            cOutputVal1.Val=0;  //ÂÖ≥Èó≠ÊâÄÊúâËæìÂá∫
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 17) 
            SystemParam->AlarmCode = 0;
      }
   }
   if (AxisNum > 3)
   {
      if (U_HLMTN)
      {
         SystemParam->AlarmCode = 9;
         if (bRunning)
         {
            bRunning = 0;
            MV_Dec_Stop(U_AXIS);
            cRunStep = 0;
         }
      }
      if (U_HLMTP)
      {
         SystemParam->AlarmCode = 10;
         if (bRunning)
         {
            bRunning = 0;
            MV_Dec_Stop(U_AXIS);
            cRunStep = 0;
         }
      }
      if (U_SLMTP)
      {
         SystemParam->AlarmCode = 18;
         if (bRunning)
         {
            bRunning = 0;
            MV_Dec_Stop(U_AXIS);
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 18) SystemParam->AlarmCode = 0;
      }
      if (U_ALARM)
      {
         SystemParam->AlarmCode = 22;
         if (bRunning)
         {
            bRunning = 0;
            MV_Dec_Stop(U_AXIS);
            cRunStep = 0;
         }
      }
      else
      {
         if (SystemParam->AlarmCode == 22) SystemParam->AlarmCode = 0;
      }
   }

 /*  if (StopperOrign == StopperValve ||
       StopperLmt != StopperValve)
   {
      if (alarmTick1 < dwTickCount)
      {
         alarmTick1 = dwTickCount  + 5000;
         SystemParam->AlarmCode = 28;
      }

   }
   else
   {
      alarmTick1 = dwTickCount  + 5000;
      if (SystemParam->AlarmCode == 28) 
        SystemParam->AlarmCode = 0;
   }*/

/*
   if (MillingLmt != MillingValve || MillingOrign == MillingValve)
   {
      if (alarmTick2 < dwTickCount)
      {
         alarmTick2 = dwTickCount  + 5000;
         SystemParam->AlarmCode = 6;
      }
   }
   else
   {
      alarmTick2 = dwTickCount  + 5000;
      if (SystemParam->AlarmCode == 6) SystemParam->AlarmCode = 0;
   }
*/
/*
   if (DrillingLmt != DrillValve || DrillingOrign == DrillValve)
   {
      if (alarmTick3 < dwTickCount)
      {
         alarmTick3 = dwTickCount  + 5000;
         SystemParam->AlarmCode = 7;
      }
   }
   else
   {
      alarmTick3 = dwTickCount  + 5000;
      if (SystemParam->AlarmCode == 7) SystemParam->AlarmCode = 0;
   }
*/
     if (GasSgn)
     {
         SystemParam->AlarmCode = 3;
         if (gas_alarm_delay==0)
         {
            if (bRunning)
            {
               bRunning = 0;
               cRunStep = 0;
               cOutputVal1.Val=0;  //ÂÖ≥Èó≠ÊâÄÊúâËæìÂá∫
            }
         }
    }
    else 
    {
       if (SystemParam->AlarmCode == 3)
       { 
        SystemParam->AlarmCode = 0;
       }
       gas_alarm_delay=5000;
    }

    if (!X10)
    {
        SystemParam->AlarmCode = 21;
        if (oil_alarm_delay==0)
        {
           if (bRunning)
           {
              bRunning = 0;
              cRunStep = 0;
              cOutputVal1.Val=0;  //ÂÖ≥Èó≠ÊâÄÊúâËæìÂá∫
           }
        }
   }
   else 
   {
      if (SystemParam->AlarmCode == 21) 
      { 
          SystemParam->AlarmCode = 0;
      }
      oil_alarm_delay=5000;
   }


    if (!MillingMotorAlarm)
    {
        SystemParam->AlarmCode = 30;
        if (bRunning)
        {
           bRunning = 0;
           cRunStep = 0;
           cOutputVal1.Val=0;  //ÂÖ≥Èó≠ÊâÄÊúâËæìÂá∫
        }
    }
    else if (SystemParam->AlarmCode == 30) 
    {
        SystemParam->AlarmCode = 0;
    }
    
   /* if (DrillMotorAlarm)
    {
        SystemParam->AlarmCode = 29;
    }
    else if (SystemParam->AlarmCode == 29) 
    {
        SystemParam->AlarmCode = 0;
    }*/
    if (EMG_STOP)
    {
      SystemParam->AlarmCode = 2;
    }
    else if (SystemParam->AlarmCode == 2) 
    {    
        SystemParam->AlarmCode = 0;
    }
}
/************************************************/
/*
≈Á”Õ¥¶¿Ì

*/
/************************************************/
void SaveSetParamToFlash(void)
{
   unsigned char buffertmp[512];//, i;
   unsigned short i = 0;
   static unsigned long show_time=0;
   if(show_time < dwTickCount)
   {
      write_success = 0;
      read_success = 0;
   }
   if (bWriteParam)
   {
      bWriteParam = 0;
      for (i = 0; i < 240; i++)
      {
         //FlashbufTmp[i] = cDataArea[USERADDR + i];
         FlashbufTmp[i] = cDataArea[i];
      }

      {
         EraseSector(SystemParam->ReadNum * 4096);
         ProgramPage(SystemParam->ReadNum * 4096, FlashbufTmp);
      }
      write_success = 1;
      show_time = dwTickCount + 2000;
   }
   if (clear_param)
   {
      clear_param=0;
      for (i=0; i<20; i++)
      {
         FactoryParam->Slot_Orign[i] = 0;
         FactoryParam->Slot_Length[i] = 0;
         UserParam->Slot_Depth[i] = 0;
      }
   }
   if (bReadParam)
   {
      bReadParam = 0;

      ReadPage(0 + SystemParam->ReadNum * 4096, FlashbufTmp);
      for (i = 0; i < 20; i++)
      {
         //UserParam->WorksDeltaSite[i] = FlashbufTmp[i + 104 - USERADDR];
         //UserParam->WorksLength[i] = FlashbufTmp[i + 124 - USERADDR];
         //UserParam->WorksDepth[i] = FlashbufTmp[i + 144 - USERADDR];

         UserParam->WorksDeltaSite[i] = FlashbufTmp[i + 104];
         UserParam->WorksLength[i] = FlashbufTmp[i + 124];
         UserParam->WorksDepth[i] = FlashbufTmp[i + 144];

         FactoryParam->Slot_Orign[i] = FlashbufTmp[i + 60];
         FactoryParam->Slot_Length[i] = FlashbufTmp[i + 80];
         UserParam->Slot_Depth[i] = FlashbufTmp[i + 220];
         /*buffertmp[4 + i * 2] = UserParam->WorksDeltaSite[i];
         buffertmp[5 + i * 2] = UserParam->WorksDeltaSite[i] >> 8;
         buffertmp[24 + i * 2] = UserParam->WorksLength[i];
         buffertmp[25 + i * 2] = UserParam->WorksLength[i] >> 8;
         buffertmp[44 + i * 2] = UserParam->WorksDepth[i];
         buffertmp[45 + i * 2] = UserParam->WorksDepth[i] >> 8;
         */
         buffertmp[120 + i * 2] = FactoryParam->Slot_Orign[i];
         buffertmp[121 + i * 2] = FactoryParam->Slot_Orign[i] >> 8;
         buffertmp[160 + i * 2] = FactoryParam->Slot_Length[i];
         buffertmp[161 + i * 2] = FactoryParam->Slot_Length[i] >> 8;  
         buffertmp[440 + i * 2] = UserParam->Slot_Depth[i];
         buffertmp[441 + i * 2] = UserParam->Slot_Depth[i] >> 8; 
         
         buffertmp[208 + i * 2] = UserParam->WorksDeltaSite[i];
         buffertmp[209 + i * 2] = UserParam->WorksDeltaSite[i] >> 8;
         buffertmp[248 + i * 2] = UserParam->WorksLength[i];
         buffertmp[249 + i * 2] = UserParam->WorksLength[i] >> 8;
         buffertmp[288 + i * 2] = UserParam->WorksDepth[i];
         buffertmp[289 + i * 2] = UserParam->WorksDepth[i] >> 8;

      }
      UserParam->TrimingLength = FlashbufTmp[101];
      UserParam->TrimingLength <<= 8;
      UserParam->TrimingLength |= FlashbufTmp[100];

      UserParam->TrimingDeepth = FlashbufTmp[103];
      UserParam->TrimingDeepth <<= 8;
      UserParam->TrimingDeepth |= FlashbufTmp[102];

      buffertmp[200] = UserParam->TrimingLength;
      buffertmp[201] = UserParam->TrimingLength >> 8;
      buffertmp[202] = UserParam->TrimingLength >> 16;
      buffertmp[203] = UserParam->TrimingLength >> 24;

      buffertmp[204] = UserParam->TrimingDeepth;
      buffertmp[205] = UserParam->TrimingDeepth >> 8;
      buffertmp[206] = UserParam->TrimingDeepth >> 16;
      buffertmp[207] = UserParam->TrimingDeepth >> 24;

      for (i = 0; i < 40; i++)
      {
         Write24C04(120 + i, buffertmp[120 + i]);
         Write24C04(160 + i, buffertmp[160 + i]);
         Write24C04(440 + i, buffertmp[440 + i]);

         Write24C04(208 + i, buffertmp[208 + i]);
         Write24C04(248 + i, buffertmp[248 + i]);
         Write24C04(288 + i, buffertmp[288 + i]);         
      }
       
      for (i = 200; i < 208; i++)
      {
         Write24C04(i, buffertmp[i]);
      }
      /*
      for (i = 0; i < 200; i++)
      {
         cDataArea[80 + i] = FlashbufTmp[i];
         buffertmp[2 * i + 1] = (cDataArea[USERADDR + i]) >> 8;
         buffertmp[2 * i] = cDataArea[USERADDR + i] & 0x00ff;
      }
      for (i = 0; i < 200; i++)
      {
         Write24C04(200 + i, buffertmp[i]);
      }
      */
      read_success = 1;
      show_time = dwTickCount + 2000;
   }
   if (RDMachParam)
   {
      RDMachParam = 0;
      ReadPage(200 * 4096, FlashbufTmp);
      for (i = 0; i < 250; i++)
      {
         cDataArea[i] = FlashbufTmp[i];
         buffertmp[2 * i + 1] = (cDataArea[i]) >> 8;
         buffertmp[2 * i] = cDataArea[i] & 0x00ff;
      }
      for (i = 0; i < 250; i++)
      {
         Write24C04(i, buffertmp[i]);
      }
   }
   if (WRMachParam)
   {
      WRMachParam = 0;
      memcpy(FlashbufTmp, cDataArea, MEMSIZE);
      EraseSector(100 * 4096);
      ProgramPage(100 * 4096, FlashbufTmp);
   }
}
/************************************************/
/*
‘⁄Õ£÷πŒª ±£¨Õ‚…Ë∏¥Œª


*/
/************************************************/
void ResetPeripheral(void)
{

   RstPphlDlay = 500;
}
/************************************************/
/*
‘⁄Õ£÷πŒª ±£¨÷·Õ£÷π


*/
/************************************************/
void StopAxis(void)
{
    if(X_DRV)MV_Dec_Stop(X_AXIS);
    if(Y_DRV)MV_Dec_Stop(Y_AXIS);
    if(Z_DRV)MV_Dec_Stop(Z_AXIS);
}
/************************************************/
/*
º∆À„≥›¬÷±»º∞ÀŸ∂»±»¬ 
*/
/************************************************/
void CalGearRatio(void)
{
   unsigned long speedratiotmp, gearratiotmp;
   //if ((MotroParam->XMotorSpeed == 0) || (MotroParam->XMotorSpeed > 5000)) 
   MotroParam->XMotorSpeed = 1200 * 1;
   //if ((MotroParam->YMotorSpeed == 0) || (MotroParam->YMotorSpeed > 5000)) 
   MotroParam->YMotorSpeed = 1200 * 1;
   //if ((MotroParam->ZMotorSpeed == 0) || (MotroParam->ZMotorSpeed > 5000)) 
   MotroParam->ZMotorSpeed = 1200 * 1;
   //if ((MotroParam->UMotorSpeed == 0) || (MotroParam->UMotorSpeed > 5000)) 
   MotroParam->UMotorSpeed = 1200;

   //if (MotroParam->XCirclingPulse == 0) 
   MotroParam->XCirclingPulse = 5000;
   //if (MotroParam->YCirclingPulse == 0) 
   MotroParam->YCirclingPulse = 10000;
   //if (MotroParam->ZCirclingPulse == 0) 
   MotroParam->ZCirclingPulse = 10000;
   //if (MotroParam->UCirclingPulse == 0) 
   MotroParam->UCirclingPulse = 10000;

   if (MotroParam->XMoveDist == 0) MotroParam->XMoveDist = 1000;
   if (MotroParam->YMoveDist == 0) MotroParam->YMoveDist = 1000;
   if (MotroParam->ZMoveDist == 0) MotroParam->ZMoveDist = 1000;
   if (MotroParam->UMoveDist == 0) MotroParam->UMoveDist = 1000;

   speedratiotmp = (MotroParam->XMotorSpeed / 60);
   speedratiotmp *= MotroParam->XCirclingPulse;
   speedratiotmp /= 1000;
   XSpeedRatio = speedratiotmp;

   speedratiotmp = (MotroParam->YMotorSpeed / 60);
   speedratiotmp *= MotroParam->YCirclingPulse;
   speedratiotmp /= 1000;
   YSpeedRatio = speedratiotmp;

   speedratiotmp = (MotroParam->ZMotorSpeed / 60);
   speedratiotmp *= MotroParam->ZCirclingPulse;
   speedratiotmp /= 1000;
   ZSpeedRatio = speedratiotmp;

   speedratiotmp = (MotroParam->UMotorSpeed / 60);
   speedratiotmp *= MotroParam->UCirclingPulse;
   speedratiotmp /= 1000;
   USpeedRatio = speedratiotmp;

   if (XSpeedRatio == 0) XSpeedRatio = 100;
   if (YSpeedRatio == 0) YSpeedRatio = 100;
   if (ZSpeedRatio == 0) ZSpeedRatio = 100;
   if (USpeedRatio == 0) USpeedRatio = 100;


   gearratiotmp = MotroParam->XMoveDist;
   gearratiotmp = MotroParam->XCirclingPulse / gearratiotmp;
   XGearRatio = gearratiotmp;

   gearratiotmp = MotroParam->YMoveDist;
   gearratiotmp = MotroParam->YCirclingPulse / gearratiotmp;
   YGearRatio = gearratiotmp;

   gearratiotmp = MotroParam->ZMoveDist;
   gearratiotmp = MotroParam->ZCirclingPulse / gearratiotmp;
   ZGearRatio = gearratiotmp;

   gearratiotmp = MotroParam->XMoveDist;
   gearratiotmp = MotroParam->XCirclingPulse / gearratiotmp;
   XGearRatio = gearratiotmp;

   gearratiotmp = MotroParam->UMoveDist;
   gearratiotmp = MotroParam->UCirclingPulse / gearratiotmp;
   UGearRatio = gearratiotmp;

   if (XGearRatio == 0) XGearRatio = 10;
   if (YGearRatio == 0) YGearRatio = 10;
   if (ZGearRatio == 0) ZGearRatio = 10;
   if (UGearRatio == 0) UGearRatio = 10;
}
/************************************************/
/*
…œµÁ πƒ‹À≈∑˛«˝∂Ø∆˜

*/
/************************************************/
void ServoInit(void)
{
   if (AxisNum > 0) ResetServoDrv(X_AXIS);
   if (AxisNum > 1) ResetServoDrv(Y_AXIS);
   if (AxisNum > 2) ResetServoDrv(Z_AXIS);
   if (AxisNum > 3) ResetServoDrv(U_AXIS);
   ServorDlay = 3000; //—” ±500ms
   while (ServorDlay) ReadInput();
}
/************************************************/
/*
∂œµÁ±£¥Ê
*/
/************************************************/
/*****************************************************************************
CRC–£—È
*****************************************************************************/
/*CRC ±Ì∏Ò*/
#if 0
static unsigned char  crc_table_hi[] = {
   0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
   0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
   0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
   0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
   0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
   0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
   0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
   0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
   0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
   0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
   0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
   0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
   0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
   0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
   0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
   0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
   0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
   0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
   0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
   0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
   0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
   0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
   0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
   0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
   0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
   0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};
//
static unsigned char crc_table_lo[] = {
   0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
   0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
   0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
   0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
   0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
   0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
   0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
   0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
   0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
   0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
   0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
   0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
   0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
   0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
   0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
   0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
   0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
   0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
   0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
   0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
   0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
   0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
   0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
   0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
   0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
   0x43, 0x83, 0x41, 0x81, 0x80, 0x40

};
/*****************************************************************************
 * –£—ÈCRC
 * 
 * @Author LXZ (2016/5/26)
 * 
 * @param src 
 * @param length 
 * 
 * @return unsigned short 
 *****************************************************************************/
static unsigned short crc_calc(void *src, int length)
{
   unsigned char lo = 0xff, hi = 0xff;
   unsigned char index = 0;
   unsigned char *ptr = (unsigned char *)src;

   while (length > 0)
   {
      length--;
      index = hi ^ (*ptr);
      hi = lo ^ crc_table_hi[index];
      lo = crc_table_lo[index];
      ptr++;
   }
   return 0x0100 * lo + hi;
}
void Crc24c04Save(unsigned short WriteAddr, unsigned short *pBuffer, unsigned short sizenum)
{
   unsigned char i, buffertmp[10];
   unsigned short crctmp1;
   crctmp1 = crc_calc(pBuffer, sizenum - 2);
   pBuffer[sizenum / 2 - 1] = crctmp1;
   for (i = 0; i < sizenum / 2; i++)
   {
      buffertmp[2 * i + 1] = (pBuffer[i]) >> 8;
      buffertmp[2 * i] = pBuffer[i] & 0x00ff;
   }
   for (i = 0; i < sizenum; i++)
   {
      Write24C04(WriteAddr + i, buffertmp[i]);
   }
}
/*
void PowerDownSave(void)
{
   unsigned short buffertmp[10];
   if (MSecondtime == 1)
   {
      CurDistanceSave.ZDistance = SystemParam->ZDistance;
      memcpy(buffertmp, &CurDistanceSave, 6);
      Crc24c04Save(120, buffertmp, 6);
   }
   else if (MSecondtime >= 2)
   {
      MSecondtime = 0;
      CurDistanceSave.ZDistance = SystemParam->ZDistance;
      memcpy(buffertmp, &CurDistanceSave, 6);
      Crc24c04Save(140, buffertmp, 6);
   }
}

/*****************************************************************************
¥¯±∏∑›µƒµƒFlash∂¡
*****************************************************************************/
/*
unsigned char PowerDownLoad(void)
{
   unsigned char Flag = 1;
   unsigned short crctmp1;
   unsigned short buffertmp[10];
   memcpy(&CurDistanceSave, cDataArea + 60, 6);
   crctmp1 = crc_calc(&CurDistanceSave, 6);
   if (crctmp1 != 0)
   {
      memcpy(&CurDistanceSave, cDataArea + 70, 6);
      crctmp1 = crc_calc(&CurDistanceSave, 6);
      if (crctmp1 != 0)
      {CurDistanceSave.ZDistance = 0; Flag = 0;}
   }
   else
   {
      memcpy(buffertmp, &CurDistanceSave, 6);
      Crc24c04Save(140, buffertmp, 6);
   }
   return Flag;
}
*/
/*****************************************************************************
‘À––÷¡◊º±∏∫√Œª÷√
*****************************************************************************/
void  RunDistProc(void)
{

}
#endif
long PluseToPosition(char axis, long p)
{
   long pluse = 1;
   long dis = 1;
   double value = 0;
   switch (axis)
   {
   case X_AXIS:
      pluse = MotroParam->XCirclingPulse;
      dis = MotroParam->XMoveDist;
      break;
   case Y_AXIS:
      pluse = MotroParam->YCirclingPulse;
      dis = MotroParam->YMoveDist;
      break;
   case Z_AXIS:
      pluse = MotroParam->ZCirclingPulse;
      dis = MotroParam->ZMoveDist;
      break;
   }

   value  = p;
   value *= dis;
   value /= pluse;
   if (value > 0)
   {
      value += 0.5;
   }
   else
   {
      value -= 0.5;
   }
   return (long)value;
}

long PositionToPluse(char axis, long p)
{
   long pluse = 1;
   long dis = 1;
   double value = 0;
   switch (axis)
   {
   case X_AXIS:
      pluse = MotroParam->XCirclingPulse;
      dis = MotroParam->XMoveDist;
      break;
   case Y_AXIS:
      pluse = MotroParam->YCirclingPulse;
      dis = MotroParam->YMoveDist;
      break;
   case Z_AXIS:
      pluse = MotroParam->ZCirclingPulse;
      dis = MotroParam->ZMoveDist;
      break;
   }

   value  = p;
   value *= pluse;
   value /= dis;
   if (value > 0)
   {
      value += 0.5;
   }
   else
   {
      value -= 0.5;
   }
   return (long)value;
}

