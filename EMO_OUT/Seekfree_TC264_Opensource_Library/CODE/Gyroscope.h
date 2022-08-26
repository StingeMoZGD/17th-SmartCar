/*
 * Gyroscope.h
 *
 *  Created on: 2022年1月8日
 *      Author: YYM
 */

#ifndef CODE_GYROSCOPE_H_
#define CODE_GYROSCOPE_H_

#include "headfile.h"

        //修正零偏量
#define ZeroDrift_gyro_x               0
#define ZeroDrift_gyro_y              13
#define ZeroDrift_gyro_z               4

#define ZeroDrift_acc_x               73
#define ZeroDrift_acc_y               22
#define ZeroDrift_acc_z               4063

/* 灵敏度 */
#define    GYRO_SENS             1/16.4
#define    ACCE_SENS             90.0/4096

/**********申明变量*************/
extern float Emo_LastAngleSpeed,
             Emo_AngleSpeed,
             Emo_Angle,dt,
             Emo_Angle_Max,
             Emo_Angle_Min,
             Emo_AngleSpeed_Max,
             Emo_AngleSpeed_Min,
             AngleSpeed,
             Emo_Pitch,
             Emo_LastPitchSpeed,
             Emo_PitchSpeed;
extern int16 Emo_gyro_z,Normal_gyro_z,Emo_gyro_y;
extern volatile unsigned char Gyroscope_Star_flag,GyroscopePitch_Star_flag;
extern int GyroscopeTime,test,test_sum;

void Gyroscope_Init(void);
void Gyroscope_GetData(void);
void Get_Gyroscope_Angle(void);
void Gyroscope_Time_Star(void);
void Gyroscope_Time_Clear(void);
void Clear_Gyroscope_Angle(void);
void Get_Gyroscope_Pitch(void);
void Clear_Gyroscope_Pitch(void);

#endif /* CODE_GYROSCOPE_H_ */
