/*
 * All_Config.c
 *
 *  Created on: 2021年11月12日
 *      Author: YYM
 */

//各类初始化
#include "All_Config.h"


void All_Config_CPU0(void)
{
    //uart_init(UART);  //串口初始化
    Wireless_Init();      //无线串口初始化
    Charge_Init();
    Encoder_Init();
    Gyroscope_Init();
    Camera_Init();
    Motor_Init();
    LED_Init();
    //Display_Init();
    systick_delay_ms(STM0, 1000);  //上电
    /****************中断*******************/

//    eru_init(ERU_CH0_REQ0_P15_4, RISING);  //外部GPIO中断检测是否达到线圈CPU0
//    gpio_init(P15_4, GPI, 0, PULLDOWN);     //下拉
    pit_interrupt_ms(CCU6_0, PIT_CH1, 8);    //陀螺仪
    pit_interrupt_ms(CCU6_0, PIT_CH0, 1);     //灯板
    pit_interrupt_ms(CCU6_1, PIT_CH1, 3);    //电容电压ADC采集中断CPU0
    pit_interrupt_ms(CCU6_1, PIT_CH0, 10);   //电机中断CPU0


}

//void All_Config_CPU1(void)
//{
//    ips200_init();          //IPS显示屏初始化
//    ips200_clear(WHITE);
//
//    mt9v03x_init();        //摄像头初始化
//
//    systick_delay_ms(STM0, 1000);  //上电
//    /****************中断*******************/
//    pit_init(CCU6_1, PIT_CH1, 10000);   //摄像头
//
//}
