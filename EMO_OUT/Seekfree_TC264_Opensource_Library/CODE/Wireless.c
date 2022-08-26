/*
 * Wireless.c
 *
 *  Created on: 2021年11月18日
 *      Author: YYM
 */

//使用的是匿名上位机

#include "Wireless.h"

void Wireless_Init(void)
{
    seekfree_wireless_init();
}

void sent_date(uint16 A,uint16 B)
{
//    uint8  sumcheck = 0 ;
//    uint8  addcheck = 0 ;
     uint8  BUFF[30];
     int i;
     uint8 sumcheck = 0;
     uint8 addcheck = 0;
     uint8 _cnt=0;
     BUFF[_cnt++]=0xAA;//帧头
     BUFF[_cnt++]=0xFF;//目标地址
     BUFF[_cnt++]=0XF1;//功能码
     BUFF[_cnt++]=0x04;//数据长度
     BUFF[_cnt++]=BYTE0(A);//数据内容,小段模式，低位在前
     BUFF[_cnt++]=BYTE1(A);//需要将字节进行拆分，调用上面的宏定义即可。
     BUFF[_cnt++]=BYTE0(B);
     BUFF[_cnt++]=BYTE1(B);
//     BUFF[_cnt++]=BYTE0(C);
     //SC和AC的校验直接抄最上面上面简介的即可
     for(i=0;i<BUFF[3]+4;i++)
     {
         sumcheck+=BUFF[i];
         addcheck+=sumcheck;
     }
     BUFF[_cnt++]=sumcheck;
     BUFF[_cnt++]=addcheck;

     seekfree_wireless_send_buff(&BUFF[0],_cnt);//串口逐个发送数据
}

void sent_dateint16(int16 A,int16 B)
{
//    uint8  sumcheck = 0 ;
//    uint8  addcheck = 0 ;
     uint8  BUFF[30];
     int i;
     uint8 sumcheck = 0;
     uint8 addcheck = 0;
     uint8 _cnt=0;
     BUFF[_cnt++]=0xAA;//帧头
     BUFF[_cnt++]=0xFF;//目标地址
     BUFF[_cnt++]=0XF1;//功能码
     BUFF[_cnt++]=0x04;//数据长度
     BUFF[_cnt++]=BYTE0(A);//数据内容,小段模式，低位在前
     BUFF[_cnt++]=BYTE1(A);//需要将字节进行拆分，调用上面的宏定义即可。
     BUFF[_cnt++]=BYTE0(B);
     BUFF[_cnt++]=BYTE1(B);
//     BUFF[_cnt++]=BYTE0(C);
     //SC和AC的校验直接抄最上面上面简介的即可
     for(i=0;i<BUFF[3]+4;i++)
     {
         sumcheck+=BUFF[i];
         addcheck+=sumcheck;
     }
     BUFF[_cnt++]=sumcheck;
     BUFF[_cnt++]=addcheck;

     seekfree_wireless_send_buff(&BUFF[0],_cnt);//串口逐个发送数据
}

//void sent_data(uint16 A,uint16 B,uint8 C)
//{
//    int i;
//    uint8 sumcheck = 0;
//    uint8 addcheck = 0;
//    uint8 _cnt=0;
//    BUFF[_cnt++]=0xAA;//帧头
//    BUFF[_cnt++]=0xFF;//目标地址
//    BUFF[_cnt++]=0XF1;//功能码
//    BUFF[_cnt++]=0x05;//数据长度
//    BUFF[_cnt++]=BYTE0(A);//数据内容,小段模式，低位在前
//    BUFF[_cnt++]=BYTE1(A);//需要将字节进行拆分，调用上面的宏定义即可。
//    BUFF[_cnt++]=BYTE0(B);
//    BUFF[_cnt++]=BYTE1(B);
//    BUFF[_cnt++]=C;
//    //SC和AC的校验直接抄最上面上面简介的即可
//    for(i=0;i<BUFF[3]+4;i++)
//    {
//        sumcheck+=BUFF[i];
//        addcheck+=sumcheck;
//    }
//    BUFF[_cnt++]=sumcheck;
//    BUFF[_cnt++]=addcheck;
//
//    for(i=0;i<_cnt;i++) uart_putchar(UART_0,BUFF[i]);//串口逐个发送数据
//}

void sent_date1(uint8 a,int16 b)
{
//    uint8  sumcheck = 0 ;
//    uint8  addcheck = 0 ;
    uint8  BUFF[30];
     int i;
     uint8 sumcheck = 0;
     uint8 addcheck = 0;
     uint8 _cnt=0;
     BUFF[_cnt++]=0xAA;//帧头
     BUFF[_cnt++]=0xFF;//目标地址
     BUFF[_cnt++]=0XF1;//功能码
     BUFF[_cnt++]=0x04;//数据长度

     BUFF[_cnt++]=BYTE0(a);//数据内容,小段模式，低位在前
     BUFF[_cnt++]=BYTE1(a);//需要将字节进行拆分，调用上面的宏定义即可。
//     BUFF[_cnt++]=BYTE2(a);
//     BUFF[_cnt++]=BYTE3(a);

     BUFF[_cnt++]=BYTE0(b);//数据内容,小段模式，低位在前
     BUFF[_cnt++]=BYTE1(b);//需要将字节进行拆分，调用上面的宏定义即可。
//     BUFF[_cnt++]=BYTE2(b);
//     BUFF[_cnt++]=BYTE3(b);

//     BUFF[_cnt++]=BYTE0(B);
//     BUFF[_cnt++]=BYTE1(B);
//     BUFF[_cnt++]=BYTE0(C);
//     BUFF[_cnt++]=BYTE1(C);

     //SC和AC的校验直接抄最上面上面简介的即可
     for(i=0;i<BUFF[3]+4;i++)
     {
         sumcheck+=BUFF[i];
         addcheck+=sumcheck;
     }
     BUFF[_cnt++]=sumcheck;
     BUFF[_cnt++]=addcheck;

      seekfree_wireless_send_buff(&BUFF[0],_cnt);//串口逐个发送数据
}

void sent_dates(int16 a,int16 b)
{
//    uint8  sumcheck = 0 ;
//    uint8  addcheck = 0 ;
    uint8  BUFF[30];
     int i;
     uint8 sumcheck = 0;
     uint8 addcheck = 0;
     uint8 _cnt=0;
     BUFF[_cnt++]=0xAA;//帧头
     BUFF[_cnt++]=0xFF;//目标地址
     BUFF[_cnt++]=0XF1;//功能码
     BUFF[_cnt++]=0x04;//数据长度

     BUFF[_cnt++]=BYTE0(a);//数据内容,小段模式，低位在前
     BUFF[_cnt++]=BYTE1(a);//需要将字节进行拆分，调用上面的宏定义即可。
//     BUFF[_cnt++]=BYTE2(a);
//     BUFF[_cnt++]=BYTE3(a);

     BUFF[_cnt++]=BYTE0(b);//数据内容,小段模式，低位在前
     BUFF[_cnt++]=BYTE1(b);//需要将字节进行拆分，调用上面的宏定义即可。

//     BUFF[_cnt++]=BYTE0(c);//数据内容,小段模式，低位在前
//     BUFF[_cnt++]=BYTE1(c);//需要将字节进行拆分，调用上面的宏定义即可。
//
//     BUFF[_cnt++]=BYTE0(d);//数据内容,小段模式，低位在前
//     BUFF[_cnt++]=BYTE1(d);//需要将字节进行拆分，调用上面的宏定义即可。
//
//     BUFF[_cnt++]=BYTE0(e);//数据内容,小段模式，低位在前
//     BUFF[_cnt++]=BYTE1(e);//需要将字节进行拆分，调用上面的宏定义即可。
//
//     BUFF[_cnt++]=BYTE0(f);//数据内容,小段模式，低位在前
//     BUFF[_cnt++]=BYTE1(f);//需要将字节进行拆分，调用上面的宏定义即可。
//     BUFF[_cnt++]=BYTE2(b);
//     BUFF[_cnt++]=BYTE3(b);

//     BUFF[_cnt++]=BYTE0(B);
//     BUFF[_cnt++]=BYTE1(B);
//     BUFF[_cnt++]=BYTE0(C);
//     BUFF[_cnt++]=BYTE1(C);

     //SC和AC的校验直接抄最上面上面简介的即可
     for(i=0;i<BUFF[3]+4;i++)
     {
         sumcheck+=BUFF[i];
         addcheck+=sumcheck;
     }
     BUFF[_cnt++]=sumcheck;
     BUFF[_cnt++]=addcheck;

      seekfree_wireless_send_buff(&BUFF[0],_cnt);//串口逐个发送数据
}


