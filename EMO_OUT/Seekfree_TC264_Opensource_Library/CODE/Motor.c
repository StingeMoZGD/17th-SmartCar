/*
 * Motor.c
 *
 *  Created on: 2021年11月12日
 *      Author: YYM
 */

#include "Motor.h"

/***************定义************/
int MotorONE=0;
int MotorTWO=0;
int MotorTime = 0;
float Pre_Speed=0;
float Exp_SpeedONE=0;
float Exp_SpeedTWO=0;
//int16 TargetAngle = 0;
unsigned char Auxiliary_CorneringLeft_flag = 0;    //强制向左辅助打角
unsigned char Auxiliary_CorneringRight_flag = 0;    //强制向右辅助打角
int16 dirONE=0;
int16 dirTWO=0;
unsigned char Crash_Out = 0;
unsigned char Garage_Out_flag = 1;          //出库标志 0：不进行出库 1：进行出库
unsigned char Garage_In_flag = 0;           //入库标志  0：不进行入库 1：进行入库
unsigned char Garage_Dir = 0;               //出库方向 0：右 1：左 默认为右
unsigned char Garage_Out_Finsh_flag = 0;    //出库完成信号  0:未出库 1：出库完成
unsigned char FindCharge_flag = 0;          //到达充电点最佳充电位置
unsigned char GarageL_In_flag = 0;
unsigned char GarageR_In_flag = 0;
unsigned char Read_Battery_Voltage_flag = 0;
unsigned char need_cornerL = 0;              //小转弯辅助：用于元素出入的一些转弯辅助
unsigned char need_cornerR = 0;
float Read_Battery_Voltage = 0;
float Read_Speed = 0;
float Dircetion_Standard=93.0;
float V;
unsigned char CS_flag = 0;  //充电停车标志
unsigned char CCC = 0;  //充电计数程序，国赛用


const uint16 Dec = 300;
const uint16 AMAX = 3803;
const int distance = 1650;    //LQ1700   ZH2400
const int Predistance = 330;
const int lowdistance = 300;
const int highdistance = 80;
const int conerdistance = 900;
float end_Bat = 7.2;
/***********转换量****************/
//extern uint8 Middle_Black_Point[120];
//extern int16 CoderONE,CoderTWO;
//extern uint8 OSTU;
//extern volatile unsigned char State;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      拉格朗日线性插值法
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       用来根据距离进行减速
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
float Lagrange_interpolation(float x1,float y1,float x2,float y2,float x)
{
    float com1 = (float)x-(float)x2;
    float con1 = (float)x1-(float)x2;
    float com2 = (float)x-(float)x1;
    float con2 = (float)x2-(float)x1;
    float c1 = com1/con1;
    float c2 = com2/con2;
    float c3 = c1*(float)y1;
    float c4 = c2*(float)y2;
    return (c3+c4);
}

void Motor_Init(void)
{
    gtm_pwm_init(PWMONE);   //电机初始化
    gtm_pwm_init(PWMone);
    gtm_pwm_init(PWMTWO);
    gtm_pwm_init(PWMtwo);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      方向环
//  @param      Exp_SpeedONE   左轮的方向环输出
//  @param      Exp_SpeedTWO   右轮的方向环输出
//  @param
//  @param
//  @return     void
//  @note       单摄像头的偏差环，建议加上角速度环，有时间就补充模糊
//  @note       额外的Pre_Speed/n  是我用于弯道或者元素的辅助转弯，帮助内切或者顺利通过元素 因为弯道中央有时候会有线圈，在靠近线圈是，车子转弯就不在内切
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
void Motor_Direction(void)    //方向环，偏差角度环，有时间做角速度环 位置式
{
    if(OSTU < 90)      //用大津法阈值判断是否冲出赛道，保护车辆
        Crash_Out = 1;
    if(Crash_Out == 1)
        Pre_Speed = 0;
    else
    {

//        if(Real_ChDistance >= 25000)
//        {
//            Pre_Speed = 0;
//        }
////        if(BoundaryRight == 0 && BoundaryLeft == 0)
////            Pre_Speed = 160;
////        else
////            Pre_Speed = 90;
//        Pre_Speed = (float)Replace_Speed;
//        Pre_Speed = 60;
//    }
//    if(MotorTime % 50 == 0)
//    {
//         Pre_Speed += 4;
//         MotorTime = 0;
     }
//     MotorTime +=1;
//     Pre_Speed = (Pre_Speed > 60) ? 60 : Pre_Speed;

//依据两轮差速控制，基于阿克曼电子差速，但是前提是有舵机，还得优化
    double Length = 23;      //车到目标点的距离，这里使用摄像头里的图像像素点位置
    double Width = 21;     //两轮之间的轮距
    double tanS = (Differential_Error);
//    double V1 = V*(1-Width*tanS/(Length*2));
//    double V2 = V*(1+Width*tanS/(Length*2));
    double V1 = Width*tanS/(Length*2);
    double V2 = Width*tanS/(Length*2);

    V = (float)V1;
    if(Auxiliary_CorneringLeft_flag == 1 && Auxiliary_CorneringRight_flag == 0)    //陀螺仪向左辅助打角
    {
        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/4;
        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/4;
    }
    else if(Auxiliary_CorneringLeft_flag == 0 && Auxiliary_CorneringRight_flag == 1)
    {
        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/4;
        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/4;
    }
//    else if(Replace_Coner == 1 && CornerLeft_flag == 1 && (AfterI_Voltage < 175 || State == ChargeFinsh_State))
//    {
////        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
////        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/8;
//        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/20;
//        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/20;
//        //Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
//    }
//    else if(Replace_Coner == 1 && CornerRight_flag == 1 && (AfterI_Voltage < 175 || State == ChargeFinsh_State))
//    {
////        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/8;
////        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
//        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/20;
//        //Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
//        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/20;
//    }
    else if(need_cornerL == 1 && Auxiliary_CorneringLeft_flag == 0 && Auxiliary_CorneringRight_flag == 0)
    {
        if(Trifork_flag == 1 && CircleBig == 0 && (AfterI_Voltage < 175 || State == ChargeFinsh_State))
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/25;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/25;
        }
//        else if(CircleBig == 1 && Trifork_flag == 0)
//        {
//            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/23;
//            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/23;
//        }
        else if(Trifork_flag == 0 && CircleBig == 0 && SlalomRight_flag == 0)
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/32;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/32;
        }
        else if(Trifork_flag == 0 && CircleBig == 0 && SlalomRight_flag == 1)
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/8;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/8;
        }
        else
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
        }
    //        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
    //        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/8;
    }
    else if(need_cornerR == 1 && Auxiliary_CorneringRight_flag == 0 && Auxiliary_CorneringLeft_flag == 0)
    {
        if(Trifork_flag == 1 && CircleBig == 0 && (AfterI_Voltage < 175 || State == ChargeFinsh_State))
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/25;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/25;
        }
//        else if(Trifork_flag == 0 && CircleBig == 1)
//        {
//            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/23;
//            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/23;
//        }
        else if(Trifork_flag == 0 && CircleBig == 0 && SlalomLeft_flag == 0)
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/35;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/35;
        }
        else if(Trifork_flag == 0 && CircleBig == 0 && SlalomLeft_flag == 1)
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/8;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/8;
        }
        else
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
        }
    }
    else
    {
        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
    }

//    Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
//    Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
    if(Pre_Speed >= 0)
    {
        Exp_SpeedONE = Exp_SpeedONE > (10 * Pre_Speed) ? (10*Pre_Speed) : Exp_SpeedONE;
        Exp_SpeedTWO = Exp_SpeedTWO > (10 * Pre_Speed) ? (10*Pre_Speed) : Exp_SpeedTWO;
    }
    else
    {
        Exp_SpeedONE = Exp_SpeedONE < (10 * Pre_Speed) ? (10*Pre_Speed) : Exp_SpeedONE;
        Exp_SpeedTWO = Exp_SpeedTWO < (10 * Pre_Speed) ? (10*Pre_Speed) : Exp_SpeedTWO;
    }

    //Exp_

}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      速度环
//  @param      MotorONE   左轮的pwm输出
//  @param      MotorTWO   右轮的pwm输出
//  @param
//  @param
//  @return     void
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
void Motor_SPEEDLOOP(void)    //速度环  增量式PID
{

//    Encoder_coder();
    //Encoder_FindCharge(20000,80);
    MotorONE = Incrementalone_PI ((float)CoderONE,Exp_SpeedONE);
    MotorTWO = Incrementaltwo_PI ((float)CoderTWO,Exp_SpeedTWO);

//    if(Ostu < 130)
//    {
//        MotorONE = 0;
//        MotorTWO = 0;
//    }
//    Incrementalone_PI ((float)CoderONE,Exp_SpeedONE) = Incrementalone_PI ((float)CoderONE,Exp_SpeedONE) < (0) ? : Incrementalone_PI ((float)CoderONE,Exp_SpeedONE);
//    Incrementaltwo_PI ((float)CoderTWO,Exp_SpeedTWO) = Incrementaltwo_PI ((float)CoderTWO,Exp_SpeedTWO) < (0) ? : Incrementaltwo_PI ((float)CoderTWO,Exp_SpeedTWO);
//
//    MotorONE = MotorONE > 7000 ? (7000) : (MotorONE);
//    MotorTWO = MotorTWO > 7000 ? (7000) : (MotorTWO);
//
//    MotorONE = MotorONE < (0) ? (0) : (MotorONE);
//    MotorTWO = MotorTWO < (0) ? (0) : (MotorTWO);
//    MotorONE = -100;
//    MotorTWO = -100;
    if(MotorONE < 0)  //反转
    {
        pwm_duty(ONE, dirONE);
        pwm_duty(one,-MotorONE);
//        pwm_duty(ONE, 100);
//        pwm_duty(one, dirONE);
    }
    else
    {
        pwm_duty(ONE, MotorONE);
        pwm_duty(one, dirONE);
    }
    if(MotorTWO < 0)
    {
        pwm_duty(TWO, dirTWO);
        pwm_duty(two,-MotorTWO);
//        pwm_duty(two, dirTWO);
//        pwm_duty(TWO, 100);
    }
    else
    {
        pwm_duty(two, dirTWO);
        pwm_duty(TWO, MotorTWO);
    }
//    pwm_duty(ONE, 1500);
//    pwm_duty(one, dirONE);
//    pwm_duty(two, dirTWO);
//    pwm_duty(TWO, 1500);
//    gpt12_clear(GPT12_T2);    //编码器清空

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      根据电容电压判断是否在线圈上需要停下
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
void Retrieval(float V , float Speed)
{
    if(V <= 12.5)
    {
        Pre_Speed = 0;
        if(MODE == 2)
        {
            Replace_Speed = 125;
        }
        else if(MODE == 3)
        {
            Replace_Speed = 133;
        }
    }

    else if(V > 12.5 && V <= 14)
    {
        Pre_Speed = 25;
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      无符号16相减
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
int Emo_Uint16(uint16 a,uint16 b)
{
    int c = (int)a;
    int d = (int)b;

    return c-d;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      遇到需要对速度做的处理
//  @param      end_Bat   按键可控制的停车电压，决定是否需要忽略此线圈
//  @param
//  @param
//  @param
//  @return     void
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
void Decelerateone(float V , float Speed)
{
    //如果电压大于8V不进行减速
    if(V >= end_Bat)  //忽略此线圈
    {
        limitspeedone();
        Read_Battery_Voltage_flag = 0;
        Coner_Charge = 0;
        Element_Charge = 0;
    }
    else
    {
        if(Speed <= 110 && Pre_Speed < 108)
        {
            if(V < 6)
            {
                if(Speed >= 25 && Real_ChDistance <= 1200 && Pre_Speed >= 26)
                {
                    Pre_Speed = Lagrange_interpolation(0.0,Speed,1200.0,25.0,(float)Real_ChDistance);
                    Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
                }
                else
                {
                    Pre_Speed = Pre_Speed > 25 ? 25 : Pre_Speed;
                }
                if(LAV >= 1800)
                {
                    if(CS_flag == 1)
                    {
                        Encoderlow_flag = 1;
                    }
                }
                if(Real_lowDistance >= (Predistance + lowdistance))
                {
                    FindCharge_flag = 1;
                    //EncoderCharge_flag = 0;
                    CCC++;
                    Pre_Speed = 0;
                    Encoderlow_flag = 0;
                }
            }
            else
            {
                if(Speed >= 70 && Real_ChDistance <= 800 && Pre_Speed >= 71)
                {
                    Pre_Speed = Lagrange_interpolation(0.0,Speed,800.0,70.0,(float)Real_ChDistance);
        //            Pre_Speed = Pre_Speed - 5;
                    Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
                    //Speed = 100;
                }
                else
                {
                    Pre_Speed = Pre_Speed > 70 ? 70 : Pre_Speed;
                }
                if(LAV >= 1800)
                {
                    if(CS_flag == 1)
                    {
                        //Encoderlow_flag = 1;   //测停车距离
                        //EncoderCharge_flag = 1;
                        Pre_Speed = 0;
                        FindCharge_flag = 1;
                        CS_flag = 0;
                        CCC++;
                    }
        //            }
                }
            }
        }
        else
        {
            if(Speed >= 25 && Real_ChDistance <= 1200 && Pre_Speed >= 26)
            {
                Pre_Speed = Lagrange_interpolation(0.0,Speed,1200.0,25.0,(float)Real_ChDistance);
                Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
                //Pre_Speed = 25;
            }
            else
            {
                Pre_Speed = Pre_Speed > 25 ? 25 : Pre_Speed;
            }
            if(LAV >= 1800)
            {
                if(CS_flag == 1)
                {
                    Encoderlow_flag = 1;
                }
            }
            if(V >= 6)
            {
                if(Real_lowDistance >= (Predistance + highdistance))
                {
                    FindCharge_flag = 1;
                    //EncoderCharge_flag = 0;
                    Pre_Speed = 0;
                    Encoderlow_flag = 0;
                    CCC++;
                }
            }
            else
            {
                if(Real_lowDistance >= (Predistance + lowdistance))
                {
                    FindCharge_flag = 1;
                    //EncoderCharge_flag = 0;
                    Pre_Speed = 0;
                    Encoderlow_flag = 0;
                    CCC++;
                }
            }
        }
    }
}

void Deceleratetwo(float V , float Speed)
{
    //如果电压大于8V不进行减速

    if(V >= end_Bat)
    {
        limitspeedtwo();
        Read_Battery_Voltage_flag = 0;
        Coner_Charge = 0;
        Element_Charge = 0;
    }
    else if(V < 6 && V < end_Bat)
    {
//        Pre_Speed = (Speed-35)/(Dec - AIN) * (float)AfterI_Voltage + 35*(Dec - AIN)/(AIN*(Speed - 35));
//        if(Real_ChDistance % 100 == 0)
//        {
//            Pre_Speed = Pre_Speed - 5;
//            Pre_Speed = Pre_Speed < 20 ? 20 : Pre_Speed;
//            // x1 DEC y1 Speed  x2 AMAX y2 25
////            if(AfterI_Voltage < )
////            {
//                //Pre_Speed =25 * (((float)AfterI_Voltage - Dec)/((AMAX-500) - Dec)) + Speed * (((float)AfterI_Voltage - (AMAX-500))/(Dec - (AMAX-200)));
////            }
//            //Pre_Speed =25 * (((float)AfterI_Voltage - Dec)/((AIN-Speed) - Dec)) + Speed * (((float)AfterI_Voltage - (AIN-Speed))/(Dec - (AIN-Speed)));
//        }
        if(Pre_Speed > 90)
        {
            Pre_Speed = 90;
        }
        if(Speed >= 25 && Real_ChDistance <= 1000 && Pre_Speed >= 26)
        {
            Pre_Speed = Lagrange_interpolation(0.0,Speed,1000.0,25.0,(float)Real_ChDistance);
            Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
        }
        else
        {
            Pre_Speed = Pre_Speed > 25 ? 25 : Pre_Speed;
        }
        if(LAV >= 1800)
        {
            if(Emo_Uint16(AfterI_Voltage,LAV) <= -7)
            {
                Encoderlow_flag = 1;
            }
        }
        if(Real_lowDistance >= (Predistance + lowdistance))
        {
            FindCharge_flag = 1;
            CCC++;
            //EncoderCharge_flag = 0;
            Pre_Speed = 0;
            Encoderlow_flag = 0;
        }
//        if(Real_ChDistance >= (distance+Predistance+lowdistance))
//        {
//            FindCharge_flag = 1;
//            //EncoderCharge_flag = 0;
//            Pre_Speed = 0;
//            Encoderlow_flag = 0;
////            EncoderCharge_flag = 1;
//        }
//        if(AfterI_Voltage < 1130)
//        {
//            if(Real_ChDistance > (distance+Predistance))
//            {
//                EncoderCharge_flag = 0;
//            }
//        }
    }
    else if(V >= 6 && V < end_Bat)
    {
//        if(Speed > 90)
//        {
//            exspeee = 90;
//        }
//        else
//        {
//            exspeee = Speed;
//        }

        if(Speed >= 70 && Speed < 110 && Real_ChDistance <= 800 && Pre_Speed >= 71)
        {
            Pre_Speed = Lagrange_interpolation(0.0,Speed,800.0,70.0,(float)Real_ChDistance);
//            Pre_Speed = Pre_Speed - 5;
            Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
            //Speed = 100;
        }
        else if(Speed >= 110)
        {
            Pre_Speed -= 20;
            Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
        }
        else
        {
            Pre_Speed = Pre_Speed > 70 ? 70 : Pre_Speed;
        }
//        if(Real_ChDistance >= (distance + lowdistance))   //防止计步过冲
//        {
//            EncoderCharge_SumClear();
//            EncoderCharge_flag = 0;
//        }
//        if(Real_ChDistance <= 1200)
//        {
//            if(CornerRight_flag == 1 || CornerLeft_flag == 1)
//            {
//                Coner_Charge = 1;
//            }
//        }
        if(LAV >= 1800)
        {
//            if(Coner_Charge == 1)
//            {
//                if(CS_flag == 1)
//                {
//                    Pre_Speed = 0;
//                    FindCharge_flag = 1;
//                    Coner_Charge = 0;
//                    CS_flag = 0;
//                }
//            }
//            else
//            {
            if(CS_flag == 1)
            {
                //Encoderlow_flag = 1;   //测停车距离
                //EncoderCharge_flag = 1;
                Pre_Speed = 0;
                FindCharge_flag = 1;
                CCC++;
                CS_flag = 0;
                //Read_AF = 0;
                //EncoderCharge_flag = 0;
            }
//            }
        }
//
//        if(AfterI_Voltage < 1130)
//        {
//            if(Real_ChDistance > distance)
//            {
//                EncoderCharge_flag = 0;
//            }
//        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      坡道速度处理
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
void RAMP_Speed(void)
{
    if(Replace_Speed >= 120)
    {
        if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 86)
        {
            if(Pre_Speed >= 86)
            {
                Pre_Speed -= 4;
                Pre_Speed = Pre_Speed < 86 ? 86 : Pre_Speed;
            }
        }
    }
    else
    {
        if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 70)
        {
            if(Pre_Speed >= 70)
            {
                Pre_Speed -= 4;
                Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      元素控速策略
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       车子因为速度环和结构原因，速度快会在转弯时跳轮
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
void Element_speedone(void)
{
    if(Element_Charge == 0 && Replace_Speed >= 120 && (SlalomLeft_flag == 1 || SlalomRight_flag == 1))
    {
        if(Pre_Speed >= 120)
        {
            Pre_Speed -= 2;
            Pre_Speed = Pre_Speed < 120 ? 120 : Pre_Speed;
        }
    }
    else if(Element_Charge == 0 && Replace_Speed >= 120 && (CircleLeft_flag == 1 || CircleRight_flag == 1))
    {
        if(Pre_Speed >= 120)
        {
            Pre_Speed -= 4;
            Pre_Speed = Pre_Speed < 120 ? 120 : Pre_Speed;
        }
    }
    RAMP_Speed();
}

void Element_speedtwo(void)
{
    if(Element_Charge == 0 && Replace_Speed >= 130 && (SlalomLeft_flag == 1 || SlalomRight_flag == 1))
    {
        if(Pre_Speed >= 130)
        {
            Pre_Speed -= 2.5;
            Pre_Speed = Pre_Speed < 130 ? 130 : Pre_Speed;
        }
    }
//    else if(Element_Charge == 0 && Replace_Speed >= 110 && (CircleLeft_flag == 1 || CircleRight_flag == 1))
//    {
//        if(Pre_Speed >= 110)
//        {
//            Pre_Speed -= 2.5;
//            Pre_Speed = Pre_Speed < 110 ? 110 : Pre_Speed;
//        }
//    }
    RAMP_Speed();
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      车子启动函数
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       重心靠后的瞬时启动会造成车子抬头，此加速启动可以抑制抬头
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
void starspeedone(void)
{
    if(Pre_Speed <= Replace_Speed && Element_Charge == 0)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
    }
    else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed >= 120)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > 120 ? 120 : Pre_Speed;
    }
    else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed < 120)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
    }
    Element_speedone();
}

void starspeedtwo(void)
{
    if(Pre_Speed <= Replace_Speed && Element_Charge == 0)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
    }
    else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed >= 120)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > 120 ? 120 : Pre_Speed;
    }
    else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed < 120)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
    }
    Element_speedtwo();
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      车子限速函数
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       电容电压的降低会是电机无法达到期望速度，可以解除pwm的限幅或者对速度限幅
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
void limitspeedone(void)
{
    if(Replace_Speed >= 90)
    {
        if(Battery_Voltage <= 4.3 &&  Battery_Voltage >= 3.3)
        {
            if(Battery_Voltage <= 4 && Pre_Speed >= 110)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 110 ? 110 : Pre_Speed;
            }
            else if(Battery_Voltage <= 4 && Pre_Speed <= 110)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 110 ? 110 : Pre_Speed;
            }
            else if(Battery_Voltage > 4.3)
            {
                starspeedone();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 3.3 &&  Battery_Voltage >= 2.5)
        {
            if(Battery_Voltage <= 3 && Pre_Speed >= 100)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage <= 3 && Pre_Speed <= 100)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage > 3.3)
            {
                starspeedone();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 2.5 && Battery_Voltage >= 1.8)
        {
            if(Battery_Voltage <= 2.3 && Pre_Speed >= 70)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
            }
            else if(Battery_Voltage <= 2.3 && Pre_Speed <= 70)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 70 ? 70 : Pre_Speed;
            }
            else if(Battery_Voltage > 2.5)
            {
                starspeedone();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 1.8)
        {
            if(Battery_Voltage <= 2 && Pre_Speed >= 25)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
            }
            else if(Battery_Voltage > 1.8)
            {
                starspeedone();
            }
//            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
//            {
//               if(Pre_Speed >= 50)
//               {
//                   Pre_Speed -= 20;
//                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
//               }
//            }
        }
//        else if(Battery_Voltage <= 3.5)
//        {
//            if(Battery_Voltage <= 3 && Pre_Speed >= 50)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 50 ? 50 : Pre_Speed;
//            }
//            else
//            {
//                starspeed();
//            }
////            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
////            {
////               if(Pre_Speed >= 50)
////               {
////                   Pre_Speed -= 20;
////                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
////               }
////            }
//        }
        else if(Battery_Voltage > 4.3)
        {
            starspeedone();
        }
    }
    else
    {
        if(Pre_Speed <= Replace_Speed)
        {
            Pre_Speed += 1;
            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
        }
        RAMP_Speed();
    }
}

void limitspeedtwo(void)
{
    if(Replace_Speed >= 90)
    {
        if(Battery_Voltage <= 4.3 &&  Battery_Voltage >= 2.3)
        {
            if(Battery_Voltage <= 4 && Pre_Speed >= 120)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 120 ? 120 : Pre_Speed;
            }
            else if(Battery_Voltage <= 4 && Pre_Speed <= 120)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 120 ? 120 : Pre_Speed;
            }
            else if(Battery_Voltage > 4.3)
            {
                starspeedtwo();
            }
            RAMP_Speed();
        }
//        if(Battery_Voltage <= 3.3 &&  Battery_Voltage >= 2.3)
//        {
//            if(Battery_Voltage <= 3 && Pre_Speed >= 100)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 100 ? 100 : Pre_Speed;
//            }
//            else if(Battery_Voltage <= 3 && Pre_Speed <= 100)
//            {
//                Pre_Speed += 1;
//                Pre_Speed = Pre_Speed > 100 ? 100 : Pre_Speed;
//            }
//            else if(Battery_Voltage > 3.3)
//            {
//                starspeedtwo();
//            }
//            RAMP_Speed();
//        }
        else if(Battery_Voltage <= 2.3 && Battery_Voltage >= 1.8)
        {
            if(Battery_Voltage <= 2 && Pre_Speed >= 100)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage <= 2 && Pre_Speed <= 100)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage > 2.3)
            {
                starspeedtwo();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 1.8)
        {
            if(Battery_Voltage <= 2 && Pre_Speed >= 25)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
            }
            else if(Battery_Voltage > 1.8)
            {
                starspeedtwo();
            }
//            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
//            {
//               if(Pre_Speed >= 50)
//               {
//                   Pre_Speed -= 20;
//                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
//               }
//            }
        }
//        else if(Battery_Voltage <= 3.5)
//        {
//            if(Battery_Voltage <= 3 && Pre_Speed >= 50)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 50 ? 50 : Pre_Speed;
//            }
//            else
//            {
//                starspeed();
//            }
////            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
////            {
////               if(Pre_Speed >= 50)
////               {
////                   Pre_Speed -= 20;
////                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
////               }
////            }
//        }
        else if(Battery_Voltage > 5.3)
        {
            starspeedtwo();
        }
    }
    else
    {
        if(Pre_Speed <= Replace_Speed)
        {
            Pre_Speed += 1;
            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
        }
        RAMP_Speed();
    }
}

void limitspeedthr(void)
{
    if(Replace_Speed >= 90)
    {
//        if(Battery_Voltage <= 5 &&  Battery_Voltage >= 4.2)
//        {
//            if(Battery_Voltage <= 4.8 && Pre_Speed >= 120)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 120 ? 120 : Pre_Speed;
//            }
//            else if(Battery_Voltage <= 4.8 && Pre_Speed <= 120)
//            {
//                Pre_Speed += 1;
//                Pre_Speed = Pre_Speed > 120 ? 120 : Pre_Speed;
//            }
//            else if(Battery_Voltage > 5)
//            {
//                starspeedone();
//            }
//            RAMP_Speed();
//        }
//        else if(Battery_Voltage <= 4.2 &&  Battery_Voltage >= 3.3)
//        {
//            if(Battery_Voltage <= 4 && Pre_Speed >= 110)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 110 ? 110 : Pre_Speed;
//            }
//            else if(Battery_Voltage <= 4 && Pre_Speed <= 110)
//            {
//                Pre_Speed += 1;
//                Pre_Speed = Pre_Speed > 110 ? 110 : Pre_Speed;
//            }
//            else if(Battery_Voltage > 4.2)
//            {
//                starspeedone();
//            }
//            RAMP_Speed();
//        }
        if(Battery_Voltage <= 3.3 &&  Battery_Voltage >= 2.5)
        {
            if(Battery_Voltage <= 3 && Pre_Speed >= 100)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage <= 3 && Pre_Speed <= 100)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage > 3.3)
            {
                starspeedone();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 2.5 && Battery_Voltage >= 1.8)
        {
            if(Battery_Voltage <= 2.3 && Pre_Speed >= 70)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
            }
            else if(Battery_Voltage <= 2.3 && Pre_Speed <= 70)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 70 ? 70 : Pre_Speed;
            }
            else if(Battery_Voltage > 2.5)
            {
                starspeedone();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 1.8)
        {
            if(Battery_Voltage <= 2 && Pre_Speed >= 25)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
            }
            else if(Battery_Voltage > 1.8)
            {
                starspeedone();
            }
//            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
//            {
//               if(Pre_Speed >= 50)
//               {
//                   Pre_Speed -= 20;
//                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
//               }
//            }
        }
//        else if(Battery_Voltage <= 3.5)
//        {
//            if(Battery_Voltage <= 3 && Pre_Speed >= 50)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 50 ? 50 : Pre_Speed;
//            }
//            else
//            {
//                starspeed();
//            }
////            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
////            {
////               if(Pre_Speed >= 50)
////               {
////                   Pre_Speed -= 20;
////                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
////               }
////            }
//        }
        else if(Battery_Voltage > 5)
        {
            starspeedone();
        }
    }
    else
    {
        if(Pre_Speed <= Replace_Speed)
        {
            Pre_Speed += 1;
            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
        }
        RAMP_Speed();
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机控制函数
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       根据状态决定此时该运行的车子状态
//  @note       Pre_Speed是我的期望速度
//-------------------------------------------------------------------------------------------------------------------
void MotorControlone(void)
{
    switch(State)
    {
        case Stop_State :   //在库
            Pre_Speed = 0;
            break;
        case Charge_State :   //充电
            if(FindCharge_flag == 0)
            {
                Decelerateone(Read_Battery_Voltage,Read_Speed);
            }
            else
            {
                Retrieval(Read_Battery_Voltage,Read_Speed);
            }
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case ChargeFinsh_State :     //充电完成起步
            //MotorTime++;
            limitspeedone();
            //LimitSpeed(Battery_Voltage);
            //Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case Run_State :           //运行
            if(Garage_Out_flag == 1 && Garage_In_flag == 0)
            {
                Garage_Out();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 0)
            {
                limitspeedone();
              //  LimitSpeed(Battery_Voltage);//26s   18
//                if(Pre_Speed < Replace_Speed)
//                {
//                    Pre_Speed += 1;
//                    Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//                }

                Motor_Direction();
                Motor_SPEEDLOOP();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 1)
            {
                Garage_In();
            }
            break;
    }
}

//电机控制集合
void MotorControltwo(void)
{
    switch(State)
    {
        case Stop_State :   //在库
            Pre_Speed = 0;
            break;
        case Charge_State :   //充电
            if(FindCharge_flag == 0)
            {
                Deceleratetwo(Read_Battery_Voltage,Read_Speed);
            }
            else
            {
                Retrieval(Read_Battery_Voltage,Read_Speed);
            }
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case ChargeFinsh_State :     //充电完成起步
            //MotorTime++;
            limitspeedtwo();
            //LimitSpeed(Battery_Voltage);
            //Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case Run_State :           //运行
            if(Garage_Out_flag == 1 && Garage_In_flag == 0)
            {
                Garage_Out();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 0)
            {
                limitspeedtwo();
              //  LimitSpeed(Battery_Voltage);//26s   18
//                if(Pre_Speed < Replace_Speed)
//                {
//                    Pre_Speed += 1;
//                    Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//                }

                Motor_Direction();
                Motor_SPEEDLOOP();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 1)
            {
                Garage_In();
            }
            break;
    }
}

//电机控制集合
void MotorControlthr(void)
{
    switch(State)
    {
        case Stop_State :   //在库
            Pre_Speed = 0;
            break;
        case Charge_State :   //充电
            if(FindCharge_flag == 0)
            {
                Deceleratetwo(Read_Battery_Voltage,Read_Speed);
            }
            else
            {
                Retrieval(Read_Battery_Voltage,Read_Speed);
            }
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case ChargeFinsh_State :     //充电完成起步
            //MotorTime++;
            limitspeedthr();
            //LimitSpeed(Battery_Voltage);
            //Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case Run_State :           //运行
            if(Garage_Out_flag == 1 && Garage_In_flag == 0)
            {
                Garage_Out();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 0)
            {
                limitspeedthr();
              //  LimitSpeed(Battery_Voltage);//26s   18
//                if(Pre_Speed < Replace_Speed)
//                {
//                    Pre_Speed += 1;
//                    Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//                }

                Motor_Direction();
                Motor_SPEEDLOOP();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 1)
            {
                Garage_In();
            }
            break;
    }
}

////再运行阶段的控速
//void SpeedControl(void)
//{
//    if(Replace_Speed >= 90 && Battery_Voltage <= 6.5 )
//    {
//        if(Battery_Voltage <= 6 && Pre_Speed >= 90)
//        {
//            Pre_Speed -= 1;
//            Pre_Speed = Pre_Speed < 90 ? 90 : Pre_Speed;
//        }
//    }
//    else if(Replace_Speed >= 90 && Battery_Voltage <= 5.5 )
//    {
//        if(Battery_Voltage <= 5 && Pre_Speed >= 80)
//        {
//            Pre_Speed -= 1;
//            Pre_Speed = Pre_Speed < 80 ? 80 : Pre_Speed;
//        }
//    }
//    else if(Replace_Speed >= 90 && Battery_Voltage <= 4.5)
//    {
//        if(Battery_Voltage <= 4 && Pre_Speed >= 60)
//        {
//            Pre_Speed -= 1;
//            Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
//        }
//    }
//    else if(Battery_Voltage > 6.5)
//    {
//        if(Pre_Speed <= Replace_Speed && Element_Charge == 0)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//        }
//        else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed >= 80)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > 80 ? 80 : Pre_Speed;
//        }
//        else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed < 80)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//        }
//        Element_speed();
//    }
//    else if(Battery_Voltage <= 6.5 && Replace_Speed < 90)
//    {
//        if(Pre_Speed <= Replace_Speed && Element_Charge == 0)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//        }
//        else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed >= 80)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > 80 ? 80 : Pre_Speed;
//        }
//        else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed < 80)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//        }
//        Element_speed();
//    }
//
//}




///*************************行偏差***************************/
//void Row_error(void)
//{
//
//}


///*******************曲率偏差************************/
////算出当前车中心的曲率得到车的转弯半径，与道路中线的角度偏差做角速度环
//void Curvature_error(void)
//{
//
//}


//PID Speed;
//
//float RealSpeed = 0;                //真实速度
//float LeftRealSpeed;
//float RighRealSpeed;
//float SpeedFilter = 0;          //阶梯滤波速度
////float ExpectSpeed = 3500;     //期望速度  3500
//float SpeedError;               //速度偏差
//float SpeedErrorTemp[5] = {0};
//float SpeedErrorInteg = 0;
//int32 Leftpulse = 0,Righpulse = 0;
//int32 LeftPWM, RighPWM;
////速度控制
//float speedControl_P = 280;     //速度P  280
//float speedControl_I = 100;     //速度I
//float SpeedControlOut = 0;      //速度输出
//
//float Distance = 0;
//float DistanceIn = 0;
//float DistanceOut = 0;
///**
// * @file        计算速度偏差
// * @note        产生全局变量g_fSpeedError
// * @date        2017
// */
//void CalSpeedError(void)
//{
//    static float SpeedOld = 0, SpeedNew = 0;
//
//    Leftpulse = ftm_count_get(ftm1);//读取左轮脉冲
//    ftm_count_clean(ftm1);
//    Righpulse = ftm_count_get(ftm0);//读取右轮脉冲
//    ftm_count_clean(ftm0);
//
//    if (gpio_get(ENCODER_DIRL) == 0)
//        Leftpulse = -Leftpulse;
//    if (gpio_get(ENCODER_DIRR) == 1)
//        Righpulse = -Righpulse;
//
//
//    DistanceIn+= (Leftpulse + Righpulse) / (2 * 5772.0f);
//    DistanceOut+= (Leftpulse + Righpulse) / (2 * 5772.0f);
//    Distance+= (Leftpulse + Righpulse) / (2 * 5772.0f);
//
//    LeftRealSpeed = Leftpulse * 207/(1175*0.02);
//    LeftRealSpeed = (LeftRealSpeed>4000?4000:LeftRealSpeed);        //滤左编码器的噪声
//    RighRealSpeed = Righpulse * 207/(1175*0.02);
//    RighRealSpeed = (RighRealSpeed>4000?4000:RighRealSpeed);        //滤右编码器的噪声
//
//    RealSpeed = (LeftRealSpeed + RighRealSpeed) / 2;                //真实速度
//
//    //速度采集梯度平滑，每次采集最大变化200
//    SpeedOld = SpeedFilter;
//    SpeedNew = RealSpeed;
//
//    if(SpeedNew>=SpeedOld)
//       SpeedFilter = ((SpeedNew-SpeedOld)>300?(SpeedOld+300):SpeedNew);
//    else
//       SpeedFilter = ((SpeedNew-SpeedOld)<-300?(SpeedOld-300):SpeedNew);
//
//    //flash中参数
////  g_fExpectSpeed = float05;  //2800
//
//    SpeedError =  ExpectSpeed - SpeedFilter;
//    SpeedErrorTemp[4] = SpeedErrorTemp[3];
//    SpeedErrorTemp[3] = SpeedErrorTemp[2];
//    SpeedErrorTemp[2] = SpeedErrorTemp[1];
//    SpeedErrorTemp[1] = SpeedErrorTemp[0];
//    SpeedErrorTemp[0] = SpeedError;
//
//}
//
//
///**
// * @file        速度控制
// * @note        速度梯度平滑
// * @date        2017
// */
//void SpeedControl(void)
//{
//        Speed.KP = speedControl_P;
//        Speed.KI = speedControl_I;
//
//    int8 index=1;
//
//    CalSpeedError();    //计算速度偏差
//    SpeedError = (SpeedError>800?800:SpeedError);//速度偏差限幅
//
////        SpeedError = LIMIT_MAX(SpeedError, 800);
//
//
//    //积分分离
//    if((SpeedError<=300)&&(SpeedError>=-300))
//    index=1;
//    else
//    index=0;
//    SpeedErrorInteg = index * 0 * SpeedError * 0.00001;
//
///*  if(Flag_Stop == OFF||Flag_Speed == OFF)
//    {
//        SpeedErrorInteg = 0;    //停车积分清零
//    }
//*/
//    //SpeedErrorInteg = (SpeedErrorInteg < 0.0? 0.0: SpeedErrorInteg);//积分下限
//    //SpeedErrorInteg = (SpeedErrorInteg > 400.0? 400.0: SpeedErrorInteg);//积分上限
//    //速度控制算法（增量式PI）
//    Speed.Out += Speed.KP *0.005*(SpeedErrorTemp[0]-SpeedErrorTemp[1]) + SpeedErrorInteg;
////        Speed.Out += Speed.KP *0.005*(SpeedErrorTemp[0]-SpeedErrorTemp[1]);
//
//        Speed.Out = LIMIT_MAX(Speed.Out, 6000);
//}




