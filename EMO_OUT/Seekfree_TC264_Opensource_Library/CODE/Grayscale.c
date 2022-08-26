/*
 * Grayscale.c
 *
 *  Created on: 2022��8��26��
 *      Author: YYM
 */
#include "Grayscale.h"

uint8 Grayscale_imag[120][188];
uint8 Grayscale_Left[120];
uint8 Grayscale_Right[120];
uint8 Grayscale_Middle[120] = {93,93,93,93,93,93,93,93,93,93,93,93,
                               93,93,93,93,93,93,93,93,93,93,93,93,
                               93,93,93,93,93,93,93,93,93,93,93,93,
                               93,93,93,93,93,93,93,93,93,93,93,93,
                               93,93,93,93,93,93,93,93,93,93,93,93,
                               93,93,93,93,93,93,93,93,93,93,93,93,
                               93,93,93,93,93,93,93,93,93,93,93,93,
                               93,93,93,93,93,93,93,93,93,93,93,93,
                               93,93,93,93,93,93,93,93,93,93,93,93,
                               93,93,93,93,93,93,93,93,93,93,93,93};

float math_abs_subcompareplus(uint8 a,uint8 b)
{
//    if(a >= b)
//        return (((float)(a-b))/((float)(a+b)) * 100);
//    else
        return (((float)(a-b))/((float)(a+b)) * 100);
}

void get_grayscaleimag(void)
{
    for(uint8 y=0;y<MT9V03X_H;y++)
    {
        for(uint8 x=0;x<MT9V03X_W;x++)
        {
            Grayscale_imag[y][x] = mt9v03x_image[y][x];
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �Ҷ�����ɨ�ߣ����벻���ƣ�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void get_grayscale_line(void)
{
    uint8 star=93;
    for(int y=119;y>=0;y--)
    {
        for(int x=star;x<188;x++)    //���м����ұ���
        {
            if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x-5]) < RThresholdr
            && math_abs_subcompareplus(Grayscale_imag[y][x-1],Grayscale_imag[y][x-6]) < RThresholdr)
            {
                Grayscale_Right[y] = (uint8)x-2;
                break;
            }
            if(x == 187)
            {
                Grayscale_Right[y] = 187;
                break;
            }
        }
        for(int x=star;x>=0;x--)
        {
            if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x+5]) < LThresholdr
            && math_abs_subcompareplus(Grayscale_imag[y][x+1],Grayscale_imag[y][x+6]) < LThresholdr)
            {
                Grayscale_Left[y] = (uint8)x+2;
                break;
            }
            if(x == 0)
            {
                Grayscale_Left[y] = 0;
                break;
            }
        }
        if(Grayscale_Right[y]==187 && Grayscale_Left[y]==0)        //���߶�û�ҵ���
        {
            Grayscale_Middle[y]=Grayscale_Middle[y+1];
            //star=Middle_Black_Point[y];
        }
        else if(Grayscale_Right[y]==187 && Grayscale_Left[y]!=0)    //����ҵ���
        {
            Grayscale_Middle[y]=Grayscale_Left[y]+Straight[y];
            star=Grayscale_Middle[y];
//            if(CurvatureRight < -0.0045)
//            {
//                kuan = ((y-120)*(y-120)/(20)+93);
//                kuan = kuan > (187-Right_Black_Point[y]) ? (187-Right_Black_Point[y]) : kuan;
//                Middle_Black_Point[y]=Left_Black_Point[y]+kuan;
//            }
        }
        else if(Grayscale_Left[y]==0 && Grayscale_Right[y]!=187)    //�ұ��ҵ���
        {
            Grayscale_Middle[y]=Grayscale_Right[y]-Straight[y];
            star=Grayscale_Middle[y];
//            if(CurvatureRight < -0.0045)
//            {
//                kuan = ((y-120)*(y-120)/(20)+93);
//                kuan = kuan > Right_Black_Point[y] ? Right_Black_Point[y] : kuan;
//                Middle_Black_Point[y]=Right_Black_Point[y]-kuan;
//            }
        }
        else             //���߶��ҵ���
        {
            Grayscale_Middle[y]=(uint8)(((int)Grayscale_Right[y]+(int)Grayscale_Left[y])/2);
            star=Grayscale_Middle[y];
        }
//        Middle_Black_Point[y] = Middle_Black_Point[y] < 1 ? 1 : Middle_Black_Point[y];
//        Middle_Black_Point[y] = Middle_Black_Point[y] > 186 ? 186 : Middle_Black_Point[y];
        Grayscale_Middle[y] = Grayscale_Middle[y] < 1 ? 0 : Grayscale_Middle[y];
        Grayscale_Middle[y] = Grayscale_Middle[y] > 186 ? 187 : Grayscale_Middle[y];
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �Ҷ����ߣ����벻���ƣ�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
unsigned char starrightpoint_findfinish_flag = 0;   //�ұ�����ʼ��Ѱ�����
unsigned char starleftpoint_findfinish_flag = 0;    //�������ʼ��Ѱ�����
unsigned char starrightpoint_findfail_flag = 0;     //�ұ�����ʼ��Ѱ��ʧ��
unsigned char starleftpoint_findfail_flag = 0;      //�������ʼ��Ѱ��ʧ��
uint8 DirRight[120];                                //�ұ��߷��� 0������ɨ�߻�߽� 1-13������ȡ������ҵ���
uint8 DirLeft[120];                                 //����߷��� 0������ɨ�߻�߽� 1-13������ȡ���������
//�Ҷ���ʼ���ߣ�����ʼ����ȡ�߽�
//�ϵ�������

void CrawlLine_Grayscale(void)
{
    int star = 0;//��ʼ������Ѱ��ʼ��
    uint8 star_rx = 0,star_ry = 0;  //�ұ�����ʼ��,������һ�п�ʼ��,������֤�������߽�
    uint8 star_lx = 0,star_ly = 0;  //�������ʼ��,������һ�п�ʼ��,������֤�������߽�
    uint8 Dircount = 0;                                 //�������,�õ���ȡ����

    for(int y=119;y>=40;y--)             //���ұ�����ʼ��
    {
       star = Grayscale_Middle[119] - 5;
       for(int x=star;x<188;x++)
       {
           if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x-5]) < RThresholdr
           && math_abs_subcompareplus(Grayscale_imag[y][x-1],Grayscale_imag[y][x-6]) < RThresholdr)
           {
               if(x <= 177)
               {
                   star_rx = (uint8)x;
                   star_ry = (uint8)y;
                   Grayscale_Right[y] = (uint8)x;
                   DirRight[y] = 0;
                   starrightpoint_findfinish_flag = 1;
               }
               else
               {
                   Grayscale_Right[y] = (uint8)x;
                   DirRight[y] = 0;
               }
               break;
           }
           if(x==187)
           {
               Grayscale_Right[y] = (uint8)x;
               DirRight[y] = 0;
               break;
           }
       }
       if(starrightpoint_findfinish_flag == 1)         //Ϊ�˲������߽籣֤��ʼ���߽�һ������
       {
           break;
       }
    }
    if(starrightpoint_findfinish_flag == 1 && star_rx <= 177)
    {
        for(int y=star_ry-1;y>=0;y--)
        {
            if(starrightpoint_findfail_flag == 0)
            {
                Dircount = 0;
                for(int x=star_rx-8;x<=star_rx+8;x++)
                {
                    Dircount++;
                    if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[star_ry][star_rx]) > RThresholde
                    && math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[star_ry][star_rx]) < -RThresholde
                    && math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x-5]) < RThresholdr
                    && math_abs_subcompareplus(Grayscale_imag[y][x-1],Grayscale_imag[y][x-6]) < RThresholdr)            //�ұ��ߵ㣬�Լ���һ����ʼ��
                    {
                        star_rx = (uint8)x;
                        star_ry = (uint8)y;
                        Grayscale_Right[y] = (uint8)x;
                        DirRight[y] = Dircount;
                        break;
                    }
                    if(x == star_rx+8 && math_abs_subcompareplus(Grayscale_imag[star_ry][star_rx],Grayscale_imag[y-5][x]) < RThresholdr) //�Ҳ�������
                    {
                        starrightpoint_findfail_flag = 1;
                        //Dircount = 0;
                        break;
                    }
                }
            }
            if(starrightpoint_findfail_flag == 1)
            {
//                if(math_abs_subcompareplus(Grayscale_imag[y][star_rx],Grayscale_imag[star_ry][star_rx]) > RThresholde
//                && math_abs_subcompareplus(Grayscale_imag[y][star_rx],Grayscale_imag[star_ry][star_rx]) < -RThresholde)
//                {
                    starrightpoint_findfail_flag = 0;
//                }
                for(int x=star_rx;x<188;x++)
                {
                    if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x-5]) < RThresholdr
                    && math_abs_subcompareplus(Grayscale_imag[y][x-1],Grayscale_imag[y][x-6]) < RThresholdr)
                    {
                        //star_rx = (uint8)x;
                        star_ry = (uint8)y;
                        Grayscale_Right[y] = (uint8)x;
                        DirRight[y] = 0;
                        break;
                    }
                    if(x == 187)
                    {
                        //star_rx = 187;
                        star_ry = (uint8)y;
                        Grayscale_Right[y] = (uint8)x;
                        DirRight[y] = 0;
                        break;
                    }
                }
            }
        }
}
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �Ҷ����ߣ����벻���ƣ�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
///////////////////////////////////////////////////
///////////////////////////////////////////////////
unsigned char FindR_Seed_flag = 0;  //���ӵ�
unsigned char FindL_Seed_flag = 0;
unsigned char FindR_Truncation_flag = 0;   //�ϵ�
unsigned char FindL_Truncation_flag = 0;
unsigned char FindR_Boundary_flag = 0;     //�߽�
unsigned char FindL_Boundary_flag = 0;
unsigned char FindR_All_flag = 0;     //��
unsigned char FindL_All_flag = 0;
uint8 TruncationR = 0;     //Ѱ���ұ߽����ʼ��
uint8 TruncationL = 0;     //Ѱ����߽����ʼ��

void CrawlLine(void)
{
    int star = 0;//��ʼ������Ѱ��ʼ��
    uint8 star_rx = 0,star_ry = 0;  //�ұ�����ʼ��,������һ�п�ʼ��,������֤�������߽�
    uint8 star_lx = 0,star_ly = 0;  //�������ʼ��,������һ�п�ʼ��,������֤�������߽�
    uint8 Dircount = 0;                                 //�������,�õ���ȡ����


    for(int y=119;y>=40;y--)             //���ұ�����ʼ��
    {
        star = Grayscale_Middle[y];
        for(int x=star-5;x<188;x++)
        {
           if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x-5]) < RThresholdr
           && math_abs_subcompareplus(Grayscale_imag[y][x-1],Grayscale_imag[y][x-6]) < RThresholdr)
           {
               if(y >= 112)
               {
                   star_rx = (uint8)x;
                   star_ry = (uint8)y;
                   Grayscale_Right[y] = (uint8)x;
                   DirRight[y] = 0;
                   TruncationR = (uint8)y;
                   FindR_Seed_flag = 1;
                   break;
               }
               else
               {
                   Grayscale_Right[y] = (uint8)x;
                   DirRight[y] = 0;
                   break;
               }
           }
           if(x==187)
           {
               Grayscale_Right[y] = (uint8)x;
               DirRight[y] = 0;
               break;
           }
        }
        if(FindR_Seed_flag == 1)         //Ϊ�˲������߽籣֤��ʼ���߽�һ������
        {
           break;
        }
        for(int x=star+5;x>=0;x--)
        {
            if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x+5]) < LThresholdr
            && math_abs_subcompareplus(Grayscale_imag[y][x+1],Grayscale_imag[y][x+6]) < LThresholdr)
            {
              if(y >= 112)
              {
                  star_lx = (uint8)x;
                  star_ly = (uint8)y;
                  Grayscale_Left[y] = (uint8)x;
                  DirLeft[y] = 0;
                  TruncationL = (uint8)y;
                  FindL_Seed_flag = 1;
                  break;
              }
              else
              {
                  Grayscale_Left[y] = (uint8)x;
                  DirLeft[y] = 0;
                  break;
              }
            }
            if(x==187)
            {
              Grayscale_Left[y] = (uint8)x;
              DirLeft[y] = 0;
              break;
            }
        }
        if(FindL_Seed_flag == 1)         //Ϊ�˲������߽籣֤��ʼ���߽�һ������
        {
           break;
        }
    }
    if(FindR_Seed_flag == 1 && FindR_All_flag == 0 && FindR_Boundary_flag == 0 && FindR_Truncation_flag == 0)
    {
        for(int y=star_ry-1;y>=0;y--)
        {
            Dircount = 0;
            for(int x=star_rx-8;x<=star_rx+8;x++)
            {
                Dircount++;
                if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[star_ly][star_lx]) > RThresholde
                && math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[star_ly][star_lx]) < -RThresholde
                && math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x-5]) < RThresholdr
                && math_abs_subcompareplus(Grayscale_imag[y][x-1],Grayscale_imag[y][x-6]) < RThresholdr)            //�ұ��ߵ㣬�Լ���һ����ʼ��
                {
                    if(y == 0)    //Ѱ����
                    {
                        Grayscale_Right[y] = (uint8)x;
                        DirRight[y] = Dircount;
                        FindR_All_flag = 1;
                        break;
                    }
                    else
                    {
                        star_rx = (uint8)x;
                        star_ry = (uint8)y;
                        Grayscale_Right[y] = (uint8)x;
                        DirRight[y] = Dircount;
                        break;
                    }
                }
                if(x == 187)   //�����߽�
                {
                    DirRight[y] = 0;
                    Grayscale_Right[y] = 187;
                    FindR_Boundary_flag = 1;
                    break;
                }
                if(x == star_rx+8 && math_abs_subcompareplus(Grayscale_imag[star_ry][star_rx],Grayscale_imag[y-5][x]) < RThresholdr) //�����ϵ�
                {
                    Grayscale_Right[y] = 187;
                    DirRight[y] = 0;
                    FindR_Truncation_flag = 1;
                    //Dircount = 0;
                    break;
                }
            }
            if(FindR_Boundary_flag == 1 || FindR_Truncation_flag == 1 || FindR_All_flag == 1)
            {
                break;
            }
        }
    }
    else if(FindL_Seed_flag == 1 && FindL_All_flag == 0 && FindL_Boundary_flag == 0 && FindL_Truncation_flag == 0)
    {
        for(int y=star_ly-1;y>=0;y--)
        {
            Dircount = 0;
            for(int x=star_lx+8;x>=star_lx-8;x--)
            {
                Dircount++;
                if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[star_ly][star_lx]) > RThresholde
                && math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[star_ly][star_lx]) < -RThresholde
                && math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x-5]) < RThresholdr
                && math_abs_subcompareplus(Grayscale_imag[y][x-1],Grayscale_imag[y][x-6]) < RThresholdr)            //�ұ��ߵ㣬�Լ���һ����ʼ��
                {
                    if(y == 0)    //Ѱ����
                    {
                        Grayscale_Left[y] = (uint8)x;
                        DirLeft[y] = Dircount;
                        FindL_All_flag = 1;
                        break;
                    }
                    else
                    {
                        star_lx = (uint8)x;
                        star_ly = (uint8)y;
                        Grayscale_Left[y] = (uint8)x;
                        DirLeft[y] = Dircount;
                        break;
                    }
                }
                if(x == 0)   //�����߽�
                {
                    DirLeft[y] = 0;
                    Grayscale_Left[y] = 0;
                    FindL_Boundary_flag = 1;
                    break;
                }
                if(x == star_lx-8 && math_abs_subcompareplus(Grayscale_imag[star_ly][star_lx],Grayscale_imag[y-5][x]) < RThresholdr) //�����ϵ�
                {
                    Grayscale_Left[y] = 0;
                    DirLeft[y] = 0;
                    FindL_Truncation_flag = 1;
                    //Dircount = 0;
                    break;
                }
            }
            if(FindL_Boundary_flag == 1 || FindL_Truncation_flag == 1 || FindL_All_flag == 1)
            {
                break;
            }
        }
    }
    if(FindR_Boundary_flag == 1 || FindR_Truncation_flag == 1 || FindR_All_flag == 1)
    {
        for(int y = TruncationR;y >= 0;y--)
        {
            for(int x=Grayscale_Right[y]-5;x>=0;x--)
            {
                if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x+5]) < LThresholdr
                && math_abs_subcompareplus(Grayscale_imag[y][x+1],Grayscale_imag[y][x+6]) < LThresholdr)
                {
                  if(y >= 112)
                  {
                      star_lx = (uint8)x;
                      star_ly = (uint8)y;
                      Grayscale_Left[y] = (uint8)x;
                      DirLeft[y] = 0;
                      TruncationL = (uint8)y;
                      FindL_Seed_flag = 1;
                      break;
                  }
                  else
                  {
                      Grayscale_Left[y] = (uint8)x;
                      DirLeft[y] = 0;
                      break;
                  }
                }
                if(x==187)
                {
                    Grayscale_Left[y] = (uint8)x;
                    DirLeft[y] = 0;
                    break;
                }
            }
            if(FindL_Seed_flag == 1)         //Ϊ�˲������߽籣֤��ʼ���߽�һ������
            {
                break;
            }
        }
    }
    else if(FindL_Boundary_flag == 1 || FindL_Truncation_flag == 1 || FindL_All_flag == 1)
    {
        for(int y = TruncationL;y >= 0;y--)
        {
            for(int x=Grayscale_Left[y]+5;x<188;x++)
            {
               if(math_abs_subcompareplus(Grayscale_imag[y][x],Grayscale_imag[y][x-5]) < RThresholdr
               && math_abs_subcompareplus(Grayscale_imag[y][x-1],Grayscale_imag[y][x-6]) < RThresholdr)
               {
                   if(y >= 112)
                   {
                       star_rx = (uint8)x;
                       star_ry = (uint8)y;
                       Grayscale_Right[y] = (uint8)x;
                       DirRight[y] = 0;
                       TruncationR = (uint8)y;
                       FindR_Seed_flag = 1;
                       break;
                   }
                   else
                   {
                       Grayscale_Right[y] = (uint8)x;
                       DirRight[y] = 0;
                       break;
                   }
               }
               if(x==187)
               {
                   Grayscale_Right[y] = (uint8)x;
                   DirRight[y] = 0;
                   break;
               }
            }
            if(FindR_Seed_flag == 1)         //Ϊ�˲������߽籣֤��ʼ���߽�һ������
            {
               break;
            }
        }
    }
    //////////����///////////
    //if()
}


