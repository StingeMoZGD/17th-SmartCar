/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#pragma section all "cpu0_dsram"
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中


//工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译
//工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
//然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
//一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化
//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因此需要我们自己手动调用enableInterrupts();来开启中断的响应。
int core0_main(void)
{
	get_clk();//获取时钟频率  务必保留
	//用户在此处调用各种初始化函数等

	DIP_Switch_Init();   //先扫描拨码开关
	Keystroke_Init();    //初始化按键
	Display_Init();      //初始化IPS
	Beep_Init();         //初始化蜂鸣器
	//gpio_init(P10_2, GPO, 0, PUSHPULL);
	//EEPROM_Default();

	while(1)     //菜单系统
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

	All_Config_CPU0();    //各个模块初始化
	//gpio_init(P33_4, GPO, 0, PUSHPULL);   //摄像头执行时间测试引脚

    //等待所有核心初始化完毕
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
	enableInterrupts();

	//注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
	while (TRUE)
	{
		//用户在此处编写任务代码
	    //EncoderCharge_flag = 1;
	    switch(MODE)
        {
            case 0:    //调试
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


