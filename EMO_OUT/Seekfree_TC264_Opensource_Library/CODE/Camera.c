/*
 * Camera.c
 *
 *  Created on: 2021��11��14��
 *      Author: YYM
 */

#include "Camera.h"
#include "SEEKFREE_MT9V03X.h"

/***********�궨��*************/

/****************����***************/

#pragma section all "cpu1_dsram"
uint8 Emo_imag[120][188];        //����������ͼ��
//vuint8 Img_IPS[120][188];
uint8 OSTU=140;     //�����ֵ
uint8 OUST1 = 0;  //��ֵ��������㲻ͬ���ضԴ����ֵ����
uint8 BoundaryLeft = 0;             //�߽����
uint8 BoundaryRight = 0;
int EmoBlackcount = 0,EmoWhitecount = 0;            //��ֹ�в���
uint8 Endline = 0;                                            //��ֹ��
uint8 Left_Black_Point[120];     //һά�㣨��Сд��
uint8 Right_Black_Point[120];
uint8 Middle_Black_Point[120] = {   93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93};
float CurvatureLeft=0;                  //���ʼ���
float CurvatureRight=0;
unsigned char Corners_flag = 0;              //���ʸ���ر�־
unsigned char CornerRight_flag = 0;   //�����־
unsigned char CornerLeft_flag = 0;
unsigned char Near_CornerLeft_flag = 0;      //���������־
unsigned char Near_CornerRight_flag = 0;
unsigned char Near_Corners_flag = 0;         //�������ʸ���ر�־
unsigned char CornerS_flag = 0;       //S���־
unsigned char Ramp_flag = 0;          //�µ���־
unsigned char RampReady_flag = 0;     //�µ�׼����־
unsigned char Ramp_ON_flag = 0;
int Rampcount = 0;
int RampTime = 0;
//unsigned char Element_Corners_flag=0;           //Ԫ�������־
unsigned char Right_Up_Point_finish_flag = 0;       //�յ��־λ
unsigned char Left_Up_Point_finish_flag = 0;
unsigned char Right_Down_Point_finish_flag = 0;
unsigned char Left_Down_Point_finish_flag = 0;
unsigned char PaddingR = 0;                //����
unsigned char PaddingL = 0;
unsigned char Paddingcurve = 0;            //�����߱�־��1�������� ��0����ֱ��
uint8 Link_Right_One_Point[2];               //���ߵ�
uint8 Link_Right_Two_Point[2];
uint8 Link_Left_One_Point[2];
uint8 Link_Left_Two_Point[2];
uint8 Right_Down_Point[2];                //�յ�   0 : x  1 : y
uint8 Right_Up_Point[2];
uint8 Left_Down_Point[2];
uint8 Left_Up_Point[2];
uint8 Last_Right_Point[2];                //��һ�ιյ㣬�յ���ʱ���ͻȻת�� 0 ��down 1��up
uint8 Last_Left_Point[2];
unsigned char Cross_flag = 0;
int Crosscount = 0;
unsigned char WindupL_flag = 0;                //Ԫ��ǰҡ
unsigned char WindupR_flag = 0;                //Ԫ��ǰҡ
unsigned char GarageR_Findfinish_flag = 0;    //�ҿ�Ѱ�ұ�־ 0��û�ҵ� 1���ҵ���
unsigned char GarageL_Findfinish_flag = 0;    //���Ѱ�ұ�־ 0��û�ҵ� 1���ҵ���
unsigned char GarageR_flag = 0;                //ִ���ҳ��ⲹ�߱�־
unsigned char GarageL_flag = 0;                //ִ���󳵿ⲹ�߱�־
int Garagecount = 0;                           //�����������
int Trialcount = 0;
unsigned char SlalomLeft_flag = 0;             //Slalom��־
int Slalomcount = 0;                 //Slalom�ڲ�����
unsigned char SlalomRight_flag = 0;
unsigned char Slalom_Padding = 0;  //Slalom���߱�־
uint8 Slalom_Point[2];
static unsigned char ObservationS_finish = 0;
static unsigned char CorneringS_finish = 0;
//static unsigned char ObservationC_finish = 0;
//static unsigned char CorneringC_finish = 0;
static unsigned char ObservationT_finish = 0;
static unsigned char CorneringT_finish = 0;
uint8 CircleOut_Point[2];
unsigned char CircleLeft_flag = 0;         //Բ����־
unsigned char CircleRight_flag = 0;
unsigned char CircleBig = 0;           //��Բ����־
unsigned char CircleSwitch_flag = 1;       //Բ�����ر�־ ��0�����رգ�1����������Ĭ��Ϊ����
int Circlecount = 0;                //Բ���ڲ�����
unsigned char Trifork_flag = 0;                        //����
unsigned char Trifork_PointLeft_Findfinish_flag = 0;
unsigned char Trifork_PointRight_Findfinish_flag = 0;
unsigned char Trifork_PointMiddle_Findfinish_flag = 0;
unsigned char Triforkpadding_flag = 0;       //�������߱�־
int Triforkcount = 0;               //�����ڲ����裬����TriforkTurn����������ת������
int TriforkTurn = 0;                //����Ȧ������һ����������ӽ�������ȫͨ��һ��
uint8 TriforkLeft_Point[2];         //�������
uint8 TriforkRight_Point[2];       //�����ҵ�
uint8 TriforkMiddle_Point[2];       //��������
vuint8 IPS_Flag = 0;                    //ͼ������ϱ�־
int findrcount = 0;                     //��¼�յ㵽�߽���룬��������Բ���ͻ�ת
int findlcount = 0;
vuint8 Emo_Index;                          //�����㷨
uint8 Left_Point[120][188],Right_Point[120][188];
int starcount = 0;
unsigned char Gacount = 0;     //��ⲽ��
unsigned char finish = 0;      //������־λ
volatile float Differential_Error = 0;
unsigned char SlC = 0; //P�ּ������򣬰�������������
unsigned char CRC = 0; //Բ���������򣬰����������Է���һ
//unsigned char TRC = 0; //�����������򣬰�������
unsigned char dieReady = 0; //0:�ճ��� 1:���� 2:Բ�� 3:�ػ� 4:���
unsigned char GReady = 0;
uint8 Corners[120] =  { 187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
                        187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
                        187, 187, 187, 187, 187, 187, 187, 179, 157, 137,
                        120, 105, 95, 84, 77, 73, 73, 73, 72, 72,
                        70, 69, 68, 67, 66, 65, 64, 64, 64, 64,
                        65, 65, 65, 66, 66, 66, 67, 67, 68, 68,
                        68, 69, 69, 69, 69, 70, 70, 70, 71, 72,
                        73, 73, 73, 74, 74, 74, 75, 76, 76, 77,
                        77, 78, 78, 78, 79, 79, 80, 80, 81, 81,
                        82, 82, 83, 83, 84, 84, 85, 86, 87, 88,
                        88, 89, 90, 90, 91, 91, 92, 92, 93, 94,
                        94, 95, 95, 95, 96, 97, 98, 98, 99, 99};

uint8 Straight[120] = { 15, 16, 16, 17, 18, 18, 19, 19, 20, 21,
                        21, 22, 22, 23, 24, 24, 25, 25, 26, 26,
                        27, 28, 29, 29, 30, 31, 32, 32, 33, 34,
                        34, 35, 35, 36, 36, 37, 38, 38, 39, 39,
                        40, 41, 41, 42, 42, 43, 44, 44, 45, 45,
                        46, 46, 47, 48, 48, 49, 49, 50, 51, 51,
                        52, 52, 53, 54, 54, 55, 55, 56, 56, 57,
                        58, 58, 59, 59, 60, 61, 61, 62, 62, 63,
                        64, 64, 65, 65, 66, 66, 67, 68, 68, 69,
                        69, 70, 71, 71, 72, 72, 73, 74, 74, 75,
                        75, 76, 76, 77, 78, 78, 79, 79, 80, 81,
                        81, 82, 82, 83, 84, 85, 85, 86, 86, 87};

uint8 Trifork_padding[120] = { 74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74};

#pragma section all restore

/*************���***************/
//copy

#define GrayScale 256

int pixelCount[GrayScale];
float pixelPro[GrayScale];

void Camera_Init(void)       //����ͷ��ʼ��
{
    mt9v03x_init();
}

int Emo_abs(int x)                  //����ֵ
{
    x = x < 0 ? (-x) : x;
    return x;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �޷���8λ��������ľ���ֵ
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     int
//  @note
//-------------------------------------------------------------------------------------------------------------------
int Emo_u8Decabs(uint8 a,uint8 b)    //�޷���8λ���������ֵ
{
    int c = (int)a;
    int d = (int)b;
    if(c>d)
    {
        return c-d;
    }
    else
    {
        return d-c;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �޷���8λ�������
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     int
//  @note
//-------------------------------------------------------------------------------------------------------------------
int Emo_Uint8_dec(uint8 a,uint8 b)   //�޷���8λ�������
{
    int c = 0;
    int d = 0;
    c=(int)a;
    d=(int)b;
    return c-d;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����֮�������֮һ
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     uint8
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8 Emo_one_third(uint8 a, uint8 b)
{
    int c = a;
    int d = b;
    if(c > d)
    {
        return (uint8)(d+((c-d)/3));
    }
    else
    {
        return (uint8)(c+((d-c)/3));
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����֮����ķ�֮һ
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     uint8
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8 Emo_one_fourth(uint8 a, uint8 b)
{
    int c = a;
    int d = b;
    if(c > d)
    {
        return (uint8)(d+((c-d)/4));
    }
    else
    {
        return (uint8)(c+((d-c)/4));
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����֮��İ˷�֮һ
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     uint8
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8 Emo_one_eighth(uint8 a, uint8 b)
{
    int c = a;
    int d = b;
    if(c > d)
    {
        return (uint8)(d+((c-d)/8));
    }
    else
    {
        return (uint8)(c+((d-c)/8));
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����֮�������֮��
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     uint8
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8 Emo_two_third(uint8 a, uint8 b)
{
    int c = a;
    int d = b;
    if(c > d)
    {
        return (uint8)(d+((c-d)*2/3));
    }
    else
    {
        return (uint8)(c+((d-c)*2/3));
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     uint8
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8 Emo_max(uint8 x , uint8 y)
{
    if(x >= y)
        return x;
    else
        return y;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���
//  @param      image  ͼ���ַ
//  @param      width  ͼ�����
//  @param      height ͼ��߶�
//  @param
//  @return     uint8
//  @note       ��ֵ�������ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8 Ostu(uint8 *image, uint16 width, uint16 height)
{

//    uint16 width = col;
//    uint16 height = row;
    uint8 threshold = 0 ;

    int i, j, pixelSum = width * height/4;

    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    uint32 gray_sum=0;
    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //����ǰ�ĵ������ֵ��Ϊ����������±�
            gray_sum+=(int)data[i * width + j];       //�Ҷ�ֵ�ܺ�
        }
    }

    //����ÿ������ֵ�ĵ�������ͼ���еı���

    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;

    }

    //�����Ҷȼ�[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;

    w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
    for (j = 0; j < GrayScale; j++)
    {
            w0 += pixelPro[j];  //��������ÿ���Ҷ�ֵ�����ص���ռ����֮��   ���������ֵı���
            u0tmp += j * pixelPro[j];  //��������       ÿ���Ҷ�ֵ�ĵ�ı��� *�Ҷ�ֵ

            w1=1-w0;
            u1tmp=gray_sum/pixelSum-u0tmp;

            u0 = u0tmp / w0;              //����ƽ���Ҷ�
            u1 = u1tmp / w1;              //ǰ��ƽ���Ҷ�
            u = u0tmp + u1tmp;            //ȫ��ƽ���Ҷ�
            deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
            if (deltaTmp > deltaMax)
            {
                deltaMax = deltaTmp;
                threshold = (uint8)j;
            }
            if (deltaTmp < deltaMax)
            {
                break;
            }
     }
    return threshold;
}

//extern uint8 IPS_Flag;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ֵ��
//  @param      ROUST   ������ֵ���ڱ���
//  @param
//  @param
//  @param
//  @return     void
//  @note       �ڲ�ʹ���˴�򷨣������˰���������ֵ�Ľ��
//-------------------------------------------------------------------------------------------------------------------
void Thresholding(void)   //��ֵ��
{
    //unsigned char Endline_finish = 0;
    OSTU=Ostu(mt9v03x_image[0], 188, 120);
    OUST1 = OSTU;
//    OUST1 = OUST1 > 118 ? 118 : OUST1;
//    OUST1 = OUST1 < 103 ? 103 : OUST1;

    Endline = 0;   //Ѱ�ҵ������ⶥֵ���������Ĺյ�Ѱ�Һ�Ԫ���жϲ����ٴ�ֵ�Ժ����
    for(uint8 y=0;y < 120;y++)
    {
        EmoWhitecount = 0;
        for(uint8 x=0;x<188;x++)
        {
            Emo_imag[y][x] = mt9v03x_image[y][x] < (OUST1 + ROUST) ? EmoBlack : EmoWhite;
            if(Emo_imag[y][x] == EmoWhite)
                EmoWhitecount++;
        }
        if(EmoWhitecount < 30 )
        {
            Endline = y;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����Ѳ����
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��������ɨ�ߵķ�������ͼ����Ͷ˿�ʼ��ÿ��ɨ������һ�����ߣ���һ��ɨ�����һ�����߿�ʼ
//-------------------------------------------------------------------------------------------------------------------
static uint8 star = 93;                             //Ѱ�߳�ʼ��
//���Ż�����ʱ�������������
//////����������Ѱ���б߽���ʹ�Ժ���߶����ڱ߽�
void Get_Line(void)
{
//    float k=0;  //б��
//    float b=0;  //�ؾ�
    //uint8 left=0;
    //int kuan=0;
//    k=((float)xtwo - (float)xone)/((float)ytwo - (float)yone);
//    b=(float)yone - ((float)xone*k);
    BoundaryRight = 0;
    BoundaryLeft = 0;
    if(Middle_Black_Point[119] == 0 || Middle_Black_Point[119] == 187)  //�ж���ʼ���Ƿ���ͼ���м�
    {
        star = 93;
    }
    else
    {
        star = Middle_Black_Point[119];
    }
    for(uint8 y=119;y>=0;y--)
    {
        for(uint8 x=star;x<188;x++)
        {
            if(Emo_imag[y][x]==EmoBlack)  //�ںںڼ��ж�Ϊ����
            {
                if(Emo_imag[y][x+1]==EmoBlack && Emo_imag[y][x+2]==EmoBlack)
                {
                    if(y < Endline )
                        Right_Black_Point[y] = 187;
                    else
                        Right_Black_Point[y]=x;
                    //left=star;
                    break;
                }
            }
            if(x==186)                      //�е����⣬��У����
            {
                Right_Black_Point[y]=187;
                //left=star;
                if(y > Endline && y < 108)
                    BoundaryRight++;
                break;
            }
        }
        for(uint8 x=star;x>=0;x--)
        {
            if(Emo_imag[y][x]==EmoBlack)
            {
                if(Emo_imag[y][x-1]==EmoBlack && Emo_imag[y][x-2]==EmoBlack)
                {
                    if(y < Endline)
                        Left_Black_Point[y] = 0;
                    else
                        Left_Black_Point[y]=x;
                    break;
                }
            }
            if(x==0)
            {
                Left_Black_Point[y]=0;
                if(y > Endline && y < 108)
                    BoundaryLeft++;
                break;
            }
        }
        if(Right_Black_Point[y]==187&&Left_Black_Point[y]==0)        //���߶�û�ҵ���
        {
            Middle_Black_Point[y]=Middle_Black_Point[y+1];
            //star=Middle_Black_Point[y];
            star = 93;
        }
        else if(Right_Black_Point[y]==187&&Left_Black_Point[y]!=0)    //����ҵ���
        {
            Middle_Black_Point[y]=Left_Black_Point[y]+Straight[y];
            star=Middle_Black_Point[y];
//            if(CurvatureRight < -0.0045)
//            {
//                kuan = ((y-120)*(y-120)/(20)+93);
//                kuan = kuan > (187-Right_Black_Point[y]) ? (187-Right_Black_Point[y]) : kuan;
//                Middle_Black_Point[y]=Left_Black_Point[y]+kuan;
//            }
        }
        else if(Left_Black_Point[y]==0&&Right_Black_Point[y]!=187)    //�ұ��ҵ���
        {
            Middle_Black_Point[y]=Right_Black_Point[y]-Straight[y];
            star=Middle_Black_Point[y];
//            if(CurvatureRight < -0.0045)
//            {
//                kuan = ((y-120)*(y-120)/(20)+93);
//                kuan = kuan > Right_Black_Point[y] ? Right_Black_Point[y] : kuan;
//                Middle_Black_Point[y]=Right_Black_Point[y]-kuan;
//            }
        }
        else             //���߶��ҵ���
        {
            Middle_Black_Point[y]=(uint8)(((int)Right_Black_Point[y]+(int)Left_Black_Point[y])/2);
            star=Middle_Black_Point[y];
        }
//        Middle_Black_Point[y] = Middle_Black_Point[y] < 1 ? 1 : Middle_Black_Point[y];
//        Middle_Black_Point[y] = Middle_Black_Point[y] > 186 ? 186 : Middle_Black_Point[y];
        Middle_Black_Point[y] = Middle_Black_Point[y] < 1 ? 0 : Middle_Black_Point[y];
        Middle_Black_Point[y] = Middle_Black_Point[y] >186 ? 187 :Middle_Black_Point[y];
        if(y==0)
            break;
    }
    //star = Middle_Black_Point[119];
}

/*********�ж���������*************/
//Ѱ���߽�ʱ�����ж������Ƿ�Ϊ�����S�䣬�ٽ��йյ�Ѱ��
//�������Ԫ����ʱ���������ж��������ͣ���Ϊʮ�֡���Բ����ȥ������������Զ��������,СSҲ�ڴ˴��ж�
//Զ���ж�����������ж����
//ʹ�������ж������СS
void Judge(void)
{
    uint8 star;
    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    //unsigned char JudgeCorner = 0;    //������ֱ߽絫��������Ͳ�ִ���ж�S��
    //unsigned char JudgeS = 0;         //��ʾִ����S��ȴû�жϳɹ�

    Near_CornerLeft_flag = 0;
    Near_CornerRight_flag = 0;
    Near_Corners_flag = 0;
    //JudgeCorner = 0;
    for(uint8 y=60;y>35;y--)
    {
        if(Right_Black_Point[y-1] == 187 && Right_Black_Point[y-2] == 187 && Right_Black_Point[y-3] == 187
        && Right_Black_Point[y-4] == 187 && Right_Black_Point[y-5] == 187 && Right_Black_Point[y-6] == 187)
        {
            //JudgeCorner = 1;
            star=y;
            for (uint8 y = (star-16); y < star; y++)//�������߽�����ۼӼ���
            {
                if (y % 2 == 0)
                {
                    LeftXSum += Left_Black_Point[y];
                    LeftYSum += y;
                    LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
                    LeftXYSum += y * Left_Black_Point[y];
                }
             }

            if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
            {
                CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
            }
            else
            {
                CurvatureLeft = 0;
            }
            if(CurvatureLeft > (-0.95) && CurvatureLeft < -0.17)
            {
                CornerRight_flag = 1;
                Corners_flag = 1;
                break;
            }
            else
            {
                CornerRight_flag = 0;
                Corners_flag = 0;
                break;
            }
        }
        else
        {
            CornerRight_flag = 0;
            Corners_flag = 0;
        }
        if(Left_Black_Point[y-1] == 0 && Left_Black_Point[y-2] == 0 && Left_Black_Point[y-3] == 0
        && Left_Black_Point[y-4] == 0 && Left_Black_Point[y-5] == 0 && Left_Black_Point[y-6] == 0)
        {
            star=y;
            for (uint8 y = (star-16); y < star; y++)//�������߽�����ۼӼ���
            {
                if (y % 2 == 0)
                {
                    RightXSum += Right_Black_Point[y];
                    RightYSum += y;
                    RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
                    RightXYSum += y * Right_Black_Point[y];
                }
             }
            if(8 * RightXXSum - RightXSum * RightXSum != 0)
            {
                CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
            }
            else
            {
                CurvatureRight = 0;
            }
            if(CurvatureRight < 0.95 && CurvatureRight > 0.17)
            {
                CornerLeft_flag = 1;
                Corners_flag = 1;
                break;
            }
            else
            {
                CornerLeft_flag = 0;
                Corners_flag = 0;
                break;
            }
        }
        else
        {
            CornerLeft_flag = 0;
            Corners_flag = 0;
        }
    }
//    if(CornerRight_flag == 1)
//    {
//        if(Right_Black_Point[100] == 187 && Right_Black_Point[99] == 187 && Right_Black_Point[98] == 187
//            && Left_Black_Point[100] != 0 && Left_Black_Point[99] != 0 && Left_Black_Point[98] != 0
//            && Left_Black_Point[95] != 0 && Left_Black_Point[94] != 187 && Left_Black_Point[93] != 187)
//        {
//            Near_CornerRight_flag = 1;
//            Near_Corners_flag = 1;
//        }
//    }
//    if(CornerLeft_flag == 1)
//    {
//        if(Left_Black_Point[100] == 0 && Left_Black_Point[99] == 0 && Left_Black_Point[98] == 0
//            && Right_Black_Point[100] != 187 && Right_Black_Point[99] != 187 && Right_Black_Point[98] != 187
//            && Right_Black_Point[95] != 187 && Right_Black_Point[94] != 187 && Right_Black_Point[93] != 187)
//        {
//            Near_CornerLeft_flag = 1;
//            Near_Corners_flag = 1;
//        }
//    }
//    if(CornerLeft_flag == 0 && CornerRight_flag == 0 && JudgeCorner == 0 && Near_CornerLeft_flag == 0 && Near_CornerRight_flag == 0)
//    {
//        //JudgeS = 1;      //˵������S��
//        for (uint8 y = 30; y > 14; y--)//�������߽�����ۼӼ���
//        {
//            if (y % 2 == 0)
//            {
//                LeftXSum += Left_Black_Point[y];
//                LeftYSum += y;
//                LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
//                LeftXYSum += y * Left_Black_Point[y];
//
//                RightXSum += Right_Black_Point[y];
//                RightYSum += y;
//                RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
//                RightXYSum += y * Right_Black_Point[y];
//            }
//         }
//
//        if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
//        {
//            CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
//        }
//
//                     //Lintercede = (float)(LeftXXSum * LeftYSum - LeftXSum * LeftXYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
//
//        if(8 * RightXXSum - RightXSum * RightXSum != 0)
//        {
//            CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
//        }
//        if(CurvatureRight < -1.41 && CurvatureLeft < -0.55 && CurvatureLeft > -0.9 && CurvatureRight > -2.0 )
//        {
//            CornerS_flag = 1;
//        }
//        else if( CurvatureRight > 0.46 && CurvatureLeft < 2.2 && CurvatureLeft > 1.5 &&  CurvatureRight < 0.73)
//        {
//            CornerS_flag = 1;
//        }
////        else if(CurvatureRight < 1.12 && CurvatureRight > 0.5 && CurvatureLeft < -0.5 && CurvatureLeft > -1.12)
////        {
////            RampReady_flag = 1;
////        }
//        else
//        {
//            CornerS_flag = 0;
//        }
//    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ж��µ�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ���������ǵĸ������ж��µ�
//-------------------------------------------------------------------------------------------------------------------
void Judge_Ramp(void)  //�ж��µ���������Ԫ��ʱ�����б����������͸�����������
{
//    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
//    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;

    if(CornerLeft_flag == 0 && CornerRight_flag == 0 && Corners_flag == 0
    && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 0
    && WindupL_flag == 0 && WindupR_flag == 0
    && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0
    && GarageL_flag == 0 && GarageR_flag == 0 && Cross_flag == 0 && Trifork_flag == 0
    && Left_Black_Point[20] != 0 && Left_Black_Point[40] != 0 && Left_Black_Point[60] != 0 && Left_Black_Point[80] != 0
    && Right_Black_Point[20] != 187 && Right_Black_Point[40] != 187 && Right_Black_Point[60] != 187 && Right_Black_Point[80] != 187
    && RampReady_flag == 0 && CornerS_flag == 0)
    {
        GyroscopePitch_Star_flag = 1;
//        if(Emo_Pitch <= -5.7)
//        {
//            Ramp_flag = 1;
//        }
    }
    else
    {
//        if(CornerS_flag == 1)
//        {
//            GyroscopePitch_Star_flag = 0;
//        }
        if(Ramp_flag == 1)
        {
            GyroscopePitch_Star_flag = 1;
        }
        else
        {
            GyroscopePitch_Star_flag = 0;
        }
    }
    if(Ramp_flag == 1)
    {
        EncoderRamp_flag = 1;
        if(Real_RaDistance > 5000)
        {
            Ramp_flag = 0;
            GyroscopePitch_Star_flag = 0;
            RampReady_flag = 1;
            EncoderRamp_SumClear();
        }
        if(Emo_Pitch >= 2)
        {
            Ramp_flag = 0;
            GyroscopePitch_Star_flag = 0;
            RampReady_flag = 1;
            EncoderRamp_SumClear();
        }
    }
//    if(CornerS_flag == 1)
//    {
//        Judge_CornerS();
//    }
    if(RampReady_flag == 1)
    {
        EncoderRamp_flag = 1;
        if(Real_RaDistance >= 10000)
        {
            RampReady_flag = 0;
            EncoderRamp_flag = 0;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ж��µ�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ���������ǵĸ������ж��µ�
//-------------------------------------------------------------------------------------------------------------------
void TJudge_Ramp(void)
{
//    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
//    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    uint8 star;
    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;

    if(CornerLeft_flag == 0 && CornerRight_flag == 0
    && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 0
    && WindupL_flag == 0 && WindupR_flag == 0
    && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0
    && GarageL_flag == 0 && GarageR_flag == 0 && Cross_flag == 0
    && Left_Black_Point[20] != 0 && Left_Black_Point[40] != 0 && Left_Black_Point[60] != 0 && Left_Black_Point[80] != 0
    && Right_Black_Point[20] != 187 && Right_Black_Point[40] != 187 && Right_Black_Point[60] != 187 && Right_Black_Point[80] != 187
    && RampReady_flag == 0 && CornerS_flag == 0)
    {
        GyroscopePitch_Star_flag = 1;
        if(Emo_Pitch <= -5.7)
        {
            Ramp_flag = 1;
        }
    }
    else
    {
        if(Ramp_flag == 1)
        {
            GyroscopePitch_Star_flag = 1;
        }
        else
        {
            GyroscopePitch_Star_flag = 0;
        }
    }
//    if(CornerS_flag == 1)
//   {
//       Judge_CornerS();
//   }
    if(Ramp_flag == 1)
    {
        EncoderRamp_flag = 1;
        if(Real_RaDistance > 5000)
        {
            Ramp_flag = 0;
            GyroscopePitch_Star_flag = 0;
            RampReady_flag = 1;
            EncoderRamp_SumClear();
        }
        //GyroscopePitch_Star_flag = 1;
        if(Emo_Pitch >= 2)
        {
            Ramp_flag = 0;
            GyroscopePitch_Star_flag = 0;
            RampReady_flag = 1;
        }
    }
    if(RampReady_flag == 1)
    {
        EncoderRamp_flag = 1;
        if(Real_RaDistance >= 10000)
        {
            RampReady_flag = 0;
            EncoderRamp_flag = 0;
        }
    }
    if(MODE == 2 || MODE == 3 || MODE == 1)
    {
        for(uint8 y=67;y>20;y--)
        {
            if(Right_Black_Point[y-1] == 187 && Right_Black_Point[y-2] == 187 && Right_Black_Point[y-3] == 187)
            {
                //JudgeCorner = 1;
                star=y;
                for (uint8 y = (star-16); y < star; y++)//�������߽�����ۼӼ���
                {
                    if (y % 2 == 0)
                    {
                        LeftXSum += Left_Black_Point[y];
                        LeftYSum += y;
                        LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
                        LeftXYSum += y * Left_Black_Point[y];
                    }
                 }

                if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
                {
                    CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
                }
                else
                {
                    CurvatureLeft = 0;
                }
                if(CurvatureLeft > (-0.95) && CurvatureLeft < -0.17)
                {
                    need_cornerR = 1;

                    break;
                }
                else
                {
                    need_cornerR = 0;
                    break;
                }
            }
            else
            {
                need_cornerR = 0;
            }
            if(Left_Black_Point[y-1] == 0 && Left_Black_Point[y-2] == 0 && Left_Black_Point[y-3] == 0)
            {
                star=y;
                for (uint8 y = (star-16); y < star; y++)//�������߽�����ۼӼ���
                {
                    if (y % 2 == 0)
                    {
                        RightXSum += Right_Black_Point[y];
                        RightYSum += y;
                        RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
                        RightXYSum += y * Right_Black_Point[y];
                    }
                 }
                if(8 * RightXXSum - RightXSum * RightXSum != 0)
                {
                    CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
                }
                else
                {
                    CurvatureRight = 0;
                }
                if(CurvatureRight < 0.95 && CurvatureRight > 0.17)
                {
                    need_cornerL = 1;
                    break;
                }
                else
                {
                    need_cornerL = 0;
                    break;
                }
            }
            else
            {
                need_cornerL = 0;
            }
        }
    }

}

//void Judge_Ramp(void)
//{
//    if(RampReady_flag == 1)
//    {
//        Beepindex = Beepon;
//        GyroscopePitch_Star_flag = 1;
//        RampTime++;
//        if(RampTime < 150 && Emo_Pitch > 8 && Rampcount == 0)
//        {
//            Rampcount = 1;
//            Ramp_flag = 1;
//        }
//        else if(RampTime >= 150 && Rampcount == 0)
//        {
//            RampTime = 0;
//            RampReady_flag = 0;
//            GyroscopePitch_Star_flag = 0;
//            Beepindex = 0;
//        }
//        if(Rampcount == 1)
//        {
//            if(Emo_Pitch < -2 && RampTime < 600)
//            {
//                RampTime = 0;
//                Ramp_flag = 0;
//                RampReady_flag = 0;
//                GyroscopePitch_Star_flag = 0;
//                Beepindex = 0;
//            }
//            else if(RampTime > 600)
//            {
//                RampTime = 0;
//                Ramp_flag = 0;
//                RampReady_flag = 0;
//                GyroscopePitch_Star_flag = 0;
//                Beepindex = 0;
//            }
//        }
//    }
//}
//


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��С���˷��������Իع鷽��
//  @param      n   ��ϲ��������
//  @param
//  @param
//  @param
//  @return     void
//  @note       �����ж�СS��������ֱ��
//-------------------------------------------------------------------------------------------------------------------
void leastSquares(uint8 n)
{
    double kR, bR,kL,bL; //y=k*x+b
    double x_averageR = 0.0, y_averageR = 0.0,x_averageL = 0.0,y_averageL = 0.0;
    double xy_sumR = 0.0, x2_sumR = 0.0 , xy_sumL = 0.0 , x2_sumL = 0.0;
    for (uint8 y = 20; y < n; y++)
    {
        x_averageR += Right_Black_Point[y];
        y_averageR += y;
        xy_sumR += Right_Black_Point[y] * y;
        x2_sumR += Right_Black_Point[y] * Right_Black_Point[y];
        x_averageL += Left_Black_Point[y];
        y_averageL += y;
        xy_sumL += Left_Black_Point[y] * y;
        x2_sumL += Left_Black_Point[y] * Left_Black_Point[y];
    }
    x_averageR /= n;
    y_averageR /= n;
    x_averageL /= n;
    y_averageL /= n;
    kR = (xy_sumR - n * x_averageR * y_averageR) / (x2_sumR - n * x_averageR * x_averageR);
    bR = y_averageR - kR * x_averageR;
    kL = (xy_sumL - n * x_averageL * y_averageL) / (x2_sumL - n * x_averageL * x_averageL);
    bL = y_averageL - kL * x_averageL;

    for(uint8 y = 0; y < n; y++)
    {
        Right_Black_Point[y]=(uint8)(((float)y-bR)/kR);
        Left_Black_Point[y]=(uint8)(((float)y-bL)/kL);
    }
}

//���ڽ���СS��
void Judge_CornerS(void)
{
    if(CornerS_flag == 1)
    {
        for(uint8 y=35;y>20;y--)
        {
            if((Right_Black_Point[y-1] == 187 && Right_Black_Point[y-2] == 187 && Right_Black_Point[y-3] == 187) || (Left_Black_Point[y-1] == 0 && Left_Black_Point[y-2] == 0 && Left_Black_Point[y-3] == 0))
            {
                PaddingR = 0;
                PaddingL = 0;
                CornerS_flag = 0;
                break;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �յ�Ѱ��
//  @param      findlcount   �յ���붪�ߵ������������жϴ�СԲ����������P�ֺ�Բ��
//  @param
//  @param
//  @param
//  @return     void
//  @note       ����5�����ԭ��Ѱ�ҹյ㣬�¹յ��ͼ��Ͷ�����ɨ���Ϲյ��ͼ���Ϸ�����ɨ������ɨ�߻��ڰ����߳������⣬
//-------------------------------------------------------------------------------------------------------------------
void Identify(void)
{
    uint8 findr_x = 0;    //�ҵ�
    uint8 findr_y = 0;
    uint8 examr_x = 0;
    uint8 examr_y = 0;
    uint8 findl_x = 0;    //���
    uint8 findl_y = 0;
    uint8 examl_x = 0;
    uint8 examl_y = 0;
    uint8 star = 0;
    uint8 end = 0;
    uint8 examcount = 0;
    //uint8 count;
    //uint8 examerror;
//    uint8 dircount;
    int directionrd[5][2] =  {{-1,1}, {-1,0}, {-1,-1}, {0,1}, {1,1}};  //˳ʱ���·���������x��y
    int directionld[5][2] =  {{1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};  //��ʱ���·�������
    int directionru[5][2] =  {{1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}};  //��ʱ���Ϸ�������
    int directionlu[5][2] =  {{-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}};  //��ʱ���Ϸ�������

    //ÿ�βɼ��󶼶Թյ��־λ����
    if(Right_Up_Point_finish_flag == 1)
        Right_Up_Point_finish_flag = 0;
    if(Left_Up_Point_finish_flag == 1)
        Left_Up_Point_finish_flag = 0;
    if(Right_Down_Point_finish_flag == 1)
        Right_Down_Point_finish_flag = 0;
    if(Left_Down_Point_finish_flag == 1)
        Left_Down_Point_finish_flag = 0;
    for(uint8 y = 105 ; y >= 30 ; y--)
    {
        if(Right_Down_Point_finish_flag == 0)
        {
            if(y > Endline && Right_Black_Point[y-1]==187 && Right_Black_Point[y-2]==187 && Emo_imag[y][Right_Black_Point[y]-6] == EmoWhite
               && y > Endline && Emo_imag[y-2][Right_Black_Point[y]] == EmoWhite && Emo_imag[y-5][Right_Black_Point[y]] == EmoWhite)    //���¹յ�
            {
                star=y;
                for(uint8 y=star;y<=(star+18);y++)
                {
                    if(Right_Black_Point[y]<184 && Emo_abs(Right_Black_Point[y+1]-Right_Black_Point[y])<3
                    && Emo_abs(Right_Black_Point[y+2]-Right_Black_Point[y])<4)
                    {
                        findr_x=Right_Black_Point[y];
                        findr_y=y;
                        for(uint8 dircount = 0;dircount<5;dircount++)
                        {
                            examr_x=findr_x+directionrd[dircount][0];
                            examr_y=findr_y+directionrd[dircount][1];
                            if(Emo_imag[examr_y][examr_x]==255)
                            {
                                examcount++;
                            }
                        }
                        if(examcount >= 4)
                        {
                            examcount=0;
                            Right_Down_Point[0]=findr_x;
                            Right_Down_Point[1]=findr_y;
//                            if(Last_Right_Point[0] == 0)
//                            {
//                                Last_Right_Point[0] = Right_Down_Point[1];
//                            }
//                            if(Emo_Uint8_dec(Right_Down_Point[1],Last_Right_Point[0]) < -15)
//                            {
//                                Right_Down_Point_finish_flag = 0;
//                            }
//                            else
//                            {
                                Right_Down_Point_finish_flag = 1;
//                                Last_Right_Point[0] = Right_Down_Point[1];
//                            }
    //                        findrcount = (int)y-(int)star;
                            break;
                        }
                        else
                        {
                            Right_Down_Point_finish_flag = 0;
                            examcount=0;
                        }
                    }
                    if(y==100)
                    {
                        Right_Down_Point_finish_flag=0;
                    }
                }
            }
        }
        if(Left_Down_Point_finish_flag == 0)
        {
            if(y > Endline && Left_Black_Point[y-1]==0 && Left_Black_Point[y-2]==0 && Emo_imag[y][Left_Black_Point[y]+6] == EmoWhite
               && y > Endline && Emo_imag[y-2][Left_Black_Point[y]] == EmoWhite && Emo_imag[y-5][Left_Black_Point[y]] == EmoWhite)     //���¹յ�
            {
                star=y;
                for(uint8 y=star;y<=(star+18);y++)
                {
                    if(Left_Black_Point[y]>4 && Emo_abs(Left_Black_Point[y+1]-Left_Black_Point[y])<3
                       && Emo_abs(Left_Black_Point[y+2]-Left_Black_Point[y])<4)
                    {
                        findl_x=Left_Black_Point[y];
                        findl_y=y;
                        for(uint8 dircount = 0;dircount<5;dircount++)
                        {
                            examl_x=findl_x+directionld[dircount][0];
                            examl_y=findl_y+directionld[dircount][1];
                            if(Emo_imag[examl_y][examl_x]==255)
                            {
                                examcount++;
                            }
                        }
                        if(examcount>=4 )
                        {
                            examcount=0;
                            Left_Down_Point[0]=findl_x;
                            Left_Down_Point[1]=findl_y;
//                            if(Last_Left_Point[0] == 0)
//                            {
//                                Last_Left_Point[0] = Left_Down_Point[1];
//                            }
//                            if(Emo_Uint8_dec(Left_Down_Point[1],Last_Left_Point[0]) < -15)
//                            {
//                                Left_Down_Point_finish_flag = 0;
//                            }
//                            else
//                            {
                                Left_Down_Point_finish_flag = 1;
//                                Last_Left_Point[0] = Left_Down_Point[1];
//                            }
    //                        findlcount = y-star;
                            break;
                        }
                        else
                        {
                            Left_Down_Point_finish_flag = 0;
                            examcount=0;
                        }
                    }
                    if(y==100)
                    {
                        Left_Down_Point_finish_flag=0;
                    }
                }
            }
        }
//        if(CrossLeft_Down_Point_finish_flag==1 && CrossRight_Down_Point_finish_flag==1)
//        {
//            break;
//        }
    }
    if(Left_Down_Point_finish_flag==1 && Right_Down_Point_finish_flag==1)
        end=Right_Down_Point[1];
    else if(Left_Down_Point_finish_flag==1)
        end=Left_Down_Point[1];
    else if(Right_Down_Point_finish_flag==1)
        end=Right_Down_Point[1];
    else
        end=94;
    for(uint8 y=20;y<=end;y++)
    {
        if(Right_Up_Point_finish_flag == 0)
        {
            if(y > Endline && Right_Black_Point[y+1]==187 && Right_Black_Point[y+2]==187 && Right_Black_Point[y+3]==187)   //���Ϲյ�
            {
               star=y;
               for(uint8 y=star;y>=(star-22);y--)
               {
                   if(Right_Black_Point[y]<180 && Emo_abs(Right_Black_Point[y-1]-Right_Black_Point[y])<4
                   && Emo_abs(Right_Black_Point[y-2]-Right_Black_Point[y])<4 && Emo_imag[y][Right_Black_Point[y]-6] == EmoWhite
                   && Emo_imag[y-1][Right_Black_Point[y-1]-5] == EmoWhite && Emo_imag[y-2][Right_Black_Point[y]-5] == EmoWhite
                   && Emo_imag[y-3][Right_Black_Point[y]-5] == EmoWhite && Right_Black_Point[y] > Middle_Black_Point[y] && Emo_imag[y+3][Right_Black_Point[y]] == EmoWhite
                   && Emo_imag[y+5][Right_Black_Point[y]] == EmoWhite && Emo_imag[y+7][Right_Black_Point[y]] == EmoWhite)
                   {
                       findr_x=Right_Black_Point[y];
                       findr_y=y;
                       for(uint8 dircount = 0;dircount<5;dircount++)
                       {
                           examr_x=findr_x+directionru[dircount][0];
                           examr_y=findr_y+directionru[dircount][1];
                           if(Emo_imag[examr_y][examr_x]==255)
                           {
                               examcount++;
                           }
                       }
                       if(examcount>=4 && findr_y >Endline)
                       {
                           examcount=0;
                           Right_Up_Point[0]=findr_x;
                           Right_Up_Point[1]=findr_y;
                           if(Last_Right_Point[1] == 0)
                           {
                               Last_Right_Point[1] = Right_Up_Point[1];
                           }
                           if(Right_Up_Point[1] < 16)
                           {
                               Right_Up_Point[1] = Last_Right_Point[1];
                               Right_Up_Point_finish_flag = 0;
                           }
                           else
                           {
                               Right_Up_Point_finish_flag = 1;
                               Last_Right_Point[1] = Right_Up_Point[1];
                           }
                           findrcount=(int)star-(int)findr_y;
                           break;
                       }
                       else
                       {
                           Right_Up_Point_finish_flag = 0;
                           examcount=0;
                       }
                   }
                   if(y==16)
                   {
                       Right_Up_Point_finish_flag=0;
                       break;
                   }
                   if(y == 1)
                   {
                       break;
                   }
               }
            }
        }
        if(Left_Up_Point_finish_flag == 0)
        {
            if(y > Endline && Left_Black_Point[y+1]==0 && Left_Black_Point[y+2]==0 && Left_Black_Point[y+3]==0)     //���Ϲյ�
            {
                star=y;
                for(uint8 y=star;y>=(star-22);y--)
                {
                    if(Left_Black_Point[y]>8 && Emo_abs(Left_Black_Point[y-1]-Left_Black_Point[y])<4
                   && Emo_abs(Left_Black_Point[y-2]-Left_Black_Point[y])<4 && Emo_imag[y][Left_Black_Point[y]+6] == EmoWhite
                   && Emo_imag[y-1][Left_Black_Point[y-1]+5] == EmoWhite && Emo_imag[y-2][Left_Black_Point[y]+5] == EmoWhite
                   && Emo_imag[y-3][Left_Black_Point[y]+5] == EmoWhite && Left_Black_Point[y] < Middle_Black_Point[y] && Emo_imag[y+3][Left_Black_Point[y]] == EmoWhite
                   && Emo_imag[y+5][Left_Black_Point[y]] == EmoWhite && Emo_imag[y+7][Left_Black_Point[y]] == EmoWhite)
                    {
                        findl_x=Left_Black_Point[y];
                        findl_y=y;
                        for(uint8 dircount = 0;dircount<5;dircount++)
                        {
                            examl_x=findl_x+directionlu[dircount][0];
                            examl_y=findl_y+directionlu[dircount][1];
                            if(Emo_imag[examl_y][examl_x]==255)
                            {
                                examcount++;
                            }
                        }
                        if(examcount>=4 && findl_y > Endline)
                        {
                            examcount=0;
                            Left_Up_Point[0]=findl_x;
                            Left_Up_Point[1]=findl_y;
                            if(Last_Left_Point[1] == 0)
                            {
                                Last_Left_Point[1] = Left_Up_Point[1];
                            }
                            if(Left_Up_Point[1] < 16)
                            {
                                Left_Up_Point[1] = Last_Left_Point[1];
                                Left_Up_Point_finish_flag = 0;
                            }
                            else
                            {
                                Left_Up_Point_finish_flag = 1;
                                Last_Left_Point[1] = Left_Up_Point[1];
                            }
                            findlcount=(int)star-(int)y;
                            break;
                        }
                        else
                        {
                            Left_Up_Point_finish_flag = 0;
                            examcount=0;
                        }
                    }
                    if(y==16)
                    {
                        Left_Up_Point_finish_flag=0;
                        break;
                    }
                    if(y == 1)
                    {
                        break;
                    }
                }
            }
        }
    }

}

//void Element_stipulate(void) //Ԫ��д�������ڹ���
//{
//    if(TriforkTurn == 0 && SlC == 0 && CRC == 0)
//    {
//        dieReady = 1;
//    }
//    else if(TriforkTurn == 1 && SlC == 0 && CRC == 0)
//    {
//        dieReady = 2;
//    }
//    else if(TriforkTurn == 1 && SlC == 0 && CRC == 1)
//    {
//        dieReady = 3;
//    }
//    else if(TriforkTurn == 1 && SlC == 1 && CRC == 1)
//    {
//        dieReady = 2;
//    }
//    else if(TriforkTurn == 1 && SlC == 1 && CRC == 2)
//    {
//        dieReady = 1;
//    }
//    else if(TriforkTurn == 2 && SlC == 1 && CRC == 2)
//    {
//        dieReady = 3;
//    }
//    else if(TriforkTurn == 2 && SlC == 2 && CRC == 2)
//    {
//        dieReady = 1;
//        GReady = 1;
//    }
//    else if(TriforkTurn == 3 && SlC == 2 && CRC == 2)
//    {
//        GReady = 0;
//        dieReady = 2;
//    }
//    else if(TriforkTurn == 3 && SlC == 2 && CRC == 3)
//    {
//        dieReady = 3;
//    }
//    else if(TriforkTurn == 3 && SlC == 3 && CRC == 3)
//    {
//        dieReady = 2;
//    }
//    else if(TriforkTurn == 3 && SlC == 3 && CRC == 4)
//    {
//        dieReady = 1;
//    }
//    else if(TriforkTurn == 4 && SlC == 3 && CRC == 4)
//    {
//        dieReady = 4;
//        GReady = 1;
//    }
//}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ж�����
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Trifork_Judge(void)
{
//    unsigned char Trifork_Left = 0;
//    unsigned char Trifork_Right = 0;

//    uint8 Trifork_y = 0;
//    uint8 Trifork_x = 0;
    int stop_left = 0;
    int stop_right = 0;
    uint8 Middle_x = 0;
    uint8 Middle_y = 0;


//    Trifork_Right = 0;
//    Trifork_Left = 0;
    stop_left = 0;
    stop_right = 0;
    Trifork_PointLeft_Findfinish_flag = 0;
    Trifork_PointRight_Findfinish_flag = 0;
    Trifork_PointMiddle_Findfinish_flag = 0;
    for(uint8 y=100;y>30;y--)
    {
        if(Trifork_PointLeft_Findfinish_flag == 0)
        {
            if((Left_Black_Point[y]-Left_Black_Point[y+1] >= 0) && (Left_Black_Point[y]-Left_Black_Point[y-1] >= 0)
            && (Left_Black_Point[y]-Left_Black_Point[y+2] >= 0) && (Left_Black_Point[y]-Left_Black_Point[y-2] >= 0)
            && (Left_Black_Point[y]-Left_Black_Point[y+3] >= 0) && (Left_Black_Point[y]-Left_Black_Point[y-3] >= 0)
            && (Left_Black_Point[y]-Left_Black_Point[y+4] > 0 ) && (Left_Black_Point[y]-Left_Black_Point[y-4] > 0)
            && (Left_Black_Point[y]-Left_Black_Point[y+4] < 10) && (Left_Black_Point[y]-Left_Black_Point[y-4] < 10)
            && (Left_Black_Point[y]-Left_Black_Point[y+5] >= 1) && (Left_Black_Point[y]-Left_Black_Point[y-5] >= 1)
            && (Left_Black_Point[y]-Left_Black_Point[y+6] >= 1) && (Left_Black_Point[y]-Left_Black_Point[y-6] >= 1)
            && (Left_Black_Point[y]-Left_Black_Point[y+7] > 1) && (Left_Black_Point[y]-Left_Black_Point[y-7] > 1))
            {
                //Trifork_Left = 1;
                stop_left = y;
                Trifork_PointLeft_Findfinish_flag = 1;
                TriforkLeft_Point[0] = Left_Black_Point[y];
                TriforkLeft_Point[1] = y;
            }
            else
            {
                Trifork_PointLeft_Findfinish_flag = 0;
            }
        }
        if(Trifork_PointRight_Findfinish_flag == 0)
        {
            if((Right_Black_Point[y+1]-Right_Black_Point[y] >= 0) && (Right_Black_Point[y-1]-Right_Black_Point[y] >= 0)
            && (Right_Black_Point[y+2]-Right_Black_Point[y] >= 0) && (Right_Black_Point[y-2]-Right_Black_Point[y] >= 0)
            && (Right_Black_Point[y+3]-Right_Black_Point[y] >= 0) && (Right_Black_Point[y-3]-Right_Black_Point[y] >= 0)
            && (Right_Black_Point[y+4]-Right_Black_Point[y] >= 0) && (Right_Black_Point[y-4]-Right_Black_Point[y] >= 0)
            && (Right_Black_Point[y+4]-Right_Black_Point[y] < 10) && (Right_Black_Point[y-4]-Right_Black_Point[y] < 10)
            && (Right_Black_Point[y+5]-Right_Black_Point[y] >= 1) && (Right_Black_Point[y-5]-Right_Black_Point[y] >= 1)
            && (Right_Black_Point[y+6]-Right_Black_Point[y] >= 1) && (Right_Black_Point[y-6]-Right_Black_Point[y] >= 1)
            && (Right_Black_Point[y+7]-Right_Black_Point[y] > 1) && (Right_Black_Point[y-7]-Right_Black_Point[y] > 1))
            {
                //Trifork_Right = 1;
                stop_right = y;
                Trifork_PointRight_Findfinish_flag = 1;
                TriforkRight_Point[0] = Right_Black_Point[y];
                TriforkRight_Point[1] = y;
            }
            else
            {
                Trifork_PointRight_Findfinish_flag = 0;
            }
        }
        if(Trifork_PointRight_Findfinish_flag == 1 && Trifork_PointLeft_Findfinish_flag == 1)
        {
            if(Emo_abs((int)stop_left - (int)stop_right) <= 24 &&
                   (Right_Black_Point[TriforkRight_Point[1] + 3] - Left_Black_Point[TriforkLeft_Point[1] + 3]) > (Right_Black_Point[TriforkRight_Point[1]] - Left_Black_Point[TriforkLeft_Point[1]])
                && (Right_Black_Point[TriforkRight_Point[1] - 3] - Left_Black_Point[TriforkLeft_Point[1] - 3]) > (Right_Black_Point[TriforkRight_Point[1]] - Left_Black_Point[TriforkLeft_Point[1]])
                && (Right_Black_Point[TriforkRight_Point[1] + 5] - Left_Black_Point[TriforkLeft_Point[1] + 5]) > (Right_Black_Point[TriforkRight_Point[1]] - Left_Black_Point[TriforkLeft_Point[1]])
                && (Right_Black_Point[TriforkRight_Point[1] - 5] - Left_Black_Point[TriforkLeft_Point[1] - 5]) > (Right_Black_Point[TriforkRight_Point[1]] - Left_Black_Point[TriforkLeft_Point[1]]))
            {
                break;
            }
            else
            {
                Trifork_PointLeft_Findfinish_flag = 0;
                Trifork_PointRight_Findfinish_flag = 0;
                break;
            }
        }
    }
//    if(Emo_abs((int)stop_left - (int)stop_right) > 14)
//    {
//        Trifork_PointRight_Findfinish_flag = 0;
//        Trifork_PointLeft_Findfinish_flag = 0;
//    }
    if(Trifork_PointRight_Findfinish_flag == 1 || Trifork_PointLeft_Findfinish_flag == 1)
    {
        Middle_x = (uint8)(((int)TriforkLeft_Point[0]+(int)TriforkRight_Point[0])/2);
        Middle_y = Emo_max(TriforkLeft_Point[1],TriforkRight_Point[1]);
        for(uint8 y=Middle_y-5 ; y > 10 ; y--)
        {
            if(Emo_imag[y][Middle_x] == EmoBlack && Emo_imag[y+1][Middle_x] == EmoWhite && Emo_imag[y-1][Middle_x] == EmoBlack && Emo_imag[y-2][Middle_x] == EmoBlack && Emo_imag[y+2][Middle_x] == EmoWhite)
            {
                TriforkMiddle_Point[0] = Middle_x;
                TriforkMiddle_Point[1] = y;
                Trifork_PointMiddle_Findfinish_flag = 1;
                break;
            }
            else
                Trifork_PointMiddle_Findfinish_flag = 0;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���涥��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Trifork_MIddlePoint(void)
{
    //Trifork_PointLeft_Findfinish_flag = 0;
    //Trifork_PointRight_Findfinish_flag = 0;
    Trifork_PointMiddle_Findfinish_flag = 0;
    for(int y=TriforkMiddle_Point[1];y<105;y++)
    {
        for(int x=30;x<158;x++)
        {
            if(Emo_imag[y][x] == EmoBlack && Emo_imag[y+1][x] == EmoWhite && Emo_imag[y+1][x+1] == EmoWhite && Emo_imag[y+1][x+2] == EmoWhite && Emo_imag[y+1][x+5] == EmoWhite && Emo_imag[y-1][x] == EmoBlack )
            {
                TriforkMiddle_Point[0] = (uint8)x;
                TriforkMiddle_Point[1] = (uint8)y;
                Trifork_PointMiddle_Findfinish_flag = 1;
                break;
            }
            if(Emo_imag[y][x] == EmoBlack && Emo_imag[y+1][x] != EmoWhite && Emo_imag[y+1][x+1] != EmoWhite && Emo_imag[y+1][x+2] != EmoWhite && Emo_imag[y+1][x+5] != EmoWhite && Emo_imag[y-1][x] == EmoBlack)
            {
                break;
            }
        }
        if(Trifork_PointMiddle_Findfinish_flag == 1)
        {
            break;
        }
    }

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ҳ���Ѱ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void GarageR_Find(void)
{
    uint8 Blackonefind = 0,Blackone = 0;
    uint8 Whiteonefind = 0,Whiteone = 0;
    uint8 Blacktwofind = 0;

    for(uint8 y=Emo_one_eighth(Right_Down_Point[1],Right_Up_Point[1]);y<=Emo_two_third(Right_Down_Point[1],Right_Up_Point[1]);y++)
    {
        if(Emo_imag[y][Right_Down_Point[0]] == EmoWhite)
        {
            for(uint8 x=Right_Down_Point[0];x>(Left_Black_Point[Right_Up_Point[1]]+10);x--)
            {
                if(Emo_imag[y][x] == EmoBlack && Emo_imag[y][x-1] == EmoBlack)
                {
                    Blackonefind = 1;
                    Blackone = x;
                    break;
                }
                if(x == (Left_Black_Point[Right_Up_Point[1]]+10))
                {
                    break;
                }
            }
        }
        if(Blackonefind == 1)
        {
            for(uint8 x = Blackone;x>(Left_Black_Point[Right_Up_Point[1]]+10);x--)
            {
                if(Emo_imag[y][x] == EmoWhite && Emo_imag[y][x-1] == EmoWhite && x > Blackone - 10)
                {
                    Whiteonefind = 1;
                    Whiteone = x;
                    break;
                }
                if(x == (Left_Black_Point[Right_Up_Point[1]]+10))
                {
                    Blackonefind = 0;
                    break;
                }
            }
        }
        if(Whiteonefind == 1)
        {
            for(uint8 x = Whiteone;x>(Left_Black_Point[Right_Up_Point[1]]+10);x--)
            {
                if(Emo_imag[y][x] == EmoBlack && Emo_imag[y][x-1] == EmoBlack && x > Whiteone - 10)
                {
                    Blacktwofind = 1;
                    break;
                }
                if(x == (Left_Black_Point[Right_Up_Point[1]]+10))
                {
                    Blackonefind = 0;
                    Whiteonefind = 0;
                    break;
                }
            }
        }
        if(Blackonefind == 1 && Whiteonefind == 1 && Blacktwofind == 1)
        {
            GarageR_Findfinish_flag = 1;
            Garge_nocharge = 0;
            Garagecount++;                 //�����������
        }
        if(GarageR_Findfinish_flag == 1)
            break;
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �󳵿�Ѱ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void GarageL_Find(void)
{
    uint8 Blackonefind = 0,Blackone = 0;
    uint8 Whiteonefind = 0,Whiteone = 0;
    uint8 Blacktwofind = 0;

    for(uint8 y=Emo_one_eighth(Left_Down_Point[1],Left_Up_Point[1]);y<=Emo_two_third(Left_Down_Point[1],Left_Up_Point[1]);y++)
    {
        if(Emo_imag[y][Left_Down_Point[0]] == EmoWhite)
        {
            for(uint8 x=Left_Down_Point[0];x<(Right_Black_Point[Left_Up_Point[1]]-10);x++)
            {
                if(Emo_imag[y][x] == EmoBlack && Emo_imag[y][x+1] == EmoBlack)
                {
                    Blackonefind = 1;
                    Blackone = x;
                    break;
                }
                if(x == (Right_Black_Point[Left_Up_Point[1]]-10))
                {
                    Blackonefind = 0;
                    break;
                }
            }
        }
        if(Blackonefind == 1)
        {
            for(uint8 x = Blackone;x<(Right_Black_Point[Left_Up_Point[1]]-10);x++)
            {
                if(Emo_imag[y][x] == EmoWhite && Emo_imag[y][x+1] == EmoWhite && x <= Blackone + 10)
                {
                    Whiteonefind = 1;
                    Whiteone = x;
                    break;
                }
                if(x == (Right_Black_Point[Left_Up_Point[1]]-10))
                {
                    Blackonefind = 0;
                    break;
                }
            }
        }
        if(Whiteonefind == 1)
        {
            for(uint8 x = Whiteone;x<(Right_Black_Point[Left_Up_Point[1]]-10);x++)
            {
                if(Emo_imag[y][x] == EmoBlack && Emo_imag[y][x+1] == EmoBlack && x < Whiteone + 10)
                {
                    Blacktwofind = 1;
                    break;
                }
                if(x == (Right_Black_Point[Left_Up_Point[1]]-10))
                {
                    Blackonefind = 0;
                    Whiteonefind = 0;
                    break;
                }
            }
        }
        if(Blackonefind == 1 && Whiteonefind == 1 && Blacktwofind == 1)
        {
            GarageL_Findfinish_flag = 1;
            Garge_nocharge = 0;
            Garagecount++;
        }
        if(GarageL_Findfinish_flag == 1)
            break;
    }
}

//=========================================================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ݹյ�������з�����
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ����5����Ĺյ�Ѱ�һ�����ܶ�����,���Խ��з�һ��յ���ж�
//-------------------------------------------------------------------------------------------------------------------
void Element_dispose(void)
{
    if(SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && Trifork_flag == 0 && GarageL_flag == 0 && GarageR_flag == 0 && WindupR_flag == 0 && WindupL_flag == 0 && Cross_flag == 0)
    {
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Up_Point[0] - Left_Down_Point[0] > 48)
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Down_Point[0] - Right_Up_Point[0] > 48)
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
    }
    if(SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && Trifork_flag == 0 && GarageL_flag == 0 && GarageR_flag == 0 && WindupR_flag == 0 && WindupL_flag == 0 && Cross_flag == 0)
    {
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Up_Point[0] < Left_Down_Point[0])
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Up_Point[0] > Right_Down_Point[0])
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Down_Point[1] - Right_Up_Point[1] < 15)
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Down_Point[1] - Left_Up_Point[1] < 15)
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Down_Point[0] > 170 && Right_Up_Point[0] > 170)
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Down_Point[0] > 170 && Left_Up_Point[0] > 170)
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Left_Down_Point[1] > 40 && (Right_Black_Point[Left_Up_Point[1]] - Right_Black_Point[Left_Down_Point[1]] < 0) && GarageL_Findfinish_flag == 0)
        {
            if((Left_Down_Point[1] - Left_Up_Point[1] <= 32) && Right_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0)
            {
                GarageL_Find();
            }
            if(GarageL_Findfinish_flag == 1)
            {
                GarageL_Findfinish_flag = 0;
                GarageL_flag = 1;
            }
            else
            {
                if((Left_Down_Point[1] - Left_Up_Point[1] > 32))
                {
                    WindupL_flag = 1;
                }
            }
        }
        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && Right_Down_Point[1] > 40 && (Left_Black_Point[Right_Up_Point[1]] - Left_Black_Point[Right_Down_Point[1]] > 0) && GarageR_Findfinish_flag == 0)
        {
            if((Right_Down_Point[1] - Right_Up_Point[1] <= 32) && Left_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0)
            {
                GarageR_Find();
            }
            if(GarageR_Findfinish_flag == 1)
            {
                GarageR_Findfinish_flag = 0;
                GarageR_flag = 1;
            }
            else
            {
                if((Right_Down_Point[1] - Right_Up_Point[1] > 32))
                {
                    WindupR_flag = 1;
                }
            }
        }
        else
        {
                Trifork_Judge();
                if(Trifork_PointMiddle_Findfinish_flag == 1 && Trifork_PointLeft_Findfinish_flag == 1 && Trifork_PointRight_Findfinish_flag == 1)
                {
                    Trifork_flag = 1;
                }
        }
    }

}

//static uint8 stop_PHI(float Speed)
//{
//    uint8 y=0;
//
//    if(Speed >=110 && Speed < 120)
//    {
//        y=38;
//        return y;
//    }
//    else if(Speed >=120 && Speed < 130)
//    {
//        y=37;
//        return y;
//    }
//    else if(Speed >=130 && Speed < 140)
//    {
//        y=37;
//        return y;
//    }
//    else if(Speed >=140 && Speed < 150)
//    {
//        y=37;
//        return y;
//    }
//    else if(Speed >=150 && Speed < 160)
//    {
//        y=34;
//        return y;
//    }
//    else if(Speed >=160 && Speed < 170)
//    {
//        y=26;
//        return y;
//    }
//    else if(Speed >=100 && Speed < 110)
//    {
//        y=39;
//        return y;
//    }
//    else if(Speed >=90 && Speed < 100)
//    {
//        y=41;
//        return y;
//    }
//    else if(Speed >=80 && Speed < 90)
//    {
//        y=42;
//        return y;
//    }
//    else if(Speed >=70 && Speed < 80)
//    {
//        y=44;
//        return y;
//    }
//    else
//    {
//        y=46;
//        return y;
//    }
//
//}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ʱ���ж�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ���⺯���ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8 stop_PHIone(float Speed)
{
    uint8 y=0;

    if(Speed >=110 && Speed < 120)
    {
        y=99;
        return y;
    }
    else if(Speed >=120 && Speed < 130)
    {
        y=98;
        return y;
    }
    else if(Speed >=130 && Speed < 140)
    {
        y=97;
        return y;
    }
    else if(Speed >=140 && Speed < 150)
    {
        y=95;
        return y;
    }
    else if(Speed >=150 && Speed < 160)
    {
        y=34;
        return y;
    }
    else if(Speed >=160 && Speed < 170)
    {
        y=26;
        return y;
    }
    else if(Speed >=100 && Speed < 110)
    {
        y=100;
        return y;
    }
    else if(Speed >=90 && Speed < 100)
    {
        y=100;
        return y;
    }
    else if(Speed >=80 && Speed < 90)
    {
        y=101;
        return y;
    }
    else if(Speed >=70 && Speed < 80)
    {
        y=102;
        return y;
    }
    else
    {
        y=103;
        return y;
    }

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���⺯��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��Ϊ�����߶�����ɨ�ߵ�Ӱ�죬ֱ��ǿ�в��߱�֤˳��ͨ��������
//-------------------------------------------------------------------------------------------------------------------
static uint8 GX = 0,GY = 0;
static uint8 FX = 0,FY = 0;
void Garage(void)
{
    if(GarageR_flag == 1)
    {
        Beepindex = Beepon;
        if(Right_Up_Point[1] > 76 && Right_Down_Point_finish_flag == 0 )
        {
            PaddingR = 0;
            PaddingL = 0;
            GarageR_flag = 0;
            Beepindex = 0;
        }
        else
        {
            if((Garagecount >= GarageIn && dieReady == 4) && Right_Down_Point[1] >= stop_PHIone((float)CoderSpeed))   //�����������
            {
                GarageR_In_flag = 1;
                Garage_In_flag = 1;
            }
            if(Right_Up_Point[0] - Middle_Black_Point[Right_Up_Point[1]] >= 18
            && Right_Down_Point[1] - Right_Up_Point[1] >= 42 && Right_Down_Point[1] >= 70
            && Middle_Black_Point[Right_Up_Point[1]-1] - Left_Black_Point[Right_Up_Point[1]-1] >= 18
            && Middle_Black_Point[Right_Up_Point[1]-2] - Left_Black_Point[Right_Up_Point[1]-2] >= 18)
            {
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                if(Right_Up_Point_finish_flag == 1)
                {
                    Link_Left_Two_Point[0] = Left_Black_Point[Right_Up_Point[1]];
                    Link_Left_Two_Point[1] = Right_Up_Point[1];
                    FX = Link_Left_Two_Point[0];
                    FY = Link_Left_Two_Point[1];
                }
                else
                {
                    if(Left_Black_Point[25] <= 35)
                    {
                        Link_Left_Two_Point[0] = FX;
                        Link_Left_Two_Point[1] = FY;
                    }
                    else
                    {
                        Link_Left_Two_Point[0] = Left_Black_Point[25];
                        Link_Left_Two_Point[1] = 25;
                    }
                }
                GX = Right_Up_Point[0];
                GY = Right_Up_Point[1];
            }
            else if(Right_Up_Point[0] - Middle_Black_Point[Right_Up_Point[1]] >= 18
            && Right_Down_Point[1] - Right_Up_Point[1] >= 34 && Right_Down_Point[1] >= 60 && Right_Down_Point[1] < 70
            && Middle_Black_Point[Right_Up_Point[1]-1] - Left_Black_Point[Right_Up_Point[1]-1] >= 18
            && Middle_Black_Point[Right_Up_Point[1]-2] - Left_Black_Point[Right_Up_Point[1]-2] >= 18)
            {
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                if(Right_Up_Point_finish_flag == 1)
                {
                    Link_Left_Two_Point[0] = Left_Black_Point[Right_Up_Point[1]];
                    Link_Left_Two_Point[1] = Right_Up_Point[1];
                    FX = Link_Left_Two_Point[0];
                    FY = Link_Left_Two_Point[1];
                }
                else
                {
                    if(Left_Black_Point[25] <= 35)
                    {
                        Link_Left_Two_Point[0] = FX;
                        Link_Left_Two_Point[1] = FY;
                    }
                    else
                    {
                        Link_Left_Two_Point[0] = Left_Black_Point[25];
                        Link_Left_Two_Point[1] = 25;
                    }
                }
                GX = Right_Up_Point[0];
                GY = Right_Up_Point[1];
            }
            else if(Right_Up_Point[0] - Middle_Black_Point[Right_Up_Point[1]] >= 18
            && Right_Down_Point[1] < 60
            && Middle_Black_Point[Right_Up_Point[1]-1] - Left_Black_Point[Right_Up_Point[1]-1] >= 18
            && Middle_Black_Point[Right_Up_Point[1]-2] - Left_Black_Point[Right_Up_Point[1]-2] >= 18)
            {
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                if(Right_Up_Point_finish_flag == 1)
                {
                    Link_Left_Two_Point[0] = Left_Black_Point[Right_Up_Point[1]];
                    Link_Left_Two_Point[1] = Right_Up_Point[1];
                    FX = Link_Left_Two_Point[0];
                    FY = Link_Left_Two_Point[1];
                }
                else
                {
                    if(Left_Black_Point[25] <= 35)
                    {
                        Link_Left_Two_Point[0] = FX;
                        Link_Left_Two_Point[1] = FY;
                    }
                    else
                    {
                        Link_Left_Two_Point[0] = Left_Black_Point[25];
                        Link_Left_Two_Point[1] = 25;
                    }
                }
                GX = Right_Up_Point[0];
                GY = Right_Up_Point[1];
            }
            else
            {
                if(GX == 0 && GY == 0)
                {
                    GX = 130;
                    GY = 20;
                }
                Right_Up_Point[0] = GX;
                Right_Up_Point[1] = GY;
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                if(Right_Up_Point_finish_flag == 1)
                {
                    Link_Left_Two_Point[0] = Left_Black_Point[Right_Up_Point[1]];
                    Link_Left_Two_Point[1] = Right_Up_Point[1];
                    FX = Link_Left_Two_Point[0];
                    FY = Link_Left_Two_Point[1];
                }
                else
                {
                    if(Left_Black_Point[25] <= 35)
                    {
                        Link_Left_Two_Point[0] = FX;
                        Link_Left_Two_Point[1] = FY;
                    }
                    else
                    {
                        Link_Left_Two_Point[0] = Left_Black_Point[25];
                        Link_Left_Two_Point[1] = 25;
                    }
                }
            }
            PaddingR = 1;
            PaddingL = 1;
        }
    }
    else if(GarageL_flag == 1)
    {
        Beepindex = Beepon;
        if(Left_Up_Point[1] > 76 && Left_Down_Point_finish_flag == 0)
        {
            PaddingR = 0;
            PaddingL = 0;
            GarageL_flag = 0;
            Beepindex = 0;
        }
        else
        {
//            if((Garagecount >= GarageIn || SlC >= 2) && Left_Up_Point[1] >= stop_PHI((float)CoderSpeed))
//            {
//                GarageL_In_flag = 1;
//                Garage_In_flag = 1;
//            }
            if(Middle_Black_Point[Left_Up_Point[1]] - Left_Up_Point[0] >= 18
            && Left_Down_Point[1] - Left_Up_Point[1] >= 42 && Left_Down_Point[1] >= 70
            && Right_Black_Point[Left_Up_Point[1] - 1] - Middle_Black_Point[Left_Up_Point[1]-1] >= 18
            && Right_Black_Point[Left_Up_Point[1] - 2] - Middle_Black_Point[Left_Up_Point[1]-2] >= 18)
//                && Right_Black_Point[Left_Up_Point[1] - 3] - Middle_Black_Point[Left_Up_Point[1]-3] >= 15
//                    && Right_Black_Point[Left_Up_Point[1] - 4] - Middle_Black_Point[Left_Up_Point[1]-4] >= 15
//                    && Right_Black_Point[Left_Up_Point[1] - 5] - Middle_Black_Point[Left_Up_Point[1]-5] >= 15
//                    && Right_Black_Point[Left_Up_Point[1] - 7] - Middle_Black_Point[Left_Up_Point[1]-7] >= 15
//                    && Right_Black_Point[Left_Up_Point[1] - 9] - Middle_Black_Point[Left_Up_Point[1]-9] >= 15
            {
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                if(Left_Up_Point_finish_flag == 1)
                {
                    Link_Right_Two_Point[0] = Right_Black_Point[Left_Up_Point[1]];
                    Link_Right_Two_Point[1] = Left_Up_Point[1];
                    FX = Link_Right_Two_Point[0];
                    FY = Link_Right_Two_Point[1];
                }
                else
                {
                    if(Right_Black_Point[25] >= 162)
                    {
                        Link_Right_Two_Point[0] = FX;
                        Link_Right_Two_Point[1] = FY;
                    }
                    else
                    {
                        Link_Right_Two_Point[0] = Right_Black_Point[25];
                        Link_Right_Two_Point[1] = 25;
                    }
                }
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                GX = Left_Up_Point[0];
                GY = Left_Up_Point[1];
            }
            else if(Middle_Black_Point[Left_Up_Point[1]] - Left_Up_Point[0] >= 18
            && Left_Down_Point[1] < 70 && Left_Down_Point[1] >= 60 && Left_Down_Point[1] - Left_Up_Point[1] >= 34
            && Right_Black_Point[Left_Up_Point[1] - 1] - Middle_Black_Point[Left_Up_Point[1]-1] >= 18
            && Right_Black_Point[Left_Up_Point[1] - 2] - Middle_Black_Point[Left_Up_Point[1]-2] >= 18)
            {
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                if(Left_Up_Point_finish_flag == 1)
                {
                    Link_Right_Two_Point[0] = Right_Black_Point[Left_Up_Point[1]];
                    Link_Right_Two_Point[1] = Left_Up_Point[1];
                    FX = Link_Right_Two_Point[0];
                    FY = Link_Right_Two_Point[1];
                }
                else
                {
                    if(Right_Black_Point[25] >= 162)
                    {
                        Link_Right_Two_Point[0] = FX;
                        Link_Right_Two_Point[1] = FY;
                    }
                    else
                    {
                        Link_Right_Two_Point[0] = Right_Black_Point[25];
                        Link_Right_Two_Point[1] = 25;
                    }
                }
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                GX = Left_Up_Point[0];
                GY = Left_Up_Point[1];
            }
            else if(Middle_Black_Point[Left_Up_Point[1]] - Left_Up_Point[0] >= 18
            && Left_Down_Point[1] < 60
            && Right_Black_Point[Left_Up_Point[1] - 1] - Middle_Black_Point[Left_Up_Point[1]-1] >= 18
            && Right_Black_Point[Left_Up_Point[1] - 2] - Middle_Black_Point[Left_Up_Point[1]-2] >= 18)
            {
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                if(Left_Up_Point_finish_flag == 1)
                {
                    Link_Right_Two_Point[0] = Right_Black_Point[Left_Up_Point[1]];
                    Link_Right_Two_Point[1] = Left_Up_Point[1];
                    FX = Link_Right_Two_Point[0];
                    FY = Link_Right_Two_Point[1];
                }
                else
                {
                    if(Right_Black_Point[25] >= 162)
                    {
                        Link_Right_Two_Point[0] = FX;
                        Link_Right_Two_Point[1] = FY;
                    }
                    else
                    {
                        Link_Right_Two_Point[0] = Right_Black_Point[25];
                        Link_Right_Two_Point[1] = 25;
                    }
                }
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                GX = Left_Up_Point[0];
                GY = Left_Up_Point[1];
            }
//            else if(Middle_Black_Point[Left_Up_Point[1]] - Left_Up_Point[0] >= 18 && Left_Down_Point_finish_flag == 1 && Left_Up_Point[0] - Left_Down_Point[0] <= 23)
//            {
//                GX = Left_Up_Point[0];
//                GY = Left_Up_Point[1];
//                Link_Right_One_Point[0] = 187;
//                Link_Right_One_Point[1] = 119;
//                if(Left_Up_Point_finish_flag == 1)
//                {
//                    Link_Right_Two_Point[0] = Right_Black_Point[Left_Up_Point[1]];
//                    Link_Right_Two_Point[1] = Left_Up_Point[1];
//                }
//                else
//                {
//                    Link_Right_Two_Point[0] = Right_Black_Point[25];
//                    Link_Right_Two_Point[1] = 25;
//                }
//                Link_Left_One_Point[0] = 0;
//                Link_Left_One_Point[1] = 119;
//                Link_Left_Two_Point[0] = Left_Up_Point[0];
//                Link_Left_Two_Point[1] = Left_Up_Point[1];
//                GX = Left_Up_Point[0];
//                GY = Left_Up_Point[1];
//            }
            else
            {
                if(GX == 0 && GY == 0)
                {
                    GX = 80;
                    GY = 20;
                }
                Left_Up_Point[0] = GX;
                Left_Up_Point[1] = GY;
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                if(Left_Up_Point_finish_flag == 1)
                {
                    Link_Right_Two_Point[0] = Right_Black_Point[Left_Up_Point[1]];
                    Link_Right_Two_Point[1] = Left_Up_Point[1];
                    FX = Link_Right_Two_Point[0];
                    FY = Link_Right_Two_Point[1];
                }
                else
                {
                    if(Right_Black_Point[25] >= 162)
                    {
                        Link_Right_Two_Point[0] = FX;
                        Link_Right_Two_Point[1] = FY;
                    }
                    else
                    {
                        Link_Right_Two_Point[0] = Right_Black_Point[25];
                        Link_Right_Two_Point[1] = 25;
                    }
                }
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
            }
            PaddingR = 1;
            PaddingL = 1;
        }
    }
}


//��ͼ��ʶ�𳣳�������ĵط���������һ��
//Բ�������������Ƿ�������ʺ������Ǽ���Ƿ���ת��
//�ػ�����ȱ�ں����Ƿ�������ʺ������Ǽ���Ƿ���ת��
//Բ������ɽ�������������������ͽ���Բ����־
//�ػ����������ڳ���������������ͽ����ػ���־
//���棺һ�������ɼ��Ԫ��
void TriforkTrial(void)
{
    Identify();
    if(SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && GarageL_flag == 0 && GarageR_flag == 0 && WindupR_flag == 0 && WindupL_flag == 0 && Cross_flag == 0)
    {
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Up_Point[0] - Left_Down_Point[0] > 48)
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Down_Point[0] - Right_Up_Point[0] > 48)
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
    }
    if(SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && GarageL_flag == 0 && GarageR_flag == 0 && WindupR_flag == 0 && WindupL_flag == 0 && Cross_flag == 0)
    {
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Up_Point[0] < Left_Down_Point[0])
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Up_Point[0] > Right_Down_Point[0])
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Down_Point[1] - Right_Up_Point[1] < 15)
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Down_Point[1] - Left_Up_Point[1] < 15)
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Down_Point[0] > 170 && Right_Up_Point[0] > 170)
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Down_Point[0] > 170 && Left_Up_Point[0] > 170)
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Left_Down_Point[1] > 40 && (Right_Black_Point[Left_Up_Point[1]] - Right_Black_Point[Left_Down_Point[1]] < 0) && GarageL_Findfinish_flag == 0)
        {
            if((Left_Down_Point[1] - Left_Up_Point[1] <= 32))
            {
                GarageL_Find();
            }
            if(GarageL_Findfinish_flag == 1)
            {
                GarageL_Findfinish_flag = 0;
                GarageL_flag = 1;
            }
            else
            {
                if((Left_Down_Point[1] - Left_Up_Point[1] > 32))
                {
                    WindupL_flag = 1;
                }
            }
        }
        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && Right_Down_Point[1] > 40 && (Left_Black_Point[Right_Up_Point[1]] - Left_Black_Point[Right_Down_Point[1]] > 0) && GarageR_Findfinish_flag == 0)
        {
            if((Right_Down_Point[1] - Right_Up_Point[1] <= 32))
            {
                GarageR_Find();
            }
            if(GarageR_Findfinish_flag == 1)
            {
                GarageR_Findfinish_flag = 0;
                GarageR_flag = 1;
            }
            else
            {
                if((Right_Down_Point[1] - Right_Up_Point[1] > 32))
                {
                    WindupR_flag = 1;
                }
            }
        }
    }
    Windup();
    if(SlalomLeft_flag == 1 || SlalomRight_flag == 1 || CircleLeft_flag == 1 || CircleRight_flag == 1 || GarageL_flag == 1 || GarageR_flag == 1 || Cross_flag == 1 )
    {
        PaddingR = 0;
        PaddingL = 0;
        Triforkpadding_flag = 0;
        Triforkcount = 0;
        Trifork_flag = 0;
        Beepindex = 0;
        Corners_flag = 0;
        Near_Corners_flag = 0;
        WindupR_flag = 0;
        WindupL_flag = 0;
    }

}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʮ�ֺ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Cross(void)
{
    if(Cross_flag == 1)
    {
        Beepindex = Beepon;
        if(Crosscount == 0)
        {
            Crosscount = 1;
        }
        if(Crosscount == 1)
        {
            if(Left_Up_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1
            && Left_Down_Point[1] >= 70 && Right_Down_Point[1] >= 70)
            {
                Crosscount = 2;
            }
        }
        if(Crosscount == 2)
        {
            if((Left_Up_Point[1] >= 74 || Right_Up_Point[1] >= 74))
            {
                Crosscount = 3;
            }
        }
        switch(Crosscount)
        {
            case 1 :
                Link_Left_One_Point[0] = Left_Down_Point[0];
                Link_Left_One_Point[1] = Left_Down_Point[1];
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                Link_Right_One_Point[0] = Right_Down_Point[0];
                Link_Right_One_Point[1] = Right_Down_Point[1];
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 1;
                break;
            case 2 :
                Link_Left_One_Point[0] = Left_Down_Point[0];
                Link_Left_One_Point[1] = Left_Down_Point[1];
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                Link_Right_One_Point[0] = Right_Down_Point[0];
                Link_Right_One_Point[1] = Right_Down_Point[1];
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 1;
                break;
            case 3 :
                Cross_flag = 0;
                Crosscount = 0;
                PaddingR = 0;
                PaddingL = 0;
                Beepindex = 0;
                break;
        }
    }
}

//Ԫ��ǰҡ
//-------------------------------------------------------------------------------------------------------------------
//  @brief      Ԫ��ǰҡ
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ɨ�赽�������ϵ����������յ��������ιյ�����ж���ʲôԪ�أ��жϰ���Բ����ʮ�֡�P��
//-------------------------------------------------------------------------------------------------------------------
void Windup(void)
{
    if(WindupL_flag == 1)
    {
        //Beepindex = Beepon;
        Link_Left_One_Point[0] = Left_Down_Point[0];
        Link_Left_One_Point[1] = Left_Down_Point[1];
        Link_Left_Two_Point[0] = Left_Up_Point[0];
        Link_Left_Two_Point[1] = Left_Up_Point[1];
        PaddingR = 0;
        PaddingL = 1;
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && Left_Down_Point[1] > 42 && findlcount < 6 && Left_Up_Point[0] > 30)
        {
            Cross_flag = 1;
            WindupL_flag = 0;
            Beepindex = 0;
        }
        else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 &&
                Right_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0
                && Left_Down_Point[1] >= 75 && Left_Down_Point[1] <= 105 && findlcount < 4 && Left_Up_Point[0] > 30
                && (Left_Up_Point[0] - Left_Down_Point[0]) <= 42 && (Left_Down_Point[1] - Left_Up_Point[1]) >= 45
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[(Left_Up_Point[1]+Left_Down_Point[1])/2]
                && Right_Black_Point[(Left_Up_Point[1]+Left_Down_Point[1])/2] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_one_third(Left_Down_Point[1],Left_Up_Point[1])]
                && Right_Black_Point[Emo_one_third(Left_Down_Point[1],Left_Up_Point[1])] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_two_third(Left_Down_Point[1],Left_Up_Point[1])]
                && Right_Black_Point[Emo_two_third(Left_Down_Point[1],Left_Up_Point[1])] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Left_Down_Point[1]])
        {
            SlalomLeft_flag = 1;
            Slalomcount = 1;
            WindupL_flag = 0;
        }
        else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 &&
                Right_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0
                && Left_Down_Point[1] >= 75 && findlcount >= 8 && Left_Up_Point[0] > 30 && (Left_Down_Point[1] - Left_Up_Point[1]) >= 45
                && (Left_Down_Point[1] - Left_Up_Point[1]) <= 78 && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 5] != EmoWhite
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[(Left_Up_Point[1]+Left_Down_Point[1])/2]
                && Right_Black_Point[(Left_Up_Point[1]+Left_Down_Point[1])/2] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_one_third(Left_Down_Point[1],Left_Up_Point[1])]
                && Right_Black_Point[Emo_one_third(Left_Down_Point[1],Left_Up_Point[1])] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_two_third(Left_Down_Point[1],Left_Up_Point[1])]
                && Right_Black_Point[Emo_two_third(Left_Down_Point[1],Left_Up_Point[1])] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Left_Down_Point[1]])
        {
            if(findlcount >= 16)
            {
                CircleBig = 1;
            }
            CircleLeft_flag = 1;
            Circlecount = 1;
            WindupL_flag = 0;
        }
        else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0 && Left_Down_Point[1] <= 110
                && findlcount <= 17)
        {
            GarageL_Find();
            if(GarageL_Findfinish_flag == 1)
            {
                GarageL_Findfinish_flag = 0;
                GarageL_flag = 1;
                WindupL_flag = 0;
            }
        }
        else if(Left_Down_Point_finish_flag == 0)
        {
            WindupL_flag = 0;
            PaddingR = 0;
            PaddingL = 0;
            Beepindex = 0;
        }
    }
    else if(WindupR_flag == 1)
    {
        //Beepindex = Beepon;
        Link_Right_One_Point[0] = Right_Down_Point[0];
        Link_Right_One_Point[1] = Right_Down_Point[1];
        Link_Right_Two_Point[0] = Right_Up_Point[0];
        Link_Right_Two_Point[1] = Right_Up_Point[1];
        PaddingR = 1;
        PaddingL = 0;
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Right_Down_Point[1] > 42 && findrcount < 6 && Right_Up_Point[0] < 158)
        {
            Cross_flag = 1;
            WindupR_flag = 0;
            Beepindex = 0;
        }
        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 &&
                Left_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0
            && Right_Down_Point[1] >= 75 && Right_Down_Point[1] <= 105 && findrcount < 4 && Right_Up_Point[0] < 158
            && (Right_Down_Point[0] - Right_Up_Point[0]) <= 42 && Right_Down_Point[1] - Right_Up_Point[1] >= 45
            && Right_Down_Point[1] - Right_Up_Point[1] <= 78 && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] != EmoWhite
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[(Right_Up_Point[1]+Right_Down_Point[1])/2]
            && Left_Black_Point[(Right_Up_Point[1]+Right_Down_Point[1])/2] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_one_third(Right_Down_Point[1],Right_Up_Point[1])]
            && Left_Black_Point[Emo_one_third(Right_Down_Point[1],Right_Up_Point[1])] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_two_third(Right_Down_Point[1],Right_Up_Point[1])]
            && Left_Black_Point[Emo_two_third(Right_Down_Point[1],Right_Up_Point[1])] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Right_Down_Point[1]])
        {
            SlalomRight_flag = 1;
            Slalomcount = 1;
            WindupR_flag = 0;
        }
        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 &&
                Left_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0
            && Right_Down_Point[1] >= 75 && findrcount >= 9 && Right_Up_Point[0] < 158 && Right_Down_Point[1] - Right_Up_Point[1] >= 45
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[(Right_Up_Point[1]+Right_Down_Point[1])/2]
            && Left_Black_Point[(Right_Up_Point[1]+Right_Down_Point[1])/2] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_one_third(Right_Down_Point[1],Right_Up_Point[1])]
            && Left_Black_Point[Emo_one_third(Right_Down_Point[1],Right_Up_Point[1])] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_two_third(Right_Down_Point[1],Right_Up_Point[1])]
            && Left_Black_Point[Emo_two_third(Right_Down_Point[1],Right_Up_Point[1])] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Right_Down_Point[1]])
        {
            if(findrcount >= 16)
            {
                CircleBig = 1;
            }
            CircleRight_flag = 1;
            Circlecount = 1;
            WindupR_flag = 0;
        }
        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 &&
                Left_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0 && Right_Down_Point[1] <= 110 && findrcount <= 17)
        {
            GarageR_Find();
            if(GarageR_Findfinish_flag == 1)
            {
                GarageR_Findfinish_flag = 0;
                GarageR_flag = 1;
                WindupR_flag = 0;
            }
        }
        else if(Right_Down_Point_finish_flag == 0)
        {
            WindupR_flag = 0;
            PaddingR = 0;
            PaddingL = 0;
            Beepindex = 0;
        }
    }
}

//����һЩ�յ������
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����һЩ�յ������
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��Ϊ�������������¹յ����µĶ������ƫ���ߵļ���
//-------------------------------------------------------------------------------------------------------------------
void Point_ClearDL(uint8 y)
{
    for(uint8 i=y;i>=y-10;i--)
    {
        if(Left_Black_Point[i] == 0)
        {
            break;
        }
        else
        {
            Left_Black_Point[i] = 0;
        }
    }
}

void Point_ClearDR(uint8 y)
{
    for(uint8 i=y;i>=y-10;i--)
    {
        if(Right_Black_Point[i] == 187)
        {
            break;
        }
        else
        {
            Right_Black_Point[i] = 187;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      P�ֳ�P�Ĳ��ߵ���Ѱ
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       P�ֺ����ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void SlalomPoint(void)
{
    if(SlalomLeft_flag == 1)
    {
//        for(uint8 y = Left_Down_Point[1];y>10;y--)
//        {
//            if(Emo_imag[y+1][(Left_Down_Point[0]+Right_Down_Point[0])/2] == EmoWhite
//            && Emo_imag[y][(Left_Down_Point[0]+Right_Down_Point[0])/2] == EmoBlack
//            && Emo_imag[y-1][(Left_Down_Point[0]+Right_Down_Point[0])/2] == EmoBlack
//            && Emo_imag[y-2][(Left_Down_Point[0]+Right_Down_Point[0])/2] == EmoBlack)
//            {
//                Slalom_Point[0]=(Left_Down_Point[0]+Right_Down_Point[0])/2;
//                Slalom_Point[1]=y;
//                break;
//            }
//            if(y==10)
//            {
//                Slalom_Point[0]=0;
//                Slalom_Point[1]=0;
//                break;
//            }
//        }
        for(uint8 y = Right_Down_Point[1];y>10;y--)
        {
            if(Emo_imag[y+1][Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoWhite
            && Emo_imag[y][Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack
            && Emo_imag[y-1][Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack
            && Emo_imag[y-2][Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack)
            {
                Slalom_Point[0]=Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5);
                Slalom_Point[1]=y;
                break;
            }
            if(y==10)
            {
                Slalom_Point[0]=Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0]))/2);
                Slalom_Point[1]=Right_Down_Point[1]/2;
                break;
            }
        }
    }
    else
    {
//        for(uint8 y = Left_Down_Point[1];y>10;y--)
//        {
//            if(Emo_imag[y+1][(Left_Down_Point[0]+Right_Down_Point[0])/2] == EmoWhite
//            && Emo_imag[y][(Left_Down_Point[0]+Right_Down_Point[0])/2] == EmoBlack
//            && Emo_imag[y-1][(Left_Down_Point[0]+Right_Down_Point[0])/2] == EmoBlack
//            && Emo_imag[y-2][(Left_Down_Point[0]+Right_Down_Point[0])/2] == EmoBlack)
//            {
//                Slalom_Point[0]=(Left_Down_Point[0]+Right_Down_Point[0])/2;
//                Slalom_Point[1]=y;
//                break;
//            }
//            if(y==10)
//            {
//                Slalom_Point[0]=187;
//                Slalom_Point[1]=0;
//                break;
//            }
//        }
        for(uint8 y = Left_Down_Point[1];y>10;y--)
        {
            if(Emo_imag[y+1][Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoWhite
            && Emo_imag[y][Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack
            && Emo_imag[y-1][Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack
            && Emo_imag[y-2][Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack)
            {
                Slalom_Point[0]=Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5);
                Slalom_Point[1]=y;
                break;
            }
            if(y==10)
            {
                Slalom_Point[0]=Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5);
                Slalom_Point[1]=Left_Down_Point[1]/2;
                break;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      P�ֺ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Slalom(void)
{
    if(SlalomRight_flag == 1)  //��
    {
        Beepindex = BeepSlalom;
//        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && findrcount < 5 && Slalomcount == 0)  //���¹ղ���
//        {
//            Slalomcount=1;
//            //EncoderSum_flag = 1;
//        }
        if(Slalomcount == 1)
        {
            if(Left_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0 && Right_Down_Point[1] <= 105 && findrcount < 7)
            {
                GarageR_Find();
                if(GarageR_Findfinish_flag == 1)
                {
                    SlalomRight_flag = 0;
                    Slalomcount = 0;
                    GarageR_Findfinish_flag = 0;
                    EncoderSum_flag = 0;
                    GarageR_flag = 1;
                    //WindupR_flag = 0;
                }
            }
            EncoderSum_flag = 1;
            if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0 && Right_Down_Point[1] > 80)     //�Ϲղ���
            {
                Slalomcount=2;
            }
            if(Real_Distance >= 2500)
            {
                Slalomcount = 3;
                EncoderSum_flag = 0;
            }
        }
        if(Slalomcount == 2)
        {
            if(Right_Up_Point_finish_flag == 0 && Right_Up_Point[1] > 70)    //���
            {
                Slalomcount=3;
                //EncoderSum_flag = 0;
            }
            if(Real_Distance >= 2500)
            {
                Slalomcount = 3;
                EncoderSum_flag = 0;
            }
        }
        if(Slalomcount == 3)
        {
            Gyroscope_Star_flag = 1;
            EncoderSum_flag = 0;
            if(Emo_Angle >= 40)   //���ֲ��ó��ֵ������Slalomȡ��
            {
                if(Element_Charge == 1)
                {
                    Element_Charge = 0;
                }
                Gyroscope_Star_flag = 0;
                need_cornerL = 0;
                PaddingR = 0;
                PaddingL = 0;
                SlalomRight_flag = 0;
                Slalom_Padding = 0;
                Slalomcount = 0;
                Paddingcurve = 0;
                Beepindex = 0;
            }
            if(Left_Down_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)   //��Slalom
            {
                SlalomPoint();
                Slalomcount = 4;
                Gyroscope_Star_flag = 0;
                Clear_Gyroscope_Angle();
            }
        }
        if(Slalomcount == 4)
        {
            Paddingcurve = 1;
            SlalomPoint();
            if((Left_Down_Point[0]/2 + Right_Down_Point[0]/2) <= 128)
            {
                EncoderSum_flag = 1;
                Gyroscope_Star_flag = 1;
            }
//            if(Slalom_Point[1] >= 58)
//            {
//                Auxiliary_CorneringLeft_flag = 1;
//            }
//            if(Left_Down_Point_finish_flag == 0 && Emo_Angle > 40)            //ͨ��һ��Slalom
//            {
//                Auxiliary_CorneringLeft_flag = 0;
//                Gyroscope_Star_flag = 0;
//                Slalomcount = 5;
//            }
            if(Left_Down_Point[1] > 73)
            {
                ObservationS_finish = 1;
            }
            if(Real_Distance >= 3100 && Emo_Angle >= 35)
            {
                CorneringS_finish = 1;
                Auxiliary_CorneringLeft_flag = 0;
            }
            if(ObservationS_finish == 1 && CorneringS_finish == 1)
            {
                Auxiliary_CorneringLeft_flag = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Slalomcount = 5;
                CorneringS_finish = 0;
                ObservationS_finish = 0;
            }
        }
        switch(Slalomcount)
        {
            case 1 :
                Link_Right_One_Point[0] = Right_Down_Point[0];
                Link_Right_One_Point[1] = Right_Down_Point[1];
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 2 :
                Link_Right_One_Point[0] = Right_Down_Point[0];
                Link_Right_One_Point[1] = Right_Down_Point[1];
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 3 :
                Corners_flag = 1;
//                if((Right_Black_Point[100] == 187 && Right_Black_Point[99] == 187 && Right_Black_Point[98] == 187 && Left_Black_Point[100] != 0 && Left_Black_Point[99] != 0 && Left_Black_Point[98] != 0 && Left_Black_Point[95] != 0 && Left_Black_Point[94] != 187 && Left_Black_Point[93] != 187) || (Left_Black_Point[100] == 0 && Left_Black_Point[99] == 0 && Left_Black_Point[98] == 0 && Right_Black_Point[100] != 187 && Right_Black_Point[99] != 187 && Right_Black_Point[98] != 187 && Right_Black_Point[95] != 187 && Right_Black_Point[94] != 187 && Right_Black_Point[93] != 187))
//                {
//                    Near_Corners_flag = 1;
//                }
//                else
//                {
//                    Near_Corners_flag = 0;
//                }
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 4 :
                Link_Right_One_Point[0] = Slalom_Point[0];
                Link_Right_One_Point[1] = Slalom_Point[1];
                Link_Right_Two_Point[0] = Right_Down_Point[0];
                Link_Right_Two_Point[1] = Right_Down_Point[1];
                Point_ClearDL(Left_Down_Point[1]);
                Corners_flag = 0;
                Slalom_Padding = 1;
//                if(Slalom_Point[1] >= 30)
//                {
                if(Battery_Voltage <= 2.8 || Slalom_Point[1] >= 42)
                {
                    need_cornerL = 1;
                }
//                    Corners_flag = 1;
////                    //need_cornerL = 1;
//                }
//                else if(Pre_Speed >= 90 && Slalom_Point[1] >= 38)
//                {
//                    if(Battery_Voltage <= 6.2)
//                    {
//                        need_cornerL
//                        = 1;
//                    }
//                    Corners_flag = 1;
//                    //need_cornerL = 1;
//                }
//                else
//                {
//                    Corners_flag = 0;
//                }
                //Corners_flag = 1;
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 5 :
                if(Element_Charge == 1)
                {
                    Element_Charge = 0;
                }
                SlC++;
                need_cornerL = 0;
                PaddingR = 0;
                PaddingL = 0;
                SlalomRight_flag = 0;
                Slalom_Padding = 0;
                Slalomcount = 0;
                Paddingcurve = 0;
                Beepindex = 0;
                break;
        }
    }
    else if(SlalomLeft_flag == 1)
    {
        Beepindex = BeepSlalom;
//        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findrcount < 5 && Slalomcount == 0)  //���¹ղ���
//        {
//            Slalomcount=1;
//            EncoderSum_flag = 1;
//        }
        if(Slalomcount == 1)
        {
            if(Right_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0 && Left_Down_Point[1] <= 105
                            && findlcount < 7)
            {
                GarageL_Find();
                if(GarageL_Findfinish_flag == 1)
                {
                    SlalomLeft_flag = 0;
                    Slalomcount = 0;
                    EncoderSum_flag = 0;
                    GarageL_Findfinish_flag = 0;
                    GarageL_flag = 1;
                    //WindupL_flag = 0;
                }
            }
            EncoderSum_flag = 1;
            if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0 && Left_Down_Point[1] > 80)     //�Ϲղ���
            {
                Slalomcount=2;
            }
            if(Real_Distance >= 2500)
            {
                Slalomcount = 3;
                EncoderSum_flag = 0;
            }
        }
        if(Slalomcount == 2)
        {
            if(Left_Up_Point_finish_flag == 0 && Left_Up_Point[1] > 70)    //���
            {
                Slalomcount=3;
            }
            if(Real_Distance >= 2500)
            {
                Slalomcount = 3;
                EncoderSum_flag = 0;
            }
        }
        if(Slalomcount == 3)
        {
            Gyroscope_Star_flag = 1;
            EncoderSum_flag = 0;
            if(Emo_Angle <= -40)
            {
                if(Element_Charge == 1)
                {
                    Element_Charge = 0;
                }
                Gyroscope_Star_flag = 0;
                need_cornerR = 0;
                PaddingR = 0;
                PaddingL = 0;
                SlalomLeft_flag = 0;
                Near_Corners_flag = 0;
                Slalom_Padding = 0;
                Slalomcount = 0;
                Beepindex = 0;
                Paddingcurve = 0;
            }
            if(Right_Down_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)   //��Slalomm
            {
                SlalomPoint();
                Slalomcount = 4;
                Gyroscope_Star_flag = 0;
                Clear_Gyroscope_Angle();
            }
        }
        if(Slalomcount == 4)
        {
            Paddingcurve = 1;
            SlalomPoint();
            if((Left_Down_Point[0]/2 + Right_Down_Point[0]/2) >= 60)  //�����תλ��
            {
                EncoderSum_flag = 1;
                Gyroscope_Star_flag = 1;
            }
//            if(Slalom_Point[1] >= 58)
//            {
//                Auxiliary_CorneringRight_flag = 1;
//            }
//            if(Right_Down_Point_finish_flag == 0 && Emo_Angle < -40)            //ͨ��һ��Slalom
//            {
//                Auxiliary_CorneringRight_flag = 0;
//                Gyroscope_Star_flag = 0;
//                Slalomcount = 5;
//            }
            if(Right_Down_Point[1] > 73)
            {
                ObservationS_finish = 1;
            }
            if(Real_Distance >= 3100 && Emo_Angle <= -35)     //���ת�������
            {
                CorneringS_finish = 1;
                Auxiliary_CorneringRight_flag = 0;
            }
            if(ObservationS_finish == 1 && CorneringS_finish == 1)
            {
                Auxiliary_CorneringRight_flag = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Slalomcount = 5;
                CorneringS_finish = 0;
                ObservationS_finish = 0;
            }
        }
        switch(Slalomcount)
        {
            case 1 :
                Link_Left_One_Point[0] = Left_Down_Point[0];
                Link_Left_One_Point[1] = Left_Down_Point[1];
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 2 :
                Link_Left_One_Point[0] = Left_Down_Point[0];
                Link_Left_One_Point[1] = Left_Down_Point[1];
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 3 :
                Corners_flag = 1;
//                if((Right_Black_Point[100] == 187 && Right_Black_Point[99] == 187 && Right_Black_Point[98] == 187 && Left_Black_Point[100] != 0 && Left_Black_Point[99] != 0 && Left_Black_Point[98] != 0 && Left_Black_Point[95] != 0 && Left_Black_Point[94] != 187 && Left_Black_Point[93] != 187) || (Left_Black_Point[100] == 0 && Left_Black_Point[99] == 0 && Left_Black_Point[98] == 0 && Right_Black_Point[100] != 187 && Right_Black_Point[99] != 187 && Right_Black_Point[98] != 187 && Right_Black_Point[95] != 187 && Right_Black_Point[94] != 187 && Right_Black_Point[93] != 187))
//                {
//                    Near_Corners_flag = 1;
//                }
//                else
//                {
//                    Near_Corners_flag = 0;
//                }
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 4 :
                Link_Left_One_Point[0] = Slalom_Point[0];
                Link_Left_One_Point[1] = Slalom_Point[1];
                Link_Left_Two_Point[0] = Left_Down_Point[0];
                Link_Left_Two_Point[1] = Left_Down_Point[1];
                Point_ClearDR(Right_Down_Point[1]);
                Corners_flag = 0;
                Slalom_Padding = 1;
                if(Battery_Voltage <= 2.8 || Slalom_Point[1] >= 38)
                {
                    need_cornerR = 1;
                }
//                if(Pre_Speed < 90 && Slalom_Point[1] >= 40)
//                {
//                    if(Battery_Voltage <= 6.2)
//                    {
//                        need_cornerR = 1;
//                    }
//                    Corners_flag = 1;
//                    //need_cornerR = 1;
//                }
//                else if(Pre_Speed >= 90 && Slalom_Point[1] >= 32)
//                {
//                    if(Battery_Voltage <= 6.2)
//                    {
//                        need_cornerR = 1;
//                    }
//                    Corners_flag = 1;
//                    //need_cornerR = 1;
//                }
//                else
//                {
//                    Corners_flag = 0;
//                }
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 5 :
                if(Element_Charge == 1)
                {
                    Element_Charge = 0;
                }
                SlC++;
                need_cornerR = 0;
                PaddingR = 0;
                PaddingL = 0;
                SlalomLeft_flag = 0;
                Near_Corners_flag = 0;
                Slalom_Padding = 0;
                Slalomcount = 0;
                Beepindex = 0;
                Paddingcurve = 0;
                break;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��Բ���Ĳ��ߵ���Ѱ
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       Բ�������ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void CircleOutPoint(void)
{
    if(CircleLeft_flag == 1)
    {
        for(int y = Right_Down_Point[1];y>=20;y--)
        {
            if(Emo_imag[y+1][Right_Down_Point[0] - 78] == EmoWhite && Emo_imag[y][Right_Down_Point[0] - 78] == EmoBlack && Emo_imag[y-1][Right_Down_Point[0] - 78] == EmoBlack && Emo_imag[y-2][Right_Down_Point[0] - 78] == EmoBlack)
            {
                CircleOut_Point[0] = Right_Down_Point[0] - 78;
                CircleOut_Point[1] = (uint8)y;
                break;
            }
            if(y==20)
            {
                CircleOut_Point[0] = Right_Down_Point[0] - 78;
                CircleOut_Point[1] = 20;
                break;
            }
        }
    }
    else if(CircleRight_flag == 1)
    {
        for(int y = Left_Down_Point[1];y>=20;y--)
        {
            if(Emo_imag[y+1][Left_Down_Point[0] + 85] == EmoWhite && Emo_imag[y][Left_Down_Point[0] + 85] == EmoBlack && Emo_imag[y-1][Left_Down_Point[0] + 85] == EmoBlack && Emo_imag[y-2][Left_Down_Point[0] + 85] == EmoBlack)
            {
                CircleOut_Point[0] = Left_Down_Point[0] + 85;
                CircleOut_Point[1] = (uint8)y;
                break;
            }
            if(y==20)
            {
                CircleOut_Point[0] = Left_Down_Point[0] + 85;
                CircleOut_Point[1] = 20;
                break;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Բ���Ĳ���ʶ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
static unsigned char circlrsu = 0;
void Circle_supplement(void)
{
    if(dieReady == 2 && CornerLeft_flag == 0 && CornerRight_flag == 0 && Corners_flag == 0  && findrcount <= 4
    && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1 && Right_Up_Point[1] >= 25 && Right_Up_Point[1] <= 50 && Right_Up_Point[0] < 145 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 0
    && WindupL_flag == 0 && WindupR_flag == 0
    && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0
    && GarageL_flag == 0 && GarageR_flag == 0 && Cross_flag == 0 && Trifork_flag == 0
    && RampReady_flag == 0 && CornerS_flag == 0 && Ramp_flag == 0
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[(Right_Up_Point[1]+105)/2]
    && Left_Black_Point[(Right_Up_Point[1]+105)/2] >  Left_Black_Point[105]
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_one_third(105,Right_Up_Point[1])]
    && Left_Black_Point[Emo_one_third(105,Right_Up_Point[1])] >  Left_Black_Point[105]
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_two_third(105,Right_Up_Point[1])]
    && Left_Black_Point[Emo_two_third(105,Right_Up_Point[1])] >  Left_Black_Point[105]
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[105]
    && Emo_imag[Right_Up_Point[1] - 1][Right_Up_Point[0] + 10] == EmoWhite
    && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 10] == EmoWhite
    && Right_Black_Point[112] == 187 && Right_Black_Point[113] == 187 && Right_Black_Point[115] == 187)
    {
        CircleRight_flag = 1;
        Circlecount = 4;
        //CircleBig = 1;
    }
    else if(dieReady == 2 && CornerLeft_flag == 0 && CornerRight_flag == 0 && Corners_flag == 0  && findlcount <= 4
    && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 0 && Left_Up_Point[1] >= 25 && Left_Up_Point[1] <= 50 && Left_Up_Point[0] > 45 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
    && WindupL_flag == 0 && WindupR_flag == 0
    && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0
    && GarageL_flag == 0 && GarageR_flag == 0 && Cross_flag == 0 && Trifork_flag == 0
    && RampReady_flag == 0 && CornerS_flag == 0 && Ramp_flag == 0
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[(Left_Up_Point[1]+105)/2]
    && Right_Black_Point[(Left_Up_Point[1]+105)/2] <  Right_Black_Point[105]
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_one_third(105,Left_Up_Point[1])]
    && Right_Black_Point[Emo_one_third(105,Left_Up_Point[1])] <  Right_Black_Point[105]
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_two_third(105,Left_Up_Point[1])]
    && Right_Black_Point[Emo_two_third(105,Left_Up_Point[1])] <  Right_Black_Point[105]
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[105]
    && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 10] == EmoWhite
    && Emo_imag[Left_Up_Point[1] - 1][Left_Up_Point[0] - 10] == EmoWhite
    && Left_Black_Point[112] == 0 && Left_Black_Point[113] == 0 && Left_Black_Point[115] == 0 )
    {
        CircleLeft_flag = 1;
        Circlecount = 4;
        //CircleBig = 1;
    }
    else if(dieReady == 2 && CornerLeft_flag == 0 && CornerRight_flag == 0 && Corners_flag == 0  && findrcount >= 12
    && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1 && Right_Up_Point[1] >= 25 && Right_Up_Point[1] <= 66 && Right_Up_Point[0] < 165 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 0
    && WindupL_flag == 0 && WindupR_flag == 0
    && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0
    && GarageL_flag == 0 && GarageR_flag == 0 && Cross_flag == 0 && Trifork_flag == 0
    && RampReady_flag == 0 && CornerS_flag == 0 && Ramp_flag == 0
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[(Right_Up_Point[1]+105)/2]
    && Left_Black_Point[(Right_Up_Point[1]+105)/2] >  Left_Black_Point[105]
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_one_third(105,Right_Up_Point[1])]
    && Left_Black_Point[Emo_one_third(105,Right_Up_Point[1])] >  Left_Black_Point[105]
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_two_third(105,Right_Up_Point[1])]
    && Left_Black_Point[Emo_two_third(105,Right_Up_Point[1])] >  Left_Black_Point[105]
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[105]
    && Left_Black_Point[10] > Left_Black_Point[Right_Up_Point[1]] && Left_Black_Point[10] > Left_Black_Point[(Right_Up_Point[1]+10)/2]
    && Right_Black_Point[Right_Up_Point[1]] <= Right_Black_Point[Right_Up_Point[1]+1] && Right_Black_Point[Right_Up_Point[1]+1] <= Right_Black_Point[Right_Up_Point[1]+2]
    && Right_Black_Point[Right_Up_Point[1]+2] <= Right_Black_Point[Right_Up_Point[1]+3] && Right_Black_Point[Right_Up_Point[1]+3] <= Right_Black_Point[Right_Up_Point[1]+4]
    && Right_Black_Point[Right_Up_Point[1]+4] <= Right_Black_Point[Right_Up_Point[1]+5] && Right_Black_Point[Right_Up_Point[1]+5] <= Right_Black_Point[Right_Up_Point[1]+6]
    && Right_Black_Point[Right_Up_Point[1]] < Right_Black_Point[Right_Up_Point[1]+5] && Right_Black_Point[Right_Up_Point[1]+1] < Right_Black_Point[Right_Up_Point[1]+6]
    && Right_Black_Point[Right_Up_Point[1]] < Right_Black_Point[Right_Up_Point[1]+8] && Right_Black_Point[Right_Up_Point[1]+1] < Right_Black_Point[Right_Up_Point[1]+9]
    && Right_Black_Point[Right_Up_Point[1]] < Right_Black_Point[Right_Up_Point[1]+11] && Right_Black_Point[Right_Up_Point[1]+1] < Right_Black_Point[Right_Up_Point[1]+12])
    {
        for(uint8 y=Right_Up_Point[1] - 3;y>=5;y--)
        {
            if(circlrsu == 0 && Right_Black_Point[y] <= Right_Black_Point[y-1] && Right_Black_Point[y-1] <= Right_Black_Point[y-2] && Right_Black_Point[y] < Right_Black_Point[y-2] )
            {
                circlrsu = 1;
            }
            if(circlrsu == 1)
            {
                if(Right_Black_Point[y] <= 187 && Right_Black_Point[y-1] >= 177 && Right_Black_Point[y-2] >= 177)
                {
                    CircleRight_flag = 1;
                    Circlecount = 12;
                    //CircleBig = 1;
                    circlrsu = 0;
                    break;
                }
            }
            if(y == 5)
            {
                circlrsu = 0;
                break;
            }

        }
    }
    else if(dieReady == 2 && CornerLeft_flag == 0 && CornerRight_flag == 0 && Corners_flag == 0  && findlcount >= 12
    && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 0 && Left_Up_Point[1] >= 25 && Left_Up_Point[1] <= 66 && Left_Up_Point[0] > 25 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
    && WindupL_flag == 0 && WindupR_flag == 0
    && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0
    && GarageL_flag == 0 && GarageR_flag == 0 && Cross_flag == 0 && Trifork_flag == 0
    && RampReady_flag == 0 && CornerS_flag == 0 && Ramp_flag == 0
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[(Left_Up_Point[1]+105)/2]
    && Right_Black_Point[(Left_Up_Point[1]+105)/2] <  Right_Black_Point[105]
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_one_third(105,Left_Up_Point[1])]
    && Right_Black_Point[Emo_one_third(105,Left_Up_Point[1])] <  Right_Black_Point[105]
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_two_third(105,Left_Up_Point[1])]
    && Right_Black_Point[Emo_two_third(105,Left_Up_Point[1])] <  Right_Black_Point[105]
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[105]
    && Right_Black_Point[10] < Right_Black_Point[Left_Up_Point[1]] && Right_Black_Point[10] < Right_Black_Point[(Left_Up_Point[1]+10)/2]
    && Left_Black_Point[Left_Up_Point[1]] >= Left_Black_Point[Left_Up_Point[1]+1] && Left_Black_Point[Left_Up_Point[1]+1] >= Left_Black_Point[Left_Up_Point[1]+2]
    && Left_Black_Point[Left_Up_Point[1]+2] >= Left_Black_Point[Left_Up_Point[1]+3] && Left_Black_Point[Left_Up_Point[1]+3] >= Left_Black_Point[Left_Up_Point[1]+4]
    && Left_Black_Point[Left_Up_Point[1]+4] >= Left_Black_Point[Left_Up_Point[1]+5] && Left_Black_Point[Left_Up_Point[1]+5] >= Left_Black_Point[Left_Up_Point[1]+6]
    && Left_Black_Point[Left_Up_Point[1]] > Left_Black_Point[Left_Up_Point[1]+5] && Left_Black_Point[Left_Up_Point[1]+1] > Left_Black_Point[Left_Up_Point[1]+6]
    && Left_Black_Point[Left_Up_Point[1]] > Left_Black_Point[Left_Up_Point[1]+8] && Left_Black_Point[Left_Up_Point[1]+1] > Left_Black_Point[Left_Up_Point[1]+9]
    && Left_Black_Point[Left_Up_Point[1]] > Left_Black_Point[Left_Up_Point[1]+11] && Left_Black_Point[Left_Up_Point[1]+1] > Left_Black_Point[Left_Up_Point[1]+12])
    {
        for(uint8 y=Left_Up_Point[1] - 3;y>=5;y--)
        {
            if(circlrsu == 0 && Left_Black_Point[y] >= Left_Black_Point[y-1] && Left_Black_Point[y-1] >= Left_Black_Point[y-2] && Left_Black_Point[y] > Left_Black_Point[y-2] )
            {
                circlrsu = 1;
            }
            if(circlrsu == 1)
            {
                if(Left_Black_Point[y] >= 0 && Left_Black_Point[y-1] <= 10 && Left_Black_Point[y-2] <= 10)
                {
                    CircleLeft_flag = 1;
                    Circlecount = 12;
                    //CircleBig = 1;
                    circlrsu = 0;
                    break;
                }
            }
            if(y == 5)
            {
                circlrsu = 0;
                break;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      Բ������
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
static uint8 RX = 0;
static uint8 RY = 0;
static int await = 0;
static unsigned char CC = 0;
//Բ��,������ۣ���һ����һ��
void Circle(void)
{
    uint8 ReplacePoint = 0;

    Circle_supplement();
    if(CircleLeft_flag == 1)
    {
        Beepindex = BeepCircle;
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount > 6 && Circlecount == 0)  //���¹ղ���
        {
            Circlecount = 1;
        }
        if(Circlecount == 1)
        {
            EncoderSum_flag = 1;
            if(Real_Distance >= 10000 && CircleBig == 0)
           {
               EncoderSum_flag = 0;
               CircleLeft_flag = 0;
               Circlecount = 0;
               Beepindex = 0;
               PaddingR = 0;
               PaddingL = 0;
           }
           else if(Real_Distance >= 11000 && CircleBig == 1)
           {
               EncoderSum_flag = 0;
               CircleLeft_flag = 0;
               Circlecount = 0;
               Beepindex = 0;
               PaddingR = 0;
               PaddingL = 0;
           }
            if(Real_Distance >= 3000)
            {
                Circlecount = 3;
            }
            if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0 && Left_Down_Point[1] > 80)    //�¹���ʧ�Ϲղ���
            {
                Circlecount = 2;
            }
            else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount <= 3
                && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
                 && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
        }
        if(Circlecount == 12)
        {
            //EncoderSum_flag = 1;
            if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 0)    //�¹ճ��֣����Ϲ�
            {
                Circlecount = 3;
            }
            else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
                 && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount <= 3
                 && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            else if(Left_Up_Point_finish_flag == 1 && Left_Up_Point[1] <= 40 && findlcount <= 4 && Left_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
        }
        if(Circlecount == 2)
        {
            if(Real_Distance >= 10000 && CircleBig == 0)
           {
               EncoderSum_flag = 0;
               CircleLeft_flag = 0;
               Circlecount = 0;
               Beepindex = 0;
               PaddingR = 0;
               PaddingL = 0;
           }
            else if(Real_Distance >= 11000 && CircleBig == 1)
           {
               EncoderSum_flag = 0;
               CircleLeft_flag = 0;
               Circlecount = 0;
               Beepindex = 0;
               PaddingR = 0;
               PaddingL = 0;
           }
            if(Real_Distance >= 3000)
            {
                Circlecount = 3;
            }
            if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 0)    //�¹ճ��֣����Ϲ�
            {
                Circlecount = 3;
            }
            else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
                 && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount <= 3
                 && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
//            else if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 1)   //�Ϲ�б���߽���
//            {
//                Circlecount = 4;
//            }
        }
        if(Circlecount == 3)
        {
            if(Real_Distance >= 10000 && CircleBig == 0)
           {
               EncoderSum_flag = 0;
               CircleLeft_flag = 0;
               Circlecount = 0;
               Beepindex = 0;
               PaddingR = 0;
               PaddingL = 0;
           }
           else if(Real_Distance >= 11000 && CircleBig == 1)
           {
               EncoderSum_flag = 0;
               CircleLeft_flag = 0;
               Circlecount = 0;
               Beepindex = 0;
               PaddingR = 0;
               PaddingL = 0;
           }
            if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
            && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 5] == EmoWhite)        //�Ϲ�б���߽���
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount <= 3
                 && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            else if(Left_Up_Point_finish_flag == 1 && Left_Up_Point[1] <= 40 && findlcount <= 4 && Left_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
        }
        if(Circlecount == 4)
        {
            //Paddingcurve = 1;
            Gyroscope_Star_flag = 1;
            EncoderSum_flag = 1;
            if(Left_Up_Point[1] < (RY - 10) && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 10] != EmoWhite)
            {
                Left_Up_Point[0] = RX;
                Left_Up_Point[1] = RY;
            }
            RX = Left_Up_Point[0];
            RY = Left_Up_Point[1];
            if(Left_Up_Point[1] >= 17)
            {
                CC = 1;
            }
            if(Left_Up_Point[1] > 23)
            {
                need_cornerL = 1;
            }
            if(Real_Distance >= 2500 && CircleBig == 1)
            {
                need_cornerL = 0;
            }
            if(Real_Distance >= 3000 && CircleBig == 0)
            {
                need_cornerL = 0;
            }
            if(Left_Up_Point[1] > 60)
            {
                Auxiliary_CorneringLeft_flag = 1;
            }
            if(Emo_Angle >= 18)
            {
                Auxiliary_CorneringLeft_flag = 0;
            }
            if(Left_Up_Point_finish_flag == 0 && Real_Distance >= 4500)        //�¹���ʧ���Ϲ�б���߽���
            {
                if(Emo_Angle >= 28)                   //����ɹ�
                {
                    need_cornerL = 0;
                    Auxiliary_CorneringLeft_flag = 0;
                    Gyroscope_Star_flag = 0;
                    Circlecount = 5;
                    Paddingcurve = 0;
                    EncoderSum_flag = 0;
                    CC = 0;
                }
                else                                  //����ʧ��
                {
                    if(Element_Charge == 1)
                    {
                        Element_Charge = 0;
                    }
                    CircleBig = 0;
                    need_cornerL = 0;
                    EncoderSum_flag = 0;
                    Gyroscope_Star_flag = 0;
                    CircleLeft_flag = 0;
                    Corners_flag = 0;
                    Near_Corners_flag = 0;
                    Circlecount = 0;
                    PaddingR = 0;
                    PaddingL = 0;
                    Paddingcurve = 0;
                    Beepindex = 0;
                    CC = 0;
                }
            }
        }
        if(Circlecount == 5)
        {
            await++;
            if(await >= 3)
            {
                Gyroscope_Star_flag = 1;
                EncoderSum_flag = 1;
                if(Real_Distance >= 3000 )                                            //��������ʧ��������������Բ������ʸ����
                {
                    if(Emo_Angle > 28)
                    {
                        Circlecount = 6;
                        EncoderSum_flag = 0;
                        Gyroscope_Star_flag = 0;
                        await = 0;
                    }
                    else
                    {
                        if(Element_Charge == 1)
                        {
                            Element_Charge = 0;
                        }
                        need_cornerL = 0;
                        CircleBig = 0;
                        EncoderSum_flag = 0;
                        Gyroscope_Star_flag = 0;
                        CircleLeft_flag = 0;
                        Corners_flag = 0;
                        Near_Corners_flag = 0;
                        Circlecount = 0;
                        Beepindex = 0;
                        PaddingR = 0;
                        PaddingL = 0;
                        await = 0;
                    }
                }
            }

        }
        if(Circlecount == 6)
        {
            //CircleInTrial();
            if(Right_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 0)       //�ҹճ��֣������ҹ�б���߳���
            {
                Circlecount = 7;
            }
        }
        if(Circlecount == 7)
        {
            Paddingcurve = 1;
            CircleOutPoint();
            Gyroscope_Star_flag = 1;
            EncoderSum_flag = 1;
            //need_cornerL = 1;
//            if(Right_Down_Point_finish_flag == 0 && Right_Down_Point[1] > 74)
//            {
//                Auxiliary_CorneringLeft_flag = 1;
//            }
            if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0
                && Real_Distance >= 3800 && Emo_Angle > 38)      //���ڳ����¹ճ����Ϲ���
            {
                //Auxiliary_CorneringLeft_flag = 0;
                //need_cornerL =  0;
                Paddingcurve = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Circlecount = 8;
            }
            else if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0
                    && Real_Distance >= 3800 && Emo_Angle > 38)  //���ڳ����¹ն���
            {
                //Auxiliary_CorneringLeft_flag = 0;
                //need_cornerL = 0;
                Paddingcurve = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Circlecount = 9;

            }
            else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0
                    && Real_Distance >= 3800 && Emo_Angle > 38)  //�¹յ���
            {
                //Auxiliary_CorneringLeft_flag = 0;
                //need_cornerL = 0;
                Paddingcurve = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Encoder_SumClear();
                Circlecount = 10;
            }
        }
        if(Circlecount == 8)
        {
            Encoder_SumClear();
            if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 1)       //���¹ղ�����ֻ��¼
            {
                Circlecount = 9;
            }
            else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1)  //�Ϲյ���
            {
                Circlecount = 10;
            }
        }
        if(Circlecount == 9)
        {
            Circlecount = 10;
            Encoder_SumClear();
            if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1)       //�Ϲյ���
            {
                Circlecount = 10;
            }
        }
        if(Circlecount == 10)                                                            //Բ������
        {
            EncoderSum_flag = 1;
            if(Left_Up_Point[1] >= 63 || (Real_Distance >= 4000 && CircleBig == 0) || (Real_Distance >= 5000 && CircleBig == 1))
            {
                Circlecount = 11;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
        }
        switch(Circlecount)
        {
            case 1 :
                Link_Left_One_Point[0] = Left_Down_Point[0];
                Link_Left_One_Point[1] = Left_Down_Point[1];
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 2 :
                Link_Left_One_Point[0] = Left_Down_Point[0];
                Link_Left_One_Point[1] = Left_Down_Point[1];
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 3 :
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 0;
                Link_Left_Two_Point[0] = 0;
                Link_Left_Two_Point[1] = 0;
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 4 :
                Link_Right_One_Point[0] = Left_Up_Point[0];
                Link_Right_One_Point[1] = Left_Up_Point[1];
                if(Left_Up_Point[1]*2 + 40 > 112)
                {
                    ReplacePoint = 112;
                }
                else
                {
                    ReplacePoint = Left_Up_Point[1]*2 + 40;
                }
                Link_Right_Two_Point[0] = Right_Black_Point[ReplacePoint];
                Link_Right_Two_Point[1] = ReplacePoint;
                Corners_flag = 1;
//                if((Right_Black_Point[100] == 187 && Right_Black_Point[99] == 187 && Right_Black_Point[98] == 187
//                    && Left_Black_Point[100] != 0 && Left_Black_Point[99] != 0 && Left_Black_Point[98] != 0
//                    && Left_Black_Point[95] != 0 && Left_Black_Point[94] != 187 && Left_Black_Point[93] != 187)
//                 || (Left_Black_Point[100] == 0 && Left_Black_Point[99] == 0 && Left_Black_Point[98] == 0
//                    && Right_Black_Point[100] != 187 && Right_Black_Point[99] != 187 && Right_Black_Point[98] != 187
//                    && Right_Black_Point[95] != 187 && Right_Black_Point[94] != 187 && Right_Black_Point[93] != 187))
//                {
//                    Near_Corners_flag = 1;
//                }
//                else
//                {
//                    Near_Corners_flag = 0;
//                }
                if(CC == 1)
                {
                    if(Right_Black_Point[Left_Up_Point[1]] < Left_Up_Point[0] && Right_Black_Point[63] != 187 && Left_Up_Point[1] >= 30)
                    {
                        Paddingcurve = 0;
                        PaddingR = 0;
                        PaddingL = 0;
                    }
                    else
                    {
                        Paddingcurve = 1;
                        PaddingR = 1;
                        PaddingL = 0;
                    }
                }
                else
                {
                    Paddingcurve = 0;
                    PaddingR = 0;
                    PaddingL = 0;
                    Corners_flag = 0;
                }
                break;
            case 5 :
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 6 :
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 7 :
                Link_Right_One_Point[0] = CircleOut_Point[0];
                Link_Right_One_Point[1] = CircleOut_Point[1];
                Link_Right_Two_Point[0] = Right_Down_Point[0];
                Link_Right_Two_Point[1] = Right_Down_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 8 :
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 0;
                Link_Left_Two_Point[0] = Left_Down_Point[0];
                Link_Left_Two_Point[1] = Left_Down_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 9 :
                Link_Left_One_Point[0] = Left_Down_Point[0];
                Link_Left_One_Point[1] = Left_Down_Point[1];
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 10 :
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 11 :
                CircleLeft_flag = 0;
                CircleBig = 0;
                if(Element_Charge == 1)
                {
                    Element_Charge = 0;
                }
                Corners_flag = 0;
                //Near_Corners_flag = 0;
                Circlecount = 0;
                PaddingR = 0;
                PaddingL = 0;
                Beepindex = 0;
                CRC++;
                break;
            case 12 :
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
        }
    }
    else if(CircleRight_flag == 1)
    {
        Beepindex = BeepCircle;
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && findrcount > 6 && Circlecount == 0)  //���¹ղ���
        {
            Circlecount = 1;
        }
        if(Circlecount == 1)
        {
            EncoderSum_flag = 1;
            if(Real_Distance >= 10000 && CircleBig == 0)
            {
                EncoderSum_flag = 0;
                CircleRight_flag = 0;
                Circlecount = 0;
                Beepindex = 0;
                PaddingR = 0;
                PaddingL = 0;
            }
            else if(Real_Distance >= 11000 && CircleBig == 1)
            {
                EncoderSum_flag = 0;
                CircleRight_flag = 0;
                Circlecount = 0;
                Beepindex = 0;
                PaddingR = 0;
                PaddingL = 0;
            }
            if(Real_Distance >= 3000)
            {
                Circlecount = 3;
            }
            if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0 && Right_Down_Point[1] > 80)   //�¹���ʧ�Ϲղ���
            {
                Circlecount = 2;
            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && findrcount <= 3 && Right_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1
            && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && findrcount <= 3 && Right_Up_Point[1] > 15)        //�Ϲ�б���߽���
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
        }
        if(Circlecount == 12)
        {
            //EncoderSum_flag = 1;
            if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 0)    //�¹ճ��֣����Ϲ�
            {
                Circlecount = 3;
            }
            else if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && Right_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && findrcount <= 3 && Right_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();

            }
            else if(Right_Up_Point_finish_flag == 1 && Right_Up_Point[1] < 40 && findrcount <= 4 && Right_Up_Point[1] > 15)
           {
               Circlecount = 4;
               EncoderSum_flag = 0;
               Encoder_SumClear();
           }
        }
        if(Circlecount == 2)
        {
            if(Real_Distance >= 10000 && CircleBig == 0)
           {
               EncoderSum_flag = 0;
               CircleRight_flag = 0;
               Circlecount = 0;
               Beepindex = 0;
               PaddingR = 0;
               PaddingL = 0;
           }
           else if(Real_Distance >= 11000 && CircleBig == 1)
           {
               EncoderSum_flag = 0;
               CircleRight_flag = 0;
               Circlecount = 0;
               Beepindex = 0;
               PaddingR = 0;
               PaddingL = 0;
           }
            if(Real_Distance >= 3000)
            {
                Circlecount = 3;
            }
            if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 0)    //�¹ճ��֣����Ϲ�
            {
                Circlecount = 3;
            }
            else if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && Right_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && findrcount <= 3 && Right_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();

            }
//            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1)   //�Ϲ�б���߽���
//            {
//                Circlecount = 4;
//            }
        }
        if(Circlecount == 3)
        {
            if(Real_Distance >= 10000 && CircleBig == 0)
           {
               EncoderSum_flag = 0;
               CircleRight_flag = 0;
               Circlecount = 0;
               Beepindex = 0;
               PaddingR = 0;
               PaddingL = 0;
           }
           else if(Real_Distance >= 11000 && CircleBig == 1)
           {
               EncoderSum_flag = 0;
               CircleRight_flag = 0;
               Circlecount = 0;
               Beepindex = 0;
               PaddingR = 0;
               PaddingL = 0;
           }
            if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1
            && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite)        //�Ϲ�б���߽���
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && findrcount <= 3 && Right_Up_Point[1] > 15)
            {
                Circlecount = 4;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
            else if(Right_Up_Point_finish_flag == 1 && Right_Up_Point[1] < 40 && findrcount <= 4 && Right_Up_Point[1] > 15)
           {
               Circlecount = 4;
               EncoderSum_flag = 0;
               Encoder_SumClear();
           }
        }
        if(Circlecount == 4)
        {
            Gyroscope_Star_flag = 1;
            EncoderSum_flag = 1;
            if(Right_Up_Point[1] < (RY - 10) && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 10] == EmoWhite)
            {
                Right_Up_Point[0] = RX;
                Right_Up_Point[1] = RY;
                //Right_Up_Point_finish_flag = 0;
            }
            RX = Right_Up_Point[0];
            RY = Right_Up_Point[1];
            if(Right_Up_Point[1] > 23)
            {
                need_cornerR = 1;
            }
            if(Real_Distance >= 2500 && CircleBig == 1)
            {
                need_cornerR = 0;
            }
            if(Real_Distance >= 3000 && CircleBig == 0)
            {
                need_cornerR = 0;
            }
            if(Right_Up_Point[1] > 60)
            {
                Auxiliary_CorneringRight_flag = 1;
            }
            if(Emo_Angle <= -18)
            {
                Auxiliary_CorneringRight_flag = 0;
            }
            if(Right_Up_Point_finish_flag == 0 && Real_Distance >= 4500)        //�¹���ʧ���Ϲ�б���߽���
            {
                if(Emo_Angle <= -28)        //����ɹ�
                {
                    need_cornerR = 0;
                    Auxiliary_CorneringRight_flag = 0;
                    Gyroscope_Star_flag = 0;
                    Circlecount = 5;
                    EncoderSum_flag = 0;
                    Paddingcurve = 0;
                }
                else                     //����ʧ��
                {
                    if(Element_Charge == 1)
                    {
                        Element_Charge = 0;
                    }
                    CircleBig = 0;
                    need_cornerR = 0;
                    Gyroscope_Star_flag = 0;
                    EncoderSum_flag = 0;
                    CircleRight_flag = 0;
                    Corners_flag = 0;
                    Near_Corners_flag = 0;
                    Paddingcurve = 0;
                    Circlecount = 0;
                    PaddingR = 0;
                    PaddingL = 0;
                    Beepindex = 0;
                }
            }
        }
        if(Circlecount == 5)
        {
            await++;
            if(await >= 3)
            {
                Gyroscope_Star_flag = 1;
                EncoderSum_flag = 1;
                if(Real_Distance > 3000)
                {
                    if(Emo_Angle < -28)
                    {
                        Circlecount = 6;
                        Gyroscope_Star_flag = 0;
                        EncoderSum_flag = 0;
                        await = 0;
                    }
                    else
                    {
                        if(Element_Charge == 1)
                        {
                            Element_Charge = 0;
                        }
                        need_cornerR = 0;
                        CircleBig = 0;
                        Gyroscope_Star_flag = 0;
                        EncoderSum_flag = 0;
                        CircleRight_flag = 0;
                        Corners_flag = 0;
                        Near_Corners_flag = 0;
                        Circlecount = 0;
                        PaddingR = 0;
                        PaddingL = 0;
                        Beepindex = 0;
                        await = 0;
                    }
                }
            }
        }
        if(Circlecount == 6)
        {
            //CircleInTrial();
            if(Left_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 0)                  //��ճ��֣��������б���߳���
            {
                Circlecount = 7;
            }
        }
        if(Circlecount == 7)
        {
            Paddingcurve = 1;
            CircleOutPoint();
            Gyroscope_Star_flag = 1;
            EncoderSum_flag = 1;
            //need_cornerR = 1 ;
//            if(Left_Down_Point_finish_flag == 0 && Left_Down_Point[1] > 74)
//            {
//                Auxiliary_CorneringRight_flag = 1;
//            }
            if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0
                 && Real_Distance >= 3800  && Emo_Angle <-38)   //���ڳ����¹ճ����Ϲ���
            {
                //Auxiliary_CorneringRight_flag = 0;
                //need_cornerR = 0;
                Paddingcurve = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Circlecount = 8;
            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0
                    && Real_Distance >= 3800 && Emo_Angle <-38)  //���ڳ����¹ն���
            {
                //Auxiliary_CorneringRight_flag = 0;
                //need_cornerR = 0;
                Paddingcurve = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Circlecount = 9;
            }
            else if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0
                    && Real_Distance >= 3800 && Emo_Angle <-38)  //�¹յ���
            {
                //Auxiliary_CorneringRight_flag = 0;
                //need_cornerR = 0;
                Paddingcurve = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Encoder_SumClear();
                Circlecount = 10;
            }
        }
        if(Circlecount == 8)
        {
            Encoder_SumClear();
            if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1)
            {
                Circlecount = 9;
            }
            else if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1)  //�Ϲյ���
            {
                Circlecount = 10;
            }
        }
        if(Circlecount == 9)
        {
            Circlecount = 10;
            Encoder_SumClear();
            if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1)  //�Ϲյ���
            {
                Circlecount = 10;
            }
        }
        if(Circlecount == 10)
        {
            EncoderSum_flag = 1;
            if(Right_Up_Point[1] >= 60 || (Real_Distance >= 3500 && CircleBig == 0) || (Real_Distance >= 4500 && CircleBig == 1))     //Բ������
            {
                Circlecount = 11;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
        }
        switch(Circlecount)
        {
            case 1 :
                Link_Right_One_Point[0] = Right_Down_Point[0];
                Link_Right_One_Point[1] = Right_Down_Point[1];
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 2 :
                Link_Right_One_Point[0] = Right_Down_Point[0];
                Link_Right_One_Point[1] = Right_Down_Point[1];
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 3 :
                Link_Right_One_Point[0] = 0;
                Link_Right_One_Point[1] = 0;
                Link_Right_Two_Point[0] = 0;
                Link_Right_Two_Point[1] = 0;
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 4 :
                Link_Left_One_Point[0] = Right_Up_Point[0];
                Link_Left_One_Point[1] = Right_Up_Point[1];
                if(Right_Up_Point[1]*2 + 40 > 112)
                {
                    ReplacePoint = 112;
                }
                else
                {
                    ReplacePoint = Right_Up_Point[1]*2 + 40;
                }
                Link_Left_Two_Point[0] = Left_Black_Point[ReplacePoint];
                Link_Left_Two_Point[1] = ReplacePoint;
                Corners_flag = 1;
//                if((Right_Black_Point[100] == 187 && Right_Black_Point[99] == 187 && Right_Black_Point[98] == 187
//                    && Left_Black_Point[100] != 0 && Left_Black_Point[99] != 0 && Left_Black_Point[98] != 0
//                    && Left_Black_Point[95] != 0 && Left_Black_Point[94] != 187 && Left_Black_Point[93] != 187)
//                 || (Left_Black_Point[100] == 0 && Left_Black_Point[99] == 0 && Left_Black_Point[98] == 0
//                    && Right_Black_Point[100] != 187 && Right_Black_Point[99] != 187 && Right_Black_Point[98] != 187
//                    && Right_Black_Point[95] != 187 && Right_Black_Point[94] != 187 && Right_Black_Point[93] != 187))
//                {
//                    Near_Corners_flag = 1;
//                }
//                else
//                {
//                    Near_Corners_flag = 0;
//                }
                if(Left_Black_Point[Right_Up_Point[1]] > Right_Up_Point[0] && Left_Black_Point[62] != 0 && Right_Up_Point[1] >= 30)
                {
                    Paddingcurve = 0;
                    PaddingR = 0;
                    PaddingL = 0;
                }
                else
                {
                    Paddingcurve = 1;
                    PaddingR = 0;
                    PaddingL = 1;
                }
                break;
            case 5 :
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 6 :
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 7 :
                Link_Left_One_Point[0] = CircleOut_Point[0];
                Link_Left_One_Point[1] = CircleOut_Point[1];
                Link_Left_Two_Point[0] = Left_Down_Point[0];
                Link_Left_Two_Point[1] = Left_Down_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 8 :
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 0;
                Link_Right_Two_Point[0] = Right_Down_Point[0];
                Link_Right_Two_Point[1] = Right_Down_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 9 :
                Link_Right_One_Point[0] = Right_Down_Point[0];
                Link_Right_One_Point[1] = Right_Down_Point[1];
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 10 :
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 11 :
                if(Element_Charge == 1)
                {
                    Element_Charge = 0;
                }
                CircleRight_flag = 0;
                Corners_flag = 0;
                CircleBig = 0;
                //Near_Corners_flag = 0;
                Circlecount = 0;
                PaddingR = 0;
                PaddingL = 0;
                Beepindex = 0;
                CRC++;
                break;
            case 12 :
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���溯��
//  @param      TRI_TRI   ����ת����������ײ������·�磬���Ըı���������ʱ��
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
static unsigned char TRI_TRI = 0;
static uint8 TX = 0,TY = 0;
//����·��
void Trifork_Shuttle(void)
{
    if(Trifork_flag == 1)
    {
        Beepindex = BeepThreefork;
        if(Triforkcount == 0 )
        {
//            TriforkPoint();
            Triforkcount = 1;
        }
        if(Triforkcount == 1)
        {
            Trifork_Judge();
            if(Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0)
            {
                Trifork_MIddlePoint();
            }
//            Gyroscope_Star_flag = 1;
//            EncoderSum_flag = 1;
//            TRI_TRI = 1;
//            if(TriforkMiddle_Point[1] >= 30 && TriforkRight_Point[1] >= 60 && Pre_Speed <= 115 )
//            {
//                Gyroscope_Star_flag = 1;
//                EncoderSum_flag = 1;
//                TRI_TRI = 1;
//            }
//            if(TriforkMiddle_Point[1] >= 26 && TriforkRight_Point[1] >= 58 && Pre_Speed > 115 && Pre_Speed <= 135)
//            {
//                Gyroscope_Star_flag = 1;
//                EncoderSum_flag = 1;
//                TRI_TRI = 1;
//            }
//            if(TriforkTurn == 0)
//            {
//                if(TriforkMiddle_Point[1] >= 22 && TriforkRight_Point[1] >= 51)
//                {
//                    Gyroscope_Star_flag = 1;
//                    EncoderSum_flag = 1;
//                    TRI_TRI = 1;
//                }
//            }
//            if(TriforkMiddle_Point[1] >= 23 && TriforkRight_Point[1] >= 48 && TriforkTurn > 0 )
//            {
            if(TriforkMiddle_Point[1] >= 30)
            {
                Gyroscope_Star_flag = 1;
                EncoderSum_flag = 1;
            }
                TRI_TRI = 1;
//            }
//            else if(TriforkMiddle_Point[1] >= 22 && TriforkRight_Point[1] >= 48 && TriforkTurn == 0)
//            {
//                Gyroscope_Star_flag = 1;
//                EncoderSum_flag = 1;
//                TRI_TRI = 1;
//            }
//            if(Pre_Speed > 145 && Pre_Speed <= 175)
//            {
//                Gyroscope_Star_flag = 1;
//                EncoderSum_flag = 1;
//                TRI_TRI = 1;
//            }
            if(TriforkLeft_Point[1] > TriforkMiddle_Point[1])
            {
                TX = TriforkMiddle_Point[0];
                TY = TriforkMiddle_Point[1];
            }
            else
            {
                TriforkMiddle_Point[0] = TX;
                TriforkMiddle_Point[1] = TY;
            }
//            if(TriforkMiddle_Point[1] > 75)
//            {
//                Auxiliary_CorneringRight_flag = 1;
//            }
            if(Real_Distance >= 2800 && Real_Distance < 4500)
            {
                if(Emo_Angle < -16)
                {
                    TRI_TRI = 0;
                    Gyroscope_Star_flag = 0;
                    EncoderSum_flag = 0;
                    Triforkcount = 2;
                    ObservationT_finish = 0;
                    CorneringT_finish = 0;
                }
            }
            else if(Real_Distance >= 4500)
            {
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Encoder_SumClear();
                Triforkcount = 0;
                TRI_TRI = 0;
                ObservationT_finish = 0;
                CorneringT_finish = 0;
                Trifork_flag = 0;
                Beepindex = 0;
                Triforkpadding_flag = 0;
                PaddingR = 0;
                PaddingL = 0;
            }
//            if(Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0 && Trifork_PointMiddle_Findfinish_flag == 0 && Emo_Angle < -17)
//            {
//                Auxiliary_CorneringRight_flag = 0;
//                Gyroscope_Star_flag = 0;
//                Triforkcount = 2 ;
//            }
//            if(TriforkMiddle_Point[1] > 72)
//            {
//                ObservationT_finish = 1;
//            }
//            if(Emo_Angle < -23)
//            {
//                CorneringT_finish = 1;
//                Auxiliary_CorneringRight_flag = 0;
//            }
//            if(ObservationT_finish == 1 && CorneringT_finish == 1)
//            {
//                Auxiliary_CorneringRight_flag = 0;
//                Gyroscope_Star_flag = 0;
//                Triforkcount = 2;
//                ObservationT_finish = 0;
//                CorneringT_finish = 0;
//            }
        }
        if(Triforkcount == 2)
        {
            Trifork_Judge();
//            if(Trifork_PointMiddle_Findfinish_flag == 0 && Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0)
//            {
//                TriforkTrial();
//            }
            if(Trifork_PointMiddle_Findfinish_flag == 1 && Trifork_PointLeft_Findfinish_flag == 1 && Trifork_PointRight_Findfinish_flag == 1)
            {
                Triforkcount = 3;
                need_cornerR = 0;
                need_cornerL = 0;
            }
            TJudge_Ramp();
        }
        if(Triforkcount == 3)
        {
            Trifork_Judge();
            if(Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0)
            {
                Trifork_MIddlePoint();
            }
//            Gyroscope_Star_flag = 1;
//            EncoderSum_flag = 1;
//            TRI_TRI = 1;
//            if(TriforkMiddle_Point[1] >= 30 && TriforkRight_Point[1] >= 60 && Pre_Speed <= 115 )
//            {
//                Gyroscope_Star_flag = 1;
//                EncoderSum_flag = 1;
//                TRI_TRI = 1;
//            }
//            if(TriforkMiddle_Point[1] >= 26 && TriforkRight_Point[1] >= 58 && Pre_Speed > 115 && Pre_Speed <= 135)
//            {
//                Gyroscope_Star_flag = 1;
//                EncoderSum_flag = 1;
//                TRI_TRI = 1;
//            }
//            if(TriforkMiddle_Point[1] >= 23 && TriforkRight_Point[1] >= 48 && TriforkTurn > 0 )
//            {
            if(TriforkMiddle_Point[1] >= 30)
            {
                Gyroscope_Star_flag = 1;
                EncoderSum_flag = 1;
            }
                TRI_TRI = 1;
//            }
//            else if(TriforkMiddle_Point[1] >= 22 && TriforkRight_Point[1] >= 48 && TriforkTurn == 0)
//            {
//                Gyroscope_Star_flag = 1;
//                EncoderSum_flag = 1;
//                TRI_TRI = 1;
//            }
//            if(Pre_Speed > 145 && Pre_Speed <= 175)
//            {
//                Gyroscope_Star_flag = 1;
//                EncoderSum_flag = 1;
//                TRI_TRI = 1;
//            }
            if(TriforkLeft_Point[1] > TriforkMiddle_Point[1])
            {
                TX = TriforkMiddle_Point[0];
                TY = TriforkMiddle_Point[1];
            }
            else
            {
                TriforkMiddle_Point[0] = TX;
                TriforkMiddle_Point[1] = TY;
            }
//            if(TriforkMiddle_Point[1] > 75)
//            {
//                Auxiliary_CorneringRight_flag = 1;
//            }
//            if(Trifork_PointLeft_Findfinish_flag == 0 && Trifork_PointRight_Findfinish_flag == 0 && Trifork_PointMiddle_Findfinish_flag == 0 && Emo_Angle < -17)
//            {
//                Auxiliary_CorneringRight_flag = 0;
//                Gyroscope_Star_flag = 0;
//                Triforkcount = 4;
//            }
            if(Real_Distance >= 2800 && Real_Distance < 5000)
            {
                if(Emo_Angle < -16)
                {
                    TRI_TRI = 0;
                    Gyroscope_Star_flag = 0;
                    EncoderSum_flag = 0;
                    Triforkcount = 4;
                    ObservationT_finish = 0;
                    CorneringT_finish = 0;
                }
            }
            else if(Real_Distance >= 5000)
            {
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Encoder_SumClear();
                Triforkcount = 0;
                TRI_TRI = 0;
                ObservationT_finish = 0;
                CorneringT_finish = 0;
                Trifork_flag = 0;
                Beepindex = 0;
                Triforkpadding_flag = 0;
                PaddingR = 0;
                PaddingL = 0;
                TriforkTurn++;
            }
//            if(Emo_Angle < -16)
//            {
//                CorneringT_finish = 1;
//                Auxiliary_CorneringRight_flag = 0;
//            }
//            if(ObservationT_finish == 1 && CorneringT_finish == 1)
//            {
//                Auxiliary_CorneringRight_flag = 0;
//                Gyroscope_Star_flag = 0;
//                EncoderSum_flag = 0;
//                Triforkcount = 4;
//                ObservationT_finish = 0;
//                CorneringT_finish = 0;
//            }
        }
        switch(Triforkcount)    //Ĭ����������ż�����ң���������Ӧ�ò�ͬһ����:��
        {
            case 1 :
                if(TRI_TRI == 1)
                {
                    Link_Left_One_Point[0] = TriforkMiddle_Point[0];
                    Link_Left_One_Point[1] = TriforkMiddle_Point[1];
                    Link_Left_Two_Point[0] = TriforkLeft_Point[0];
                    Link_Left_Two_Point[1] = TriforkLeft_Point[1];
                    Triforkpadding_flag = 1;
                    PaddingR = 0;
                    PaddingL = 1;
                }
                else
                {
                    Link_Left_One_Point[0] = TriforkMiddle_Point[0];
                    Link_Left_One_Point[1] = TriforkMiddle_Point[1];
                    Link_Left_Two_Point[0] = TriforkLeft_Point[0];
                    Link_Left_Two_Point[1] = TriforkLeft_Point[1];
                    Link_Right_One_Point[0] = TriforkMiddle_Point[0];
                    Link_Right_One_Point[1] = TriforkMiddle_Point[1];
                    Link_Right_Two_Point[0] = TriforkRight_Point[0];
                    Link_Right_Two_Point[1] = TriforkRight_Point[1];
                    PaddingR = 1;
                    PaddingL = 1;
                }
                if(Real_Distance >= 2000 && Left_Black_Point[100] > 0 && Left_Black_Point[105] > 0)
                {
                    PaddingR = 0;
                    PaddingL = 0;
                    Triforkpadding_flag = 0;
                }
//                    Link_Left_One_Point[0] = TriforkMiddle_Point[0];
//                    Link_Left_One_Point[1] = TriforkMiddle_Point[1];
//                    Link_Left_Two_Point[0] = TriforkLeft_Point[0] - 10;
//                    Link_Left_Two_Point[1] = TriforkLeft_Point[1] - 10;
                    //Paddingcurve = 1;
//                Triforkpadding_flag = 1;
//                PaddingR = 0;
//                PaddingL = 1;
                break;
            case 2 :
                Corners_flag = 1;
                Triforkpadding_flag = 0;
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 3 :
                if(TRI_TRI == 1)
                {
                    Link_Left_One_Point[0] = TriforkMiddle_Point[0];
                    Link_Left_One_Point[1] = TriforkMiddle_Point[1];
                    Link_Left_Two_Point[0] = TriforkLeft_Point[0];
                    Link_Left_Two_Point[1] = TriforkLeft_Point[1];
                    Triforkpadding_flag = 1;
                    PaddingR = 0;
                    PaddingL = 1;
                }
                else
                {
                    Link_Left_One_Point[0] = TriforkMiddle_Point[0];
                    Link_Left_One_Point[1] = TriforkMiddle_Point[1];
                    Link_Left_Two_Point[0] = TriforkLeft_Point[0];
                    Link_Left_Two_Point[1] = TriforkLeft_Point[1];
                    Link_Right_One_Point[0] = TriforkMiddle_Point[0];
                    Link_Right_One_Point[1] = TriforkMiddle_Point[1];
                    Link_Right_Two_Point[0] = TriforkRight_Point[0];
                    Link_Right_Two_Point[1] = TriforkRight_Point[1];
                    PaddingR = 1;
                    PaddingL = 1;
                }
                if(Real_Distance >= 2000 && Left_Black_Point[100] > 0 && Left_Black_Point[105] > 0)
                {
                    PaddingR = 0;
                    PaddingL = 0;
                    Triforkpadding_flag = 0;
                }
                break;
            case 4 :
                PaddingR = 0;
                PaddingL = 0;
                Triforkpadding_flag = 0;
                Triforkcount = 0;
                Trifork_flag = 0;
                Beepindex = 0;
                Corners_flag = 0;
//                TRC++;
                TriforkTurn++;
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
                break;
        }

    }
}

/*******************����**********************/
//���ҵ�Ҫ����������ߣ�ͨ���������б�ʵõ�������ɵ�һ�η��̣��õ�ʣ��x��λ�ã����߻������ұ���
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ֱ�߲��ߺ���
//  @param      xone  ��һ�����ߵ�x����
//  @param      yone  ��һ�����ߵ�y����
//  @param      xtwo  �ڶ������ߵ�x����
//  @param      ytwo  �ڶ������ߵ�y����
//  @return     void
//  @note  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void Padding_LineR(uint8 xone,uint8 yone,uint8 xtwo,uint8 ytwo)
{
    float k=0;  //б��
    float b=0;  //�ؾ�
    //uint8 xstar=0;
    //uint8 xend=0;
    uint8 ystar=0;
    uint8 yend=0;

    k=((float)ytwo - (float)yone)/((float)xtwo - (float)xone);
    //k=((float)xtwo - (float)xone)/((float)ytwo - (float)yone);
    b=(float)yone - ((float)xone*k);

    if(yone>ytwo)
    {
        ystar=ytwo;
        yend=yone;
    }
    else
    {
        ystar=yone;
        yend=ytwo;
    }
    for(uint8 y=ystar;y<=yend;y++)
    {
        Right_Black_Point[y]=(uint8)(((float)y-b)/k);  //����֮�䲹��
    }
}

void Padding_LineL(uint8 xone,uint8 yone,uint8 xtwo,uint8 ytwo)
{
    float k=0;  //б��
    float b=0;  //�ؾ�
    //uint8 xstar=0;
    //uint8 xend=0;
    uint8 ystar=0;
    uint8 yend=0;

    k=((float)ytwo - (float)yone)/((float)xtwo - (float)xone);
    //k=((float)xtwo - (float)xone)/((float)ytwo - (float)yone);
    b=(float)yone - ((float)xone*k);

    if(yone>ytwo)
    {
        ystar=ytwo;
        yend=yone;
    }
    else
    {
        ystar=yone;
        yend=ytwo;
    }
    for(uint8 y=ystar;y<=yend;y++)
    {
        Left_Black_Point[y]=(uint8)(((float)y-b)/k);
    }
}

//�����ߣ�����������в�
//Cx�����ϵ�x��Cy�����ϵ�y
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���߲��ߺ���
//  @param      Ux  �ϲ��ߵ�x����
//  @param      Uy  �ϲ��ߵ�y����
//  @param      Dx  �²��ߵ�x����
//  @param      Dx  �²��ߵ�y����
//  @return     void
//  @note       �����������ղ�ֵ����������������ͼ��������м��Ϊ�̶��㣬�������Ч�����ã���Ҫ����У׼�м��
//  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void Padding_CurveL(uint8 Ux,uint8 Uy,uint8 Dx,uint8 Dy)
{
    int x0 = 0,x1 = 0,x2 = 0;
    int y0 = 0,y1 = 0,y2 = 0;


    //0.0096   -2.1047  138.5182
    //0.0103   -2.2049  141.8985
    //x=x0(y-y1)(y-y2)/(y0-y1)(y0-y2)+x1(y-y0)(y-y2)/(y1-y0)(y1-y2)+x2(y-y0)(y-y1)/(y2-y0)(y2-y1)
    x0 = (int)Dx;
    x1 = (int)(Dx + (float)3*(Ux-Dx)/5);
    x2 = (int)Ux;
    y0 = (int)Dy;
    y1 = (int)(Dy - (float)2*(Dy-Uy)/3);
    y2 = (int)Uy;
    if(Ux == 0 && Ux == 0 && Dx == 0 && Dy == 0)
    {

    }
    else
    {
        if(Dy > 110)
        {
            Dy = 110;
        }
        //Re = Left_Black_Point[Dy];
//        Left_Black_Point[Dy] = (uint8)(a*(float)(Dy*Dy)+b*(float)Dy+c);
        //error = (int)Re - (int)Left_Black_Point[Dy];
        for(uint8 y = Uy ;y <= Dy;y++)
        {
//            Re = y - Uy + 25;
//            Left_Black_Point[y]=(uint8)(a*(float)(Re*Re)+b*(float)Re+c);
            Left_Black_Point[y]=(uint8)((x0*(y-y1)*(y-y2))/((y0-y1)*(y0-y2)))+((x1*(y-y0)*(y-y2))/((y1-y0)*(y1-y2)))+((x2*(y-y0)*(y-y1))/((y2-y0)*(y2-y1)));
        }
    }

}

void Padding_CurveR(uint8 Ux,uint8 Uy,uint8 Dx,uint8 Dy)
{
    int x0 = 0,x1 = 0,x2 = 0;
    int y0 = 0,y1 = 0,y2 = 0;
    //0.0096   -2.1047  138.5182
    //0.0103   -2.2049  141.8985
    //x=x0(y-y1)(y-y2)/(y0-y1)(y0-y2)+x1(y-y0)(y-y2)/(y1-y0)(y1-y2)+x2(y-y0)(y-y1)/(y2-y0)(y2-y1)
    x0 = (int)Dx;
    x1 = (int)(Dx - (float)3*(Dx-Ux)/5);
    x2 = (int)Ux;
    y0 = (int)Dy;
    y1 = (int)(Dy - (float)2*(Dy-Uy)/3);
    y2 = (int)Uy;
    if(Ux == 0 && Ux == 0 && Dx == 0 && Dy == 0)
    {

    }
    else
    {
        if(Dy > 110)
        {
            Dy = 110;
        }
        for(uint8 y = Uy ;y <= Dy;y++)
        {
            Right_Black_Point[y]=(uint8)((x0*(y-y1)*(y-y2))/((y0-y1)*(y0-y2)))+((x1*(y-y0)*(y-y2))/((y1-y0)*(y1-y2)))+((x2*(y-y0)*(y-y1))/((y2-y0)*(y2-y1)));
        }
    }

}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ߺ���
//  @param      PaddingR  �Ҳ��߱�־  0�������� 1��Ҫ����
//  @param      PaddingL  ���߱�־
//  @param      Padding_CurveR  �����߲��߱�־ 0����ֱ�� 1��������
//  @param      Padding_CurveL  �����߲��߱�־
//  @return     void
//  @note       ���ߵķ�ʽ��ͨ���˺������У��ⲿֻ��Ҫ�����������ߵ��λ�ã����Ƿ����Ҳ���
//  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void Padding_Line(void)
{
    if(PaddingL == 1 && PaddingR == 1 && Paddingcurve == 0)
    {
        Padding_LineR(Link_Right_One_Point[0],Link_Right_One_Point[1],Link_Right_Two_Point[0],Link_Right_Two_Point[1]);
        Padding_LineL(Link_Left_One_Point[0],Link_Left_One_Point[1],Link_Left_Two_Point[0],Link_Left_Two_Point[1]);
    }
    else if(PaddingL == 1 && PaddingR == 0 && Paddingcurve == 0)
    {
        Padding_LineL(Link_Left_One_Point[0],Link_Left_One_Point[1],Link_Left_Two_Point[0],Link_Left_Two_Point[1]);
        Padding_LineR(0,0,0,0);
    }
    else if(PaddingL == 0 && PaddingR == 1 && Paddingcurve == 0)
    {
        Padding_LineR(Link_Right_One_Point[0],Link_Right_One_Point[1],Link_Right_Two_Point[0],Link_Right_Two_Point[1]);
        Padding_LineL(0,0,0,0);
    }
    else if(PaddingL == 0 && PaddingR == 1 && Paddingcurve == 1)
    {
        Padding_CurveR(Link_Right_One_Point[0],Link_Right_One_Point[1],Link_Right_Two_Point[0],Link_Right_Two_Point[1]);
        Padding_CurveL(0,0,0,0);
    }
    else if(PaddingL == 1 && PaddingR == 0 && Paddingcurve == 1)
    {
        Padding_CurveL(Link_Left_One_Point[0],Link_Left_One_Point[1],Link_Left_Two_Point[0],Link_Left_Two_Point[1]);
        Padding_CurveR(0,0,0,0);
    }
    else
    {
        Padding_LineL(0,0,0,0);
        Padding_LineR(0,0,0,0);
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��С���˷���������
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void curvature_computeL(void)
{
    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    //float LeftK = 0, LeftB = 0;

    //int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    //float RightK = 0, RightB = 0;

    //int temp;
    //int LeftBlackError = 0, RightBlackError = 0;

    for (uint8 y = 53; y < 61; y++)//�������߽�����ۼӼ���
    {
        if (y % 2 == 0)
        {
            LeftXSum += Left_Black_Point[y];
            LeftYSum += y;
            LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
            LeftXYSum += y * Left_Black_Point[y];

//            RightXSum += Right_Black_Point[y];
//            RightYSum += y;
//            RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
//            RightXYSum += y * Right_Black_Point[y];
        }
     }

    if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
    {
        CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
    }

                 //Lintercede = (float)(LeftXXSum * LeftYSum - LeftXSum * LeftXYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);

    //CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
                 //Rintercede = (float)(
}

void curvature_computeR(void)
{
    //int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    //float LeftK = 0, LeftB = 0;

    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    //float RightK = 0, RightB = 0;

    //int temp;
    //int LeftBlackError = 0, RightBlackError = 0;

    for (uint8 y = 53; y < 61; y++)//�������߽�����ۼӼ���
    {

        if (y % 2 == 0)
        {
//            LeftXSum += Left_Black_Point[y];
//            LeftYSum += y;
//            LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
//            LeftXYSum += y * Left_Black_Point[y];

            RightXSum += Right_Black_Point[y];
            RightYSum += y;
            RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
            RightXYSum += y * Right_Black_Point[y];
        }
     }

//    if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
//    {
//        CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
//    }

                 //Lintercede = (float)(LeftXXSum * LeftYSum - LeftXSum * LeftXYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);

    if(8 * RightXXSum - RightXSum * RightXSum != 0)
    {
        CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
    }
                 //Rintercede = (float)(
}

void curvature_compute(void)
{
    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    //float LeftK = 0, LeftB = 0;

    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    //float RightK = 0, RightB = 0;

    //int temp;
    //int LeftBlackError = 0, RightBlackError = 0;

    for (uint8 y = 53; y < 61; y++)//�������߽�����ۼӼ���
    {

        if (y % 2 == 0)
        {
            LeftXSum += Left_Black_Point[y];
            LeftYSum += y;
            LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
            LeftXYSum += y * Left_Black_Point[y];

            RightXSum += Right_Black_Point[y];
            RightYSum += y;
            RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
            RightXYSum += y * Right_Black_Point[y];
        }
     }

    if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
    {
        CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
    }

                 //Lintercede = (float)(LeftXXSum * LeftYSum - LeftXSum * LeftXYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);

    if(8 * RightXXSum - RightXSum * RightXSum != 0)
    {
        CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
    }
                 //Rintercede = (float)(
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ٴ�ȷ������
//  @param
//  @param
//  @param
//  @param      ��Ϊ���ߺ���߷����仯����Ҫ�ٴμ������ߣ�������ԶԶ���������
//  @return     void
//  @note  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
static uint8 Last_Middle_Point = 93;   //��ʱ�����߻���Ϊ���߶�ԾǨ���˴����ڰ������
//�ٴ�ȷ������
void Get_Middle_Line(void)
{
    for(uint8 y=119 ; y >= 0 ; y--)
    {
        if(Right_Black_Point[y]==187 && Left_Black_Point[y]==0 && Corners_flag == 0 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)        //���߶�û�ҵ���
        {
            if(y == 119 )
            {
                Middle_Black_Point[y] = 93;
            }
            else
            {
                Middle_Black_Point[y]=Middle_Black_Point[y+1];
            }
            if(Emo_imag[y][Middle_Black_Point[y]] == EmoBlack && y < 114)
            {
                Middle_Black_Point[y] = Middle_Black_Point[y+5];
            }
            if(Emo_imag[y][Middle_Black_Point[y]] == EmoBlack && y > 114)
            {
                Middle_Black_Point[y] = 93;
            }
            //star=Middle_Black_Point[y];
        }
        else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Corners_flag == 0 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //ֱ������ҵ���
        {
            Middle_Black_Point[y]=Left_Black_Point[y]+Straight[y];
//            if(CurvatureRight < -0.0045)
//            {
//                kuan = ((y-120)*(y-120)/(20)+93);
//                kuan = kuan > (187-Right_Black_Point[y]) ? (187-Right_Black_Point[y]) : kuan;
//                Middle_Black_Point[y]=Left_Black_Point[y]+kuan;
//            }
        }
        else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Corners_flag == 0 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //ֱ���ұ��ҵ���
        {
            Middle_Black_Point[y]=Right_Black_Point[y]-Straight[y];
//            if(CurvatureRight < -0.0045)
//            {
//                kuan = ((y-120)*(y-120)/(20)+93);
//                kuan = kuan > Right_Black_Point[y] ? Right_Black_Point[y] : kuan;
//                Middle_Black_Point[y]=Right_Black_Point[y]-kuan;
//            }
        }
        else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Corners_flag == 1 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //����ұ��ҵ���
        {
            if(Right_Black_Point[y] < Corners[y])
                Middle_Black_Point[y]=0;
            else
                Middle_Black_Point[y]=Right_Black_Point[y]-(Corners[y] - 6);
        }
        else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Corners_flag == 1 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //�������ҵ���
        {
            if(Left_Black_Point[y] + Corners[y] > 187)
                Middle_Black_Point[y]=187;
            else
                Middle_Black_Point[y]=Left_Black_Point[y]+(Corners[y] - 6);
        }
        else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Triforkpadding_flag == 1 && Corners_flag == 0 && Near_Corners_flag == 0)    //���������ҵ���
        {
            if(Left_Black_Point[y] > 113)
                Middle_Black_Point[y]=187;
            else
                Middle_Black_Point[y]=Left_Black_Point[y]+Trifork_padding[y];
        }
        else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Triforkpadding_flag == 1 && Corners_flag == 0 && Near_Corners_flag == 0)    //���������ҵ���
        {
            if(Right_Black_Point[y] < 75)
                Middle_Black_Point[y]=0;
            else
                Middle_Black_Point[y]=Right_Black_Point[y]-Trifork_padding[y];
        }
//        else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Triforkpadding_flag == 0 && Corners_flag == 1 && Near_Corners_flag == 1)    //�ҽ�������ҵ���
//        {
//            if(Left_Black_Point[y] + Corners[y] > 187)
//                Middle_Black_Point[y]=187;
//            else
//                Middle_Black_Point[y]=Left_Black_Point[y]+(Corners[y]-6);
//        }
//        else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Triforkpadding_flag == 0 && Corners_flag == 1 && Near_Corners_flag == 1)    //���������ҵ���
//        {
//            if(Right_Black_Point[y] < Corners[y])
//                Middle_Black_Point[y]=0;
//            else
//                Middle_Black_Point[y]=Right_Black_Point[y]-(Corners[y]-6);
//        }
        else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Slalom_Padding == 1 && Corners_flag == 0 && Near_Corners_flag == 0)    //����Slalom�ҵ���
        {
            if(Left_Black_Point[y] > 113)
                Middle_Black_Point[y]=187;
            else
                Middle_Black_Point[y]=Left_Black_Point[y]+(Corners[y]);
        }
        else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Slalom_Padding == 1 && Corners_flag == 0 && Near_Corners_flag == 0)    //����Slalom�ҵ���
        {
            if(Right_Black_Point[y] < 75)
                Middle_Black_Point[y]=0;
            else
                Middle_Black_Point[y]=Right_Black_Point[y]-(Corners[y]);
        }
        else             //���߶��ҵ���
        {
            Middle_Black_Point[y]=(uint8)(((int)Right_Black_Point[y]+(int)Left_Black_Point[y])/2);
            if(Emo_imag[y][Middle_Black_Point[y]] == EmoBlack)
            {
                if(y<=114)
                {
                    Middle_Black_Point[y] = Middle_Black_Point[y+5];
                }
                else
                {
                    Middle_Black_Point[y] = 93;
                }

            }
        }
        if(y < 118 && Right_Black_Point[y] == 187 && Left_Black_Point[y] == 0 && (Emo_Uint8_dec(Middle_Black_Point[y],Last_Middle_Point) >= 18 || Emo_Uint8_dec(Middle_Black_Point[y],Last_Middle_Point) <= -18)
        && Corners_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && Trifork_flag == 0)
        {
            Middle_Black_Point[y] = Last_Middle_Point;
        }
        else
        {
            Last_Middle_Point = Middle_Black_Point[y];
        }
//        Middle_Black_Point[y] = Middle_Black_Point[y] < 1 ? 1 : Middle_Black_Point[y];
//        Middle_Black_Point[y] = Middle_Black_Point[y] > 186 ? 186 : Middle_Black_Point[y];
        Middle_Black_Point[y] = Middle_Black_Point[y] < 1 ? 0 : Middle_Black_Point[y];
        Middle_Black_Point[y] = Middle_Black_Point[y] >186 ? 187 :Middle_Black_Point[y];
        if(y==0)
            break;
    }
}

//Ԫ��ʶ��ļ���
//-------------------------------------------------------------------------------------------------------------------
//  @brief      Ԫ��ʶ��ļ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note  Ԫ��ʶ����ܴ���
//  @note  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void Think(void)
{
    Judge_Ramp();
    //Judge_CornerS();
    if(SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && Trifork_flag == 0 && CornerS_flag == 0 && Cross_flag == 0 && WindupR_flag == 0 && WindupL_flag == 0 && Ramp_flag == 0)
    {
        Judge();
    }
    if(CornerS_flag == 0 && CornerLeft_flag == 0 && CornerRight_flag == 0 && Ramp_flag == 0)
    {
        if(Trifork_flag == 0)
            Identify();
        Element_dispose();
        Cross();
        Windup();
        Garage();
        Slalom();
        Circle();
        Trifork_Shuttle();
    }
}

//�������������
//�µ�ʱ���ȡ�복���ĵط�
//�������룬ɵ�Ʋ�д
void Differential_Calculate(void)
{
    float middle_standard = 93.0;
//    float Last_Differential = 0;
//
//
//    Last_Differential = Differential_Error;
    if(Ramp_flag == 1)
    {
        Differential_Error = ((float)((5 * (int)Middle_Black_Point[70] + 3 * (int)Middle_Black_Point[69] + 2 * (int)Middle_Black_Point[68]) / 10) - middle_standard)/70;
    }
    else
    {
        if(Pre_Speed >= 180)
        {
            Differential_Error = ((float)((5 * (int)Middle_Black_Point[50] + 3 * (int)Middle_Black_Point[49] + 2 * (int)Middle_Black_Point[48]) / 10) - middle_standard)/50;
        }
        else if(Pre_Speed < 180 && Pre_Speed >= 171)
        {
            Differential_Error = ((float)((5 * (int)Middle_Black_Point[55] + 3 * (int)Middle_Black_Point[54] + 2 * (int)Middle_Black_Point[53]) / 10) - middle_standard)/55;
        }
        else if(Pre_Speed < 171 && Pre_Speed >= 70)
        {
            Differential_Error = ((float)((5 * (int)Middle_Black_Point[58] + 3 * (int)Middle_Black_Point[57] + 2 * (int)Middle_Black_Point[56]) / 10) - middle_standard)/58;
        }
        else if(Pre_Speed < 70 && Pre_Speed >= 40)
        {
            Differential_Error = ((float)((5 * (int)Middle_Black_Point[61] + 3 * (int)Middle_Black_Point[60] + 2 * (int)Middle_Black_Point[59]) / 10) - middle_standard)/61;
        }
        else if(Pre_Speed <= 40)
        {
            Differential_Error = ((float)((5 * (int)Middle_Black_Point[65] + 3 * (int)Middle_Black_Point[64] + 2 * (int)Middle_Black_Point[63]) / 10) - middle_standard)/65;
        }
    }
//    Last_Differential = Differential_Error;
//    if((Differential_Error - Last_Differential) > 30)
//    {
//        Differential_Error = Last_Differential + 3;
//    }
//    else if((Differential_Error - Last_Differential) < -30)
//    {
//        Differential_Error = Last_Differential - 3;
//    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ͷ�����ܺ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note  �Ƚ��ж�ֵ����Ȼ��Ѱ���ߣ�Ȼ���ҹյ㣬�ж�Ԫ�أ����ߣ��ٴμ������ߣ���ƫ��
//  @note  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void Camera_Pro(void)        //����ͷ�����ܺ���
{
   //gpio_set(P33_4, 1);
    if(Garage_Out_flag == 0 && Garage_In_flag == 0)
    {
        Thresholding();
        Get_Line();
        Think();
        Padding_Line();
        Get_Middle_Line();
        Differential_Calculate();
        IPS_Flag = 1;
    }
//    else if(Garage_Out_flag == 0 && Garage_In_flag == 1)
//    {
//        Thresholding();
//        Get_Line();
//        Identify();
//        Element_dispose();
//        GarageIN();
//        Padding_Line();
//        Get_Middle_Line();
//        Differential_Calculate();
//        IPS_Flag = 1;
//    }

    //gpio_set(P33_4, 0);
}