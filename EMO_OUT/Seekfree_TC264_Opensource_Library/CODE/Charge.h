
/*
 * Charge.h
 *
 *  Created on: 2021��12��20��
 *      Author: YYM
 */

#ifndef CODE_CHARGE_H_
#define CODE_CHARGE_H_

#include "headfile.h"

#define Stop_State  0      //��
#define Charge_State  1    //���
#define ChargeFinsh_State 2   //��������
#define Run_State  3          //����
#define Garage_Out_State  4   //����
#define Garage_In_State 5     //���
#define ChargePrepare_State  6 //�ҵ����㣬δ�ܵ���ѳ��λ��


#define C_Module   ADC_0
#define C_Pin      ADC0_CH6_A6
#define I_Module   ADC_0
#define FI_Pin     ADC0_CH5_A5
#define AI_Pin     ADC0_CH3_A3

/*************��������***********/
extern volatile unsigned char State;
extern float Battery_Voltage,Display_Battery_Voltage,Run_Voltage;
extern uint16 LAV,AfterI_Voltage,Read_AF;
extern int StateTime;
extern unsigned char ChargeFinish_flag,Garge_nocharge,Element_Charge,Coner_Charge;

void Charge_Init(void);
void Capacitance_Voltage_Get(void);
void Inductance_Get(void);
void State_Update(void);
void Coil_Detect(void);

#endif /* CODE_CHARGE_H_ */
