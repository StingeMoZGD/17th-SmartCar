/*
 * Wireless.c
 *
 *  Created on: 2021��11��18��
 *      Author: YYM
 */

//ʹ�õ���������λ��

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
     BUFF[_cnt++]=0xAA;//֡ͷ
     BUFF[_cnt++]=0xFF;//Ŀ���ַ
     BUFF[_cnt++]=0XF1;//������
     BUFF[_cnt++]=0x04;//���ݳ���
     BUFF[_cnt++]=BYTE0(A);//��������,С��ģʽ����λ��ǰ
     BUFF[_cnt++]=BYTE1(A);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
     BUFF[_cnt++]=BYTE0(B);
     BUFF[_cnt++]=BYTE1(B);
//     BUFF[_cnt++]=BYTE0(C);
     //SC��AC��У��ֱ�ӳ�������������ļ���
     for(i=0;i<BUFF[3]+4;i++)
     {
         sumcheck+=BUFF[i];
         addcheck+=sumcheck;
     }
     BUFF[_cnt++]=sumcheck;
     BUFF[_cnt++]=addcheck;

     seekfree_wireless_send_buff(&BUFF[0],_cnt);//���������������
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
     BUFF[_cnt++]=0xAA;//֡ͷ
     BUFF[_cnt++]=0xFF;//Ŀ���ַ
     BUFF[_cnt++]=0XF1;//������
     BUFF[_cnt++]=0x04;//���ݳ���
     BUFF[_cnt++]=BYTE0(A);//��������,С��ģʽ����λ��ǰ
     BUFF[_cnt++]=BYTE1(A);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
     BUFF[_cnt++]=BYTE0(B);
     BUFF[_cnt++]=BYTE1(B);
//     BUFF[_cnt++]=BYTE0(C);
     //SC��AC��У��ֱ�ӳ�������������ļ���
     for(i=0;i<BUFF[3]+4;i++)
     {
         sumcheck+=BUFF[i];
         addcheck+=sumcheck;
     }
     BUFF[_cnt++]=sumcheck;
     BUFF[_cnt++]=addcheck;

     seekfree_wireless_send_buff(&BUFF[0],_cnt);//���������������
}

//void sent_data(uint16 A,uint16 B,uint8 C)
//{
//    int i;
//    uint8 sumcheck = 0;
//    uint8 addcheck = 0;
//    uint8 _cnt=0;
//    BUFF[_cnt++]=0xAA;//֡ͷ
//    BUFF[_cnt++]=0xFF;//Ŀ���ַ
//    BUFF[_cnt++]=0XF1;//������
//    BUFF[_cnt++]=0x05;//���ݳ���
//    BUFF[_cnt++]=BYTE0(A);//��������,С��ģʽ����λ��ǰ
//    BUFF[_cnt++]=BYTE1(A);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
//    BUFF[_cnt++]=BYTE0(B);
//    BUFF[_cnt++]=BYTE1(B);
//    BUFF[_cnt++]=C;
//    //SC��AC��У��ֱ�ӳ�������������ļ���
//    for(i=0;i<BUFF[3]+4;i++)
//    {
//        sumcheck+=BUFF[i];
//        addcheck+=sumcheck;
//    }
//    BUFF[_cnt++]=sumcheck;
//    BUFF[_cnt++]=addcheck;
//
//    for(i=0;i<_cnt;i++) uart_putchar(UART_0,BUFF[i]);//���������������
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
     BUFF[_cnt++]=0xAA;//֡ͷ
     BUFF[_cnt++]=0xFF;//Ŀ���ַ
     BUFF[_cnt++]=0XF1;//������
     BUFF[_cnt++]=0x04;//���ݳ���

     BUFF[_cnt++]=BYTE0(a);//��������,С��ģʽ����λ��ǰ
     BUFF[_cnt++]=BYTE1(a);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
//     BUFF[_cnt++]=BYTE2(a);
//     BUFF[_cnt++]=BYTE3(a);

     BUFF[_cnt++]=BYTE0(b);//��������,С��ģʽ����λ��ǰ
     BUFF[_cnt++]=BYTE1(b);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
//     BUFF[_cnt++]=BYTE2(b);
//     BUFF[_cnt++]=BYTE3(b);

//     BUFF[_cnt++]=BYTE0(B);
//     BUFF[_cnt++]=BYTE1(B);
//     BUFF[_cnt++]=BYTE0(C);
//     BUFF[_cnt++]=BYTE1(C);

     //SC��AC��У��ֱ�ӳ�������������ļ���
     for(i=0;i<BUFF[3]+4;i++)
     {
         sumcheck+=BUFF[i];
         addcheck+=sumcheck;
     }
     BUFF[_cnt++]=sumcheck;
     BUFF[_cnt++]=addcheck;

      seekfree_wireless_send_buff(&BUFF[0],_cnt);//���������������
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
     BUFF[_cnt++]=0xAA;//֡ͷ
     BUFF[_cnt++]=0xFF;//Ŀ���ַ
     BUFF[_cnt++]=0XF1;//������
     BUFF[_cnt++]=0x04;//���ݳ���

     BUFF[_cnt++]=BYTE0(a);//��������,С��ģʽ����λ��ǰ
     BUFF[_cnt++]=BYTE1(a);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
//     BUFF[_cnt++]=BYTE2(a);
//     BUFF[_cnt++]=BYTE3(a);

     BUFF[_cnt++]=BYTE0(b);//��������,С��ģʽ����λ��ǰ
     BUFF[_cnt++]=BYTE1(b);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�

//     BUFF[_cnt++]=BYTE0(c);//��������,С��ģʽ����λ��ǰ
//     BUFF[_cnt++]=BYTE1(c);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
//
//     BUFF[_cnt++]=BYTE0(d);//��������,С��ģʽ����λ��ǰ
//     BUFF[_cnt++]=BYTE1(d);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
//
//     BUFF[_cnt++]=BYTE0(e);//��������,С��ģʽ����λ��ǰ
//     BUFF[_cnt++]=BYTE1(e);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
//
//     BUFF[_cnt++]=BYTE0(f);//��������,С��ģʽ����λ��ǰ
//     BUFF[_cnt++]=BYTE1(f);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
//     BUFF[_cnt++]=BYTE2(b);
//     BUFF[_cnt++]=BYTE3(b);

//     BUFF[_cnt++]=BYTE0(B);
//     BUFF[_cnt++]=BYTE1(B);
//     BUFF[_cnt++]=BYTE0(C);
//     BUFF[_cnt++]=BYTE1(C);

     //SC��AC��У��ֱ�ӳ�������������ļ���
     for(i=0;i<BUFF[3]+4;i++)
     {
         sumcheck+=BUFF[i];
         addcheck+=sumcheck;
     }
     BUFF[_cnt++]=sumcheck;
     BUFF[_cnt++]=addcheck;

      seekfree_wireless_send_buff(&BUFF[0],_cnt);//���������������
}


