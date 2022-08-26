/*
 * OLED.c
 *
 *  Created on: 2021年11月13日
 *      Author: YYM
 */

#include "Display.h"
#include "SEEKFREE_MT9V03X.h"
#include "Camera.h"
#include "headfile.h"


unsigned char displayflag = 1;  //图像显示标志位  1:显示 0:不显示

void Display_Init(void)
{
    ips200_init();          //IPS显示屏初始化
    ips200_clear(WHITE);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      IPS画线函数
//  @param      p      画线数组
//  @param      color  颜色
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Draw_Line(uint8 *p,uint16 color)
{
    for(uint8 y=0;y<120;y++)
    {
        ips200_drawpoint(*(p+y),y,color);
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      IPS显示
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void IPS_display(void)
{
    ips200_displayimage032(Emo_imag[0], MT9V03X_W, MT9V03X_H);
    Draw_Line(Right_Black_Point,BLUE);
    Draw_Line(Left_Black_Point,PURPLE );
    Draw_Line(Middle_Black_Point,RED);
    //ips200_drawpoint(Right_Down_Point[0],Right_Down_Point[1],YELLOW);

    ips200_showint16(0,10,CoderONE);
    ips200_showint16(0,11,CoderTWO);
//    ips200_showint32(0,12,MotorONE,4);
//    ips200_showint32(0,13,MotorTWO,4);
//    ips200_showuint8(0,14,Middle_Black_Point[60]);
//    ips200_showfloat(0,15,Exp_SpeedONE,3,2);
//    ips200_showfloat(0,16,Exp_SpeedTWO,3,2);
////    ips200_showint16(0,17,Right_Black_Point[80]-93);
////    ips200_showint16(0,18,Right_Black_Point[100]);
////    ips200_showint16(0,19,Right_Black_Point[20]-93);
////    ips200_showint16(50,19,Right_Black_Point[20]);
//    //ips200_showfloat(50,10,CurvatureRight,3,2);
    ips200_showfloat(100,10,CurvatureRight,6,4);
    ips200_showfloat(100,11,CurvatureLeft,6,4);
    ips200_showuint8(160,14,Right_Down_Point[0]);
    ips200_showuint8(160,15,Right_Down_Point[1]);
    ips200_showuint8(160,12,Right_Up_Point[0]);
    ips200_showuint8(160,13,Right_Up_Point[1]);
    ips200_showuint8(100,14,Left_Down_Point[0]);
    ips200_showuint8(100,15,Left_Down_Point[1]);
    ips200_showuint8(100,12,Left_Up_Point[0]);
    ips200_showuint8(100,13,Left_Up_Point[1]);
    ips200_showint32(190,14,Right_Down_Point_finish_flag,1);
    ips200_showint32(190,12,Right_Up_Point_finish_flag,1);
    ips200_showint32(140,14,Left_Down_Point_finish_flag,1);
    ips200_showint32(140,12,Left_Up_Point_finish_flag,1);
//    //ips200_showint32(130,18,findrcount,3);
    ips200_showint32(140,16,SlalomRight_flag,1);
    ips200_showint32(100,16,SlalomLeft_flag,1);
    ips200_showint32(140,17,CircleRight_flag,1);
    ips200_showint32(100,17,CircleLeft_flag,1);
    ips200_showint32(100,18,Trifork_flag,1);
    ips200_showint32(140,18,CornerS_flag,1);
    ips200_showint32(140,19,CornerRight_flag,1);
    ips200_showint32(100,19,CornerLeft_flag,1);
    ips200_showint32(120,19,Cross_flag,1);
    ips200_showint32(160,19,Ramp_flag,1);
    ips200_showint32(180,19,CornerS_flag,1);
    ips200_showuint8(120,9,OSTU);
    ips200_showint32(160,9,ROUST,2);
    ips200_showint32(180,11,Circlecount,2);
    ips200_showfloat(180,16,Emo_Angle ,3,2);
    ips200_showint32(180,17,findlcount ,2);
    ips200_showint32(180,18,findrcount ,2);
//    ips200_showuint8(180,19,Endline);
    ips200_showint32(0,8,Trifork_PointLeft_Findfinish_flag,1);
    ips200_showint32(30,8,Trifork_PointMiddle_Findfinish_flag,1);
    ips200_showint32(60,8,Trifork_PointRight_Findfinish_flag,1);
    ips200_showint32(90,8,Triforkcount,1);
    ips200_showuint8(120,8,TriforkMiddle_Point[0]);
    ips200_showuint8(150,8,TriforkMiddle_Point[1]);
    ips200_showuint8(0,9,TriforkRight_Point[0]);
    ips200_showuint8(30,9,TriforkRight_Point[1]);
////    ips200_showuint8(60,9,Right_Black_Point[80]);
////    ips200_showuint8(90,9,Middle_Black_Point[80]);
//    //ips200_drawpoint(93,80,BLACK);
//    ips200_showuint8(90,9,BoundaryRight);
//    ips200_showuint8(60,9,BoundaryLeft);

}


//1.8TFT
//void TFT_Init(void)
//{
//    lcd_init();
//}
//
//void TFT_Draw_Line(uint8 *p,uint16 color)
//{
//    for(uint8 y=0;y<120;y++)
//    {
//        lcd_drawpoint(*(p+y),y,color);
//    }
//}
//
//void TFT_display(void)
//{
//    lcd_displayimage032(Emo_imag[0], MT9V03X_W, MT9V03X_H);
//}

//指针
//int *a;
//
//a[1]=1;
//*(a+1)=1;
//*(a+0)=1;
//*a
//
//int b
//int *bb=&b
//
//
//
//
//
//a[1]=*(a+1);
