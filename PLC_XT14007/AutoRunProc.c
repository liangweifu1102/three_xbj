#include "Global.h"
unsigned char motor_run_flg;
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

unsigned char cCheckStep = 0; //²âÁ¿×´Ì¬
unsigned char cCheckFliter = 0; //²âÁ¿ÂË²¨

#define bCheckSignal  I012
volatile char cCheckObjectOk = 0;
volatile long dwCheckPosition = 0;
volatile long dwStartPosition = 0;

volatile char bBacked = 0;
long dwComparePluse = 0;
unsigned char bWorkOk = 0;
unsigned char cAlarmFlag = 0;

unsigned short work_orign[20];
unsigned short work_length[20];
unsigned short work_depth[20];

unsigned char xc_frun_step;
unsigned char xc_rrun_step;
unsigned char xb_frun_step;
unsigned char xb_rrun_step;

void AutoCalModel(void);


void run_mech_posi(unsigned char axis, unsigned short speed, long mech_posi)
{
    MV_Set_Startv(axis, 10);
    MV_Set_Speed(axis, speed);
    dwRealPosi = MV_Get_Command_Pos(axis);
    cSetPulse = mech_posi;
    cSetPulse = PositionToPluse(axis, cSetPulse);
    cSetPulse = cSetPulse - dwRealPosi;
    MV_Pmov(axis, cSetPulse); 
}

void run_distance(unsigned char axis, unsigned short speed, long go_distance)
{
    MV_Set_Startv(axis, 10);
    MV_Set_Speed(axis, speed);
    cSetPulse = PositionToPluse(axis, go_distance);
    MV_Pmov(axis, cSetPulse); 
}

unsigned char slot_num_count(void)
{
    unsigned char i;
    unsigned char slot_num=0;
    for (i=0; i<20; i++)
    {
        work_orign[i]=0;
        work_length[i]=0;
        work_depth[i]=0;
    }
    for (i = 0; i < 20; i++)
    {
        if (FactoryParam->Slot_Orign[i] != 0 && FactoryParam->Slot_Length[i] != 0 
            && UserParam->Slot_Depth[i]!=0)
       {
            work_orign[slot_num]=FactoryParam->Slot_Orign[i];
            work_length[slot_num]=FactoryParam->Slot_Length[i];
            work_depth[slot_num]=UserParam->Slot_Depth[i];
            slot_num++;
       }
    }
    return slot_num;
}

void run_xc_forward(void)
{

}
void run_xc_reverse(void)
{

}
void run_xb_forward(void)
{
    switch (xb_frun_step)
    {
        case 1:
        case 3:
            if (!Y_DRV)
            {
                set_dis = FactoryParam->DrillSiteOrign-(UserParam->TrimingRadius/2);  //xåˆ°èµ·ç‚¹
                run_mech_posi(X_AXIS,UserParam->SiteIdleSpeed,set_dis);
                xb_frun_step = 4;
            }             
           break;
        case 4:
           if (!X_DRV)        //yåˆ°èµ·ç‚¹
           {
               run_mech_posi(Y_AXIS,UserParam->DeepthIdleSpeed,FactoryParam->TrimingDeepthOrign); 
               xb_frun_step = 5;
           }
           break;
        case 5:
           if (!Y_DRV)        //yè¿›æ·±åº¦
           {
               if (!feed_xb)  //ä¸€æ¬¡è¿›åˆ€
               {
                   run_distance(Y_AXIS, UserParam->DrillFeedSpeed, UserParam->TrimingDeepth);
                   xb_frun_step = 6;                       
               }
               else           //å¤šæ¬¡è¿›åˆ€
               {
                   if ((UserParam->TrimingDeepth-cur_depth) > MotroParam->xb_one_feed)  //æ€»-å½“å‰>ä¸€æ¬¡è¿›åˆ€
                   {    
                       cur_depth += MotroParam->xb_one_feed;              
                       run_distance(Y_AXIS, UserParam->DrillFeedSpeed, cur_depth); 
                       xb_frun_step = 6;  
                   }
                   else  
                   {
                       cur_depth = UserParam->TrimingDeepth;
                       run_distance(Y_AXIS, UserParam->DrillFeedSpeed, cur_depth);
                       xb_frun_step = 6;  
                   }
               }
           }
           break;
        case 6:
            if (!Y_DRV)    //xä¿®è¾¹
            {
                set_dis = UserParam->TrimingRadius + UserParam->TrimingLength;
                run_distance(X_AXIS,UserParam->TrimingSpeed,set_dis);
                xb_frun_step = 7;
            }
            break;
        case 7:
            if (!X_DRV)    //yé€€åˆ€
            {
                run_mech_posi(Y_AXIS,UserParam->DeepthIdleSpeed,0);
                xb_frun_step = 8;
            }
            break;
        case 8:
            if (!Y_DRV)
            {
                if (!feed_xb)
                {
                    xb_frun_step=9;
                }
                else
                {
                    if (cur_depth>=UserParam->TrimingDeepth)
                    {
                        xb_frun_step=9;
                    }
                    else
                    {
                        xb_frun_step=3;
                    }   
                }
            }
            break;
        case 9:
            xb_frun_step = 0;
            break;
        default:
            break;
    }
}

void run_xb_reverse(void)
{

}


void aotu_run(void)
{
    static unsigned long run_delay=0;
    long set_dis;
    static long cur_depth;

    static unsigned char  all_slot_num;
    static unsigned char  cur_slot_num;
    static unsigned short cut_slot_depth;

    if (bRunning)
    {
        switch (cRunStep)
        {
            case 1:
                {
                    run_mech_posi(Y_AXIS,UserParam->DeepthIdleSpeed,0);                   //yå›žé›¶ç‚¹
                    run_mech_posi(Z_AXIS,UserParam->MillingRadius,0); 
                cRunStep = 2;
                }      
                break;
            case 2:
                if (!Y_DRV && !Z_DRV)
                {
                    if (MotroParam->mode_lift == MODEXIUB)
                   {
                       if (MotroParam->mode_right == MODEXIUB)
                       {
                          
                       }
                       else if (MotroParam->mode_right == MODEXICAO)
                       {
                          
                       }
                       else
                       {

                       }
                   }
                   else if (MotroParam->mode_lift == MODEXICAO)
                   {
                       if (MotroParam->mode_right == MODEXIUB)
                       {
                           if (!motor_run_flg)
                           {
                               motor_run_flg=1;
                               run_delay = dwTickCount + UserParam->MillingMotorStartTime * 100UL; 
                               Y00=1;
                               Y15=1;
                               Y07=1;
                               Y10=1;
                           }
                           else
                           {
                               Y07=1;
                               Y10=1;
                               run_delay = dwTickCount + UserParam->PressValveOpenTime * 100UL; 
                           }
                           cRunStep = 3;
                           cur_depth=0;
                       }
                       else if (MotroParam->mode_right == MODEXICAO)
                       {

                       }
                       else
                       {

                       }                  
                   }
                   else
                   {
                       if (MotroParam->mode_right == MODEXIUB)
                       {

                       }
                       else if (MotroParam->mode_right == MODEXICAO)
                       {

                       }
                       else
                       {

                       }   
                   }
                }
               break;
            case 3:
                if (!Y_DRV)
                {
                    set_dis = FactoryParam->DrillSiteOrign-(UserParam->TrimingRadius/2);  //xåˆ°èµ·ç‚¹
                    run_mech_posi(X_AXIS,UserParam->SiteIdleSpeed,set_dis);
                    cRunStep = 4;
                }             
               break;
           case 4:
               if (!X_DRV)        //yåˆ°èµ·ç‚¹
               {
                   run_mech_posi(Y_AXIS,UserParam->DeepthIdleSpeed,FactoryParam->TrimingDeepthOrign); 
                   cRunStep = 5;
               }
               break;
           case 5:
               if (!Y_DRV)        //yè¿›æ·±åº¦
               {
                   if (!feed_xb)  //ä¸€æ¬¡è¿›åˆ€
                   {
                       run_distance(Y_AXIS, UserParam->DrillFeedSpeed, UserParam->TrimingDeepth);
                       cRunStep = 6;                       
                   }
                   else           //å¤šæ¬¡è¿›åˆ€
                   {
                       if ((UserParam->TrimingDeepth-cur_depth) > MotroParam->xb_one_feed)  //æ€»-å½“å‰>ä¸€æ¬¡è¿›åˆ€
                       {    
                           cur_depth += MotroParam->xb_one_feed;              
                           run_distance(Y_AXIS, UserParam->DrillFeedSpeed, cur_depth); 
                           cRunStep = 6;  
                       }
                       else  
                       {
                           cur_depth = UserParam->TrimingDeepth;
                           run_distance(Y_AXIS, UserParam->DrillFeedSpeed, cur_depth);
                           cRunStep = 6;  
                       }
                   }
               }
               break;
            case 6:
                if (!Y_DRV)    //xä¿®è¾¹
                {
                    set_dis = UserParam->TrimingRadius + UserParam->TrimingLength;
                    run_distance(X_AXIS,UserParam->TrimingSpeed,set_dis);
                    cRunStep = 7;
                }
                break;
            case 7:
                if (!X_DRV)    //yé€€åˆ€
                {
                    run_mech_posi(Y_AXIS,UserParam->DeepthIdleSpeed,0);
                    cRunStep = 8;
                }
                break;
            case 8:
                if (!Y_DRV)
                {
                    if (!feed_xb)
                    {
                        cRunStep=9;
                    }
                    else
                    {
                        if (cur_depth>=UserParam->TrimingDeepth)
                        {
                            cRunStep=9;
                        }
                        else
                        {
                            cRunStep=3;
                        }   
                    }
                }
                break;
            case 9:
                Y00=0;
                Y15=0;
                run_delay = dwTickCount + 800; 
                cRunStep = 10;
                break;
            case 10:
                if (run_delay < dwTickCount)
                {
                    run_mech_posi(Z_AXIS,UserParam->MillingRadius,0);                   //Zå›žé›¶ç‚¹
                    cRunStep = 11;
                }
                break;
            case 11:
                if (!Z_DRV)
                {
                    all_slot_num = slot_num_count();  
                    if (all_slot_num>0)
                    {
                        cur_slot_num = all_slot_num-1;
                        cRunStep = 12;
                    }
                    else    //é¢„é˜²æ²¡æœ‰è®¾æœ‰å­”çš„æƒ…å†µ
                    {
                            
                    }
                }
                break;
            case 12:
                {
                    Y14=1;
                    Y00=1;
                    run_delay = dwTickCount + UserParam->DrillMotorStartTime * 100UL; 
                    cRunStep = 13;  
                    cut_slot_depth=0;
                }
                break;
            case 13:
                if (run_delay < dwTickCount)  //åˆ°æ§½ä½ç½®
                {
                    set_dis = work_orign[cur_slot_num] + work_length[cur_slot_num];
                    run_mech_posi(X_AXIS,UserParam->SiteIdleSpeed,set_dis);
                    cRunStep = 14;
                }
                break;
            case 14:
                if (!X_DRV)     //åˆ°Zè½´èµ·ç‚¹
                {
                    run_mech_posi(Z_AXIS,UserParam->MillingRadius,FactoryParam->DrillDeepthOrign);
                    cRunStep = 15;
                }
                break;
            case 15:
                if (!Z_DRV)   //è¿›åˆ€æ·±åº¦
                {
                    if (!feed_xc)  //ä¸€æ¬¡è¿›åˆ€
                    {
                        set_dis = work_depth[cur_slot_num];
                        run_distance(Z_AXIS,UserParam->MillingSpeed,set_dis);
                        cRunStep = 16;                    
                    }
                    else           //å¤šæ¬¡è¿›åˆ€
                    {
                        if ((work_depth[cur_slot_num]-cut_slot_depth) > MotroParam->xc_one_feed)  //æ€»-å½“å‰>ä¸€æ¬¡è¿›åˆ€
                        {    
                            cut_slot_depth += MotroParam->xc_one_feed;              
                            run_distance(Z_AXIS, UserParam->MillingSpeed, cut_slot_depth); 
                            cRunStep = 16;  
                        }
                        else  
                        {
                            cut_slot_depth = work_depth[cur_slot_num];
                            run_distance(Z_AXIS, UserParam->MillingSpeed, cut_slot_depth);
                            cRunStep = 16;  
                        }
                    }
                }
                break;
            case 16:
                if (!Z_DRV)  //é“£æ§½
                {
                    set_dis = (-1) * work_length[cur_slot_num];
                    run_distance(X_AXIS, UserParam->TrimingSpeed, set_dis);
                    cRunStep = 17;
                }
                break;
            case 17:
                if (!X_DRV)   //é€€å‡º
                {
                    run_mech_posi(Z_AXIS,UserParam->MillingRadius,0);
                    cRunStep = 18;
                }
                break;
            case 18:
                if (!Z_DRV)
                {
                    if (!feed_xc)
                    {
                        cRunStep=19;
                    }
                    else
                    {
                        if (cut_slot_depth >= work_depth[cur_slot_num])
                        {
                            cRunStep=19;
                        }
                        else
                        {
                            cRunStep=13;
                        }   
                    }
                }
                break;
            case 19:
                if (cur_slot_num!=0)
                {
                    cur_slot_num--;
                    cRunStep=13;
                }
                else
                {
                    cRunStep=20;
                }
                break;
            case 20:
                {
                    run_mech_posi(X_AXIS,UserParam->SiteIdleSpeed,0);
                    cRunStep = 21;
                }
                break;
            case 21:
                if (!X_DRV)
                {
                    run_delay = dwTickCount + MotroParam->no_work_time * 100UL; 
                    cRunStep = 22;
                }
                break;
            case 22:
                if (run_delay < dwTickCount)
                {
                    motor_run_flg=0;
                    Y00 = 0;
                    Y14 = 0;
                    Y15 = 0;
                    cRunStep = 0;
                    bRunning = 0;
                }
                break;
            case 23:

                break;
            case 24:
                break;

           default:
               break;
        }
    }
}

















/**
 * ËÅ·þÖÐ¶Ï£¬ÓÃÓÚ¼ì²â°åµÄ³¤¶ÈÓÃ
 * 
 * @author xuzhenglim (2017-10-8)
 * 
 * @param void 
 */
void ServorHandler(void)
{
}


//ÐèÒª¼Ó¹¤µÄÊý¾Ý
typedef struct
{
   long position;
   long length;
   long depth;
} DrillsData;

//static long currentdeltaDeepth = 0;
static DrillsData drillWorks[15]; //×ê¼Ó¹¤Êý¾Ý»º³å
static DrillsData drillWorks2[15]; // ²ÛÖÐ²Û ¼Ó¹¤Êý¾Ý»º´æ
static char drillWorksCnt = 0;   //×ê¼Ó¹¤¼ÆÊý
//static char oldMode = 0;
static char errorStep = 0;
 char curDrillIndex = 0;
static char milliingDir = 0;
static DrillsData drillDataTemp; //×ê¿×Êý¾Ý¿½±´»º³å
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
     //ÅÐ¶ÏÅÅÐò·½Ê½
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
              //²¹³¥ÐÞ±ß³¤¶È
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
    //ËÅ·þÏÈ×ßµ½¼Ó¹¤Æðµã
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

// ²ÛÖÐÔÚ´ò¿×»ò²Û
void Slot2Proc(void)
{
    static char _lmilliingDir = 0;
    
    switch(cSlot2Step)
    {
      case 1:
         //ÕÒµ½¼Ó¹¤Êý¾ÝÅÐ¶ÏÊÇ¼Ó¹¤¿×Î»»¹ÊÇ¼Ó¹¤²Û
         if (drillWorks2[curDrillIndex].length == 0)
         {
            //Ö´ÐÐ×ê¿×
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
         //×ßµ½×ê¿×Î»ÖÃ
         MV_Set_Startv(X_AXIS, 10);
         MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
         dwRealPosi = MV_Get_Command_Pos(X_AXIS);
         cSetPulse = FactoryParam->DrillSiteOrign + drillWorks2[curDrillIndex].position;
         cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
         cSetPulse = cSetPulse - dwRealPosi;
         MV_Pmov(X_AXIS, cSetPulse);
         //DrillValve = 1;
         //³öµ¶
         cSlot2Step++;
         break;
      case 101:
         if (!X_DRV)
         {
            //×ßµ½×êÉî¶ÈÔ­µã
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
            //×ßµ½×êÉî¶ÈÔ­µã
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
            //µÈ´ýÔ²ÕûÊ±¼ä
            NextStepDlay = 10UL * UserParam->DrillCycleTime;
            cSlot2Step++;
         }
         break;
      case 104:
         if (NextStepDlay == 0)
         {
            //×ßµ½Éî¶ÈÁãµã
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
            //×ê¿×½áÊø
            cSlot2Step = 12;
         }
         break;
         //Ï³²Û¶¯×÷
      case 200:
         //×ßµ½×ê¿×Î»ÖÃ

         _lmilliingDir = 1; //0´ÓÕý·½ÏòÏ³ 1´Ó·´·½ÏòÏ³
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
         //³öµ¶
         cSlot2Step++;
         break;
      case 201:
         if (!X_DRV)
         {
            //×ßµ½×êÉî¶ÈÔ­µã
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
            //×ßµ½×êÉî¶ÈÔ­µã
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->MillingFeedSpeed);
            //Éî¶È×î¶àÒ»´ÎÖ»ÄÜ×ßµ½½ø¸øÖµ
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
            //µÈ´ýÔ²ÕûÊ±¼ä
            NextStepDlay = 10UL * UserParam->MillingCycleTime;
            cSlot2Step++;
         }
         break;
      case 204:
         if (NextStepDlay == 0)
         {
            //×ß²Û³¤¶È
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
            //ÅÐ¶ÏÊÇ·ñµ½´ïÉî¶È
            //Éî¶È×î¶àÒ»´ÎÖ»ÄÜ×ßµ½½ø¸øÖµ
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
×Ô¶¯ÔËÐÐ

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
         //Ìø¹ýÐÞ±ß
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
         //ÔÙ´Î°´ÏÂÆô¶¯·§
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
         //µÈ´ýÐÅºÅ¿ª¹Øµ½Î»
         if (!X_DRV && StopperOrign && NextStepDlay == 0 && NextDlay == 0)
         {
            //×ßµ½Î»ÖÃºóÏ³µ¶Ç°½ø
            //MillingValve = 1;
            cRunStep++;
         }
         break;
      case 5:
         //if (MillingLmt && !MillingOrign)
         {
            //µ½Î»ºóÐèÒªµÈ´ýÊ±¼ä£¬±£Ö¤ÎÈ¶¨
            //NextStepDlay = 10UL * UserParam->MillingInplcaeTime;
            NextStepDlay = 0;
            cRunStep++;
         }
         break;
      case 6:
         if (NextStepDlay == 0)
         {
            //×ßµ½ÐÞ±ßÔ­µã
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
            //×ßµ½ÐÞ±ßÉî¶È
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
         {//¿ªÊ¼×ßµ½¼Ó¹¤¾àÀë
            MoveforWorkLength();
            cRunStep++;
         }
         break;
      case 9:
         if (!X_DRV)
         {
            //·µ»ØÏ³µ¶
            //MillingValve = 0;
            //Éî¶È»ØÁãµã
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
            {//Ï³ºóÃæ²¿·Ö
               cRunStep = 40;
            }
            else 
            {//Ï³ºóÃæ²¿·Ö
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
            //×ßµ½ÐÞ±ßÔ­µã
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = TrimingSoftOrign;
            cSetPulse = PositionToPluse(Z_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);

            //³öÏ³µ¶·§
            //MillingValve = 1;
            cRunStep++;

         }
         break;
      case 42:
         if (!Z_DRV && !MillingOrign)// && MillingLmt )
         {
            //×ßµ½ÐÞ±ßÉî¶È
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
            //¿ªÊ¼×ßµ½¼Ó¹¤¾àÀë
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
            //·µ»ØÏ³µ¶
            //MillingValve = 0;
            //Éî¶È»ØÁãµã
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
            //×ßµ½ÐÞ±ßÔ­µã
            MV_Set_Startv(Z_AXIS, 10);
            MV_Set_Speed(Z_AXIS, UserParam->DeepthIdleSpeed);
            dwRealPosi = MV_Get_Command_Pos(Z_AXIS);
            cSetPulse = TrimingSoftOrign;
            cSetPulse = PositionToPluse(Z_AXIS, cSetPulse);
            cSetPulse = cSetPulse - dwRealPosi;
            MV_Pmov(Z_AXIS, cSetPulse);

            //³öÏ³µ¶·§
            //MillingValve = 1;
            cRunStep++;

         }
         break;
      case 52:
         if (!Z_DRV && !MillingOrign)// && MillingLmt)
         {
            //×ßµ½ÐÞ±ßÉî¶È
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
            //¿ªÊ¼×ßµ½¼Ó¹¤¾àÀë
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
            //·µ»ØÏ³µ¶
            //MillingValve = 0;
            //Éî¶È»ØÁãµã
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
         //ÅÐ¶ÏÊÇ·ñÓÐÐèÒª¼Ó¹¤µÄÊý¾Ý
         if (NextDlay == 0)
         {
            //ÐèÒª¼Ó¹¤
            //ÅÐ¶ÏÊÇÐèÒª´ÓÄÄ¸ö·½Ïò¼Ó¹¤
            if (drillWorksCnt > 1)
            {
               //¸ù¾ÝÇé¿ö¶ÔÄÚ²¿ÔÙÅÅÐò,¼Ó¹¤±¾ÉíÊÇ·´Ðò¼Ó¹¤µÄ
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
                     //ÐèÒª´ÓÍ·¿ªÊ¼·´Ðò
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
                     //ÐèÒª´ÓÍ·¿ªÊ¼·´Ðò
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
                {// ÔÙÐÞ±ß
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
            //¼Ó¹¤¼ÆÊý¼Ó1
            SystemParam->Proctotal++;
            Write24C04((16 + 0), SystemParam->Proctotal);
            Write24C04((16 + 1), SystemParam->Proctotal >> 8);
            Write24C04((16 + 2), SystemParam->Proctotal >> 16);
            Write24C04((16 + 3), SystemParam->Proctotal >> 24);
        break;
      case 13:

         //ÕÒµ½¼Ó¹¤Êý¾ÝÅÐ¶ÏÊÇ¼Ó¹¤¿×Î»»¹ÊÇ¼Ó¹¤²Û
         if (drillWorks[curDrillIndex].length == 0)
         {
            //Ö´ÐÐ×ê¿×
            cRunStep = 100;

         }
         else
         {
            cRunStep = 200;

         }
         break;
      case 100:

         //×ßµ½×ê¿×Î»ÖÃ
         MV_Set_Startv(X_AXIS, 10);
         MV_Set_Speed(X_AXIS, UserParam->SiteIdleSpeed);
         dwRealPosi = MV_Get_Command_Pos(X_AXIS);
         cSetPulse = FactoryParam->DrillSiteOrign + drillWorks[curDrillIndex].position;
         cSetPulse = PositionToPluse(X_AXIS, cSetPulse);
         cSetPulse = cSetPulse - dwRealPosi;
         MV_Pmov(X_AXIS, cSetPulse);
         //DrillValve = 1;
         //³öµ¶
         cRunStep++;
         break;
      case 101:
         if (!X_DRV)
         {
            //×ßµ½×êÉî¶ÈÔ­µã
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
            //×ßµ½×êÉî¶ÈÔ­µã
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
            //µÈ´ýÔ²ÕûÊ±¼ä
            NextStepDlay = 10UL * UserParam->DrillCycleTime;
            cRunStep++;
         }
         break;
      case 104:
         if (NextStepDlay == 0)
         {
            //×ßµ½Éî¶ÈÁãµã
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
            //×ê¿×½áÊø
            cRunStep = 12;
         }
         break;
         //Ï³²Û¶¯×÷
      case 200:
         //×ßµ½×ê¿×Î»ÖÃ

         milliingDir = 1; //0´ÓÕý·½ÏòÏ³ 1´Ó·´·½ÏòÏ³
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
         //³öµ¶
         cRunStep++;
         break;
      case 201:
         if (!X_DRV)
         {
            //×ßµ½×êÉî¶ÈÔ­µã
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
            //×ßµ½×êÉî¶ÈÔ­µã
            MV_Set_Startv(Y_AXIS, 10);
            MV_Set_Speed(Y_AXIS, UserParam->MillingFeedSpeed);
            //Éî¶È×î¶àÒ»´ÎÖ»ÄÜ×ßµ½½ø¸øÖµ
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
            //µÈ´ýÔ²ÕûÊ±¼ä
            NextStepDlay = 10UL * UserParam->MillingCycleTime;
            cRunStep++;
         }
         break;
      case 204:
         if (NextStepDlay == 0)
         {
            //×ß²Û³¤¶È
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
            //ÅÐ¶ÏÊÇ·ñµ½´ïÉî¶È
            //Éî¶È×î¶àÒ»´ÎÖ»ÄÜ×ßµ½½ø¸øÖµ
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
                //×ßµ½Éî¶ÈÁãµã
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
            //X»ØÔ­µã
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
            //¼Ó¹¤Íê³É
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

