#include "Global.h"
/************************************************/
/*
通信内存及通信变量初始化

*/
/************************************************/
void ComMenInit(void)
{

}
/************************************************/
/*
初始化系统变量

*/
/************************************************/
//运行变量初始化
void InitVariable(void)
{
   unsigned short ch, k;
   memset(cDataArea, 0, 512 * 2);
   for (ch = 0; ch < 255; ch++)
   {
      k = (ch << 1);
      cDataArea[ch] = ((unsigned short)Read24C04(k + 1) << 8) + Read24C04(k);
   }
   cXRstStep = 0;
   cYRstStep = 0;
   SystemParam = (SystemParamStrct *)&cDataArea[SYSTERMADDR];
   FactoryParam = (FactoryParamStrct *)&cDataArea[FACTORYADDR];
   UserParam = (UserParamStrct *)&cDataArea[USERADDR];
   MotroParam = (MortorParamStrct *)&cDataArea[MORTORADD];
   TestData = (TestData_str *)(cDataArea + 400);
   NextDlay = 0;
   NextStepDlay = 0;
   OnceOnpowerFLG = 1;
   NOAirFLG = 1;
   RebackXYFLG = 1;
   SystemParam->AlarmCode = 0;
   bFengchiFlag = 0;
   if (UserParam->WorkMode > 2)
   {
      UserParam->WorkMode = 0;
   }
   MotroParam->XCirclingPulse = 10000;
   MotroParam->YCirclingPulse = 10000;
   MotroParam->ZCirclingPulse = 10000;
   if (UserParam->TrimingRadius < 10000 || UserParam->TrimingRadius > 25000)
   {
      UserParam->TrimingRadius = 15000;
   }
   if (FactoryParam->XAxisAutoZero > 1)
   {
      FactoryParam->XAxisAutoZero = 0;
   }
   if (FactoryParam->YAxisAutoZero > 1)
   {
      FactoryParam->YAxisAutoZero = 0;
   }
   if (FactoryParam->ZAxisAutoZero > 1)
   {
      FactoryParam->ZAxisAutoZero = 0;
   }
}
/************************************************/
/*
初始化是否的速度

*/
/************************************************/
void ServoSpeedInit(void)
{
   if (AxisNum > 0)
   {
      X_ALARMEN = X_Axis_SV; //驱动器故障使能
      MV_Set_Range(X_AXIS, 100);
      MV_Set_Acc(X_AXIS, 100 + MotroParam->x_acc_time);
      MV_Set_Dec(X_AXIS, 100 + MotroParam->x_dec_time);
      MV_Set_Startv(X_AXIS, 10);
      MV_Set_Speed(X_AXIS, 400);
      MV_Set_Command_Pos(X_AXIS, 0);
      CalDecStop(X_CurSpeed, &XCurSpeedPusel);
      CalAccRun(X_CurSpeed, &XCurSpeedPusel);
   }
   if (AxisNum > 1)
   {
      Y_ALARMEN = Y_Axis_SV; //驱动器故障使能
      MV_Set_Range(Y_AXIS, 100);
      MV_Set_Acc(Y_AXIS, 150);
      MV_Set_Dec(Y_AXIS, 150);
      MV_Set_Startv(Y_AXIS, 10);
      MV_Set_Speed(Y_AXIS, 400);
      MV_Set_Command_Pos(Y_AXIS, 0);
      CalDecStop(Y_CurSpeed, &YCurSpeedPusel);
      CalAccRun(Y_CurSpeed, &YCurSpeedPusel);
   }
   if (AxisNum > 2)
   {
      Z_ALARMEN = Z_Axis_SV; //驱动器故障使能
      MV_Set_Range(Z_AXIS, 100);
      MV_Set_Acc(Z_AXIS, 150);
      MV_Set_Dec(Z_AXIS, 150);
      MV_Set_Startv(Z_AXIS, 10);
      MV_Set_Speed(Z_AXIS, 400);
      MV_Set_Command_Pos(Z_AXIS, CurDistanceSave.ZDistance * ZGearRatio);
      CalDecStop(Z_CurSpeed, &ZCurSpeedPusel);
      CalAccRun(Z_CurSpeed, &ZCurSpeedPusel);
   }
   if (AxisNum > 3)
   {
      U_ALARMEN = U_Axis_SV; //驱动器故障使能
      MV_Set_Range(U_AXIS, 100);
      MV_Set_Acc(U_AXIS, 300);
      MV_Set_Dec(U_AXIS, 200);
      MV_Set_Startv(U_AXIS, 10);
      MV_Set_Speed(U_AXIS, 400);
      MV_Set_Command_Pos(U_AXIS, 0);
      CalDecStop(U_CurSpeed, &ZCurSpeedPusel);
      CalAccRun(U_CurSpeed, &ZCurSpeedPusel);
   }
}
