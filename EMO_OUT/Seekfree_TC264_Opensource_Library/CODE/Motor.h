/*
 * Motor.h
 *
 *  Created on: 2021年11月12日
 *      Author: YYM
 */

#ifndef CODE_MOTOR_H_
#define CODE_MOTOR_H_

#include "headfile.h"



/*******************宏定义**********************/

#define ONE ATOM0_CH0_P21_2
#define one ATOM0_CH1_P21_3
#define TWO ATOM0_CH2_P21_4
#define two ATOM0_CH3_P21_5

#define Stop_State  0      //库
#define Charge_State  1    //充电
#define ChargeFinsh_State 2   //充电完成
#define Run_State  3          //运行

//#define Dec  250
//#define AMAX  3790
//#define distance 1600      //检测距离
//#define Predistance 300     //制动距离


/*****************申明变量****************/
extern int MotorONE,
           MotorTWO,
           MotorTime;
extern float Pre_Speed,
             Exp_SpeedTWO,
             Exp_SpeedONE,
             Dircetion_Standard,
             Read_Battery_Voltage,
             Read_Speed;
extern float V;
extern int16 dirONE,
             dirTWO;
extern const uint16 Dec,
                    AMAX;
extern const int distance,Predistance;
extern unsigned char Crash_Out,Garage_Out_flag,Garage_In_flag,Garage_Dir,Garage_Out_Finsh_flag,
                     Auxiliary_CorneringLeft_flag,Auxiliary_CorneringRight_flag,FindCharge_flag,Read_Battery_Voltage_flag
                     ,GarageL_In_flag,GarageR_In_flag,Speed_Ready,need_cornerL,need_cornerR,CS_flag,CCC;
extern float end_Bat;

void Motor_Init(void);
void Motor_Direction(void);
void Motor_SPEEDLOOP(void);
void MotorControlone(void);
void MotorControltwo(void);
void MotorControlthr(void);
void limitspeedone(void);
void limitspeedtwo(void);
int Emo_Uint16(uint16 a,uint16 b);

#endif /* CODE_MOTOR_H_ */
