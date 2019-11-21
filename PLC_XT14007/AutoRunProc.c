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

unsigned char cCheckStep = 0; //����״̬
unsigned char cCheckFliter = 0; //�����˲�

#define bCheckSignal  I012
volatile char cCheckObjectOk = 0;
volatile long dwCheckPosition = 0;
volatile long dwStartPosition = 0;

volatile char bBacked = 0;
long dwComparePluse = 0;
unsigned char bWorkOk = 0;
unsigned char cAlarmFlag = 0;

unsigned long work_orign[20];
unsigned long work_length[20];
unsigned long work_depth[20];

unsigned char xc_frun_step;
unsigned char xc_rrun_step;
unsigned char xb_frun_step;
unsigned char xb_rrun_step;

unsigned char xb_f_r_step;

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

unsigned char slot_num_count(long orig,unsigned char dir)
{
    unsigned char i;
    unsigned char slot_num=0;
    for (i=0; i<20; i++)
    {
        work_orign[i]=0;
        work_length[i]=0;
        work_depth[i]=0;
    }
    if (dir==0)
    {
        for (i = 0; i < 10; i++)
        {
            if (FactoryParam->Slot_Orign[i] != 0 && FactoryParam->Slot_Length[i] != 0 
                && UserParam->Slot_Depth[i]!=0)
           {
                work_orign[slot_num]=FactoryParam->Slot_Orign[i]*10UL + orig;
                work_length[slot_num]=FactoryParam->Slot_Length[i]*10UL;
                work_depth[slot_num]=UserParam->Slot_Depth[i]*10UL;
                slot_num++;
           }
        }        
    }
    else
    {
        for (i = 10; i < 20; i++)
        {
            if (FactoryParam->Slot_Orign[i] != 0 && FactoryParam->Slot_Length[i] != 0 
                && UserParam->Slot_Depth[i]!=0)
           {
                work_orign[slot_num]=FactoryParam->Slot_Orign[i]*10UL + orig;
                work_length[slot_num]=FactoryParam->Slot_Length[i]*10UL;
                work_depth[slot_num]=UserParam->Slot_Depth[i]*10UL;
                slot_num++;
           }
        }
    }
    return slot_num;
}

void run_xc_forward(void)  //要改
{
    long set_dis;
    static unsigned char  all_slot_num;
    static unsigned char  cur_slot_num;
    static unsigned short cut_slot_depth;
    static unsigned long xc_rec_delay;

    switch (xc_frun_step)
    {
        case 1:
        case 10:
            if (1)
            {
                run_mech_posi(Y_AXIS,UserParam->y_idl_speed,0);                   //Z回零点
                xc_frun_step = 11;
            }
            break;
        case 11:
            if (!Y_DRV)
            {
                all_slot_num = slot_num_count(FactoryParam->x_drill1_dis,0);  
                if (all_slot_num>0)
                {
                    cur_slot_num = 0;
                    xc_frun_step = 12;
                }
                else    //预防没有设有孔的情况
                {

                }
            }
            break;
        case 12:
            {
                Y15=1;
                Y00=1;
                Y07=0;
                Y10=1;
                xc_rec_delay = dwTickCount + UserParam->xc_motor_start_time * 100UL; 
                xc_frun_step = 13;  
                cut_slot_depth=0;
            }
            break;
        case 13:
            if (xc_rec_delay < dwTickCount)  //到槽位置
            {
                set_dis = work_orign[cur_slot_num];
                run_mech_posi(X_AXIS,UserParam->x_idl_speed,set_dis);
                xc_frun_step = 14;
            }
            break;
        case 14:
            if (!X_DRV)     //到起点
            {
                set_dis = FactoryParam->dill_origin_dis1-UserParam->board_distance-UserParam->drill1_radius;
                run_mech_posi(Y_AXIS,UserParam->y_idl_speed,set_dis);
                xc_frun_step = 15;
            }
            break;
        case 15:
            if (!Y_DRV)   //进刀深度
            {
                if (!feed_xc)  //一次进刀
                {
                    set_dis = work_depth[cur_slot_num];
                    run_distance(Y_AXIS,UserParam->y_work_speed,set_dis);
                    xc_frun_step = 16;                    
                }
                else           //多次进刀
                {
                    if ((work_depth[cur_slot_num]-cut_slot_depth) > MotroParam->xc_one_feed)  //总-当前>一次进刀
                    {    
                        cut_slot_depth += MotroParam->xc_one_feed;              
                        run_distance(Y_AXIS, UserParam->y_work_speed, cut_slot_depth); 
                        xc_frun_step = 16;  
                    }
                    else  
                    {
                        cut_slot_depth = work_depth[cur_slot_num];
                        run_distance(Y_AXIS, UserParam->y_work_speed, cut_slot_depth);
                        xc_frun_step = 16;  
                    }
                }
            }
            break;
        case 16:
            if (!Y_DRV)  //铣槽
            {
                set_dis = work_length[cur_slot_num];
                run_distance(X_AXIS, UserParam->xc_work_speed, set_dis);
                xc_frun_step = 17;
            }
            break;
        case 17:
            if (!X_DRV)   //退出
            {
                set_dis = FactoryParam->dill_origin_dis1 - UserParam->board_distance - UserParam->drill1_radius - FactoryParam->safe_dis;
                run_mech_posi(Y_AXIS,UserParam->y_idl_speed,set_dis);
                xc_frun_step = 18;
            }
            break;
        case 18:
            if (!Y_DRV)
            {
                if (!feed_xc)
                {
                    xc_frun_step=19;
                }
                else
                {
                    if (cut_slot_depth >= work_depth[cur_slot_num])
                    {
                        xc_frun_step=19;
                        cut_slot_depth = 0;
                    }
                    else
                    {
                        xc_frun_step=13;
                    }   
                }
            }
            break;
        case 19:
            if (cur_slot_num<all_slot_num-1)
            {
                cur_slot_num++;
                xc_frun_step=13;
            }
            else
            {
                xc_frun_step=20;
            }
            break;
        case 20:
            xc_frun_step=0;
            break;
        default:
            break;
    }

}

void run_xc_reverse(void)
{
	long set_dis;
    static unsigned char  all_slot_num;
    static unsigned char  cur_slot_num;
    static unsigned short cut_slot_depth;
	static unsigned long xc_rec_delay;

    switch (xc_rrun_step)
    {
        case 1:
        case 10:
            if (1)
            {
                run_mech_posi(Z_AXIS,UserParam->z_idl_speed,0);                   //Z回零点
                xc_rrun_step = 11;
            }
            break;
        case 11:
            if (!Z_DRV)
            {
                all_slot_num = slot_num_count(FactoryParam->x_drill2_dis,1);  
                if (all_slot_num>0)
                {
                    cur_slot_num = all_slot_num-1;
                    xc_rrun_step = 12;
                }
                else    //预防没有设有孔的情况
                {
                        
                }
            }
            break;
        case 12:
            {
                Y14=1;
                Y00=1;
                xc_rec_delay = dwTickCount + UserParam->xc_motor_start_time * 100UL; 
                xc_rrun_step = 13;  
                cut_slot_depth=0;
            }
            break;
        case 13:
            if (1)  //到槽位置
            {
                set_dis = work_orign[cur_slot_num] + work_length[cur_slot_num];
                run_mech_posi(X_AXIS,(UserParam->x_idl_speed*0.6),set_dis);
                xc_rrun_step = 14;
            }
            break;
        case 14:
            if (!X_DRV && xc_rec_delay < dwTickCount)     //到Z轴起点
            {
                set_dis = FactoryParam->dill_origin_dis2 - UserParam->board_distance - UserParam->drill2_radius;
                run_mech_posi(Z_AXIS,UserParam->z_idl_speed,set_dis);
                xc_rrun_step = 15;
            }
            break;
        case 15:
            if (!Z_DRV)   //进刀深度
            {
                if (!feed_xc)  //一次进刀
                {
                    set_dis = work_depth[cur_slot_num];
                    run_distance(Z_AXIS,UserParam->z_work_speed,set_dis);
                    xc_rrun_step = 16;                    
                }
                else           //多次进刀
                {
                    if ((work_depth[cur_slot_num]-cut_slot_depth) > MotroParam->xc_one_feed)  //总-当前>一次进刀
                    {    
                        cut_slot_depth += MotroParam->xc_one_feed;              
                        run_distance(Z_AXIS, UserParam->z_work_speed, cut_slot_depth); 
                        xc_rrun_step = 16;  
                    }
                    else  
                    {
                        cut_slot_depth = work_depth[cur_slot_num];
                        run_distance(Z_AXIS, UserParam->z_work_speed, cut_slot_depth);
                        xc_rrun_step = 16;  
                    }
                }
            }
            break;
        case 16:
            if (!Z_DRV)  
            {
                set_dis = (-1) * work_length[cur_slot_num];
                run_distance(X_AXIS, UserParam->xc_work_speed, set_dis);
                xc_rrun_step = 17;
            }
            break;
        case 17:
            if (!X_DRV)            
			{
                set_dis = FactoryParam->dill_origin_dis2 - UserParam->board_distance - UserParam->drill2_radius - FactoryParam->safe_dis;
                run_mech_posi(Z_AXIS, UserParam->z_idl_speed, set_dis);
                xc_rrun_step = 18;
            }
            break;
        case 18:
            if (!Z_DRV)
            {
                if (!feed_xc)
                {
                    xc_rrun_step=19;
                }
                else
                {
                    if (cut_slot_depth >= work_depth[cur_slot_num])
                    {
                        xc_rrun_step=19;
                        cut_slot_depth = 0;
                    }
                    else
                    {
                        xc_rrun_step=13;
                    }   
                }
            }
            break;
        case 19:
            if (cur_slot_num>0)
            {
                cur_slot_num--;
                xc_rrun_step=13;
            }
            else if (cur_slot_num<=0)
            {
                xc_rrun_step=20;
            }
            break;
        case 20:
            xc_rrun_step=0;
            break;
        default:
            break;
    }

}
void run_xb_forward(void)
{
	long set_dis;
    static long cur_depth;
    static unsigned long xb_forw_delay;

    switch (xb_frun_step)
    {
        case 1:
		    cur_depth=0;
			xb_frun_step=3;

            xb_forw_delay = dwTickCount + UserParam->xb_motor_start_time * 100UL; 
            Y00=1;
            Y15=1;
            Y07=0;
            Y10=1;

		    break;
        case 3:
            if (!Y_DRV)
            {
                set_dis = FactoryParam->x_drill1_dis - UserParam->xb_yuxi_dis;  //x到起点
				
				run_mech_posi(X_AXIS,UserParam->x_idl_speed,set_dis);
                set_dis = FactoryParam->dill_origin_dis1 - UserParam->board_distance - UserParam->drill1_radius;
                run_mech_posi(Y_AXIS,UserParam->y_idl_speed,set_dis); 
                xb_frun_step = 4;
            }             
           break;
        case 4:
           if (!X_DRV && xb_forw_delay<dwTickCount)        //y到起点
           
		   {
               
               xb_frun_step = 5;
           }
           break;
        case 5:
           if (!Y_DRV)        //y进深度
           
		   {
               if (!feed_xb)  //一次进刀
               {
                   run_distance(Y_AXIS, UserParam->y_work_speed, UserParam->TrimingDeepth);
                   xb_frun_step = 6;                       
               }
               else           //多次进刀
               {
                   if ((UserParam->TrimingDeepth-cur_depth) > MotroParam->xb_one_feed)  //总-当前>一次进刀
                   {    
                       cur_depth += MotroParam->xb_one_feed;              
                       run_distance(Y_AXIS, UserParam->y_work_speed, cur_depth); 
                       xb_frun_step = 6;  
                   }
                   else  
                   {
                       cur_depth = UserParam->TrimingDeepth;
                       run_distance(Y_AXIS, UserParam->y_work_speed, cur_depth);
                       xb_frun_step = 6;  
                   }
               }
           }
           break;
        case 6:
            if (!Y_DRV)    //x修边
            {
                set_dis = UserParam->TrimingLength + (UserParam->xb_yuxi_dis * 2UL);
                run_distance(X_AXIS,UserParam->x_work_speed,set_dis);
                xb_frun_step = 7;
            }
            break;
        case 7:
            if (!X_DRV)    //y退刀
            {
                set_dis = FactoryParam->dill_origin_dis1 - UserParam->board_distance - UserParam->drill1_radius - FactoryParam->safe_dis;
                run_mech_posi(Y_AXIS, UserParam->y_idl_speed, set_dis);
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
                    if (cur_depth >= UserParam->TrimingDeepth)
                    {
                        xb_frun_step=9;
                        cur_depth=0;
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

void run_xb_fore_reve(void)
{
	static long set_dis;
    static long cur_depth;
    static unsigned char feed_count;
    static unsigned long xb_f_r_delay;
   
    switch (xb_f_r_step)
    {
        case 1:
            feed_count=0;
            cur_depth=0;
			xb_f_r_step=2;
		    break;
        case 2:
            motor_run_flg=1;
            xb_f_r_delay = dwTickCount + UserParam->xb_motor_start_time * 100UL; 
            Y00=1;
            Y15=1;
            Y07=0;
            Y10=1;
            xb_f_r_step = 3;
            break;
        case 3:
            if (xb_f_r_delay<dwTickCount)
            {
                if (feed_count%2==1)
                {
                    set_dis = FactoryParam->x_drill2_dis + UserParam->xb_yuxi_dis;
                    set_dis += UserParam->TrimingLength;  
                }
                else
                {
                    set_dis = FactoryParam->x_drill1_dis - UserParam->xb_yuxi_dis;  //x到起点
                }
				
				run_mech_posi(X_AXIS,UserParam->x_idl_speed,set_dis);

                if (feed_count%2==1)
                {
                    set_dis = FactoryParam->dill_origin_dis2 - UserParam->board_distance - UserParam->drill2_radius;
                    run_mech_posi(Z_AXIS, UserParam->z_idl_speed,set_dis);                   
                }
                else
                {
                    set_dis = FactoryParam->dill_origin_dis1-UserParam->board_distance - UserParam->drill1_radius;
                    run_mech_posi(Y_AXIS, UserParam->y_idl_speed,set_dis);
                }
                xb_f_r_step = 4;
            }             
           break;
        case 4:
           if (!X_DRV)        //y到起点
           {
               xb_f_r_step = 5;
           }
           break;
        case 5:
           if (!Y_DRV && !Z_DRV)        //y进深度
           {
               if (!feed_xb)  //一次进刀
               {
                   run_distance(Y_AXIS, UserParam->y_work_speed, UserParam->TrimingDeepth);
                   xb_f_r_step = 6;                       
               }
               else           //多次进刀
               {
                   if ((UserParam->TrimingDeepth-cur_depth) > MotroParam->xb_one_feed)  //总-当前>一次进刀
                   {    
                       cur_depth += MotroParam->xb_one_feed;   
                       if(feed_count%2==1)  
                           run_distance(Z_AXIS, UserParam->z_work_speed, cur_depth);
                       else         
                           run_distance(Y_AXIS, UserParam->y_work_speed, cur_depth); 
                       xb_f_r_step = 6;  
                   }
                   else  
                   {
                       cur_depth = UserParam->TrimingDeepth;
                       if(feed_count%2==1)
                           run_distance(Z_AXIS, UserParam->z_work_speed, cur_depth);
                       else
                           run_distance(Y_AXIS, UserParam->y_work_speed, cur_depth);
                       xb_f_r_step = 6;  
                   }
               }
           }
           break;
        case 6:
            if (!Y_DRV && !Z_DRV)    //x修边
            {
                if(feed_count%2==1) 
                {
                    set_dis = UserParam->TrimingLength + (UserParam->xb_yuxi_dis * 2UL);
                    set_dis *= -1;
                    run_distance(X_AXIS,UserParam->x_work_speed,set_dis);
                }
                else
                {
                    set_dis = UserParam->TrimingLength + (UserParam->xb_yuxi_dis * 2UL);
                    run_distance(X_AXIS,UserParam->x_work_speed,set_dis);
                }
                xb_f_r_step = 7;
            }
            break;
        case 7:
            if (!X_DRV)    //y退刀
            {
                if (feed_count%2==0)
                {
                    set_dis = FactoryParam->dill_origin_dis1 - UserParam->board_distance - UserParam->drill1_radius - FactoryParam->safe_dis;
                    run_mech_posi(Y_AXIS, UserParam->y_idl_speed, set_dis);
                }
                else
                {
                    set_dis = FactoryParam->dill_origin_dis2 - UserParam->board_distance - UserParam->drill2_radius - FactoryParam->safe_dis;
                    run_mech_posi(Z_AXIS, UserParam->z_idl_speed, set_dis);
                }
                xb_f_r_step = 8;
            }
            break;
        case 8:
            if (!Y_DRV && !Z_DRV)
            {
                if (!feed_xb)
                {
                    xb_f_r_step=9;
                }
                else
                {
                    if (cur_depth >= UserParam->TrimingDeepth)
                    {
                        xb_f_r_step=9;
                        cur_depth=0;
                    }
                    else
                    {
                        xb_f_r_step=10;
                        feed_count++;
                    }   
                }
            }
            break;
        case 9:
            xb_f_r_step = 0;
            break;

        case 10:
            Y00=0;
            Y15=0;
            Y14=0;
            xb_f_r_delay = dwTickCount + MOTOR_SWITCH__TIME; 
            xb_f_r_step = 11;
            break;
        case 11:
            if (xb_f_r_delay < dwTickCount)
            {
                if (feed_count%2==1)
                {
                    Y00 = 1;
                    Y14=1;
                    xb_f_r_step = 12;
                    xb_f_r_delay = dwTickCount + UserParam->xb_motor_start_time * 100UL; 
                }
                else
                { 
                    xb_f_r_step=2;      
                }
            }
            break;
        case 12:
            if (xb_f_r_delay < dwTickCount)
            {
                xb_f_r_step=3;
            }
            break;
        default:
            break;
    }
}


void run_xb_reverse(void)//要改
{
    long set_dis;
    static long cur_depth;
    static unsigned long xb_reve_delay;

    switch (xb_rrun_step)
    {
        case 1:
            cur_depth=0;
            xb_rrun_step=3;
            xb_reve_delay = dwTickCount + UserParam->xb_motor_start_time * 100UL; 
            Y00=1;
            Y14=1;
            break;
        case 3:
            if (1)
            {
                set_dis = FactoryParam->x_drill2_dis + UserParam->xb_yuxi_dis;
                set_dis += UserParam->TrimingLength;  
                run_mech_posi(X_AXIS,UserParam->x_idl_speed,set_dis);

                set_dis = FactoryParam->dill_origin_dis2 - UserParam->board_distance - UserParam->drill2_radius;
                run_mech_posi(Z_AXIS,UserParam->z_idl_speed,set_dis); 
                xb_rrun_step = 4;
            }             
           break;
        case 4:
           if (!X_DRV)        //到起点
           {
               xb_rrun_step = 5;
           }
           break;
        case 5:
           if (!Z_DRV && xb_reve_delay<dwTickCount)        //y进深度
           {
               if (!feed_xb)  //一次进刀
               {
                   run_distance(Z_AXIS, UserParam->z_work_speed, UserParam->TrimingDeepth);
                   xb_rrun_step = 6;                       
               }
               else           //多次进刀
               {
                   if ((UserParam->TrimingDeepth-cur_depth) > MotroParam->xb_one_feed)  //总-当前>一次进刀
                   {    
                       cur_depth += MotroParam->xb_one_feed;              
                       run_distance(Z_AXIS, UserParam->z_work_speed, cur_depth); 
                       xb_rrun_step = 6;  
                   }
                   else  
                   {
                       cur_depth = UserParam->TrimingDeepth;
                       run_distance(Z_AXIS, UserParam->z_work_speed, cur_depth);
                       xb_rrun_step = 6;  
                   }
               }
           }
           break;
        case 6:
            if (!Z_DRV)    //x修边
            {
                set_dis = UserParam->TrimingLength + (UserParam->xb_yuxi_dis*2UL);
                set_dis *= (-1);
                run_distance(X_AXIS,UserParam->x_work_speed,set_dis);
                xb_rrun_step = 7;
            }
            break;
        case 7:
            if (!X_DRV)    //y退刀
            {
                set_dis = FactoryParam->dill_origin_dis2 - UserParam->board_distance - UserParam->drill2_radius - FactoryParam->safe_dis;
                run_mech_posi(Z_AXIS, UserParam->z_idl_speed, set_dis);
                xb_rrun_step = 8;
            }
            break;
        case 8:
            if (!Z_DRV)
            {
                if (!feed_xb)
                {
                    xb_rrun_step=9;
                }
                else
                {
                    if (cur_depth >= UserParam->TrimingDeepth)
                    {
                        xb_rrun_step=9;
                        cur_depth=0;
                    }
                    else
                    {
                        xb_rrun_step=3;
                    }   
                }
            }
            break;
        case 9:
            xb_rrun_step = 0;
            break;
        default:
            break;
    }

}

void aotu_run(void)
{
    static unsigned long run_delay=0;
    TestData->testdata[1] = cRunStep;
    TestData->testdata[2] = xb_f_r_step;
    if (bRunning)
    {
        switch (cRunStep)
        {
            case 1:
                {
                    run_mech_posi(Y_AXIS,UserParam->y_idl_speed,0);                   //y回零点
                    
					run_mech_posi(Z_AXIS,UserParam->z_idl_speed,0); 
                    cRunStep = 2;
                }      
                break;
            case 2:
                if (!Y_DRV && !Z_DRV)
                {
                    if (MotroParam->mode_lift == MODEXIUB)
                   {
                       if (MotroParam->mode_right == MODEXIUB)//ok
                       {
                           cRunStep = 33;
                           xb_f_r_step = 1;
                       }
                       else if (MotroParam->mode_right == MODEXICAO)//OK
                       {
                           run_delay = dwTickCount + UserParam->xc_motor_start_time * 100UL; 
                           Y00=1;
                           Y15=1;

                           Y07=0;
                           Y10=1;
                           
                           cRunStep = 13;
                           xc_frun_step = 1;                          
                       }
                   }
                   else if (MotroParam->mode_lift == MODEXICAO)
                   {
                       if (MotroParam->mode_right == MODEXIUB)//
                       {
                           cRunStep = 3;
                           xb_frun_step = 1;
                       }
                       else if (MotroParam->mode_right == MODEXICAO)//ok
                       {
                           if (!motor_run_flg)
                           {
                               motor_run_flg=1;
                               run_delay = dwTickCount + UserParam->xc_motor_start_time * 100UL; 
                               Y00=1;
                               Y15=1;
                               Y07=0;
                               Y10=1;
                           }
                           else
                           {
                               Y07=0;
                               Y10=1;
                               run_delay = dwTickCount + UserParam->PressValveOpenTime * 100UL; 
                           }
                           cRunStep = 23;
                           xc_frun_step = 1;
                       }               
                   }
                   else  //左边不加工
                   {
                       if (MotroParam->mode_right == MODEXIUB)
                       {
                           cRunStep = 43;
                           xb_frun_step = 1;
                       }
                       else if (MotroParam->mode_right == MODEXICAO)
                       {
                           cRunStep = 53;
                           xc_frun_step = 1;
                       }
                   }
                }
               break;
            case 3:      
                run_xb_forward();
                if (xb_frun_step==0)
                {
                    cRunStep=4;
                }
                break;
            case 4:
                Y00=0;
                Y15=0;
                run_delay = dwTickCount + MOTOR_SWITCH__TIME; 
                cRunStep = 5;
                break;
            case 5:
                if (run_delay < dwTickCount)
                {
                    cRunStep = 6;
                    xc_rrun_step = 1;
                }
                break;
            case 6:
                run_xc_reverse();
                if (xc_rrun_step==0)
                {
                    cRunStep=80;
                }
                break;

            case 13:  //修边铣槽
                run_xc_forward();
                if (xc_frun_step==0)
                {
                    cRunStep=14;
                }
                break;
            case 14:
                Y00=0;
                Y15=0;
                run_delay = dwTickCount + MOTOR_SWITCH__TIME; 
                cRunStep = 15;
                break;
            case 15:
                if (run_delay < dwTickCount)
                {
                    cRunStep = 16;
                    xb_rrun_step = 1;
                }
                break;
            case 16:
                run_xb_reverse();
                if (xb_rrun_step==0)
                {
                    cRunStep=80;
                }
                break;

            case 23:  
                run_xc_forward();
                if (xc_frun_step==0)
                {
                    cRunStep=24;
                }
                break;
            case 24:
			    {
		            Y00=0;
		            Y15=0;
		            run_delay = dwTickCount + MOTOR_SWITCH__TIME; 
		            cRunStep = 25;
			    }
                break;
            case 25:
                if (run_delay < dwTickCount)
                {
                    cRunStep = 26;
                    xc_rrun_step = 1;
                }
                break;
            case 26:
                run_xc_reverse();
                if (xc_rrun_step==0)
                {
                    cRunStep=80;
                }
                break;

            case 33:      //修边修边
                run_xb_fore_reve();
                if (xb_f_r_step==0)
                {
                    cRunStep=80;
                }
                break;

            case 43:
                run_xb_forward();
                if (xb_frun_step==0)
                {
                    cRunStep=80;
                }
                break;

            case 53:
                run_xc_forward();
                if (xc_frun_step==0)
                {
                    cRunStep=80;
                }
                break;
                
            case 80:
                {
                    Y00 = 0;
                    Y14 = 0;
                    Y15 = 0;
                    run_mech_posi(X_AXIS,UserParam->x_idl_speed,0);
                    run_mech_posi(Y_AXIS,UserParam->y_idl_speed,0);
                    run_mech_posi(Z_AXIS,UserParam->z_idl_speed,0);
                    cRunStep = 81;
                    SystemParam->Proctotal++;
                    Write24C04((16 + 0), SystemParam->Proctotal);
                    Write24C04((16 + 1), SystemParam->Proctotal >> 8);
                    Write24C04((16 + 2), SystemParam->Proctotal >> 16);
                    Write24C04((16 + 3), SystemParam->Proctotal >> 24);
                }
                break;
            case 81:
                if (!X_DRV && !Y_DRV && !Z_DRV)
                {
                    Y07 = 1;
                    run_delay = dwTickCount + UserParam->PressValveCloseTime * 100UL; 
                    cRunStep = 82;
                }
                break;
            case 82:
                if (run_delay < dwTickCount)
                {
                    motor_run_flg=0;
                    Y10 = 0;
                    cRunStep = 0;
                    bRunning = 0;
                }
                break;

           default:
               break;
        }
    }
}



void ServorHandler(void)
{
	
}


//��Ҫ�ӹ�������
typedef struct
{
   long position;
   long length;
   long depth;
} DrillsData;

//static long currentdeltaDeepth = 0;
static DrillsData drillWorks[15]; //��ӹ����ݻ���
static DrillsData drillWorks2[15]; // ���в� �ӹ����ݻ���
static char drillWorksCnt = 0;   //��ӹ�����
//static char oldMode = 0;
static char errorStep = 0;
 char curDrillIndex = 0;
static char milliingDir = 0;
static DrillsData drillDataTemp; //������ݿ�������
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
	return 0;
}

void MovetoWorkPosition(void)
{
}

void MoveforWorkLength(void)
{
}

// �����ڴ�׻��
void Slot2Proc(void)
{
   
}

void SawAction(void)
{
    if(cSawRunstep == 1)
    {

    }
}

/************************************************/
/*
�Զ�����

*/
/************************************************/
void AutoRun(void)
{
}

