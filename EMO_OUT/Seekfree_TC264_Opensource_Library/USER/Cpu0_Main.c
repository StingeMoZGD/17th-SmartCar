/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#pragma section all "cpu0_dsram"
//���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��


//���̵��뵽����֮��Ӧ��ѡ�й���Ȼ����refreshˢ��һ��֮���ٱ���
//����Ĭ������Ϊ�ر��Ż��������Լ��һ�����ѡ��properties->C/C++ Build->Setting
//Ȼ�����Ҳ�Ĵ������ҵ�C/C++ Compiler->Optimization->Optimization level�������Ż��ȼ�
//һ��Ĭ���½����Ĺ��̶���Ĭ�Ͽ�2���Ż�����˴��Ҳ��������Ϊ2���Ż�
//����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ��enableInterrupts();�������ж�Ƕ��
//�򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ�������disableInterrupts();���ܾ���Ӧ�κε��жϣ������Ҫ�����Լ��ֶ�����enableInterrupts();�������жϵ���Ӧ��
int core0_main(void)
{
	get_clk();//��ȡʱ��Ƶ��  ��ر���
	//�û��ڴ˴����ø��ֳ�ʼ��������

	DIP_Switch_Init();   //��ɨ�貦�뿪��
	Keystroke_Init();    //��ʼ������
	Display_Init();      //��ʼ��IPS
	Beep_Init();         //��ʼ��������
	//gpio_init(P10_2, GPO, 0, PUSHPULL);
	//EEPROM_Default();

	while(1)     //�˵�ϵͳ
	{
	    DIP_Switch_Contorl();
	    switch(MODE)
	    {
	        case 0:
	            Garage_Out_flag = 0;
	            Keystroke_Menu();
	            break;
	        case 1:
	            RUN_STAR = 1;
	            break;
	        case 2:
	            RUN_STAR = 1;
	            break;
	        case 3:
	            RUN_STAR = 1;
	            break;
	    }
	    if(RUN_STAR == 1)
	    {
	        ips200_clear(WHITE);
	        EEPROM_FLASH();
	        if(MODE == 2)
	        {
	            Run_Voltage = 10.7;
	        }
	        else if(MODE == 3)
	        {
                Run_Voltage = 11;
	        }
	        break;
	    }
	}

	All_Config_CPU0();    //����ģ���ʼ��
	//gpio_init(P33_4, GPO, 0, PUSHPULL);   //����ͷִ��ʱ���������

    //�ȴ����к��ĳ�ʼ�����
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
	enableInterrupts();

	//ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
	while (TRUE)
	{
		//�û��ڴ˴���д�������
	    //EncoderCharge_flag = 1;
	    switch(MODE)
        {
            case 0:    //����
                Keystroke_Scan();
                if(KeystrokeLabel == KeystrokeONE)
                {
                    THRESHOLD = flash_read(EEPROM_THRESHOLD,0,int);
                    THRESHOLD += 1;
                    if(flash_check(EEPROM_THRESHOLD,0) == 1)
                    {
                        eeprom_erase_sector(EEPROM_THRESHOLD);
                    }
                    Write_Date = (uint32)THRESHOLD;
                    eeprom_page_program(EEPROM_THRESHOLD,0,&Write_Date);
                }
                if(KeystrokeLabel == KeystrokeTWO)
                {
                    THRESHOLD = flash_read(EEPROM_THRESHOLD,0,int);
                    THRESHOLD -= 1;
                    if(flash_check(EEPROM_THRESHOLD,0) == 1)
                    {
                        eeprom_erase_sector(EEPROM_THRESHOLD);
                    }
                    Write_Date = (uint32)THRESHOLD;
                    eeprom_page_program(EEPROM_THRESHOLD,0,&Write_Date);
                }
                if(KeystrokeLabel == KeystrokeTHREE)
                {
                    displayflag = 0;
                    ips200_clear(WHITE);
                }
                else if(KeystrokeLabel == KeystrokeFOUR)
                {
                    displayflag= 1;
                    ips200_clear(WHITE);
                }
                if(IPS_Flag == 1 && displayflag == 1)
                {
                   IPS_Flag = 0;
                   IPS_display();
                }
                ROUST = flash_read(EEPROM_THRESHOLD,0,int);
                ips200_showfloat(190,0,Battery_Voltage,2,2);
                ips200_showfloat(190,1,Read_Battery_Voltage,2,2);
                ips200_showuint16(190,2,AfterI_Voltage);
                ips200_showuint8(190,3,State);
                ips200_showuint8(190,7,Slalom_Point[1]);
                ips200_showint32(190,4,Real_Distance,6);
                ips200_showfloat(190,5,Emo_Angle,2,2);
                ips200_showfloat(190,6,Emo_Pitch,2,2);
                ips200_showfloat(190,9,Pre_Speed,3,0);
                ips200_showfloat(190,8,end_Bat,2,1);
//                ips200_showuint16(0,16,Read_AF);
                sent_date((uint16)(Battery_Voltage*100),(uint16)Pre_Speed);
                break;
            case 1:
//                ips200_showfloat(190,0,Battery_Voltage,2,2);
//                ips200_showfloat(190,1,Read_Battery_Voltage,2,2);
                sent_date((uint16)dieReady,(uint16)TriforkTurn);
                break;
            case 2:
//                ips200_showfloat(190,0,Battery_Voltage,2,2);
//                ips200_showfloat(190,1,Read_Battery_Voltage,2,2);
                sent_date((uint16)(Battery_Voltage*100),(uint16)CoderSpeed);
                break;
            case 3:
//                sent_date((uint16)(Battery_Voltage*100),(uint16)Pre_Speed);
                break;
        }
	}
}

#pragma section all restore

