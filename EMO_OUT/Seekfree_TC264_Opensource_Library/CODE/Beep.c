/*
 * Beep.c
 *
 *  Created on: 2022��2��5��
 *      Author: YYM
 */
//������
#include "Beep.h"

uint8 Beepindex = 0;
int BeepTime = 0;

void Beep_Init(void)
{
    gpio_init(Beep_Pin, GPO, 0, PUSHPULL);
}

void Beep_ON(void)
{
    gpio_set(Beep_Pin, 1);
}


void Beep_OFF(void)
{
    gpio_set(Beep_Pin, 0);
}

//0.2����
void Beep_onepoint(void)
{
    BeepTime++;
    if(BeepTime % 50 == 0)
    {
        Beep_ON();
        BeepTime = 0;
    }
    else
    {
        Beep_OFF();
    }
}

//���0.5��˫���
void Beep_twopoint(void)
{
    BeepTime++;
    if(BeepTime <= 10)
    {
        Beep_ON();
    }
    else if(BeepTime > 10 && BeepTime <= 20)
    {
        Beep_OFF();
    }
    else if(BeepTime > 20 && BeepTime <= 30)
    {
        Beep_ON();
    }
    else if(BeepTime > 30 && BeepTime <= 80)
    {
        Beep_OFF();
    }
    else
    {
        BeepTime = 0;
    }
}

//���0.5������
void Beep_threepoint(void)
{
    BeepTime++;
    if(BeepTime <= 10)
    {
        Beep_ON();
    }
    else if(BeepTime > 10 && BeepTime <= 20)
    {
        Beep_OFF();
    }
    else if(BeepTime > 20 && BeepTime <= 30)
    {
        Beep_ON();
    }
    else if(BeepTime > 30 && BeepTime <= 40)
    {
        Beep_OFF();
    }
    else if(BeepTime > 40 && BeepTime <= 50)
    {
        Beep_ON();
    }
    else if(BeepTime > 50 && BeepTime <= 60)
    {
        Beep_OFF();
    }
    else if(BeepTime > 60 && BeepTime <= 70)
    {
        Beep_ON();
    }
    else if(BeepTime > 70 && BeepTime <= 120)
    {
        Beep_OFF();
    }
    else
    {
        BeepTime = 0;
    }
}

//������ִ�к�������ϸ�������ָ�����ִ��
void Beep_Customize(void)
{
    switch(Beepindex)
    {
        case 0 :
            Beep_OFF();
            BeepTime = 0;
            break;
        case BeepCircle :
            Beep_onepoint();
            break;
        case BeepSlalom :
            Beep_twopoint();
            break;
        case BeepThreefork :
            Beep_threepoint();
            break;
        case Beepon :
            Beep_ON();
            break;
    }
}
