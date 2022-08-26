/*
 * remember.h
 *
 *  Created on: 2022年5月10日
 *      Author: YYM
 */

#ifndef CODE_REMEMBER_H_
#define CODE_REMEMBER_H_



//static int DecelaerateTime = 0;   //时间计数，用于不卡死在前电感减速程序
//void Decelerate(float V , float Speed)
//{
//    //如果电压大于8V不进行减速
//    if(V < 8)
//    {
////        if(Speed >= 100)
////        {
////            Pre_Speed = 100;
////            Speed = 100;
////        }
////        DecelaerateTime++;
////        if(DecelaerateTime >= 1 && AfterI_Voltage > 1400 )
////        {
////            if(Speed >= 100)
////            {
////                Pre_Speed = (10.0 - Speed)/3000.0*(float)FormerI_Voltage + Speed - (10.0 - Speed)/6.0;
////                DecelaerateTime = 0;
////            }
////            else
////            {
//        Pre_Speed = (Speed-35)/(Dec - AIN) * (float)AfterI_Voltage + 35*(Dec - AIN)/(AIN*(Speed - 35))
////            Pre_Speed = (35.0 - Speed)/1500.0*(float)AfterI_Voltage + Speed - (35.0 - Speed)/3.0;
//            //DecelaerateTime = 0;
////            }
//
////        }
//
//    }
//    if(V >= 8)
//    {
//        if(Speed >= 100)
//        {
//            Pre_Speed = 100;
//            Speed = 100;
//        }
////        DecelaerateTime++;
////        if(DecelaerateTime >= 1 && AfterI_Voltage > 1400 )
////        {
////            if(Speed >= 100)
////            {
////                Pre_Speed = (35.0 - Speed)/3000.0*(float)FormerI_Voltage + Speed - (35.0 - Speed)/6.0;
////                DecelaerateTime = 0;
////            }
////            else
////            {
////                Pre_Speed = (40.0 - Speed)/1500.0*(float)AfterI_Voltage + Speed - (40.0 - Speed)/3.0;
////                DecelaerateTime = 0;
////            }
//
////        }
//    }
//
//}

//    if(V >= 0 && V <= 5)
//    {
//        if(FindCharge_flag == 0)
//        {
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//            }
//        }
//        else
//        {
//            Pre_Speed = 0;
//        }
//    }
//    else if(V > 5 && V <= 6.5)
//    {
//        if(FindCharge_flag == 0)
//        {
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//            }
//        }
//        else
//        {
//            Pre_Speed = 0;
//        }
//    }
//    else if(V > 6.5 && V <= 7.5)
//    {
//        if(FindCharge_flag == 0)
//        {
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//            }
//        }
//        else
//        {
//            Pre_Speed = 1;
//        }
//    }
//    else if(V > 7.5 && V <= 8.3)
//    {
//        if(FindCharge_flag == 0)
//        {
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//            }
//        }
//        else
//        {
//            Pre_Speed = 2;
//        }
//    }
//    else if(V > 8.3 && V <= 9.2)
//    {
//        if(FindCharge_flag == 0)
//        {
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//            }
//        }
//        else
//        {
//            Pre_Speed = 3;
//        }
//    }

//    if(Read_Speed >= 85)
//    {
//        Pre_Speed = 85;
//    }
//    DecelaerateTime++;
//    if(DecelaerateTime >= 1 && )
//    {
//
//    }
//    if(V >= 0 && V <= 5)
//    {
//        if(FindCharge_flag == 0)
//        {
//
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//                CoderSumONE = 0;
//                CoderSumTWO = 0;
//            }
////            if(Real_Distance >= EEPROM_ChargeDistance)
////            {
////                Inone = 0;
////                FindCharge_flag = 1;
////                CoderSumONE = 0;
////                CoderSumTWO = 0;
////            }
//        }
//        else
//        {
//            State =
//            Pre_Speed = 0;
//        }
//    }
//    else if(V > 5 && V <= 6.5)
//    {
//        if(FindCharge_flag == 0)
//        {
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//                CoderSumONE = 0;
//                CoderSumTWO = 0;
//            }
////            if(Real_Distance >= EEPROM_ChargeDistance)
////            {
////                Inone = 0;
////                FindCharge_flag = 1;
////                CoderSumONE = 0;
////                CoderSumTWO = 0;
////            }
//        }
//        else
//        {
//            Pre_Speed = 0;
//        }
//    }
//    else if(V > 6.5 && V <= 7.5)
//    {
//        if(FindCharge_flag == 0)
//        {
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//                CoderSumONE = 0;
//                CoderSumTWO = 0;
//            }
////            if(Real_Distance >= EEPROM_ChargeDistance)
////            {
////                Inone = 0;
////                FindCharge_flag = 1;
////                CoderSumONE = 0;
////                CoderSumTWO = 0;
////            }
//        }
//        else
//        {
//            Pre_Speed = 1;
//        }
//    }
//    else if(V > 7.5 && V <= 8.3)
//    {
//        if(FindCharge_flag == 0)
//        {
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//                CoderSumONE = 0;
//                CoderSumTWO = 0;
//            }
////            if(Real_Distance >= EEPROM_ChargeDistance)
////            {
////                Inone = 0;
////                FindCharge_flag = 1;
////                CoderSumONE = 0;
////                CoderSumTWO = 0;
////            }
//        }
//        else
//        {
//            Pre_Speed = 2;
//        }
//    }
//    else if(V > 8.3 && V <= 9.2)
//    {
//        if(FindCharge_flag == 0)
//        {
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//                CoderSumONE = 0;
//                CoderSumTWO = 0;
//            }
////            if(Real_Distance >= EEPROM_ChargeDistance)
////            {
////                Inone = 0;
////                FindCharge_flag = 1;
////                CoderSumONE = 0;
////                CoderSumTWO = 0;
////            }
//        }
//        else
//        {
//            Pre_Speed = 3;
//        }
//    }
//    else if(V > 9.2 && V <= 10)
//    {
//        if(FindCharge_flag == 0)
//        {
//            if(FormerI_Voltage >= FIN)
//            {
//                Inone = 1;
//            }
//            if(Inone == 1 && AfterI_Voltage >= AIN)
//            {
//                Inone = 0;
//                FindCharge_flag = 1;
//                CoderSumONE = 0;
//                CoderSumTWO = 0;
//            }
////            if(Real_Distance >= EEPROM_ChargeDistance)
////            {
////                Inone = 0;
////                FindCharge_flag = 1;
////                CoderSumONE = 0;
////                CoderSumTWO = 0;
////            }
//        }
//        else
//        {
//            Pre_Speed = 20;
//        }
//    }
//    else if(V > 10 && V <= 10.5)
//    {
//        Pre_Speed = 30;
//    }
//    else if(V > 10.5 && V <= 11)
//    {
//        Pre_Speed = 40;
//    }
//    else if(V > 11 && V <= 11.5)
//    {
//        Pre_Speed = Read_Speed;
//    }
//    else if(V > 11.5 && V <= 12.3)
//    {
//        Pre_Speed = (float)Replace_Speed;
//    }
//    else
//    {
//        Pre_Speed = (float)Replace_Speed;
//    }

//校赛
//unsigned char zuobuxian = 0,youbuxian = 0;
//
//void Judge_exhibition_match(void)
//{
//    uint8 star;
//    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
//    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
//    //unsigned char JudgeCorner = 0;    //如果出现边界但不是弯道就不执行判断S弯
//    //unsigned char JudgeS = 0;         //表示执行了S弯却没判断成功
//
//    CornerRight_flag = 0;
//    CornerLeft_flag = 0;
//    Near_CornerLeft_flag = 0;
//    Near_CornerRight_flag = 0;
//    Near_Corners_flag = 0;
//    for(uint8 y=67;y>20;y--)
//    {
//        if(Right_Black_Point[y-1] == 187 && Right_Black_Point[y-2] == 187 && Right_Black_Point[y-3] == 187 && Left_Black_Point[y-1] != 0 && Left_Black_Point[y-2] != 0 && Left_Black_Point[y-3] != 0 && Left_Black_Point[y-6] != 0 && Left_Black_Point[y-7] != 187 && Left_Black_Point[y-8] != 187)
//        {
//            //JudgeCorner = 1;
//            star=y;
//            for (uint8 y = (star-16); y < star; y++)//对赛道边界进行累加计算
//            {
//                if (y % 2 == 0)
//                {
//                    LeftXSum += Left_Black_Point[y];
//                    LeftYSum += y;
//                    LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
//                    LeftXYSum += y * Left_Black_Point[y];
//                }
//             }
//
//            if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
//            {
//                CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
//            }
//            else
//            {
//                CurvatureLeft = 0;
//            }
//            if(CurvatureLeft > (-1) && CurvatureLeft < 0)
//            {
//                CornerRight_flag = 1;
//                Corners_flag = 1;
//                break;
//            }
//            else
//            {
//                CornerRight_flag = 0;
//                Corners_flag = 0;
//                break;
//            }
//        }
//        else
//        {
//            CornerRight_flag = 0;
//            Corners_flag = 0;
//        }
//        if(Left_Black_Point[y-1] == 0 && Left_Black_Point[y-2] == 0 && Left_Black_Point[y-3] == 0 && Right_Black_Point[y-1] != 187 && Right_Black_Point[y-2] != 187 && Right_Black_Point[y-3] != 187 && Right_Black_Point[y-6] != 187 && Right_Black_Point[y-7] != 187 && Right_Black_Point[y-8] != 187)
//        {
//            star=y;
//            for (uint8 y = (star-16); y < star; y++)//对赛道边界进行累加计算
//            {
//                if (y % 2 == 0)
//                {
//                    RightXSum += Right_Black_Point[y];
//                    RightYSum += y;
//                    RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
//                    RightXYSum += y * Right_Black_Point[y];
//                }
//             }
//            if(8 * RightXXSum - RightXSum * RightXSum != 0)
//            {
//                CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
//            }
//            else
//            {
//                CurvatureRight = 0;
//            }
//            if(CurvatureRight < 1.0 && CurvatureRight > 0)
//            {
//                CornerLeft_flag = 1;
//                Corners_flag = 1;
//                break;
//            }
//            else
//            {
//                CornerLeft_flag = 0;
//                Corners_flag = 0;
//                break;
//            }
//        }
//        else
//        {
//            CornerLeft_flag = 0;
//            Corners_flag = 0;
//        }
//    }
//    if(CornerRight_flag == 1)
//    {
//        if(Right_Black_Point[100] == 187 && Right_Black_Point[99] == 187 && Right_Black_Point[98] == 187 && Left_Black_Point[100] != 0 && Left_Black_Point[99] != 0 && Left_Black_Point[98] != 0 && Left_Black_Point[95] != 0 && Left_Black_Point[94] != 187 && Left_Black_Point[93] != 187)
//        {
//            Near_CornerRight_flag = 1;
//            Near_Corners_flag = 1;
//        }
//    }
//    if(CornerLeft_flag == 1)
//    {
//        if(Left_Black_Point[100] == 0 && Left_Black_Point[99] == 0 && Left_Black_Point[98] == 0 && Right_Black_Point[100] != 187 && Right_Black_Point[99] != 187 && Right_Black_Point[98] != 187 && Right_Black_Point[95] != 187 && Right_Black_Point[94] != 187 && Right_Black_Point[93] != 187)
//        {
//            Near_CornerLeft_flag = 1;
//            Near_Corners_flag = 1;
//        }
//    }
//
//
//}
//void exhibition_match1(void)
//{
//    if(CornerLeft_flag == 0 && CornerRight_flag == 0 && zuobuxian == 0)
//    {
//        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount < 4 && Left_Down_Point[1] > 46)
//        {
//            zuobuxian = 1;
//        }
//    }
//    if(CornerLeft_flag == 0 && CornerRight_flag == 0 && youbuxian == 0)
//    {
//        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && findrcount < 4 && Right_Down_Point[1] > 46)
//        {
//            youbuxian = 1;
//        }
//    }
//
//}
//unsigned char zuobuxiancount = 0,youbuxiancount = 0;
//void exhibition_match2(void)
//{
//    if(zuobuxian == 1)
//    {
//        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && zuobuxiancount == 0)
//        {
//            zuobuxiancount = 1;
//        }
//        if(zuobuxiancount == 1)
//        {
//            if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0)
//            {
//                zuobuxiancount = 2;
//            }
//        }
//        if(zuobuxiancount == 2)
//        {
//            if(Left_Up_Point_finish_flag == 0)
//            {
//                zuobuxiancount = 3;
//            }
//        }
//        switch(zuobuxiancount)
//        {
//            case 1 :
//                Link_Left_One_Point[0] = Left_Down_Point[0];
//                Link_Left_One_Point[1] = Left_Down_Point[1];
//                Link_Left_Two_Point[0] = Left_Up_Point[0];
//                Link_Left_Two_Point[1] = Left_Up_Point[1];
//                //PaddingR = 0;
//                PaddingL = 1;
//                break;
//            case 2 :
//                Link_Left_One_Point[0] = Left_Down_Point[0];
//                Link_Left_One_Point[1] = Left_Down_Point[1];
//                Link_Left_Two_Point[0] = Left_Up_Point[0];
//                Link_Left_Two_Point[1] = Left_Up_Point[1];
//                //PaddingR = 0;
//                PaddingL = 1;
//                break;
//            case 3 :
//                //PaddingR = 0;
//                PaddingL = 0;
//                zuobuxian = 0;
//                zuobuxiancount = 0;
//                break;
//        }
//    }
//    if(youbuxian == 1)
//    {
//        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && youbuxiancount == 0)
//        {
//            youbuxiancount = 1;
//        }
//        if(youbuxiancount == 1)
//        {
//            if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0)
//            {
//                youbuxiancount = 2;
//            }
//        }
//        if(youbuxiancount == 2)
//        {
//            if(Right_Up_Point_finish_flag == 0)
//            {
//                youbuxiancount = 3;
//            }
//        }
//        switch(youbuxiancount)
//        {
//            case 1 :
//                Link_Right_One_Point[0] = Right_Down_Point[0];
//                Link_Right_One_Point[1] = Right_Down_Point[1];
//                Link_Right_Two_Point[0] = Right_Up_Point[0];
//                Link_Right_Two_Point[1] = Right_Up_Point[1];
//                PaddingR = 1;
//                //PaddingL = 0;
//                break;
//            case 2 :
//                Link_Right_One_Point[0] = Right_Down_Point[0];
//                Link_Right_One_Point[1] = Right_Down_Point[1];
//                Link_Right_Two_Point[0] = Right_Up_Point[0];
//                Link_Right_Two_Point[1] = Right_Up_Point[1];
//                PaddingR = 1;
//                //PaddingL = 0;
//                break;
//            case 3 :
//                PaddingR = 0;
//                //PaddingL = 0;
//                youbuxian = 0;
//                youbuxiancount = 0;
//                break;
//        }
//    }
//}
//void exhibition_match(void)
//{
//    if(zuobuxian == 0 && youbuxian == 0)
//    {
//        Judge_exhibition_match();
//    }
//    if(CornerLeft_flag == 0 && CornerRight_flag == 0)
//    {
//        Identify();
//        exhibition_match1();
//        exhibition_match2();
//    }
//}

//    if(CircleLeft_flag == 1 && Trialcount < 2)
//    {
//        if(Right_Black_Point[80] != 187 && Right_Black_Point[81] != 187 &&
//          Left_Black_Point[90] == 0 && Left_Black_Point[80] == 0)
//        for (uint8 y = (star-16); y < star; y++)//对赛道边界进行累加计算
//        {
//            if (y % 2 == 0)
//            {
//                RightXSum += Right_Black_Point[y];
//                RightYSum += y;
//                RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
//                RightXYSum += y * Right_Black_Point[y];
//            }
//         }
//        if(8 * RightXXSum - RightXSum * RightXSum != 0)
//        {
//            CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
//        }
//        else
//        {
//            CurvatureRight = 0;
//        }
//        if(CurvatureRight < 0.82 && CurvatureRight > 0.17)
//        {
//            Trialcount++;
//        }
//        else
//        {
//            Circlecount = 0;
//            CircleLeft_flag = 0;
//            PaddingR = 0;
//            PaddingL = 0;
//            Trialcount = 0;
//        }
//    }
//    if(CircleRight_flag == 1 && Trialcount < 2)
//    {
//        if(Left_Black_Point[80] != 0 && Left_Black_Point[81] != 0 &&
//           Right_Black_Point[90] == 187 && Right_Black_Point[80] == 187)
//        {
//            for (uint8 y = (star-16); y < star; y++)//对赛道边界进行累加计算
//            {
//                if (y % 2 == 0)
//                {
//                    LeftXSum += Left_Black_Point[y];
//                    LeftYSum += y;
//                    LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
//                    LeftXYSum += y * Left_Black_Point[y];
//                }
//             }
//
//            if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
//            {
//                CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
//            }
//            else
//            {
//                CurvatureLeft = 0;
//            }
//            if(CurvatureLeft > (-0.82) && CurvatureLeft < -0.17)
//            {
//                Trialcount++;
//            }
//            else
//            {
//                Circlecount = 0;
//                CircleRight_flag = 0;
//                PaddingR = 0;
//                PaddingL = 0;
//                Trialcount = 0;
//            }
//        }
//    }

//uint8 Trifork_Point[2];
//
//static void TriforkPoint(void)
//{
//    for(uint8 y=0;y<110;y++)
//    {
//        if(Emo_imag[y][93]==EmoWhite)
//        {
//            Trifork_Point[0]=93;
//            Trifork_Point[1]=y;
//            break;
//        }
//    }
//}

//三叉路口
//void Trifork(void)
//{
//    if(Trifork_flag == 1)
//    {
//        Beepindex = BeepThreefork;
//        if(Triforkcount == 0 )
//        {
////            TriforkPoint();
//            Triforkcount=1;
//        }
//        if(Triforkcount == 1)
//        {
//            Trifork_Judge();
//            if(Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0 && TriforkMiddle_Point[1] > 26)
//            {
//                Triforkcount = 2 ;
//            }
//        }
//        if(Triforkcount == 2)
//        {
//            Trifork_MIddlePoint();
//            if(Trifork_PointMiddle_Findfinish_flag == 0 && Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0)
//            {
//                Triforkcount = 3;
//            }
//        }
//        if(Triforkcount == 3)
//        {
//            Trifork_Judge();
//            if(Trifork_PointMiddle_Findfinish_flag == 1 && Trifork_PointLeft_Findfinish_flag == 1 && Trifork_PointRight_Findfinish_flag == 1)
//            {
//                Triforkcount = 4;
//            }
//        }
//        if(Triforkcount == 4)
//        {
//            Trifork_Judge();
//            if(Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0 && TriforkMiddle_Point[1] > 26)
//            {
//                Triforkcount = 5;
//            }
//        }
//        if(Triforkcount == 5)
//        {
//            Trifork_MIddlePoint();
//            if(Trifork_PointMiddle_Findfinish_flag == 0 && Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0)
//            {
//                Triforkcount = 6;
//            }
//        }
//        switch(Triforkcount)
//        {
//            case 1 :
//                if(TriforkTurn % 2 == 0)        //默认奇数向左，偶数向右，往返赛道应该补同一边线
//                {
//                    Link_Right_One_Point[0] = TriforkRight_Point[0];
//                    Link_Right_One_Point[1] = TriforkRight_Point[1];
//                    Link_Right_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Right_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 1;
//                    PaddingL = 0;
//                    break;
//                }
//                else
//                {
//                    Link_Left_One_Point[0] = TriforkLeft_Point[0];
//                    Link_Left_One_Point[1] = TriforkLeft_Point[1];
//                    Link_Left_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Left_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 0;
//                    PaddingL = 1;
//                    break;
//                }
//            case 2 :
//                if(TriforkTurn % 2 == 0)
//                {
//                    Link_Right_One_Point[0] = TriforkRight_Point[0];
//                    Link_Right_One_Point[1] = TriforkRight_Point[1];
//                    Link_Right_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Right_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 1;
//                    PaddingL = 0;
//                    break;
//                }
//                else
//                {
//                    Link_Left_One_Point[0] = TriforkLeft_Point[0];
//                    Link_Left_One_Point[1] = TriforkLeft_Point[1];
//                    Link_Left_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Left_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 0;
//                    PaddingL = 1;
//                    break;
//                }
//            case 3 :
//                Triforkpadding_flag = 0;
//                PaddingR = 0;
//                PaddingL = 0;
//                break;
//            case 4 :
//                if(TriforkTurn % 2 == 0)        //默认奇数向左，偶数向右
//                {
//                    Link_Right_One_Point[0] = TriforkRight_Point[0];
//                    Link_Right_One_Point[1] = TriforkRight_Point[1];
//                    Link_Right_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Right_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 1;
//                    PaddingL = 0;
//                    break;
//                }
//                else
//                {
//                    Link_Left_One_Point[0] = TriforkLeft_Point[0];
//                    Link_Left_One_Point[1] = TriforkLeft_Point[1];
//                    Link_Left_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Left_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 0;
//                    PaddingL = 1;
//                    break;
//                }
//            case 5 :
//                if(TriforkTurn % 2 == 0)
//                {
//                    Link_Right_One_Point[0] = TriforkRight_Point[0];
//                    Link_Right_One_Point[1] = TriforkRight_Point[1];
//                    Link_Right_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Right_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 1;
//                    PaddingL = 0;
//                    break;
//                }
//                else
//                {
//                    Link_Left_One_Point[0] = TriforkLeft_Point[0];
//                    Link_Left_One_Point[1] = TriforkLeft_Point[1];
//                    Link_Left_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Left_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 0;
//                    PaddingL = 1;
//                    break;
//                }
//            case 6 :
//                PaddingR = 0;
//                PaddingL = 0;
//                Triforkpadding_flag = 0;
//                Triforkcount = 0;
//                Trifork_flag = 0;
//                Beepindex = 0;
//                if(TriforkTurn == 0)
//                    TriforkTurn = 1;
//                else if(TriforkTurn == 1)
//                    TriforkTurn = 2;
//                else if(TriforkTurn == 2)
//                    TriforkTurn = 3;
//                else if(TriforkTurn == 3)
//                    TriforkTurn = 4;
//                else if(TriforkTurn == 5)
//                    TriforkTurn = 6;
//                else if(TriforkTurn == 6)
//                    TriforkTurn = 7;
//                break;
//        }
//
//    }
//}

////三叉路口
//void Trifork_Shuttle(void)
//{
//    if(Trifork_flag == 1)
//    {
//        if(Triforkcount == 0 )
//        {
////            TriforkPoint();
//            Triforkcount=1;
//        }
//        if(Triforkcount == 1)
//        {
//            Trifork_Judge();
//            Gyroscope_Star_flag = 1;
//            if(Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0 && TriforkMiddle_Point[1] > 26)
//            {
//                Triforkcount = 2 ;
//            }
//        }
//        if(Triforkcount == 2)
//        {
//            //Trifork_Judge();
//            Trifork_MIddlePoint();
//            if(Trifork_PointMiddle_Findfinish_flag == 0 && Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0 && Emo_Angle < -20)
//            {
//                Triforkcount = 3;
//                Gyroscope_Star_flag = 0;
//            }
//        }
//        if(Triforkcount == 3)
//        {
//            Trifork_Judge();
//            if(Trifork_PointMiddle_Findfinish_flag == 1 && Trifork_PointLeft_Findfinish_flag == 1 && Trifork_PointRight_Findfinish_flag == 1)
//            {
//                Triforkcount = 4;
//            }
//        }
//        if(Triforkcount == 4)
//        {
//            Trifork_Judge();
//            Gyroscope_Star_flag = 1;
//            if(Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0 && TriforkMiddle_Point[1] > 26)
//            {
//                Triforkcount = 5;
//            }
//        }
//        if(Triforkcount == 5)
//        {
//            Trifork_MIddlePoint();
//            if(Trifork_PointMiddle_Findfinish_flag == 0 && Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0 && Emo_Angle < -20)
//            {
//                Triforkcount = 6;
//            }
//        }
//        switch(Triforkcount)    //默认奇数向左，偶数向右，往返赛道应该补同一边线:右
//        {
//            case 1 :
//                    Link_Left_One_Point[0] = TriforkLeft_Point[0];
//                    Link_Left_One_Point[1] = TriforkLeft_Point[1];
//                    Link_Left_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Left_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 0;
//                    PaddingL = 1;
//                    break;
//            case 2 :
//                    Link_Left_One_Point[0] = TriforkLeft_Point[0];
//                    Link_Left_One_Point[1] = TriforkLeft_Point[1];
//                    Link_Left_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Left_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 0;
//                    PaddingL = 1;
//                    break;
//            case 3 :
//                Triforkpadding_flag = 0;
//                PaddingR = 0;
//                PaddingL = 0;
//                break;
//            case 4 :
//                    Link_Left_One_Point[0] = TriforkLeft_Point[0];
//                    Link_Left_One_Point[1] = TriforkLeft_Point[1];
//                    Link_Left_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Left_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 0;
//                    PaddingL = 1;
//                    break;
//            case 5 :
//                    Link_Left_One_Point[0] = TriforkLeft_Point[0];
//                    Link_Left_One_Point[1] = TriforkLeft_Point[1];
//                    Link_Left_Two_Point[0] = TriforkMiddle_Point[0];
//                    Link_Left_Two_Point[1] = TriforkMiddle_Point[1];
//                    Triforkpadding_flag = 1;
//                    PaddingR = 0;
//                    PaddingL = 1;
//                    break;
//            case 6 :
//                PaddingR = 0;
//                PaddingL = 0;
//                Triforkpadding_flag = 0;
//                Triforkcount = 0;
//                Trifork_flag = 0;
//                if(TriforkTurn == 0)
//                    TriforkTurn = 1;
//                else if(TriforkTurn == 1)
//                    TriforkTurn = 2;
//                else if(TriforkTurn == 2)
//                    TriforkTurn = 3;
//                else if(TriforkTurn == 3)
//                    TriforkTurn = 4;
//                else if(TriforkTurn == 5)
//                    TriforkTurn = 6;
//                else if(TriforkTurn == 6)
//                    TriforkTurn = 7;
//                break;
//        }
//
//    }
//}

//static void Garage_Findpoint(void)
//{
//    if(Garage_Out_Dir == 0)
//    {
//        for(uint8 y=Right_Down_Point[1];y>20;y--)
//        {
//            if(Emo_imag[y][Right_Down_Point[0]] == EmoBlack && Emo_imag[y-1][Right_Down_Point[0]] == EmoBlack && Emo_imag[y-2][Right_Down_Point[0]] == EmoBlack)
//            {
//                Garage_Point[0] = Right_Down_Point[0];
//                Garage_Point[1] = y;
//                break;
//            }
//        }
//    }
//    else
//    {
//        for(uint8 y=Left_Down_Point[1];y>20;y--)
//        {
//            if(Emo_imag[y][Left_Down_Point[0]] == EmoBlack && Emo_imag[y-1][Left_Down_Point[0]] == EmoBlack && Emo_imag[y-2][Left_Down_Point[0]] == EmoBlack)
//            {
//                Garage_Point[0] = Left_Down_Point[0];
//                Garage_Point[1] = y;
//                break;
//            }
//        }
//    }
//}
//
//void Garage_Out(void)
//{
//    if(Right_Down_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Garage_Out_Count == 0)
//    {
//        Garage_Out_Count = 1;
//        Garage_Findpoint();
//    }
//    if(Garage_Out_Count == 1)
//    {
//        Garage_Findpoint();
//        if(Right_Down_Point_finish_flag == 0)
//        {
//            Garage_Out_Count = 2;
//        }
//    }
//    switch(Garage_Out_Count)
//    {
//        case 1 :
//            if(Garage_Out_Dir == 1)
//            {
//                Link_Right_One_Point[0] = Right_Down_Point[0];
//                Link_Right_One_Point[1] = Right_Down_Point[1];
//                Link_Right_Two_Point[0] = Garage_Point[0];
//                Link_Right_Two_Point[1] = Garage_Point[1];
//                PaddingR = 1;
//                PaddingL = 0;
//                break;
//            }
//            else
//            {
//                Link_Left_One_Point[0] = Left_Down_Point[0];
//                Link_Left_One_Point[1] = Left_Down_Point[1];
//                Link_Left_Two_Point[0] = Garage_Point[0];
//                Link_Left_Two_Point[1] = Garage_Point[1];
//                PaddingR = 0;
//                PaddingL = 1;
//                break;
//            }
//        case 2 :
//            Garage_Out_Count = 0;
//            Garage_Out_Finsh_flag = 1;
//            PaddingR = 0;
//            PaddingL = 0;
//            break;
//    }
//}
//
//void Garage_In(void)
//{
//
//}
//出入库
//void Garage(void)
//{
//
//}

//        else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && Right_Down_Point[1] > 40 && (Left_Black_Point[Right_Up_Point[1]] - Left_Black_Point[Right_Down_Point[1]] > 0) && GarageR_Findfinish_flag == 0)
//        {
//            Cross_flag = 1;
//        }
//        else
//        {
//
//        }
//        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount < 4 && Left_Down_Point[1] > 54 && (Right_Black_Point[Left_Up_Point[1]] - Right_Black_Point[Left_Down_Point[1]] < 0) && GarageL_Findfinish_flag == 0)
//        {
//            SlalomLeft_flag=1;
//        }
//        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && findrcount < 4 && Right_Down_Point[1] > 54 && (Left_Black_Point[Right_Up_Point[1]] - Left_Black_Point[Right_Down_Point[1]] > 0) && GarageR_Findfinish_flag == 0)
//        {
//            SlalomRight_flag=1;
//        }
//        else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount < 4 && Left_Down_Point[1] > 54 && (Right_Black_Point[Left_Up_Point[1]] - Right_Black_Point[Left_Down_Point[1]] < 0) && GarageL_Findfinish_flag == 1)
//        {
//            GarageL_Findfinish_flag = 0;
//            GarageL_flag = 1;
//        }
//        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && findrcount < 4 && Right_Down_Point[1] > 54 && (Left_Black_Point[Right_Up_Point[1]] - Left_Black_Point[Right_Down_Point[1]] > 0) && GarageR_Findfinish_flag == 1)
//        {
//            GarageR_Findfinish_flag = 0;
//            GarageR_flag = 1;
//        }
//        else if(CircleSwitch_flag == 1 && Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount >= 7 && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 0 && Left_Down_Point[1] > 54 && (Right_Black_Point[Left_Up_Point[1]] - Right_Black_Point[Left_Down_Point[1]] < 0))
//        {
//            CircleLeft_flag=1;
//        }
//        else if(CircleSwitch_flag == 1 && Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && findrcount >= 7 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 0 && Right_Down_Point[1] > 54 && (Left_Black_Point[Right_Up_Point[1]] - Left_Black_Point[Right_Down_Point[1]] > 0))
//        {
//            CircleRight_flag=1;
//        }
//        else if(Right_Down_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Emo_imag[3][93]==EmoBlack && Emo_imag[3][92]==EmoBlack && Emo_imag[3][94]==EmoBlack && Left_Up_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 0)
//        {
//            Trifork_flag = 1;
//        }


//    for(uint8 y=28;y<46;y++)
//    {
//        if(Trifork_Left == 0)
//        {
//            if((Left_Black_Point[y+1]-Left_Black_Point[y] >= 0) && (Left_Black_Point[y+2]-Left_Black_Point[y] > 0) && (Left_Black_Point[y+3]-Left_Black_Point[y] > 0) && (Left_Black_Point[y+4]-Left_Black_Point[y+1] > 0) && Left_Black_Point[y] < 93 && (Left_Black_Point[y+5]-Left_Black_Point[y+2] > 0) && (Left_Black_Point[y+5]-Left_Black_Point[y+3] > 0) && (Left_Black_Point[y+6]-Left_Black_Point[y+4] > 0) && (Left_Black_Point[y+7]-Left_Black_Point[y+5] > 0) && (Left_Black_Point[y+8]-Left_Black_Point[y+6] > 0))
//            {
//                Trifork_Left = 1;
//            }
//        }
//        if(Trifork_Right == 0)
//        {
//            if((Right_Black_Point[y]-Right_Black_Point[y+1] >= 0) && (Right_Black_Point[y]-Right_Black_Point[y+2] > 0) && (Right_Black_Point[y]-Right_Black_Point[y+3] > 0) && (Right_Black_Point[y+1]-Right_Black_Point[y+4] > 0) && Right_Black_Point[y] > 93 && (Right_Black_Point[y+2]-Right_Black_Point[y+5] > 0) && (Right_Black_Point[y+3]-Right_Black_Point[y+5] > 0) && (Right_Black_Point[y+4]-Right_Black_Point[y+6] > 0) && (Right_Black_Point[y+5]-Right_Black_Point[y+7] > 0) && (Right_Black_Point[y+6]-Right_Black_Point[y+8] > 0))
//            {
//                Trifork_Right = 1;
//            }
//        }
//        if(Trifork_Left == 1 && Trifork_Right == 1)
//        {
//            Trifork_y = y;
////            for(uint8 )
//            TriforkPoint_Judge();
//            if(Trifork_PointMiddle_Findfinish_flag == 1 && Trifork_PointRight_Findfinish_flag == 1 && Trifork_PointLeft_Findfinish_flag == 1)
//            {
//                break;
//            }
//        }
//    }


//void TriforkPoint_Judge(void)
//{
//    //uint8 Temp = 0;
//    uint8 star = 0;            //存储寻找中间点的y的起始值
//
//    Trifork_PointLeft_Findfinish_flag = 0;
//    Trifork_PointRight_Findfinish_flag = 0;
//    Trifork_PointMiddle_Findfinish_flag = 0;
//    for(uint8 y=Trifork_y;y<105;y++)
//    {
//        if(Trifork_PointLeft_Findfinish_flag == 0)
//        {
//            if((Left_Black_Point[y]-Left_Black_Point[y-1] >= 0) && (Left_Black_Point[y]-Left_Black_Point[y-2] > 0) && (Left_Black_Point[y]-Left_Black_Point[y-3] > 0) && (Left_Black_Point[y-1]-Left_Black_Point[y-3] > 0) && (Left_Black_Point[y]-Left_Black_Point[y+1] >= 0) && (Left_Black_Point[y]-Left_Black_Point[y+2] > 0) && (Left_Black_Point[y]-Left_Black_Point[y+3] > 0) && (Left_Black_Point[y+1]-Left_Black_Point[y+3] > 0))
//            {
//                TriforkLeft_Point[0] = Left_Black_Point[y];
//                TriforkLeft_Point[1] = y;
//                Trifork_PointLeft_Findfinish_flag = 1;
//            }
//            else
//            {
//                Trifork_PointLeft_Findfinish_flag = 0;
//            }
//        }
//        if(Trifork_PointRight_Findfinish_flag == 0)
//        {
//            if((Right_Black_Point[y-1]-Right_Black_Point[y] >= 0) && (Right_Black_Point[y-2]-Right_Black_Point[y] > 0) && (Right_Black_Point[y-3]-Right_Black_Point[y] > 0) && (Right_Black_Point[y-3]-Right_Black_Point[y-1] > 0) && (Right_Black_Point[y+1]-Right_Black_Point[y] >= 0) && (Right_Black_Point[y+2]-Right_Black_Point[y] > 0) && (Right_Black_Point[y+3]-Right_Black_Point[y] > 0) && (Right_Black_Point[y+3]-Right_Black_Point[y+1] > 0))
//            {
//                TriforkRight_Point[0] = Left_Black_Point[y];
//                TriforkRight_Point[1] = y;
//                Trifork_PointRight_Findfinish_flag = 1;
//            }
//            else
//            {
//                Trifork_PointRight_Findfinish_flag = 0;
//            }
//        }
//        if(TriforkLeft_Point[1] >= TriforkRight_Point[1])
//        {
//            star = TriforkRight_Point[1];
//        }
//        else
//        {
//            star = TriforkLeft_Point[1];
//        }
//        if(Trifork_PointRight_Findfinish_flag == 1 || Trifork_PointLeft_Findfinish_flag == 1)
//        {
//            for(uint8 y=star+5;y>2;y--)
//            {
//                for(uint8 x = 23 ;x < 160 ; x++)
//                {
//                    if(Emo_imag[y][x] == EmoBlack && Emo_imag[y+1][x] == EmoWhite && Emo_imag[y+1][x-1] == EmoWhite && Emo_imag[y+1][x+1] == EmoWhite && Emo_imag[y-1][x] == EmoBlack)
//                    {
//                        TriforkMiddle_Point[0] = x;
//                        TriforkMiddle_Point[1] = y;
//                        Trifork_PointMiddle_Findfinish_flag = 1;
//                        break;
//                    }
//                    else
//                    {
//                        Trifork_PointMiddle_Findfinish_flag = 0;
//                    }
//                }
//                if(Trifork_PointMiddle_Findfinish_flag == 1)
//                    break;
//                if(y == 2)
//                    break;
////                Temp = (uint8)(TriforkRight_Point[0] - TriforkLeft_Point[0])/2;
////                if(Emo_imag[y][Temp] == EmoBlack && Emo_imag[y-1][Temp] == EmoBlack)
////                {
////                    TriforkMiddle_Point[0] = Temp;
////                    TriforkMiddle_Point[1] = y;
////                    Trifork_PointMiddle_Findfinish_flag = 1;
////                    break;
////                }
////                else
////                {
////                    Trifork_PointMiddle_Findfinish_flag = 0;
////                }
//            }
//            if(Trifork_PointMiddle_Findfinish_flag == 1 && Trifork_PointRight_Findfinish_flag == 1 && Trifork_PointLeft_Findfinish_flag == 1)
//            {
//                break;
//            }
//        }
//    }
//}

////先进行简单左右寻线，再依据八领域的拐点寻找，即右下拐点的左、左上、上、右上都是白的
//void Identify(void)
//{
//    uint8 findr_x;    //右点
//    uint8 findr_y;
//    uint8 examr_x;
//    uint8 examr_y;
//    uint8 findl_x;    //左点
//    uint8 findl_y;
//    uint8 examl_x;
//    uint8 examl_y;
//    uint8 examcount;
//    //uint8 examerror;
////    uint8 dircount;
//    int directionrd[5][2] =  {{-1,1}, {-1,0}, {-1,-1}, {0,1}, {1,1}};  //顺时针下方向数组先x再y
//    int directionld[5][2] =  {{1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};  //逆时针下方向数组
//    int directionru[5][2] =  {{1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}};  //逆时针上方向数组
//    int directionlu[5][2] =  {{-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}};  //逆时针上方向数组
//    for(uint8 y = 100 ; y >= 15 ; y--)
//    {
//        if(Right_Black_Point[y-4]==187 && Right_Black_Point[y-5]==187 && Right_Black_Point[y]<=184 && Left_Black_Point[y-1] != 187 )  //左下拐点
//        {
//            findr_x=Right_Black_Point[y];
//            findr_y=y;
//            for(uint8 dircount = 0;dircount<5;dircount++)
//            {
//                examr_x=findr_x+directionrd[dircount][0];
//                examr_y=findr_y+directionrd[dircount][1];
//                if(Emo_imag[examr_y][examr_x]==255)
//                {
//                    examcount++;
//                }
//            }
//            if(examcount>=4)
//            {
//                examcount=0;
//                CrossRight_Down_Point[0]=findr_x;
//                CrossRight_Down_Point[1]=findr_y;
//                CrossRight_Down_Point_finish_flag = 1;
//                break;
//            }
//            else
//            {
//                CrossRight_Down_Point_finish_flag = 0;
//                examcount=0;
//            }
//        }
//        if(Left_Black_Point[y-4]==1 && Left_Black_Point[y-5]==1 && Left_Black_Point[y]>=4 && Right_Black_Point[y-1] != 1)
//        {
//            findl_x=Left_Black_Point[y];
//            findl_y=y;
//            for(uint8 dircount = 0;dircount<5;dircount++)
//            {
//                examl_x=findl_x+directionld[dircount][0];
//                examl_y=findl_y+directionld[dircount][1];
//                if(Emo_imag[examl_y][examl_x]==255)
//                {
//                    examcount++;
//                }
//            }
//            if(examcount>=4)
//            {
//                examcount=0;
//                CrossLeft_Down_Point[0]=findl_x;
//                CrossLeft_Down_Point[1]=findl_y;
//                CrossLeft_Down_Point_finish_flag = 1;
//                break;
//            }
//            else
//            {
//                CrossLeft_Down_Point_finish_flag = 0;
//                examcount=0;
//            }
//        }
//        if(y==15)
//        {
//            CrossLeft_Down_Point_finish_flag = 0;
//            CrossRight_Down_Point_finish_flag = 0;
//            break;
//        }
//    }
//    if(CrossLeft_Down_Point_finish_flag == 1 )
//    {
//        for(uint8 y=15;y<CrossLeft_Down_Point[1];y++)
//        {
//            if(Left_Black_Point[y+7]==1 && Left_Black_Point[y+8]==1 && Left_Black_Point[y]>=4 && Right_Black_Point[y-1] != 1)
//            {
//                findl_x=Left_Black_Point[y];
//                findl_y=y;
//                for(uint8 dircount = 0;dircount<5;dircount++)
//                {
//                    examl_x=findl_x+directionlu[dircount][0];
//                    examl_y=findl_y+directionlu[dircount][1];
//                    if(Emo_imag[examl_y][examl_x]==255)
//                    {
//                        examcount++;
//                    }
//                }
//                if(examcount>=4)
//                {
//                    examcount=0;
//                    CrossLeft_Up_Point[0]=findl_x;
//                    CrossLeft_Up_Point[1]=findl_y;
//                    CrossLeft_Up_Point_finish_flag = 1;
//                    break;
//                }
//                else
//                {
//                    CrossLeft_Up_Point_finish_flag = 0;
//                    examcount=0;
//                }
//            }
//        }
//    }
//    if(CrossRight_Down_Point_finish_flag == 1 )
//    {
//        for(uint8 y = 15 ; y < CrossRight_Down_Point[1] ; y++)
//        {
//            if(Right_Black_Point[y+7]==187 && Right_Black_Point[y+8]==187 && Right_Black_Point[y]<=184 && Left_Black_Point[y-1] != 187 )  //左下拐点
//            {
//                findr_x=Right_Black_Point[y];
//                findr_y=y;
//                for(uint8 dircount = 0;dircount<5;dircount++)
//                {
//                    examr_x=findr_x+directionru[dircount][0];
//                    examr_y=findr_y+directionru[dircount][1];
//                    if(Emo_imag[examr_y][examr_x]==255)
//                    {
//                        examcount++;
//                    }
//                }
//                if(examcount>=4)
//                {
//                    examcount=0;
//                    CrossRight_Up_Point[0]=findr_x;
//                    CrossRight_Up_Point[1]=findr_y;
//                    CrossRight_Up_Point_finish_flag = 1;
//                    break;
//                }
//                else
//                {
//                    CrossRight_Up_Point_finish_flag = 0;
//                    examcount=0;
//                }
//            }
//        }
//    }
//}


//if(V < 6)
//        {
//    //        Pre_Speed = (Speed-35)/(Dec - AIN) * (float)AfterI_Voltage + 35*(Dec - AIN)/(AIN*(Speed - 35));
//    //        if(Real_ChDistance % 100 == 0)
//    //        {
//    //            Pre_Speed = Pre_Speed - 5;
//    //            Pre_Speed = Pre_Speed < 20 ? 20 : Pre_Speed;
//    //            // x1 DEC y1 Speed  x2 AMAX y2 25
//    ////            if(AfterI_Voltage < )
//    ////            {
//    //                //Pre_Speed =25 * (((float)AfterI_Voltage - Dec)/((AMAX-500) - Dec)) + Speed * (((float)AfterI_Voltage - (AMAX-500))/(Dec - (AMAX-200)));
//    ////            }
//    //            //Pre_Speed =25 * (((float)AfterI_Voltage - Dec)/((AIN-Speed) - Dec)) + Speed * (((float)AfterI_Voltage - (AIN-Speed))/(Dec - (AIN-Speed)));
//    //        }
//    //        if(Pre_Speed > 90)
//    //        {
//    //            Pre_Speed = 90;
//    //        }
//            if(Speed >= 25 && Real_ChDistance <= 1000 && Pre_Speed >= 26)
//            {
//                Pre_Speed = Lagrange_interpolation(0.0,Speed,1000.0,25.0,(float)Real_ChDistance);
//                Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
//            }
//            else
//            {
//                Pre_Speed = Pre_Speed > 25 ? 25 : Pre_Speed;
//            }
//            if(LAV >= 1800)
//            {
//                if(Emo_Uint16(AfterI_Voltage,LAV) <= -7)
//                {
//                    Encoderlow_flag = 1;
//                }
//            }
//            if(Real_lowDistance >= (Predistance + lowdistance))
//            {
//                FindCharge_flag = 1;
//                //EncoderCharge_flag = 0;
//                Pre_Speed = 0;
//                Encoderlow_flag = 0;
//            }
//    //        if(Real_ChDistance >= (distance+Predistance+lowdistance))
//    //        {
//    //            FindCharge_flag = 1;
//    //            //EncoderCharge_flag = 0;
//    //            Pre_Speed = 0;
//    //            Encoderlow_flag = 0;
//    ////            EncoderCharge_flag = 1;
//    //        }
//    //        if(AfterI_Voltage < 1130)
//    //        {
//    //            if(Real_ChDistance > (distance+Predistance))
//    //            {
//    //                EncoderCharge_flag = 0;
//    //            }
//    //        }
//        }
//        else if(V >= 6 && V < end_Bat)
//        {
//    //        if(Speed > 90)
//    //        {
//    //            exspeee = 90;
//    //        }
//    //        else
//    //        {
//    //            exspeee = Speed;
//    //        }
//
//            if(Speed >= 70 && Real_ChDistance <= 500 && Pre_Speed >= 71)
//            {
//                Pre_Speed = Lagrange_interpolation(0.0,Speed,500.0,70.0,(float)Real_ChDistance);
//    //            Pre_Speed = Pre_Speed - 5;
//                Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
//                //Speed = 100;
//            }
//    //        else if(Speed >= 110)
//    //        {
//    //            Pre_Speed -= 20;
//    //            Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
//    //        }
//            else
//            {
//                Pre_Speed = Pre_Speed > 70 ? 70 : Pre_Speed;
//            }
//    //        if(Real_ChDistance >= (distance + lowdistance))   //防止计步过冲
//    //        {
//    //            EncoderCharge_SumClear();
//    //            EncoderCharge_flag = 0;
//    //        }
//    //        if(Real_ChDistance <= 1200)
//    //        {
//    //            if(CornerRight_flag == 1 || CornerLeft_flag == 1)
//    //            {
//    //                Coner_Charge = 1;
//    //            }
//    //        }
//            if(LAV >= 1800)
//            {
//    //            if(Coner_Charge == 1)
//    //            {
//    //                if(CS_flag == 1)
//    //                {
//    //                    Pre_Speed = 0;
//    //                    FindCharge_flag = 1;
//    //                    Coner_Charge = 0;
//    //                    CS_flag = 0;
//    //                }
//    //            }
//    //            else
//    //            {
//                if(CS_flag == 1)
//                {
//                    //Encoderlow_flag = 1;   //测停车距离
//                    //EncoderCharge_flag = 1;
//                    Pre_Speed = 0;
//                    FindCharge_flag = 1;
//                    CS_flag = 0;
//                    //Read_AF = 0;
//                    //EncoderCharge_flag = 0;
//                }
//    //            }
//            }
//    //
//    //        if(AfterI_Voltage < 1130)
//    //        {
//    //            if(Real_ChDistance > distance)
//    //            {
//    //                EncoderCharge_flag = 0;
//    //            }
//    //        }
//        }


#endif /* CODE_REMEMBER_H_ */
