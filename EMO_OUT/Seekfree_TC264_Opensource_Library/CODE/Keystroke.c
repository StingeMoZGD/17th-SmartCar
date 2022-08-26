/*
 * Keystroke.c
 *
 *  Created on: 2022��1��1��
 *      Author: YYM
 */

#include "Keystroke.h"

//�����˵�
//���뿪�����ڿ������Ժ�����ģʽ
//����ģʽ��4���������ֱ��Ӧͼ�񡢿��ơ�**������
//ͼ����ʾͼ�񡢹յ㡢��־λ
//���ƣ�1������ 2������ 3������
//����:1�����ⷽ�� 2��Ԫ�عر� 3������
//������1���ٶ� 2������   3������
//��������P: 1������ 2������ 3����д
//
//���У��ڵ���ģʽ�°��¼�����
//����������ҳ�����Ʋ�������
//����0�����ⷽ��
//����1��Բ������
//����2���ٶ�
//����3������P  D��P�ɱ���
//��¼���´�����֤ÿ�ΰ�����ʾ�����ظ������úö�ӦĿ¼���ڰ���ʱ����ӦĿ¼��ת
/*************�������Ŷ��塢������������Ӧ�ı�ǩ���壨��ά��*************************/
const PIN_enum ButtonPins[ButtonCnt] =
{
    P15_6,
    P15_8,
    P14_0,
    P15_7
};
const ButtonLabel_enum ButtonLabels[ButtonCnt] =
{
    ButtonOne,
    ButtonTwo,
    ButtonThree,
    ButtonFour
};
uint8 KeystrokeLabel = 0;
uint8 Keystrokecount = 0;
unsigned char Keystroke_Scan_Finish_Flag = 0;
unsigned char RUN_STAR = 0;  //С�����п���
uint8 EEPROM_Garage_Dir = 0;   //���ⷽ�� 0����  1����  Ĭ��Ϊ��
uint8 EEPROM_Coner = 1;       //������п��� 0����ر� 1������ Ĭ��Ϊ����
uint16 EEPROM_Pre_Speed = 60;  //Ĭ���ٶ�60 ���٣�40 ���٣�80
float EEPROM_DircetionP = 1;   //����P
uint16 EEPROM_GarageDistance = 1700;   //����������
uint16 EEPROM_ChargeDistance = 0;   //���������
float EEPROM_ChBat = 0;   //����ѹ
uint32 Write_Date = 0;         //��д����λ
int Dispay_Codename = 0;       //��ʾҳ�����
uint8 Replace_GarageDir = 0;
unsigned char Replace_Coner = 0;
uint16 Replace_Speed = 0;
float Replace_DircetionP = 0;
float Repalce_ChBat = 0;
int THRESHOLD = 0;
int ROUST = 0;
int MODE = 0;              //�н�ģʽ   0:���� 1:�������� 2:���ٱ��� 3:�ռ�����

//������дĬ��ֵ
void EEPROM_Default(void)
{
    eeprom_erase_sector(EEPROM_Garage_Out_Dir);
    eeprom_erase_sector(EEPROM_Circle_Switch);
    eeprom_erase_sector(EEPROM_Speed);
    eeprom_erase_sector(EEPROM_Direction);
    eeprom_erase_sector(EEPROM_DistanceG);
    eeprom_erase_sector(EEPROM_DistanceC);
    Write_Date = (uint32)EEPROM_Garage_Dir;
    eeprom_page_program(EEPROM_Garage_Out_Dir,0,&Write_Date);
    Write_Date = (uint32)EEPROM_Coner;
    eeprom_page_program(EEPROM_Circle_Switch,0,&Write_Date);
    Write_Date = (uint32)EEPROM_Pre_Speed;
    eeprom_page_program(EEPROM_Speed,0,&Write_Date);
    Write_Date = (uint32)float_conversion_uint32(EEPROM_DircetionP);
    eeprom_page_program(EEPROM_Direction,0,&Write_Date);
    Write_Date = (uint32)EEPROM_GarageDistance;
    eeprom_page_program(EEPROM_DistanceG,0,&Write_Date);
//    Write_Date = (uint32)EEPROM_ChargeDistance;
//    eeprom_page_program(EEPROM_DistanceC,0,&Write_Date);
    Write_Date = (uint32)float_conversion_uint32(EEPROM_ChBat);
    eeprom_page_program(EEPROM_DistanceC,0,&Write_Date);
    Write_Date = (uint32)THRESHOLD;
    eeprom_page_program(EEPROM_THRESHOLD,0,&Write_Date);
}

//ȷ����дֵ���������
//��д���ݣ�Garage_Dir��Pre_Speed��Position_KP��CircleSwitch_flag
//flash_read(sector_num,page_num,type)
void EEPROM_FLASH(void)
{
    Replace_GarageDir = flash_read(EEPROM_Garage_Out_Dir,0,uint8);
    EEPROM_Coner = flash_read(EEPROM_Circle_Switch,0,uint8);
    Replace_Coner = (unsigned char)EEPROM_Coner;
    Replace_Speed = flash_read(EEPROM_Speed,0,uint16);
    Replace_DircetionP = flash_read(EEPROM_Direction,0,float);
    Garage_Dir = (unsigned char)Replace_GarageDir;
    Repalce_ChBat = flash_read(EEPROM_DistanceC,0,float);
    end_Bat = Repalce_ChBat;
    EEPROM_GarageDistance = flash_read(EEPROM_DistanceG,0,uint16);
    ROUST = flash_read(EEPROM_THRESHOLD,0,int);
}

//���뿪�س�ʼ����1��2  OFF����������ģʽ   1 ON 2 OFF������ 1 ON 2 ON������ 1 OFF 2 ON��
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���뿪�س�ʼ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void DIP_Switch_Init(void)
{
    gpio_init(DIP_SwitchONE,GPI,0,NO_PULL);
    gpio_init(DIP_SwitchTWO,GPI,0,NO_PULL);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���뿪��ɨ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void DIP_Switch_Contorl(void)
{
    if(gpio_get(DIP_SwitchONE) == 1 && gpio_get(DIP_SwitchTWO) == 1)      //1��2  OFF����������ģʽ
    {
        MODE = 0;
    }
    else if(gpio_get(DIP_SwitchONE) == 0 && gpio_get(DIP_SwitchTWO) == 1) //1 ON 2 OFF������
    {
        MODE = 1;
        RUN_STAR = 1;
    }
    else if(gpio_get(DIP_SwitchONE) == 0 && gpio_get(DIP_SwitchTWO) == 0) //1 ON 2 ON������
    {
        MODE = 2;
        RUN_STAR = 1;
    }
    else if(gpio_get(DIP_SwitchONE) == 1 && gpio_get(DIP_SwitchTWO) == 0) //1 OFF 2 ON���ռ�
    {
        MODE = 3;
        RUN_STAR = 1;
    }

}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ʼ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Init(void)
{
    for(uint8 Cnt=0;Cnt<ButtonCnt;Cnt++)
    {
        gpio_init(ButtonPins[Cnt], GPI, 1, NO_PULL);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ɨ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Scan(void)
{
    KeystrokeLabel = 0;
    for(uint8 Cnt=0;Cnt<ButtonCnt;Cnt++)
    {
        if(gpio_get(ButtonPins[Cnt]) == 0)
        {
            systick_delay_ms(STM0, 20);
            if(gpio_get(ButtonPins[Cnt]) == 0)
            {
                systick_delay_ms(STM0, 200);
                if(gpio_get(ButtonPins[Cnt]) == 1)
                {
                    systick_delay_ms(STM0, 20);
                    if(gpio_get(ButtonPins[Cnt]) == 1)
                    {
                        KeystrokeLabel = Cnt+1;
                        break;
//                        Keystrokecount++;
//                        Keystroke_Scan_Finish_Flag = 1;
                    }
                }
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �˵�Ŀ¼
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ����while����ʾĿ��ҳ��  ��ÿ��ҳ�水�������󶼻�ı䵽��Ӧҳ�棬�˺������ڸ�����Ļ��ʾ
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu(void)
{
    switch(Dispay_Codename)
    {
        case 0:
            Keystroke_Menu_HOME();
            break;
        case 1:
            Keystroke_Menu_ONE();
            break;
        case 11:
            Keystroke_Menu_ONE_One();
            break;
        case 12:
            Keystroke_Menu_ONE_Two();
            break;
        case 2:
            Keystroke_Menu_TWO();
            break;
        case 21:
            Keystroke_Menu_TWO_One();
            break;
//        case 211:
//            Keystroke_Menu_TWO_One_one();
//            break;
//        case 212:
//            Keystroke_Menu_TWO_One_two();
//            break;
        case 22:
            Keystroke_Menu_TWO_Two();
            break;
//        case 221:
//            Keystroke_Menu_TWO_Two_one();
//            break;
//        case 222:
//            Keystroke_Menu_TWO_Two_two();
//            break;
        case 3:
            Keystroke_Menu_THREE();
            break;
        case 31:
            Keystroke_Menu_THREE_One();
            break;
        case 32:
            Keystroke_Menu_THREE_Two();
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ܲ˵�Ŀ¼
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ0
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_HOME(void)    //0
{
    ips200_showstr(0,0,"Parameter");
    ips200_showstr(0,6,"Encoder");
    ips200_showstr(0,12,"Control");
    ips200_showstr(0,18,"Run");
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
            Dispay_Codename = 0;
            break;
        case KeystrokeONE :
            Dispay_Codename = 1;
            ips200_clear(WHITE);
            break;
        case KeystrokeTWO :
            Dispay_Codename = 2;
            ips200_clear(WHITE);
            break;
        case KeystrokeTHREE :
            Dispay_Codename = 3;
            ips200_clear(WHITE);
            break;
        case KeystrokeFOUR :
            RUN_STAR = 1;
            ips200_clear(WHITE);
            break;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����˵�Ŀ¼
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ1
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_ONE(void)   //1
{
    EEPROM_Pre_Speed = flash_read(EEPROM_Speed,0,uint16);
    EEPROM_DircetionP = flash_read(EEPROM_Direction,0,float);
    ips200_showstr(0,0,"PreSpeed");
    ips200_showuint16(120,0,EEPROM_Pre_Speed);
    ips200_showstr(0,6,"dirP");
    ips200_showfloat(60,6,EEPROM_DircetionP,2,3);
    ips200_showstr(0,12,"dirD");
    ips200_showfloat(60,12,EEPROM_DircetionP/7,2,3);
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
            Dispay_Codename = 1;
            break;
        case KeystrokeONE :
            Dispay_Codename = 11;
            ips200_clear(WHITE);
            break;
        case KeystrokeTWO :
            Dispay_Codename = 12;
            ips200_clear(WHITE);
            break;
        case KeystrokeTHREE :
            Dispay_Codename = 0;
            ips200_clear(WHITE);
            break;
        case KeystrokeFOUR :
            RUN_STAR = 1;
            ips200_clear(WHITE);
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����˵��е��ٶȲ˵�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ11
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_ONE_One(void)  //11
{
    EEPROM_Pre_Speed = flash_read(EEPROM_Speed,0,uint16);
    ips200_showstr(0,0,"PreSpeed");
    ips200_showfloat(120,0,EEPROM_Pre_Speed,3,1);
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
            Dispay_Codename = 11;
            break;
        case KeystrokeONE :
            EEPROM_Pre_Speed = flash_read(EEPROM_Speed,0,uint16);
            EEPROM_Pre_Speed += 2;
            if(flash_check(EEPROM_Speed,0) == 1)
            {
                eeprom_erase_sector(EEPROM_Speed);
            }
            Write_Date = (uint32)EEPROM_Pre_Speed;
            eeprom_page_program(EEPROM_Speed,0,&Write_Date);
            Dispay_Codename = 11;
            ips200_clear(WHITE);
            break;
        case KeystrokeTWO :
            EEPROM_Pre_Speed = flash_read(EEPROM_Speed,0,uint16);
            EEPROM_Pre_Speed = EEPROM_Pre_Speed - 1;
            if(flash_check(EEPROM_Speed,0) == 1)
            {
                eeprom_erase_sector(EEPROM_Speed);
            }
            Write_Date = (uint32)EEPROM_Pre_Speed;
            eeprom_page_program(EEPROM_Speed,0,&Write_Date);
            Dispay_Codename = 11;
            ips200_clear(WHITE);
            break;
        case KeystrokeTHREE :
            Dispay_Codename = 1;
            ips200_clear(WHITE);
            break;
        case KeystrokeFOUR :
            RUN_STAR = 1;
            ips200_clear(WHITE);
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����˵��еķ���˵�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ12
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_ONE_Two(void)  //12
{
    EEPROM_DircetionP = flash_read(EEPROM_Direction,0,float);
    ips200_showstr(0,0,"dirP");
    ips200_showfloat(60,0,EEPROM_DircetionP,2,3);
    ips200_showstr(0,6,"dirD");
    ips200_showfloat(60,6,EEPROM_DircetionP/7,2,3);
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
            Dispay_Codename = 12;
            break;
        case KeystrokeONE :
            EEPROM_DircetionP = flash_read(EEPROM_Direction,0,float);
            EEPROM_DircetionP += 0.03;
            if(flash_check(EEPROM_Direction,0) == 1)
            {
                eeprom_erase_sector(EEPROM_Direction);
            }
            Write_Date = (uint32)float_conversion_uint32(EEPROM_DircetionP);;
            eeprom_page_program(EEPROM_Direction,0,&Write_Date);
            Dispay_Codename = 12;
            ips200_clear(WHITE);
            break;
        case KeystrokeTWO :
            EEPROM_DircetionP = flash_read(EEPROM_Direction,0,float);
            EEPROM_DircetionP = EEPROM_DircetionP - 0.03;
            if(flash_check(EEPROM_Direction,0) == 1)
            {
                eeprom_erase_sector(EEPROM_Direction);
            }
            Write_Date = (uint32)float_conversion_uint32(EEPROM_DircetionP);
            eeprom_page_program(EEPROM_Direction,0,&Write_Date);
            Dispay_Codename = 12;
            ips200_clear(WHITE);
            break;
        case KeystrokeTHREE :
            Dispay_Codename = 1;
            ips200_clear(WHITE);
            break;
        case KeystrokeFOUR :
            RUN_STAR = 1;
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���Ʋ˵�Ŀ¼
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ2
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_TWO(void) //2
{
    EEPROM_GarageDistance = flash_read(EEPROM_DistanceG,0,uint16);
    EEPROM_ChBat = flash_read(EEPROM_DistanceC,0,float);
    ips200_showstr(0,0,"GarageDistance");
    ips200_showuint16(120,0,EEPROM_GarageDistance);
    ips200_showstr(0,6,"CHBAT");
    ips200_showfloat(120,6,EEPROM_ChBat,2,1);
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
            Dispay_Codename = 2;
            break;
        case KeystrokeONE :
            Dispay_Codename = 21;
            ips200_clear(WHITE);
            break;
        case KeystrokeTWO :
            Dispay_Codename = 22;
            ips200_clear(WHITE);
            break;
        case KeystrokeTHREE :
            Dispay_Codename = 0;
            ips200_clear(WHITE);
            break;
        case KeystrokeFOUR :
            RUN_STAR = 1;
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���Ʋ˵��еĳ���������Ʋ��˵�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ21
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_TWO_One(void)   //21
{
    EEPROM_GarageDistance = flash_read(EEPROM_DistanceG,0,uint16);
    ips200_showstr(0,0,"GarageDistance");
    ips200_showuint16(120,0,EEPROM_GarageDistance);
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
            Dispay_Codename = 21;
            break;
        case KeystrokeONE :
            EEPROM_GarageDistance = flash_read(EEPROM_DistanceG,0,uint16);
            EEPROM_GarageDistance += 100;
            if(flash_check(EEPROM_DistanceG,0) == 1)
            {
                eeprom_erase_sector(EEPROM_DistanceG);
            }
            Write_Date = (uint32)EEPROM_GarageDistance;
            eeprom_page_program(EEPROM_DistanceG,0,&Write_Date);
            Dispay_Codename = 21;
            ips200_clear(WHITE);
            break;
        case KeystrokeTWO :
            EEPROM_GarageDistance = flash_read(EEPROM_DistanceG,0,uint16);
            EEPROM_GarageDistance = EEPROM_GarageDistance - 100;
            if(flash_check(EEPROM_DistanceG,0) == 1)
            {
                eeprom_erase_sector(EEPROM_DistanceG);
            }
            Write_Date = (uint32)EEPROM_GarageDistance;
            eeprom_page_program(EEPROM_DistanceG,0,&Write_Date);
            Dispay_Codename = 21;
            ips200_clear(WHITE);
            break;
        case KeystrokeTHREE :
            Dispay_Codename = 2;
            ips200_clear(WHITE);
            break;
        case KeystrokeFOUR :
            RUN_STAR = 1;
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���Ʋ˵��еĳ���ѹ�˵�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ22
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_TWO_Two(void)   //22
{
    EEPROM_ChBat = flash_read(EEPROM_DistanceC,0,float);
    ips200_showstr(0,0,"CHBAT");
    ips200_showfloat(120,0,EEPROM_ChBat,2,1);
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
            Dispay_Codename = 22;
            break;
        case KeystrokeONE :
            EEPROM_ChBat = flash_read(EEPROM_DistanceC,0,float);
            EEPROM_ChBat += 0.2;
            if(flash_check(EEPROM_DistanceC,0) == 1)
            {
                eeprom_erase_sector(EEPROM_DistanceC);
            }
            Write_Date = (uint32)float_conversion_uint32(EEPROM_ChBat);
            eeprom_page_program(EEPROM_DistanceC,0,&Write_Date);
            Dispay_Codename = 22;
            ips200_clear(WHITE);
            break;
        case KeystrokeTWO :
            EEPROM_ChBat = flash_read(EEPROM_DistanceC,0,float);
            EEPROM_ChBat = EEPROM_ChBat-0.2;
            if(flash_check(EEPROM_DistanceC,0) == 1)
            {
                eeprom_erase_sector(EEPROM_DistanceC);
            }
            Write_Date = (uint32)float_conversion_uint32(EEPROM_ChBat);
            eeprom_page_program(EEPROM_DistanceC,0,&Write_Date);
            Dispay_Codename = 22;
            ips200_clear(WHITE);
            break;
        case KeystrokeTHREE :
            Dispay_Codename = 2;
            ips200_clear(WHITE);
            break;
        case KeystrokeFOUR :
            RUN_STAR = 1;
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���Բ˵�Ŀ¼
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ3
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_THREE(void) //3
{
    EEPROM_Garage_Dir = flash_read(EEPROM_Garage_Out_Dir,0,uint8);
    EEPROM_Coner = flash_read(EEPROM_Circle_Switch,0,uint8);
    ips200_showstr(0,0,"GarageDir");
    if(EEPROM_Garage_Dir == 0)
    {
        ips200_showstr(90,0,"Right");
    }
    else
    {
        ips200_showstr(90,0,"Left");
    }
    ips200_showstr(0,6,"corners");
    if(EEPROM_Coner == 1)
    {
        ips200_showstr(90,6,"1");
    }
    else
    {
        ips200_showstr(90,6,"0");
    }
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
            Dispay_Codename = 3;
            break;
        case KeystrokeONE :
            Dispay_Codename = 31;
            ips200_clear(WHITE);
            break;
        case KeystrokeTWO :
            Dispay_Codename = 32;
            ips200_clear(WHITE);
            break;
        case KeystrokeTHREE :
            Dispay_Codename = 0;
            ips200_clear(WHITE);
            break;
        case KeystrokeFOUR :
            RUN_STAR = 1;
            ips200_clear(WHITE);
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���Բ˵��г��ⷽ��˵�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ31
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_THREE_One(void)  //31
{
    EEPROM_Garage_Dir = flash_read(EEPROM_Garage_Out_Dir,0,uint8);
    ips200_showstr(0,0,"GarageDir");
    if(EEPROM_Garage_Dir == 0)
    {
        ips200_showstr(90,0,"Right");
    }
    else
    {
        ips200_showstr(90,0,"Left");
    }
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
            Dispay_Codename = 31;
            break;
        case KeystrokeONE :
            EEPROM_Garage_Dir = flash_read(EEPROM_Garage_Out_Dir,0,uint8);
            if(EEPROM_Garage_Dir == 1)
            {
                EEPROM_Garage_Dir = 0;
            }
            else
            {
                EEPROM_Garage_Dir = 1;
            }
            if(flash_check(EEPROM_Garage_Out_Dir,0) == 1)
            {
                eeprom_erase_sector(EEPROM_Garage_Out_Dir);
            }
            Write_Date = (uint32)EEPROM_Garage_Dir;
            eeprom_page_program(EEPROM_Garage_Out_Dir,0,&Write_Date);
            Dispay_Codename = 31;
            ips200_clear(WHITE);
            break;
        case KeystrokeTWO :
            Dispay_Codename = 31;
            ips200_clear(WHITE);
            break;
        case KeystrokeTHREE :
            Dispay_Codename = 3;
            ips200_clear(WHITE);
            break;
        case KeystrokeFOUR :
            RUN_STAR = 1;
            ips200_clear(WHITE);
            break;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���Բ˵������������ٲ˵�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ32
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_THREE_Two(void)  //32
{
    EEPROM_Coner = flash_read(EEPROM_Circle_Switch,0,uint8);
    ips200_showstr(0,0,"corners");
    if(EEPROM_Coner == 1)
    {
        ips200_showstr(90,0,"1");
    }
    else
    {
        ips200_showstr(90,0,"0");
    }
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
            Dispay_Codename = 32;
            break;
        case KeystrokeONE :
            EEPROM_Coner = flash_read(EEPROM_Circle_Switch,0,uint8);
            if(EEPROM_Coner == 1)
            {
                EEPROM_Coner = 0;
            }
            else
            {
                EEPROM_Coner = 1;
            }
            if(flash_check(EEPROM_Circle_Switch,0) == 1)
            {
                eeprom_erase_sector(EEPROM_Circle_Switch);
            }
            Write_Date = (uint32)EEPROM_Coner;
            eeprom_page_program(EEPROM_Circle_Switch,0,&Write_Date);
            Dispay_Codename = 32;
            ips200_clear(WHITE);
            break;
        case KeystrokeTWO :
            Dispay_Codename = 32;
            ips200_clear(WHITE);
            break;
        case KeystrokeTHREE :
            Dispay_Codename = 3;
            ips200_clear(WHITE);
            break;
        case KeystrokeFOUR :
            RUN_STAR = 1;
            ips200_clear(WHITE);
            break;
    }
}


//�����˵��������ٶȺͷ���PID
//void Keystroke_Menu_ONE(void)  //1
//{
//    Camera_Init();
//    ips200_displayimage032(Emo_imag[0], MT9V03X_W, MT9V03X_H);
//    Draw_Line(Right_Black_Point,BLUE);
//    Draw_Line(Left_Black_Point,PURPLE );
//    Draw_Line(Middle_Black_Point,RED);
//    ips200_showuint8(160,14,Right_Down_Point[0]);
//    ips200_showuint8(160,15,Right_Down_Point[1]);
//    ips200_showuint8(160,12,Right_Up_Point[0]);
//    ips200_showuint8(160,13,Right_Up_Point[1]);
//    ips200_showuint8(100,14,Left_Down_Point[0]);
//    ips200_showuint8(100,15,Left_Down_Point[1]);
//    ips200_showuint8(100,12,Left_Up_Point[0]);
//    ips200_showuint8(100,13,Left_Up_Point[1]);
//    ips200_showint32(190,14,Right_Down_Point_finish_flag,1);
//    ips200_showint32(190,12,Right_Up_Point_finish_flag,1);
//    ips200_showint32(140,14,Left_Down_Point_finish_flag,1);
//    ips200_showint32(140,12,Left_Up_Point_finish_flag,1);
//    ips200_showint32(140,16,SlalomRight_flag,1);
//    ips200_showint32(100,16,SlalomLeft_flag,1);
//    ips200_showint32(140,17,CircleRight_flag,1);
//    ips200_showint32(100,17,CircleLeft_flag,1);
//    ips200_showint32(100,18,Trifork_flag,1);
//    ips200_showint32(140,18,CornerS_flag,1);
//    ips200_showint32(140,19,CornerRight_flag,1);
//    ips200_showint32(100,19,CornerLeft_flag,1);
//    ips200_showuint8(180,10,OSTU);
//    ips200_showuint8(90,9,BoundaryRight);
//    ips200_showuint8(60,9,BoundaryLeft);
//    Keystroke_Scan();
//    switch(KeystrokeLabel)
//    {
//        case 0 :
//            Dispay_Codename = 1;
//            break;
//        case KeystrokeONE :
//            Dispay_Codename = 11;
//            ips200_clear(WHITE);
//            break;
//        case KeystrokeTWO :
//            Dispay_Codename = 1;
//            ips200_clear(WHITE);
//            break;
//        case KeystrokeTHREE :
//            Dispay_Codename = 0;
//            ips200_clear(WHITE);
//            break;
//        case KeystrokeFOUR :
//            RUN_STAR = 1;
//            ips200_clear(WHITE);
//            break;
//    }
//}

//�ٶȲ����˵�
//void Keystroke_Menu_ONE_One(void) //11
//{
//    ips200_showstr(0,0,"EEPROMDefault");
//    Keystroke_Scan();
//    switch(KeystrokeLabel)
//    {
//        case 0 :
//            Dispay_Codename = 11;
//            break;
//        case KeystrokeONE :
//            EEPROM_Default();
//            Dispay_Codename = 1;
//            ips200_clear(WHITE);
//            break;
//        case KeystrokeTWO :
//            Dispay_Codename = 1;
//            ips200_clear(WHITE);
//            break;
//        case KeystrokeTHREE :
//            Dispay_Codename = 1;
//            ips200_clear(WHITE);
//            break;
//        case KeystrokeFOUR :
//            RUN_STAR = 1;
//            ips200_clear(WHITE);
//            break;
//    }
//}


////dirP�˵�
//void Keystroke_Menu_TWO_Two_one_KP(void)
//{
//    ips200_showstr(0,0,"dirP");
//    ips200_showfloat(60,0,Position_KP,2,3);
//    ips200_showstr(0,6,"dirD");
//    ips200_showfloat(60,6,Position_KD,2,3);
//    switch(KeystrokeLabel)
//    {
//        case KeystrokeONE :
//
//            break;
//        case KeystrokeTWO :
//            break;
//        case KeystrokeTHREE :
//            Keystroke_Menu_TWO_One();
//            break;
//        case KeystrokeFOUR :
//            break;
//    }
//}
//
////dirI�˵�
//void Keystroke_Menu_TWO_Two_one_KI(void)
//{
//
//}
