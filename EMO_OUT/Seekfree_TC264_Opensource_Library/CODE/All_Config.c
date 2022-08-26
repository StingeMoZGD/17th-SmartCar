/*
 * All_Config.c
 *
 *  Created on: 2021��11��12��
 *      Author: YYM
 */

//�����ʼ��
#include "All_Config.h"


void All_Config_CPU0(void)
{
    //uart_init(UART);  //���ڳ�ʼ��
    Wireless_Init();      //���ߴ��ڳ�ʼ��
    Charge_Init();
    Encoder_Init();
    Gyroscope_Init();
    Camera_Init();
    Motor_Init();
    LED_Init();
    //Display_Init();
    systick_delay_ms(STM0, 1000);  //�ϵ�
    /****************�ж�*******************/

//    eru_init(ERU_CH0_REQ0_P15_4, RISING);  //�ⲿGPIO�жϼ���Ƿ�ﵽ��ȦCPU0
//    gpio_init(P15_4, GPI, 0, PULLDOWN);     //����
    pit_interrupt_ms(CCU6_0, PIT_CH1, 8);    //������
    pit_interrupt_ms(CCU6_0, PIT_CH0, 1);     //�ư�
    pit_interrupt_ms(CCU6_1, PIT_CH1, 3);    //���ݵ�ѹADC�ɼ��ж�CPU0
    pit_interrupt_ms(CCU6_1, PIT_CH0, 10);   //����ж�CPU0


}

//void All_Config_CPU1(void)
//{
//    ips200_init();          //IPS��ʾ����ʼ��
//    ips200_clear(WHITE);
//
//    mt9v03x_init();        //����ͷ��ʼ��
//
//    systick_delay_ms(STM0, 1000);  //�ϵ�
//    /****************�ж�*******************/
//    pit_init(CCU6_1, PIT_CH1, 10000);   //����ͷ
//
//}
