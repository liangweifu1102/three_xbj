#include "Global.h"
unsigned char cRunStep ,cSlot2Step,cSawRunstep;
unsigned short NextDlay;
unsigned short NextStepDlay;
unsigned char  VerDrillNum,HorDrillNum,cYDrillCount;
unsigned long  PicFCDist;
unsigned long  PicSetionNum;
unsigned short CurSetionNum;
long WorkDistace;
unsigned short CurDuanNUM;
unsigned short  CurWorkNUM;
void ManualCalModel(void);

unsigned char cCheckStep = 0; //测量状态
unsigned char cCheckFliter = 0; //测量滤波

#define bCheckSignal  I012
volatile char cCheckObjectOk = 0;
volatile long dwCheckPosition = 0;
volatile long dwStartPosition = 0;

volatile char bBacked = 0;
long dwComparePluse = 0;
unsigned char bWorkOk = 0;

unsigned char cAlarmFlag = 0;

void AutoCalModel(void);

/**
 * 伺服中断，用于检测板的长度用
 * 
 * @author xuzhenglim (2017-10-8)
 * 
 * @param void 
 */
void ServorHandler(void)
{
}


//需要加工的数据
typedef struct
{
   long position;
   long length;
   long depth;
} DrillsData;

static long currentdeltaDeepth = 0;
static DrillsData drillWorks[15]; //钻加工数据缓冲
static DrillsData drillWorks2[15]; // 槽中槽 加工数据缓存
static char drillWorksCnt = 0;   //钻加工计数
static char oldMode = 0;
static char errorStep = 0;
 char curDrillIndex = 0;
static char milliingDir = 0;
static DrillsData drillDataTemp; //钻孔数据拷贝缓冲
static char TrimingDoneFlag = 0; 

char RunCheckData(void)
{
    long temp = 0,temp2 = 0;
    long i = 0;
    char flag = 0;
    
    for(i = 0; i < 15;i++)
    {
        if (FactoryParam->Slot_Orign[curDrillIndex] > 0 &&
            UserParam->Slot_Depth[curDrillIndex] > 0)
       {
            temp = UserParam->WorksLength[i];
            temp2 = FactoryParam->Slot_Orign[i];
            if(temp2 > temp)       
            {
                flag  = 1;
            }
            else
            {
                temp2 += FactoryParam->Slot_Length[i];
                if(temp2 > temp)
                {
                    flag = 1;
                    
                }
            }

            if(flag > 0)
            {
                TestData->testdata[0] = i;
                TestData->testdata[1] = FactoryParam->Slot_Orign[i];
                TestData->testdata[2] = FactoryParam->Slot_Length[i];
                TestData->testdata[5] = UserParam->WorksLength[i];
                //SystemParam->ZDistance = i;
                break;
            }
        }
    }

    return flag;
}
unsigned char AutoRunInit(void)
{
    unsigned char flag = 0;
    memset(drillWorks, 0, sizeof(drillWorks));
    memset(drillWorks2, 0, sizeof(drillWorks2));
    drillWorksCnt = 0;
    dwRealPosi = 0;
    TrimingDoneFlag = 0;
     //判断排序方式
    if (bDrillingSelect)
    {
        for (curDrillIndex = 0; curDrillIndex < 1; curDrillIndex++)
        {
            if (UserParam->WorksLength[curDrillIndex] > 0 &&
                UserParam->WorksDepth[curDrillIndex] > 0)
            {
                //dwRealPosi += 10UL * UserParam->WorksDeltaSite[curDrillIndex];

                drillWorks[drillWorksCnt].position = 0;//dwRealPosi;

                drillWorks[drillWorksCnt].length = 10UL * UserParam->WorksLength[curDrillIndex];
                dwRealPosi += drillWorks[drillWorksCnt].length;

                drillWorks[drillWorksCnt].depth = 10UL * UserParam->WorksDepth[curDrillIndex];
                UserParam->MillingFeed = drillWorks[drillWorksCnt].depth;
              //补偿修边长度
                //if (bTrimingSelect)
                //{
                //    drillWorks[drillWorksCnt].depth += UserParam->TrimingDeepth;
                //}
/*
                if (FactoryParam->Slot_Orign[curDrillIndex] > 0 &&
                   UserParam->Slot_Depth[curDrillIndex] > 0)
                {
                    long temp = 0;
                    temp = drillWorks[drillWorksCnt].position;
                    temp += 10UL * FactoryParam->Slot_Orign[curDrillIndex];

                    drillWorks2[drillWorksCnt].position = temp;
                    if (10UL * FactoryParam->Slot_Length[curDrillIndex] > 0)
                    {
                        drillWorks2[drillWorksCnt].length = 10UL * FactoryParam->Slot_Length[curDrillIndex];
                    }
                    else
                    {
                        drillWorks2[drillWorksCnt].length = 0;
                    }
                    drillWorks2[drillWorksCnt].depth = 10UL * UserParam->Slot_Depth[curDrillIndex];
                    drillWorks2[drillWorksCnt].depth += drillWorks[drillWorksCnt].depth;
                }
                   */ 
                drillWorksCnt++;
           }
           else
           {
            flag = 1;
              curDrillIndex = 1;
           }
        }
    }

    return flag;
}

void MovetoWorkPosition(void)
{
    //伺服先走到加工起点
    //if (M90)
    /*
    if(bWorkMode1)
    {
       MV_Set_Startv(X_AXIS, 10);
       MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
       dwRealPosi = MV_Get_Command_Pos(X_AXIS);
       cSetPulse = FactoryParam->TrimingSiteOrign - UserParam->HeaderLength;
       cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
       cSetPulse = cSetPulse - dwRealPosi;
       MV_Pmov(X_AXIS, cSetPulse);
    }
    //else if (M91)
    else if (bWorkMode2)
    {
        MV_Set_Startv(X_AXIS, 10);
       MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
       dwRealPosi = MV_Get_Command_Pos(X_AXIS);
       cSetPulse = FactoryParam->TrimingSiteOrign + UserParam->MiddlePoint;
       cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
       cSetPulse = cSetPulse - dwRealPosi;
       MV_Pmov(X_AXIS, cSetPulse);
    }
    else
    */
    {
       MV_Set_Startv(X_AXIS, 10);
       MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
       dwRealPosi = MV_Get_Command_Pos(X_AXIS);
       cSetPulse = FactoryParam->TrimingSiteOrign + UserParam->TrimingLength + UserParam->HeaderLength;
       cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
       cSetPulse = cSetPulse - dwRealPosi;
       MV_Pmov(X_AXIS, cSetPulse);
    }
}

void MoveforWorkLength(void)
{
    //if (M93)
    //if (bWorkMode3)
    {
        MV_Set_Startv(X_AXIS, 10);
       MV_Set_Speed(X_AXIS, UserParam->TrimingSpeed);
       dwRealPosi = MV_Get_Command_Pos(X_AXIS);
       cSetPulse = FactoryParam->TrimingSiteOrign - UserParam->HeaderLength;//UserParam->MiddlePoint + UserParam->TrimingLength;
       cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
       cSetPulse = cSetPulse - dwRealPosi;
       MV_Pmov(X_AXIS, cSetPulse);
    }
    /*
   else
    {
       MV_Set_Startv(X_AXIS, 10);
       MV_Set_Speed(X_AXIS, UserParam->TrimingSpeed);
       dwRealPosi = MV_Get_Command_Pos(X_AXIS);
       cSetPulse = FactoryParam->TrimingSiteOrign + UserParam->HeaderLength + UserParam->TrimingLength;
       cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
       cSetPulse = cSetPulse - dwRealPosi;
       MV_Pmov(X_AXIS, cSetPulse);
      
    }
    */
}

// 槽中在打孔或槽
void Slot2Proc(void)
{
    static char _lmilliingDir = 0;
    
    switch(cSlot2Step)
    {
      case 1:
         //找到加工数据判断是加工孔位还是加工槽
         if (drillWorks2[curDrillIndex].length == 0)
         {
            //执行钻孔
            cSlot2Step = 100;
         }
         else
         {
            cSlot2Step = 200;
            _lmilliingDir = 0;
         }
         break;
      case 12:
        cSlot2Step = 0;
        break;
      case 100:
         //走到钻孔位置
         MV_Set_Startv(X_AXIS, 10);
         MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
         dwRealPosi = MV_Get_Command_Pos(X_AXIS);
         cSetPulse = FactoryParam->DrillSiteOrign + drillWorks2[curDrillIndex].position;
         cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
         cSetPulse = cSetPulse - dwRealPosi;
         MV_Pmov(X_AXIS, cSetPulse);
         //DrillValve = 1;
         //出刀
         cSlot2Step++;
         break;
      case 101:
         if (!X_DRV)
         {
            //走到钻深度原点
            /*MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = DrillingSoftOrign;
            cSetPulse = PositionToPluse(Y_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            */
            cSlot2Step++;
         }
         break;
      case 102:
         if (!Y_DRV && !DrillingOrign)// && DrillingLmt)
         {
            //走到钻深度原点
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->DrillFeedSpeed);
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = DrillingSoftOrign + drillWorks2[curDrillIndex].depth;
            cSetPulse = PositionToPluse(Y_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            cSlot2Step++;
         }
         break;
      case 103:
         if (!Y_DRV)
         {
            //等待圆整时间
            NextStepDlay = 10UL * UserParam->DrillCycleTime;
            cSlot2Step++;
         }
         break;
      case 104:
         if (NextStepDlay == 0)
         {
            //走到深度零点
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = 0 - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            cSlot2Step++;
         }
         break;
      case 105:
         if (!Y_DRV)
         {
            //钻孔结束
            cSlot2Step = 12;
         }
         break;
         //铣槽动作
      case 200:
         //走到钻孔位置

         _lmilliingDir = 1; //0从正方向铣 1从反方向铣
         MV_Set_Startv(X_AXIS, 10);
         MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
         dwRealPosi = MV_Get_Command_Pos(X_AXIS);
         cSetPulse = FactoryParam->DrillSiteOrign + drillWorks2[curDrillIndex].position +
            drillWorks2[curDrillIndex].length;
         cSetPulse = PositionToPluse(X_AXIS, cSetPulse);

         if (cSetPulse > dwRealPosi)
         {
            cSetPulse = FactoryParam->DrillSiteOrign + drillWorks2[curDrillIndex].position;
            cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
            _lmilliingDir = 0;
         }
         cSetPulse = cSetPulse - dwRealPosi;
         MV_Pmov(X_AXIS, cSetPulse);

         //DrillValve = 1;
         //出刀
         cSlot2Step++;
         break;
      case 201:
         if (!X_DRV)
         {
            //走到钻深度原点
            /*MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = DrillingSoftOrign;
            cSetPulse = PositionToPluse(Y_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            */
            cSlot2Step++;

         }
         break;
      case 202:
         if (!Y_DRV && !DrillingOrign)// && DrillingLmt)
         {
            //走到钻深度原点
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->MillingFeedSpeed);
            //深度最多一次只能走到进给值
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            dwComparePluse = UserParam->MillingFeed;
            dwComparePluse = PositionToPluse(Y_AXIS, dwComparePluse);
            cSetPulse = DrillingSoftOrign + drillWorks2[curDrillIndex].depth;
            cSetPulse = PositionToPluse(Y_AXIS, cSetPulse);
            if ((dwRealPosi + dwComparePluse) < cSetPulse)
            {
               cSetPulse = dwRealPosi + dwComparePluse;
            }
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            cSlot2Step++;
         }
         break;
      case 203:
         if (!Y_DRV)
         {
            //等待圆整时间
            NextStepDlay = 10UL * UserParam->MillingCycleTime;
            cSlot2Step++;
         }
         break;
      case 204:
         if (NextStepDlay == 0)
         {
            //走槽长度
            MV_Set_Startv(X_AXIS, 10);
            MV_Set_Speed(X_AXIS, UserParam->MillingSpeed);
            dwRealPosi = MV_Get_Command_Pos(X_AXIS);
            if (_lmilliingDir == 0)
            {
               cSetPulse = drillWorks2[curDrillIndex].position + drillWorks2[curDrillIndex].length +
                  FactoryParam->DrillSiteOrign;
               _lmilliingDir = 1;
            }
            else
            {
               cSetPulse = drillWorks2[curDrillIndex].position  +
                  FactoryParam->DrillSiteOrign;
               _lmilliingDir = 0;
            }
            cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(X_AXIS, cSetPulse);
            cSlot2Step++;
         }
         break;
      case 205:
         if (!X_DRV)
         {
            //判断是否到达深度
            //深度最多一次只能走到进给值
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = DrillingSoftOrign + drillWorks2[curDrillIndex].depth;
            cSetPulse = PositionToPluse(Y_AXIS, cSetPulse);
            if (dwRealPosi != cSetPulse)
            {
               cSlot2Step = 202;
            }
            else
            {
               NextStepDlay = 10UL * UserParam->MillingCycleTime;
               cSlot2Step++;
            }
         }
         break;
      case 206:
         if(!Y_DRV)
         {
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = 0 - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            cSlot2Step++;
         }
        break;
     case 207:
        if(!Y_DRV)
        {
            cSlot2Step = 12;
        }
        break;
     default:
        break;
     }
}

void SawAction(void)
{
    if(cSawRunstep == 1)
    {

    }
}

/************************************************/
/*
自动运行

*/
/************************************************/
void AutoRun(void)
{
    
   if (bRunning)
   {
      switch (cRunStep)
      {
      case 1:
      {
        char flag = 0;
        //flag = RunCheckData();

         flag = AutoRunInit();
         cRunStep = 3;
         cSlot2Step = 0;
         errorStep = 0;
        StopperValve = 0;
        PressValve = 1;
        NextStepDlay = 10UL * UserParam->PressValveCloseTime;

        if(bDrillingSelect)
        {
            cRunStep = 10;
        }
        /*
         //跳过修边
         if (!bTrimingSelect)
         {
            cRunStep = 10;    
         }
         else 
         {// 
            if(bFirstWorkSelect)
            {
                cRunStep = 10;
            }
         }
         */
        if(flag > 0)
        {
            cRunStep = 0;
            cAlarmFlag = 1;
            SystemParam->AlarmCode = 8;
        }
      }
         break;
      case 3:
         //再次按下启动阀
         if(StopperOrign)
         {
            cRunStep++;
            StopperValve = 0;
            PressValve = 1;
            NextStepDlay = 10UL * UserParam->PressValveCloseTime;
            DrillMotor = 0;
            if (!MillingMotor)
            {
                MillingMotor = 1;
               NextDlay = 10UL * UserParam->MillingMotorStartTime;
            }
            else
            {
               //NextDlay = 0;
            }
            

            MovetoWorkPosition();
         }
         break;
      case 4:
         //等待信号开关到位
         if (!X_DRV && StopperOrign && NextStepDlay == 0 && NextDlay == 0)
         {
            //走到位置后铣刀前进
            //MillingValve = 1;
            cRunStep++;
         }
         break;
      case 5:
         //if (MillingLmt && !MillingOrign)
         {
            //到位后需要等待时间，保证稳定
            //NextStepDlay = 10UL * UserParam->MillingInplcaeTime;
            NextStepDlay = 0;
            cRunStep++;
         }
         break;
      case 6:
         if (NextStepDlay == 0)
         {
            //走到修边原点
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = TrimingSoftOrign;
            cSetPulse = PositionToPluse(Z_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);
            cRunStep++;
         }
         break;
      case 7:
         if (!Z_DRV && !MillingOrign)// && MillingLmt )
         {
            //走到修边深度
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->TrimingFeedSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = TrimingSoftOrign + UserParam->TrimingDeepth;
            cSetPulse = PositionToPluse(Z_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);
            cRunStep++;
         }
         break;

      case 8:
         if (!Z_DRV)
         {//开始走到加工距离
            MoveforWorkLength();
            cRunStep++;
         }
         break;
      case 9:
         if (!X_DRV)
         {
            //返回铣刀
            //MillingValve = 0;
            //深度回零点
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = 0 - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);
            cRunStep = 12;
            TrimingDoneFlag =  1;
            //if (M90)
            /*
            if(bWorkMode1)
            {
               cRunStep++;
            }
            //else if (M91)
            else if (bWorkMode2)
            {//铣后面部分
               cRunStep = 40;
            }
            else 
            {//铣后面部分
               cRunStep = 50;
            }
            */
            
         }
         break;
      case 40:
         if (MillingOrign && !MillingLmt && !Z_DRV)
         {
            MV_Set_Startv(X_AXIS, 10);
            MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(X_AXIS);
            cSetPulse = FactoryParam->TrimingSiteOrign + UserParam->MiddlePoint + UserParam->HeaderLength;
            cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(X_AXIS, cSetPulse);
            cRunStep++;
         }
         break;
      case 41:
         if (!X_DRV)
         {
            //走到修边原点
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = TrimingSoftOrign;
            cSetPulse = PositionToPluse(Z_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);

            //出铣刀阀
            //MillingValve = 1;
            cRunStep++;

         }
         break;
      case 42:
         if (!Z_DRV && !MillingOrign)// && MillingLmt )
         {
            //走到修边深度
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->TrimingFeedSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = TrimingSoftOrign + UserParam->TrimingDeepth;
            cSetPulse = PositionToPluse(Z_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);
            cRunStep++;
         }
         break;
      case 43:
         if (!Z_DRV)
         {
            //开始走到加工距离
            MV_Set_Startv(X_AXIS, 10);
            MV_Set_Speed(X_AXIS, UserParam->TrimingSpeed);
            dwRealPosi = MV_Get_Command_Pos(X_AXIS);
            cSetPulse = FactoryParam->TrimingSiteOrign - UserParam->HeaderLength;
            cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(X_AXIS, cSetPulse);
            cRunStep++;
         }
         break;
      case 44:
         if (!X_DRV)
         {
            //返回铣刀
            //MillingValve = 0;
            //深度回零点
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = 0 - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);

            cRunStep = 10;

         }

         break;
      case 50:
         if (MillingOrign && !MillingLmt && !Z_DRV)
         {
            MV_Set_Startv(X_AXIS, 10);
            MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(X_AXIS);
            cSetPulse = FactoryParam->TrimingSiteOrign - UserParam->HeaderLength;
            cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(X_AXIS, cSetPulse);
            cRunStep++;

         }
         break;
      case 51:
         if (!X_DRV)
         {
            //走到修边原点
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = TrimingSoftOrign;
            cSetPulse = PositionToPluse(Z_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);

            //出铣刀阀
            //MillingValve = 1;
            cRunStep++;

         }
         break;
      case 52:
         if (!Z_DRV && !MillingOrign)// && MillingLmt)
         {
            //走到修边深度
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->TrimingFeedSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = TrimingSoftOrign + UserParam->TrimingDeepth ;
            cSetPulse = PositionToPluse(Z_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);
            cRunStep++;
         }
         break;
      case 53:
         if (!Z_DRV)
         {
            //开始走到加工距离
            MV_Set_Startv(X_AXIS, 10);
            MV_Set_Speed(X_AXIS, UserParam->TrimingSpeed);
            dwRealPosi = MV_Get_Command_Pos(X_AXIS);
            cSetPulse = FactoryParam->TrimingSiteOrign + UserParam->TrimingLength + 
               UserParam->HeaderLength;
            cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(X_AXIS, cSetPulse);
            cRunStep++;
         }
         break;
      case 54:
         if (!X_DRV)
         {
            //返回铣刀
            //MillingValve = 0;
            //深度回零点
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = 0 - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);

            cRunStep = 10;
         }
         break;
      case 10:
        if (StopperOrign && MillingOrign && !MillingLmt && !Z_DRV && NextStepDlay == 0)
        {
            cRunStep = 60;
            /*
            if(bTrimingSelect && bDrillingSelect)
            {
                if(bFirstWorkSelect)
                {
                    if(TrimingDoneFlag == 1)
                    {
                        cRunStep = 12;
                    }
                }
            }
            */
        }
        break;
      case 60:
         //if (MillingOrign && !MillingLmt && !Z_DRV && NextStepDlay == 0)
         {
            cRunStep = 11;
            curDrillIndex = drillWorksCnt;
            MillingMotor = 0;
            if (drillWorksCnt > 0)
            {
               if (!DrillMotor)
               {
                  NextDlay = 10UL * UserParam->DrillMotorStartTime;
               }
               else
               {
                  NextDlay = 0;
               }
               DrillMotor = 1;
            }
         }
         break;
      case 11:
         //判断是否有需要加工的数据
         if (NextDlay == 0)
         {
            //需要加工
            //判断是需要从哪个方向加工
            if (drillWorksCnt > 1)
            {
               //根据情况对内部再排序,加工本身是反序加工的
               dwRealPosi = MV_Get_Command_Pos(X_AXIS);
               dwComparePluse = FactoryParam->DrillSiteOrign + drillWorks[0].position;
               dwComparePluse = PositionToPluse(X_AXIS, dwComparePluse);
               cSetPulse =  FactoryParam->DrillSiteOrign + drillWorks[drillWorksCnt - 1].position +
                  drillWorks[drillWorksCnt - 1].length;
               cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
               //
               if (dwRealPosi < cSetPulse)
               {
                  if (dwRealPosi < dwComparePluse)
                  {
                     //需要从头开始反序
                     for (curDrillIndex = 0; curDrillIndex < (drillWorksCnt / 2); curDrillIndex++)
                     {
                        drillDataTemp = drillWorks[curDrillIndex];
                        drillWorks[curDrillIndex] = drillWorks[drillWorksCnt - curDrillIndex - 1];
                        drillWorks[drillWorksCnt - curDrillIndex - 1] = drillDataTemp;

                        drillDataTemp = drillWorks2[curDrillIndex];
                        drillWorks2[curDrillIndex] = drillWorks2[drillWorksCnt - curDrillIndex - 1];
                        drillWorks2[drillWorksCnt - curDrillIndex - 1] = drillDataTemp;
                     }

                  }
                  else if ((dwRealPosi - dwComparePluse) > (cSetPulse - dwRealPosi))
                  {
                     //需要从头开始反序
                     for (curDrillIndex = 0; curDrillIndex < (drillWorksCnt / 2); curDrillIndex++)
                     {
                        drillDataTemp = drillWorks[curDrillIndex];
                        drillWorks[curDrillIndex] = drillWorks[drillWorksCnt - curDrillIndex - 1];
                        drillWorks[drillWorksCnt - curDrillIndex - 1] = drillDataTemp;

                        drillDataTemp = drillWorks2[curDrillIndex];
                        drillWorks2[curDrillIndex] = drillWorks2[drillWorksCnt - curDrillIndex - 1];
                        drillWorks2[drillWorksCnt - curDrillIndex - 1] = drillDataTemp;
                     }
                  }
               }

            }
            curDrillIndex = drillWorksCnt;
            cRunStep++;
         }
         break;
      case 12:
         if (curDrillIndex > 0)
         {
            curDrillIndex--;
            if (drillWorks[curDrillIndex].length > 0 && drillWorks[curDrillIndex].depth > 0)
            {
               cRunStep++;
            }
         }
         else
         {
            cRunStep = 80;
            if(bTrimingSelect)// && bDrillingSelect)
            {
                if(TrimingDoneFlag == 0)
                {
                    cRunStep = 3;
                    TrimingDoneFlag = 1;
                }
                /*if(bFirstWorkSelect)
                {// 再修边
                    if(TrimingDoneFlag == 0)
                    {
                        cRunStep = 3;
                        TrimingDoneFlag = 1;
                    }
                }
                */
            }
         }

         break;
      case 80:
            cRunStep = 20;
            //DrillValve = 0;
            //MillingValve = 0;
            //加工计数加1
            SystemParam->Proctotal++;
            Write24C04((16 + 0), SystemParam->Proctotal);
            Write24C04((16 + 1), SystemParam->Proctotal >> 8);
            Write24C04((16 + 2), SystemParam->Proctotal >> 16);
            Write24C04((16 + 3), SystemParam->Proctotal >> 24);
        break;
      case 13:

         //找到加工数据判断是加工孔位还是加工槽
         if (drillWorks[curDrillIndex].length == 0)
         {
            //执行钻孔
            cRunStep = 100;

         }
         else
         {
            cRunStep = 200;

         }
         break;
      case 100:

         //走到钻孔位置
         MV_Set_Startv(X_AXIS, 10);
         MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
         dwRealPosi = MV_Get_Command_Pos(X_AXIS);
         cSetPulse = FactoryParam->DrillSiteOrign + drillWorks[curDrillIndex].position;
         cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
         cSetPulse = cSetPulse - dwRealPosi;
         MV_Pmov(X_AXIS, cSetPulse);
         //DrillValve = 1;
         //出刀
         cRunStep++;
         break;
      case 101:
         if (!X_DRV)
         {
            //走到钻深度原点
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = DrillingSoftOrign;
            cSetPulse = PositionToPluse(Y_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            cRunStep++;
         }
         break;
      case 102:
         if (!Y_DRV && !DrillingOrign)// && DrillingLmt)
         {
            //走到钻深度原点
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->DrillFeedSpeed);
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = DrillingSoftOrign + drillWorks[curDrillIndex].depth;
            cSetPulse = PositionToPluse(Y_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            cRunStep++;
         }
         break;
      case 103:
         if (!Y_DRV)
         {
            //等待圆整时间
            NextStepDlay = 10UL * UserParam->DrillCycleTime;
            cRunStep++;
         }
         break;
      case 104:
         if (NextStepDlay == 0)
         {
            //走到深度零点
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = 0 - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            cRunStep++;
         }
         break;
      case 105:
         if (!Y_DRV)
         {
            //钻孔结束
            cRunStep = 12;
         }
         break;
         //铣槽动作
      case 200:
         //走到钻孔位置

         milliingDir = 1; //0从正方向铣 1从反方向铣
         MV_Set_Startv(X_AXIS, 10);
         MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
         dwRealPosi = MV_Get_Command_Pos(X_AXIS);
         cSetPulse = FactoryParam->DrillSiteOrign + drillWorks[curDrillIndex].position +
            drillWorks[curDrillIndex].length;
         cSetPulse = PositionToPluse(X_AXIS, cSetPulse);

         if (cSetPulse > dwRealPosi)
         {
            cSetPulse = FactoryParam->DrillSiteOrign + drillWorks[curDrillIndex].position;
            cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
            milliingDir = 0;
         }
         cSetPulse = cSetPulse - dwRealPosi;
         MV_Pmov(X_AXIS, cSetPulse);

         //DrillValve = 1;
         //出刀
         cRunStep++;
         break;
      case 201:
         if (!X_DRV)
         {
            //走到钻深度原点
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = DrillingSoftOrign + drillWorks[curDrillIndex].depth;
            cSetPulse = PositionToPluse(Y_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            cRunStep++;

         }
         break;
      case 202:
         if (!Y_DRV && !DrillingOrign)// && DrillingLmt)
         {
         /*
            //走到钻深度原点
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->MillingFeedSpeed);
            //深度最多一次只能走到进给值
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            dwComparePluse = UserParam->MillingFeed;
            dwComparePluse = PositionToPluse(Y_AXIS, dwComparePluse);
            cSetPulse = DrillingSoftOrign + drillWorks[curDrillIndex].depth;
            cSetPulse = PositionToPluse(Y_AXIS, cSetPulse);
            if ((dwRealPosi + dwComparePluse) < cSetPulse)
            {
               cSetPulse = dwRealPosi + dwComparePluse;
            }
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Y_AXIS, cSetPulse);
            */
            cRunStep++;
         }
         break;
      case 203:
         if (!Y_DRV)
         {
            //等待圆整时间
            NextStepDlay = 10UL * UserParam->MillingCycleTime;
            cRunStep++;
         }
         break;
      case 204:
         if (NextStepDlay == 0)
         {
            //走槽长度
            MV_Set_Startv(X_AXIS, 10);
            MV_Set_Speed(X_AXIS, UserParam->MillingSpeed);
            dwRealPosi = MV_Get_Command_Pos(X_AXIS);
            if (milliingDir == 0)
            {
               cSetPulse = drillWorks[curDrillIndex].position + drillWorks[curDrillIndex].length +
                  FactoryParam->DrillSiteOrign;
               milliingDir = 1;
            }
            else
            {
               cSetPulse = drillWorks[curDrillIndex].position  +
                  FactoryParam->DrillSiteOrign;
               milliingDir = 0;
            }
            cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(X_AXIS, cSetPulse);
            cRunStep++;
         }
         break;
      case 205:
         if (!X_DRV)
         {
            //判断是否到达深度
            //深度最多一次只能走到进给值
            dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
            cSetPulse = DrillingSoftOrign + drillWorks[curDrillIndex].depth;
            cSetPulse = PositionToPluse(Y_AXIS, cSetPulse);
            if (dwRealPosi != cSetPulse)
            {
               cRunStep = 202;
            }
            else
            {
               NextStepDlay = 10UL * UserParam->MillingCycleTime;
               cRunStep++;
            }
         }
         break;
      case 206:
         if (NextStepDlay == 0)
         {
         /*
            if(drillWorks2[curDrillIndex].position > 0 && 
                drillWorks2[curDrillIndex].depth> 0)
            {
                cSlot2Step = 1;
                cRunStep = 208;
            }
            else
            */
            {
                //走到深度零点
                cSlot2Step = 0;
                MV_Set_Startv(Y_AXIS, 10);
                MV_Set_Speed(Y_AXIS, UserParam->DeepthIdleSpeed);
                dwRealPosi = MV_Get_Command_Pos(Y_AXIS);
                cSetPulse = 0 - dwRealPosi;
                MV_Pmov(Y_AXIS, cSetPulse);
                cRunStep++;
            }
         }
         break;
      case 207:
         if (!Y_DRV)
         {
            DrillMotor = 0;
            cRunStep = 12;
         }
         break;
      case 208:
        Slot2Proc();
        if (cSlot2Step == 0)
        {
            cRunStep = 12;
        }
        break;
      case 20:
         if (DrillingOrign && !DrillingLmt && MillingOrign && !MillingLmt)
         {
            //X回原点
            MV_Set_Startv(X_AXIS, 10);
            MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(X_AXIS);
            cSetPulse = 0 - dwRealPosi;
            MV_Pmov(X_AXIS, cSetPulse);
            cRunStep++;
            MillingMotor = 0;
            DrillMotor = 0;
         }
         break;
    
      case 21:
         if (!X_DRV)
         {
            //加工完成
            cRunStep = 0;
            TrimingDoneFlag = 0;
            bRunning = 0;
            cAutoResetStep = 1;
            if (FactoryParam->XAxisAutoZero == 1)
            {
               bXoriginST = 1;
               bXRst = 1;
               cXRstStep = 1;
            }
            if (FactoryParam->YAxisAutoZero == 1)
            {
               bYoriginST = 1;
               bYRst = 1;
               cYRstStep = 1;
            }
            if (FactoryParam->ZAxisAutoZero == 1)
            {
               bZoriginST = 1;
               bZRst = 1;
               cZRstStep = 1;
            }
         }
         break;
      }

      if ((!StopperOrign && (MillingValve || DrillValve)) || MillingMotorAlarm || DrillMotorAlarm)
      {
         //M03 = 1;
         //bRunning = 1;
         cRunStep = 0;
         switch (errorStep)
         {

         case 0:
            if (MillingValveLocker)
            {
               NextStepDlay = 10UL * UserParam->MillingUnLockerTime;
               MillingValveLocker = 0;
            }
            else
            {

               NextStepDlay = 0;
            }
            if (X_DRV)
            {
               MV_Dec_Stop(X_AXIS);
            }
            if (Y_DRV)
            {
               MV_Dec_Stop(Y_AXIS);
            }
            errorStep++;
            break;
         case 1:
            if (NextStepDlay == 0)
            {
               MillingValve = 0;
               MillingMotor = 0;
               StopperValve = 0;
               errorStep++;
            }
            break;
         }
      }
      else
      {
         errorStep = 0;
      }

   }
}

