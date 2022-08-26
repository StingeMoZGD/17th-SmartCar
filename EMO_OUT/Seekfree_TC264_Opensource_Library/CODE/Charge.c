/*
 * State.c
 *
 *  Created on: 2021��12��20��
 *      Author: YYM
 */
#include "Charge.h"



volatile unsigned char State = 0;
unsigned char ChargeFinish_flag = 0;  //�뿪���㣬����ʾ��1.5���ڲ�����Ѱ����
unsigned char Element_Charge = 0;     //Ԫ�س��� ,��Ҫ���������ٶȣ��Ա�֤�ܹ�˳��ͨ��Ԫ��
unsigned char Coner_Charge = 0;       //������㣬��Ҫ���һЩ����������
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
unsigned char Garge_nocharge = 0; //�ڳ�����߽��г������ʱ�����г���ж�: 0:�����Գ�� 1:���Գ��


void Charge_Init(void)
{
    adc_init(C_Module, C_Pin);   //���ݵ�ѹADC��ʼ��
    //adc_init(I_Module, FI_Pin);   //���ADC��ʼ��
    adc_init(I_Module, AI_Pin);   //���ADC��ʼ��
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ݵ�ѹ�ɼ�
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
    Battery_Voltage = ((float)adc_mean_filter(C_Module, C_Pin, ADC_12BIT, 10) / 4096.0)*3.28*34.1;  //���ݵ�ѹADC�ɼ�
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
//  @brief      ��вɼ�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ���ڶ�λ�����Ȧ
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
    //FormerI_Voltage = adc_mean_filter(I_Module, FI_Pin, ADC_12BIT, 6);  //ǰ���ADC�ɼ�
    AfterI_Voltage = adc_mean_filter(I_Module, AI_Pin, ADC_12BIT, 10);   //����ADC�ɼ�
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
//  @brief      ��������״̬���º���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       �����Ƿ��ڿ⡢��硢�뿪��Ȧ�������ܳ����и���״̬��״̬�����ڵ��������
//-------------------------------------------------------------------------------------------------------------------
static float Last_Voltage = 0;
static float New_Voltage = 0;
//static unsigned char Detection_Hover = 0; //�����ͣ
void State_Update(void)
{
    if(State == Stop_State)     //�ڿ�
    {
        if(Battery_Voltage >= Garage_Out_Voltage)
        {
            State = Run_State;    //����
        }
    }

    if(State == Charge_State)  //���
    {
        //Encoder_Summation();
//        if(AfterI_Voltage >= AIN)    //���ٲ���ˣ�תΪ���״̬
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
//            State = ChargeFinsh_State;    //������
//            Last_Voltage = 0;
//            New_Voltage = 0;
//            StateTime = 0;
//        }
        if(StateTime % 333 == 0)    //һ����ж��Ƿ��ڳ��
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
        if(StateTime >= 1000)           //��ֹһֱ���ڳ��
        {
            FindCharge_flag = 0;
            EncoderCharge_flag = 0;
            State = ChargeFinsh_State;    //������
            Encoderlow_flag = 0;
            Last_Voltage = 0;
            New_Voltage = 0;
            StateTime = 0;
            CS_flag = 0;
        }
        if(Battery_Voltage >= Run_Voltage)
        {
            EncoderCharge_flag = 0;
            State = ChargeFinsh_State;    //������
            Encoderlow_flag = 0;
            FindCharge_flag = 0;
            Last_Voltage = 0;
            New_Voltage = 0;
            StateTime = 0;
            CS_flag = 0;
        }
    }
    if(State == ChargeFinsh_State)        //�뿪��Ȧ
    {
        if(Read_Battery_Voltage < end_Bat && Element_Charge == 0 && (SlalomLeft_flag == 1 || SlalomRight_flag == 1 || CircleLeft_flag == 1 || CircleRight_flag == 1))
        {
            Element_Charge = 1;
        }
        if(AfterI_Voltage < (Dec - 9))
        {
            //EncoderCharge_flag = 0;
            FindCharge_flag = 0;
            State = Run_State;               //����
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
//        if(StateTime > 30)   //���ִ��������˵�����������⣬תΪ������״̬��
//        {
//            Detection_Hover = 1;
//            StateTime = 0;
//            State = Run_State;
//        }
//        if(AfterI_Voltage >= AIN)    //���ٲ���ˣ�תΪ���״̬
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
        if(StateTime > 5)   //�뿪��Ȧ��0.015�벻�ټ����Ȧ
        {
            Read_Battery_Voltage_flag = 0;
            //FindCharge_flag = 0;
            ChargeFinish_flag = 0;
            StateTime = 0;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��⵽�����Ȧ
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Coil_Detect(void)                 //�����Ȧ
{
    if(State == ChargeFinsh_State)           //����������ͣ�����
    {
        State = ChargeFinsh_State;
    }
    else if(State == Charge_State)
    {
        State = Charge_State;
    }
    else
    {
        State = Charge_State;               //������Ȧ������
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

