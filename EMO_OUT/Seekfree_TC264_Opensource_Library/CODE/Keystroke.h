/*
 * Keystroke.h
 *
 *  Created on: 2022��1��1��
 *      Author: YYM
 */

#ifndef CODE_KEYSTROKE_H_
#define CODE_KEYSTROKE_H_

#include "headfile.h"

#define ButtonCnt 4//���尴���������������Ŷ�����.c��
#define KeystrokeONE      1
#define KeystrokeTWO      2
#define KeystrokeTHREE    3
#define KeystrokeFOUR     4

#define KeyONE          P15_6
#define KeyTWO          P15_8
#define KeyTHREE        P14_0
#define KeyFOUR         P15_7

#define DIP_SwitchONE   P23_1
#define DIP_SwitchTWO   P32_4

#define EEPROM_Garage_Out_Dir    (0)
#define EEPROM_Circle_Switch     (1)
#define EEPROM_Speed             (2)
#define EEPROM_Direction         (3)
#define EEPROM_DistanceG         (4)
#define EEPROM_DistanceC         (5)
#define EEPROM_THRESHOLD         (6)


//������ǩö��
typedef enum
{
    ButtonOne,
    ButtonTwo,
    ButtonThree,
    ButtonFour
}ButtonLabel_enum;

/**************************************��������**************************************/
extern const PIN_enum ButtonPins[ButtonCnt];//��������
extern const ButtonLabel_enum ButtonLabels[ButtonCnt];//���Ŷ�Ӧ�ı�ǩ
extern uint8 Keystrokecount,KeystrokeLabel,EEPROM_Garage_Dir,EEPROM_Coner,Replace_GarageDir;
extern unsigned char RUN_STAR,Keystroke_Scan_Finish_Flag,Replace_Coner;
extern uint16 EEPROM_Pre_Speed,Replace_Speed,EEPROM_GarageDistance,EEPROM_ChargeDistance;
extern uint32 Write_Date;
extern float EEPROM_DircetionP,Replace_DircetionP;
extern int MODE,ROUST,THRESHOLD;


void DIP_Switch_Init(void);
void DIP_Switch_Contorl(void);
void EEPROM_Default(void);
void EEPROM_FLASH(void);
void Keystroke_Init(void);
void Keystroke_Scan(void);
void Keystroke_Menu(void);
void Keystroke_Menu_HOME(void);
void Keystroke_Menu_ONE(void);
void Keystroke_Menu_ONE_One(void);
void Keystroke_Menu_ONE_Two(void);
void Keystroke_Menu_TWO(void);
void Keystroke_Menu_TWO_One(void);
void Keystroke_Menu_TWO_Two(void);
void Keystroke_Menu_THREE(void);
void Keystroke_Menu_THREE_One(void);
void Keystroke_Menu_THREE_Two(void);

#endif /* CODE_KEYSTROKE_H_ */
