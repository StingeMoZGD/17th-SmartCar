/*
 * Encoder.c
 *
 *  Created on: 2021��11��12��
 *      Author: YYM
 */

#include "Encoder.h"

/*******************����**************/
//��ΪONE ��ΪTWO
int16 CoderONE=0;
int16 CoderTWO=0;
int16 CoderSpeed = 0,SpeedFilter = 0,SpeedNew = 0,SpeedOld = 0;  //����ʵ���ٶȣ����ڳ���������ٶȲ���
int CoderSumONE = 0;
int CoderSumTWO = 0;
int CoderChSumONE = 0;
int CoderChSumTWO = 0;
int CoderRaSumONE = 0;
int CoderRaSumTWO = 0;
int CoderGaSumONE = 0;
int CoderGaSumTWO = 0;
float SpeedError = 0;               //�ٶ�ƫ��
float SpeedErrorTemp[5];
int Real_Distance = 0;
int Real_ChDistance = 0;
int Real_RaDistance = 0;
int Real_GaDistance = 0;
int Real_lowDistance = 0;
unsigned char EncoderSum_flag = 0;    //�����ܶ��������ۼӱ�־
unsigned char EncoderCharge_flag = 0;  //��������ڼ�ʹ�õı������ۼӱ�־  ��Ϊ����ڼ䳵������ִ���ܶ���������ֵ��ײ
unsigned char Encoderlow_flag = 0;
unsigned char EncoderRamp_flag = 0;   //�µ��������������
unsigned char EncoderGa_flag = 0;

//unsigned char Garage_Out_flag = 0;          //�����־
//unsigned char Garage_In_flag = 0;           //����־
//unsigned char Garage_Out_Dir = 0;           //���ⷽ�� 0���� 1���� Ĭ��Ϊ��

void Encoder_Init(void)
{
    gpt12_init(EncoderONE);  //��������ʼ��
    gpt12_init(EncoderTWO);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ɼ�
//  @param      gptn ��������Ӧ���
//  @param      n    n�ξ�ֵ�˲�
//  @param
//  @param
//  @return     int16
//  @note
//-------------------------------------------------------------------------------------------------------------------
int16 Encoder_MTM(GPTN_enum gptn,int n)
{
    int16 Coder = 0;
    int16 CoderOut = 0;
    switch(gptn)
    {
        case GPT12_T2:
            for(int i = 0;i < n;i++)
            {
                Coder += - gpt12_get(GPT12_T2);
                //gpt12_clear(GPT12_T2);
            }
            CoderOut = Coder/n;
            break;
        case GPT12_T6:
            for(int i = 0;i < n;i++)
            {
                Coder += gpt12_get(GPT12_T6);
                //gpt12_clear(GPT12_T6);
            }
            CoderOut = Coder/n;
            break;
    }
    gpt12_clear(gptn);    //���������
//    gpt12_clear(GPT12_T6);
    return CoderOut;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������Ʋ�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ͬ��־��Ӧ��ͬ�����ļƲ�
//-------------------------------------------------------------------------------------------------------------------
void Encoder_coder(void)
{
    CoderONE = Encoder_MTM(GPT12_T2,3);
    CoderTWO = Encoder_MTM(GPT12_T6,3);

    Encoder_SpeedSmooth();

    if(EncoderSum_flag == 1)
    {
        Encoder_Summation();
    }
    else
    {
        Encoder_SumClear();
    }
    if(EncoderCharge_flag == 1)
    {
        EncoderCharge_Summation();
    }
    else
    {
        EncoderCharge_SumClear();
    }
    if(EncoderRamp_flag == 1)
    {
        EncoderRamp_Summation();
    }
    else
    {
        EncoderRamp_SumClear();
    }
    if(EncoderGa_flag == 1)
    {
        EncoderGar_Summation();
    }
    else
    {
        EncoderGar_SumClear();
    }
    if(Encoderlow_flag == 1)
    {
        Real_lowDistance += CoderSpeed;
    }
    else
    {
        Real_lowDistance = 0;
    }

//    Encoder_SpeedSmooth();
//    CoderONE = CoderONE < 0 ? 0 : CoderONE;
//    CoderTWO = CoderTWO < 0 ? 0 : CoderTWO;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����������޷�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Encoder_SpeedSmooth(void)
{
    //Encoder_coder();
    CoderSpeed = (CoderONE + CoderTWO)/2;
    SpeedOld = SpeedNew;
    SpeedNew = CoderSpeed;
    //�ٶȲɼ��ݶ�ƽ����ÿ�βɼ����仯6
//
//    if(SpeedNew >= SpeedOld)
//       SpeedFilter = (SpeedNew-SpeedOld)> (6) ? (SpeedOld+6) : SpeedNew;
//    else
//       SpeedFilter = (SpeedNew-SpeedOld)< (-6) ? (SpeedOld-6) : SpeedNew;
    SpeedError =  Pre_Speed - CoderSpeed;
    SpeedError = SpeedError < 0 ? (-SpeedError) : SpeedError;
//    SpeedErrorTemp[4] = SpeedErrorTemp[3];
//    SpeedErrorTemp[3] = SpeedErrorTemp[2];
//    SpeedErrorTemp[2] = SpeedErrorTemp[1];
//    SpeedErrorTemp[1] = SpeedErrorTemp[0];
//    SpeedErrorTemp[0] = SpeedError;
    IncrementPID_Transition();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ۼ�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Encoder_Summation(void)
{
    CoderSumONE += CoderONE;
    CoderSumTWO += CoderTWO;
    Real_Distance = (CoderSumONE + CoderSumTWO)/2;
}

void EncoderCharge_Summation(void)
{
    CoderChSumONE += CoderONE;
    CoderChSumTWO += CoderTWO;
    Real_ChDistance = (CoderChSumONE + CoderChSumTWO)/2;
}

void EncoderCharge_SumClear(void)
{
    CoderChSumONE = 0;
    CoderChSumTWO = 0;
    Real_ChDistance = 0;
}

void EncoderRamp_Summation(void)
{
    CoderRaSumONE += CoderONE;
    CoderRaSumTWO += CoderTWO;
    Real_RaDistance = (CoderRaSumONE + CoderRaSumTWO)/2;
}

void EncoderGar_Summation(void)  //����ר�ñ�����
{
    CoderGaSumONE += CoderONE;
    CoderGaSumTWO += CoderTWO;
    Real_GaDistance = (CoderGaSumONE + CoderGaSumTWO)/2;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����������
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void EncoderRamp_SumClear(void)
{
    CoderRaSumONE = 0;
    CoderRaSumTWO = 0;
    Real_RaDistance = 0;
}


void EncoderGar_SumClear(void)
{
    CoderGaSumONE = 0;
    CoderGaSumTWO = 0;
    Real_GaDistance = 0;
}

//�������ۼ�����
void Encoder_SumClear(void)
{
    CoderSumONE = 0;
    CoderSumTWO = 0;
    Real_Distance = 0;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������мƲ�
//  @param      TargetDistanceONE   ����Ŀ�����
//  @param      TargetDistanceTWO   ����Ŀ�����
//  @param      TargetSpeedONE      ����Ŀ���ٶ�
//  @param      TargetSpeedTWO      ����Ŀ���ٶ�
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
static int t = 0;           //���жϴ���
void Encoder_Distance(int TargetDistanceONE,int TargetDistanceTWO,float Time,float TargetSpeedONE,float TargetSpeedTWO)
{
    int DistanceONE = 0;
    int DistanceTWO = 0;
    //float T = 0.01;        //�ж�ʱ��  ��λ��
    //Pre_Speed = TargetSpeedONE;
    t++;
    EncoderSum_flag = 1;
    DistanceONE = TargetDistanceONE - CoderSumONE;
    DistanceTWO = TargetDistanceTWO - CoderSumTWO;
    if(DistanceONE > TargetSpeedONE)
    {
//        Exp_SpeedONE = (float)DistanceONE/(Time - T*(float)t);
//        Exp_SpeedTWO = (float)DistanceTWO/(Time - T*(float)t);
        Exp_SpeedONE = TargetSpeedONE;
        Exp_SpeedTWO = TargetSpeedTWO;
    }
    else
    {
        Exp_SpeedONE = (float)DistanceONE;
        Exp_SpeedTWO = (float)DistanceTWO;
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������мƲ�
//  @param
//  @param
//  @param      TargetSpeedONE      ����Ŀ���ٶ�
//  @param      TargetSpeedTWO      ����Ŀ���ٶ�
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void GarCoder(float TargetSpeedONE,float TargetSpeedTWO)
{
    EncoderSum_flag = 1;
//        Exp_SpeedONE = (float)DistanceONE/(Time - T*(float)t);
//        Exp_SpeedTWO = (float)DistanceTWO/(Time - T*(float)t);
        Exp_SpeedONE = TargetSpeedONE;
        Exp_SpeedTWO = TargetSpeedTWO;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ı��������мƲ�
//  @param      TargetDistance   Ŀ�����
//  @param      Speed            Ŀ���ٶ�
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Encoder_FindCharge(int TargetDistance,float Speed)
{
    int Distance = 0;
    //float T = 0.01;        //�ж�ʱ��  ��λ��
    //Pre_Speed = TargetSpeedONE;
    //t++;
    EncoderSum_flag = 1;
    Real_Distance = (CoderSumONE + CoderSumTWO)/2;
    Distance = TargetDistance - Real_Distance;
    if(Distance > Speed)
    {
//        Exp_SpeedONE = (float)DistanceONE/(Time - T*(float)t);
//        Exp_SpeedTWO = (float)DistanceTWO/(Time - T*(float)t);
//        Pre_Speed = Speed;
    }
    else
    {
        Pre_Speed = (float)Distance;
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������⺯��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
static int Outcount = 0;
static int pspeedone = 0;
static int pspeedtwo = 0;
void Garage_Out(void)
{
    if(Garage_Dir == 0)         //��
    {
        if(Outcount == 0)  //����һ�׶�
        {
            if(CoderSumONE< EEPROM_GarageDistance && CoderSumTWO < EEPROM_GarageDistance )
            {
                pspeedone+=2;
                pspeedtwo=pspeedone;
                pspeedone = pspeedone > 70 ? 70 : pspeedone;
                pspeedtwo = pspeedtwo > 70 ? 70 : pspeedtwo;
                GarCoder((float)pspeedone,(float)pspeedtwo);
            }
            else
            {
                Outcount = 1;
            }
        }
        if(Outcount == 1)               //������׶�
        {
            pspeedone+=2;
            pspeedone = pspeedone > 100 ? 100 : pspeedone;
            pspeedtwo-=2;
            pspeedtwo = pspeedtwo < 40 ? 40 : pspeedtwo;
            Gyroscope_Star_flag = 1;     //������������������Ƕ�
            if(CoderSumONE < EEPROM_GarageDistance+9600 && (Emo_Angle > (-50) && Emo_Angle < 10))
            {
                GarCoder((float)pspeedone,(float)pspeedtwo);
            }
            else
            {
                Gyroscope_Star_flag = 0;   //�����ǽ���������
                Outcount = 2;
                CoderSumONE = 0;
                CoderSumTWO = 0;
                Real_Distance = 0;
            }
        }
        if(Outcount == 2)
        {
//            CoderSumONE = 0;
//            CoderSumTWO = 0;
//            Exp_SpeedONE = 0;
//            Exp_SpeedTWO = 0;
            pspeedone-=2;
            pspeedone = pspeedone < 70 ? 70 : pspeedone;
            pspeedtwo+=2;
            pspeedtwo = pspeedtwo > 70 ? 70 : pspeedtwo;
            if(CoderSumONE < 1210)
            {
                GarCoder((float)pspeedone,(float)pspeedtwo);
            }
            else
            {
                pspeedone = 0;
                pspeedtwo = 0;
                CoderSumONE = 0;
                CoderSumTWO = 0;
                Real_Distance = 0;
//                Exp_SpeedONE = 40;
//                Exp_SpeedTWO = 40;
                Outcount = 0;
                Pre_Speed = (float)(CoderONE + CoderTWO)/2 + 1;
                Garage_Out_flag = 0;
                Garage_Out_Finsh_flag = 1;
                EncoderSum_flag = 0;
            }
        }
    }
    else
    {
        if(Outcount == 0)  //����һ�׶�
        {
            if(CoderSumONE< EEPROM_GarageDistance && CoderSumTWO < EEPROM_GarageDistance )
            {
                pspeedone+=2;
                pspeedtwo+=2;
                pspeedone = pspeedone > 70 ? 70 : pspeedone;
                pspeedtwo = pspeedtwo > 70 ? 70 : pspeedtwo;
                GarCoder((float)pspeedone,(float)pspeedtwo);
            }
            else
            {
                Outcount = 1;
            }
        }
        if(Outcount == 1)               //������׶�
        {
            pspeedone-=1.5;
            pspeedone = pspeedone < 40 ? 40 : pspeedone;
            pspeedtwo +=1.5;
            pspeedtwo = pspeedtwo > 100 ? 100 : pspeedtwo;
            Gyroscope_Star_flag = 1;     //������������������Ƕ�
            if(CoderSumTWO < EEPROM_GarageDistance+9600 && (Emo_Angle < 50 && Emo_Angle > -10))
            {
                GarCoder((float)pspeedone,(float)pspeedtwo);
            }
            else
            {
                Gyroscope_Star_flag = 0;
                Outcount = 2;
                CoderSumONE = 0;
                CoderSumTWO = 0;
                Real_Distance = 0;
            }
        }
        if(Outcount == 2)
        {
            pspeedone+=2;
            pspeedone = pspeedone > 70 ? 70 : pspeedone;
            pspeedtwo-=2;
            pspeedtwo = pspeedtwo < 70 ? 70 : pspeedtwo;
            if(CoderSumTWO < 1210)
            {
                GarCoder((float)pspeedone,(float)pspeedtwo);
            }
            else
            {
                //Gyroscope_Star_flag = 0;
                //Outcount = 2;
                pspeedone = 0;
                pspeedtwo = 0;
                CoderSumONE = 0;
                CoderSumTWO = 0;
                Real_Distance = 0;
//                Exp_SpeedONE = 55;
//                Exp_SpeedTWO = 55;
                Outcount = 0;
                Pre_Speed = (float)(CoderONE + CoderTWO)/2 + 1;
                Garage_Out_flag = 0;
                Garage_Out_Finsh_flag = 1;
                EncoderSum_flag = 0;
//                Exp_SpeedONE = 0;
//                Exp_SpeedTWO = 0;
            }
//            CoderSumONE = 0;
//            CoderSumTWO = 0;
//            Real_Distance = 0;
////            Exp_SpeedONE = 0;
////            Exp_SpeedTWO = 0;
//            Outcount = 0;
//            Pre_Speed = (float)(CoderONE + CoderTWO)/2 - 12;
//            Garage_Out_flag = 0;
//            Garage_Out_Finsh_flag = 1;
//            EncoderSum_flag = 0;
        }
    }
    Motor_SPEEDLOOP();   //�ٶȻ�����
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��������⺯��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
static int Incount = 0;
void Garage_In(void)
{
    if(GarageR_In_flag == 1)
    {
        if(Incount == 0)
        {
            Gyroscope_Star_flag = 1;
            if(CoderSumONE < 5000 && Emo_Angle >= -60)
            {
                Encoder_Distance(5000,3000,0.5,120,20);
            }
            else
            {
                Gyroscope_Star_flag = 0;
                Incount = 1;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
        }
        if(Incount == 1)
        {
            if(Real_Distance < 1500)
            {
                Encoder_Distance(1500,1500,0.5,100,100);
            }
            else
            {
                Incount = 2;
            }
        }
        if(Incount == 2)
        {
            Pre_Speed = 0;
            Exp_SpeedONE = 0;
            Exp_SpeedTWO = 0;
            EncoderSum_flag = 0;
            Beepindex = 0;
            //Gyroscope_Star_flag = 0;
        }
    }
    else if(GarageL_In_flag == 1)
    {
        if(Incount == 0)
        {
            Gyroscope_Star_flag = 1;
            if(CoderSumTWO < 5000 && Emo_Angle <= 60)
            {
                Encoder_Distance(3000,5000,0.5,20,120);
            }
            else
            {
                Gyroscope_Star_flag = 0;
                Incount = 1;
                EncoderSum_flag = 0;
                Encoder_SumClear();
            }
        }
        if(Incount == 1)
        {
            if(Real_Distance < 1500)
            {
                Encoder_Distance(1500,1500,0.5,100,100);
            }
            else
            {
                Incount = 2;
            }
        }
        if(Incount == 2)
        {
            Pre_Speed = 0;
            Exp_SpeedONE = 0;
            Exp_SpeedTWO = 0;
            EncoderSum_flag = 0;
            Beepindex = 0;
            //Gyroscope_Star_flag = 0;
        }
    }
    Motor_SPEEDLOOP();   //�ٶȻ�����
}
