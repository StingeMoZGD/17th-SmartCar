/*
 * Gyroscope.c
 *
 *  Created on: 2022年1月8日
 *      Author: YYM
 */

#include "Gyroscope.h"

int16 Emo_gyro_z = 0,Normal_gyro_z = 0,Emo_gyro_y = 0;
float Emo_LastAngleSpeed = 0,Emo_AngleSpeed = 0,Emo_Angle = 0;
float Emo_Pitch = 0,Emo_PitchSpeed = 0,Emo_LastPitchSpeed = 0;
float dt=0.008;
float Emo_Angle_Max =  360;
float Emo_Angle_Min = -360;
float Emo_AngleSpeed_Max = 500;
float Emo_AngleSpeed_Min = -500;
float AngleSpeed = 0;
int GyroscopeTime = 0;
int test = 0;
int test_sum = 0;
volatile unsigned char Gyroscope_Star_flag = 0;  //启动计算陀螺仪的角度用来判断元素进行情况
volatile unsigned char GyroscopePitch_Star_flag = 0;  //启动计算陀螺仪的角度用来判断元素进行情况

//陀螺仪初始化
void Gyroscope_Init(void)
{
    icm20602_init_spi();
}

void Gyroscope_Time_Star(void)
{
    GyroscopeTime++;
}

void Gyroscope_Time_Clear(void)
{
    GyroscopeTime = 0;
}
void Gyroscope_GetData(void)
{
    //get_icm20602_accdata_spi();
    get_icm20602_gyro_spi();
    gyro_z = icm_gyro_z;
    //test += gyro_z;
    AngleSpeed = ((gyro_z-ZeroDrift_gyro_z) * GYRO_SENS)*dt;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      陀螺仪计算航偏角角度
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note   一阶线性滤波角速度积分得到偏航角
//-------------------------------------------------------------------------------------------------------------------
void Get_Gyroscope_Angle(void)
{
    float K=0.7;
//    get_icm20602_gyro_spi();
    //Gyroscope_Time_Star();
    Emo_gyro_z = icm_gyro_z;
    Emo_LastAngleSpeed=Emo_AngleSpeed;
    Emo_AngleSpeed += ((Emo_gyro_z-ZeroDrift_gyro_z) * GYRO_SENS)*dt;
    Emo_Angle = Emo_AngleSpeed*K+Emo_LastAngleSpeed*(1-K);                //向左为正
    Emo_Angle = Emo_Angle > Emo_Angle_Max ? Emo_Angle_Max : Emo_Angle;
    Emo_Angle = Emo_Angle < Emo_Angle_Min ? Emo_Angle_Min : Emo_Angle;
    Emo_Angle = -Emo_Angle;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      陀螺仪计算俯仰角角度
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note   一阶线性滤波角速度积分得到俯仰角，用于判断坡道
//-------------------------------------------------------------------------------------------------------------------
void Get_Gyroscope_Pitch(void)
{
    float K=0.7;
    Emo_LastPitchSpeed=Emo_PitchSpeed;
    Emo_gyro_y = icm_gyro_y;
    Emo_PitchSpeed += ((Emo_gyro_y-ZeroDrift_gyro_y) * GYRO_SENS)*dt;
    Emo_Pitch = Emo_PitchSpeed*K+Emo_LastPitchSpeed*(1-K);                //向左为正
    Emo_Pitch = Emo_Pitch > 40 ? 40 : Emo_Pitch;
    Emo_Pitch = Emo_Pitch < (-40) ? (-40) : Emo_Pitch;
    if(Emo_Pitch <= -5.7)
    {
        Ramp_flag = 1;
    }
    if(Ramp_flag == 1 && Emo_Pitch >= 2)
    {
        Ramp_flag = 0;
        GyroscopePitch_Star_flag = 0;
        RampReady_flag = 1;
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      俯仰角角度清算
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Clear_Gyroscope_Pitch(void)
{
    Emo_PitchSpeed = 0;
    Emo_Pitch = 0;
    Emo_LastPitchSpeed = 0;
    Emo_gyro_y = 0;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      偏航角角度清算
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Clear_Gyroscope_Angle(void)
{
    Emo_LastAngleSpeed = 0;
    Emo_AngleSpeed = 0;
    Emo_gyro_z = 0;
    Emo_Angle = 0;
    Gyroscope_Time_Clear();
}
