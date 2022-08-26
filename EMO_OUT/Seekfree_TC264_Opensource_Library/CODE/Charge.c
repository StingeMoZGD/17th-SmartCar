/*
 * State.c
 *
 *  Created on: 2021年12月20日
 *      Author: YYM
 */
#include "Charge.h"



volatile unsigned char State = 0;
unsigned char ChargeFinish_flag = 0;  //离开充电点，并表示在1.5秒内不在找寻充电点
unsigned char Element_Charge = 0;     //元素充电点 ,需要降低期望速度，以保证能够顺利通过元素
unsigned char Coner_Charge = 0;       //弯道充电点，需要提高一些编码器距离
float Battery_Voltage = 0;
const float Full_Voltage = 12.0;
float Run_Voltage = 10.5;
const float Garage_Out_Voltage = 12.3;
float Last_Battery_Voltage = 0;
float Display_Battery_Voltage = 0;
uint16 LAV = 0;
uint16 AfterI_Voltage = 0;
uint16 Read_AF = 0;
int StateTime = 0;
unsigned char Garge_nocharge = 0; //在出库或者进行车库程序时不进行充电判断: 0:不可以充电 1:可以充电


void Charge_Init(void)
{
    adc_init(C_Module, C_Pin);   //电容电压ADC初始化
    //adc_init(I_Module, FI_Pin);   //电感ADC初始化
    adc_init(I_Module, AI_Pin);   //电感ADC初始化
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      电容电压采集
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Capacitance_Voltage_Get(void)
{
    //Last_Battery_Voltage = Battery_Voltage;
    Battery_Voltage = ((float)adc_mean_filter(C_Module, C_Pin, ADC_12BIT, 10) / 4096.0)*3.28*34.1;  //电容电压ADC采集
//    if(Battery_Voltage - Last_Battery_Voltage > 0.2)
//    {
//        Display_Battery_Voltage = Battery_Voltage;
//    }
//    else
//    {
//        Display_Battery_Voltage = Last_Battery_Voltage;
//    }
//    Battery_Voltage = 9;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      电感采集
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       用于定位充电线圈
//-------------------------------------------------------------------------------------------------------------------
void Inductance_Get(void)
{
    if(State == Charge_State  || AfterI_Voltage >= 179)
    {
        LAV = AfterI_Voltage;
    }
    else
    {
        LAV = 0;
    }
    //FormerI_Voltage = adc_mean_filter(I_Module, FI_Pin, ADC_12BIT, 6);  //前电感ADC采集
    AfterI_Voltage = adc_mean_filter(I_Module, AI_Pin, ADC_12BIT, 10);   //后电感ADC采集
    if(State == Charge_State && FindCharge_flag == 0)  //Emo_Uint16(AfterI_Voltage,LAV) >= 1 && AfterI_Voltage >= Dec && State == Run_State && ChargeFinish_flag == 0 && Garge_nocharge == 1 && (Element_Charge == 0 || Battery_Voltage <= 10)
    {
        if(Read_Battery_Voltage < end_Bat)
        {
            if(LAV >= 1800)
            {
                    if(Emo_Uint16(AfterI_Voltage,LAV) <= -7)
                    {
                        CS_flag = 1;
                    }
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      车辆运行状态更新函数
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       根据是否在库、充电、离开线圈、正常跑车进行更换状态，状态体现在电机控制中
//-------------------------------------------------------------------------------------------------------------------
static float Last_Voltage = 0;
static float New_Voltage = 0;
//static unsigned char Detection_Hover = 0; //检测悬停
void State_Update(void)
{
    if(State == Stop_State)     //在库
    {
        if(Battery_Voltage >= Garage_Out_Voltage)
        {
            State = Run_State;    //出库
        }
    }

    if(State == Charge_State)  //充电
    {
        //Encoder_Summation();
//        if(AfterI_Voltage >= AIN)    //减速差不多了，转为充电状态
//        {
//            StateTime = 0;
//            State = Charge_State;
//            FindCharge_flag = 1;
//            EncoderCharge_flag = 1;
//            Last_Voltage = Battery_Voltage;
//            Read_Battery_Voltage = Battery_Voltage;
//            Read_Speed = (float)CoderSpeed;
//        }
        if(Read_Battery_Voltage < end_Bat && Element_Charge == 0 && (SlalomLeft_flag == 1 || SlalomRight_flag == 1 || CircleLeft_flag == 1 || CircleRight_flag == 1))
        {
            Element_Charge = 1;
        }
        if(GarageR_flag == 1 || GarageL_flag == 1)
        {
            FindCharge_flag = 0;
            State = Run_State;
            Garge_nocharge = 0;
            CoderGaSumONE = 0;
            CoderGaSumTWO = 0;
            Real_GaDistance = 0;
            Encoderlow_flag = 0;
            EncoderCharge_flag = 0;
            CS_flag = 0;
        }
        if(AfterI_Voltage < (Dec-15))
        {
            FindCharge_flag = 0;
            EncoderCharge_flag = 0;
            State = Run_State;
            Encoderlow_flag = 0;
            Read_Battery_Voltage_flag = 0;
            CS_flag = 0;
        }
//        if(AfterI_Voltage >= AMAX && Real_ChDistance >= 1600)
//        {
//            FindCharge_flag = 1;
//            EncoderCharge_flag = 0;
////            EncoderCharge_flag = 1;
//            Last_Voltage = Battery_Voltage;
//        }
        if(FindCharge_flag == 1)
        {
            if(StateTime == 0)
            {
                Last_Voltage = Battery_Voltage;
            }
            StateTime++;

        }
//        if(AfterI_Voltage < AIN-200)
//        {
//            State = ChargeFinsh_State;    //充电完成
//            Last_Voltage = 0;
//            New_Voltage = 0;
//            StateTime = 0;
//        }
        if(StateTime % 333 == 0)    //一秒后判断是否在充电
        {
            New_Voltage = Battery_Voltage;
            if(New_Voltage - Last_Voltage >= 0.6)
            {
                StateTime = 0;
                Last_Voltage = Battery_Voltage;
            }
            else
            {
                Last_Voltage = Battery_Voltage;
            }
        }
        if(StateTime >= 1000)           //防止一直卡在充电
        {
            FindCharge_flag = 0;
            EncoderCharge_flag = 0;
            State = ChargeFinsh_State;    //充电完成
            Encoderlow_flag = 0;
            Last_Voltage = 0;
            New_Voltage = 0;
            StateTime = 0;
            CS_flag = 0;
        }
        if(Battery_Voltage >= Run_Voltage)
        {
            EncoderCharge_flag = 0;
            State = ChargeFinsh_State;    //充电完成
            Encoderlow_flag = 0;
            FindCharge_flag = 0;
            Last_Voltage = 0;
            New_Voltage = 0;
            StateTime = 0;
            CS_flag = 0;
        }
    }
    if(State == ChargeFinsh_State)        //离开线圈
    {
        if(Read_Battery_Voltage < end_Bat && Element_Charge == 0 && (SlalomLeft_flag == 1 || SlalomRight_flag == 1 || CircleLeft_flag == 1 || CircleRight_flag == 1))
        {
            Element_Charge = 1;
        }
        if(AfterI_Voltage < (Dec - 9))
        {
            //EncoderCharge_flag = 0;
            FindCharge_flag = 0;
            State = Run_State;               //运行
            //MotorTime = 0;
            //Pre_Speed = (float)Replace_Speed;
            ChargeFinish_flag = 1;
        }
    }
//    if(Garage_Out_Finsh_flag == 1)
//    {
//        EncoderGa_flag = 1;
//        if(Real_GaDistance >= 13000)
//        {
//            Garge_nocharge = 1;
//            EncoderGa_flag = 0;
//            Garage_Out_Finsh_flag = 0;
//        }
//    }
    if(Garge_nocharge == 0)
    {
        EncoderGa_flag = 1;
        if(Real_GaDistance >= 13000)
        {
            Garge_nocharge = 1;
            EncoderGa_flag = 0;
        }
    }
//    if(GarageR_flag ==  1 || GarageL_flag == 1)
//    {
//        EncoderGa_flag = 1;
//        if(Real_GaDistance >= 13000)
//        {
//            Garge_nocharge = 1;
//            EncoderGa_flag = 0;
//            Garage_Out_Finsh_flag = 0;
//        }
//    }
//    if(State == ChargePrepare_State)
//    {
//        StateTime++;
//        if(StateTime > 30)   //出现此种情况则说明充电点有问题，转为充电完成状态起步
//        {
//            Detection_Hover = 1;
//            StateTime = 0;
//            State = Run_State;
//        }
//        if(AfterI_Voltage >= AIN)    //减速差不多了，转为充电状态
//        {
//            StateTime = 0;
//            State = Charge_State;
//            FindCharge_flag = 1;
//            Last_Voltage = Battery_Voltage;
//            Read_Battery_Voltage = Battery_Voltage;
//            Read_Speed = (float)CoderSpeed;
//        }
//    }
    if(ChargeFinish_flag == 1)
    {
        StateTime++;
        if(AfterI_Voltage > Dec)
        {
            StateTime = 0;
        }
//        if(AfterI_Voltage > 500)
//        {
//            State = Charge_State;
//        }
        if(StateTime > 5)   //离开线圈后0.015秒不再检测线圈
        {
            Read_Battery_Voltage_flag = 0;
            //FindCharge_flag = 0;
            ChargeFinish_flag = 0;
            StateTime = 0;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      检测到充电线圈
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Coil_Detect(void)                 //检测线圈
{
    if(State == ChargeFinsh_State)           //充电完成则不再停留充电
    {
        State = ChargeFinsh_State;
    }
    else if(State == Charge_State)
    {
        State = Charge_State;
    }
    else
    {
        State = Charge_State;               //遇到线圈，减速
        EncoderCharge_flag = 1;
        if(Read_Battery_Voltage < end_Bat && Element_Charge == 0 && (SlalomLeft_flag == 1 || SlalomRight_flag == 1 || CircleLeft_flag == 1 || CircleRight_flag == 1))
        {
            Element_Charge = 1;
        }
//        if(CornerRight_flag == 1 || CornerLeft_flag == 1)
//        {
//            Coner_Charge = 1;
//        }
//        if(Pre_Speed >= 85)
//        {
//            Pre_Speed  = 85;
//        }
        if(Read_Battery_Voltage_flag == 0)
        {
            //Read_AF = AfterI_Voltage - Dec;
            Read_Battery_Voltage_flag = 1;
            Read_Battery_Voltage = Battery_Voltage;
            Read_Speed = (float)CoderSpeed;
        }
    }
}

