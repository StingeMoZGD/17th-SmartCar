/*
 * Wireless.h
 *
 *  Created on: 2021��11��18��
 *      Author: YYM
 */

#ifndef CODE_WIRELESS_H_
#define CODE_WIRELESS_H_

#include "headfile.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))     //ȡ��int�ͱ����ĵ��ֽ�
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))   // ȡ�洢�ڴ˱�����һ�ڴ��ֽڵ����ݣ����ֽ�
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))



void Wireless_Init(void);
void sent_date(uint16 A,uint16 B);
void sent_date1(uint8 a,int16 b);
void sent_dateint16(int16 A,int16 B);

#endif /* CODE_WIRELESS_H_ */
