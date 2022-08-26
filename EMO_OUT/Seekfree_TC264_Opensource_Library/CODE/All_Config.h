/*
 * All_Config.h
 *
 *  Created on: 2021年11月12日
 *      Author: YYM
 */

#ifndef CODE_ALL_CONFIG_H_
#define CODE_ALL_CONFIG_H_

#include "headfile.h"
/********************define*****************/
//#define UART UART_1, 115200, UART1_TX_P02_2, UART1_RX_P02_3  //串口

#define EncoderONE GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6  //编码器
#define EncoderTWO GPT12_T6, GPT12_T6INA_P20_3 ,GPT12_T6EUDA_P20_0

#define PWMONE ATOM0_CH1_P21_3, 15000, 0  //电机PWM
#define PWMone ATOM0_CH0_P21_2, 15000, 0
#define PWMTWO ATOM0_CH3_P21_5, 15000, 0
#define PWMtwo ATOM0_CH2_P21_4, 15000, 0

//#define Steer ATOM0_CH1_P33_9,50,0  //舵机PWM



/*********************void********************/
void All_Config_CPU0(void);

void All_Config_CPU1(void);


#endif /* CODE_ALL_CONFIG_H_ */
