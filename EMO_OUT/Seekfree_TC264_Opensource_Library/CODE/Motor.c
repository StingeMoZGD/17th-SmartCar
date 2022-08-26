/*
 * Motor.c
 *
 *  Created on: 2021��11��12��
 *      Author: YYM
 */

#include "Motor.h"

/***************����************/
int MotorONE=0;
int MotorTWO=0;
int MotorTime = 0;
float Pre_Speed=0;
float Exp_SpeedONE=0;
float Exp_SpeedTWO=0;
//int16 TargetAngle = 0;
unsigned char Auxiliary_CorneringLeft_flag = 0;    //ǿ�����������
unsigned char Auxiliary_CorneringRight_flag = 0;    //ǿ�����Ҹ������
int16 dirONE=0;
int16 dirTWO=0;
unsigned char Crash_Out = 0;
unsigned char Garage_Out_flag = 1;          //�����־ 0�������г��� 1�����г���
unsigned char Garage_In_flag = 0;           //����־  0����������� 1���������
unsigned char Garage_Dir = 0;               //���ⷽ�� 0���� 1���� Ĭ��Ϊ��
unsigned char Garage_Out_Finsh_flag = 0;    //��������ź�  0:δ���� 1���������
unsigned char FindCharge_flag = 0;          //���������ѳ��λ��
unsigned char GarageL_In_flag = 0;
unsigned char GarageR_In_flag = 0;
unsigned char Read_Battery_Voltage_flag = 0;
unsigned char need_cornerL = 0;              //Сת�丨��������Ԫ�س����һЩת�丨��
unsigned char need_cornerR = 0;
float Read_Battery_Voltage = 0;
float Read_Speed = 0;
float Dircetion_Standard=93.0;
float V;
unsigned char CS_flag = 0;  //���ͣ����־
unsigned char CCC = 0;  //���������򣬹�����


const uint16 Dec = 300;
const uint16 AMAX = 3803;
const int distance = 1650;    //LQ1700   ZH2400
const int Predistance = 330;
const int lowdistance = 300;
const int highdistance = 80;
const int conerdistance = 900;
float end_Bat = 7.2;
/***********ת����****************/
//extern uint8 Middle_Black_Point[120];
//extern int16 CoderONE,CoderTWO;
//extern uint8 OSTU;
//extern volatile unsigned char State;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����������Բ�ֵ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       �������ݾ�����м���
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
float Lagrange_interpolation(float x1,float y1,float x2,float y2,float x)
{
    float com1 = (float)x-(float)x2;
    float con1 = (float)x1-(float)x2;
    float com2 = (float)x-(float)x1;
    float con2 = (float)x2-(float)x1;
    float c1 = com1/con1;
    float c2 = com2/con2;
    float c3 = c1*(float)y1;
    float c4 = c2*(float)y2;
    return (c3+c4);
}

void Motor_Init(void)
{
    gtm_pwm_init(PWMONE);   //�����ʼ��
    gtm_pwm_init(PWMone);
    gtm_pwm_init(PWMTWO);
    gtm_pwm_init(PWMtwo);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����
//  @param      Exp_SpeedONE   ���ֵķ������
//  @param      Exp_SpeedTWO   ���ֵķ������
//  @param
//  @param
//  @return     void
//  @note       ������ͷ��ƫ���������Ͻ��ٶȻ�����ʱ��Ͳ���ģ��
//  @note       �����Pre_Speed/n  ���������������Ԫ�صĸ���ת�䣬�������л���˳��ͨ��Ԫ�� ��Ϊ���������ʱ�������Ȧ���ڿ�����Ȧ�ǣ�����ת��Ͳ�������
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
void Motor_Direction(void)    //���򻷣�ƫ��ǶȻ�����ʱ�������ٶȻ� λ��ʽ
{
    if(OSTU < 90)      //�ô����ֵ�ж��Ƿ�����������������
        Crash_Out = 1;
    if(Crash_Out == 1)
        Pre_Speed = 0;
    else
    {

//        if(Real_ChDistance >= 25000)
//        {
//            Pre_Speed = 0;
//        }
////        if(BoundaryRight == 0 && BoundaryLeft == 0)
////            Pre_Speed = 160;
////        else
////            Pre_Speed = 90;
//        Pre_Speed = (float)Replace_Speed;
//        Pre_Speed = 60;
//    }
//    if(MotorTime % 50 == 0)
//    {
//         Pre_Speed += 4;
//         MotorTime = 0;
     }
//     MotorTime +=1;
//     Pre_Speed = (Pre_Speed > 60) ? 60 : Pre_Speed;

//�������ֲ��ٿ��ƣ����ڰ��������Ӳ��٣�����ǰ�����ж���������Ż�
    double Length = 23;      //����Ŀ���ľ��룬����ʹ������ͷ���ͼ�����ص�λ��
    double Width = 21;     //����֮����־�
    double tanS = (Differential_Error);
//    double V1 = V*(1-Width*tanS/(Length*2));
//    double V2 = V*(1+Width*tanS/(Length*2));
    double V1 = Width*tanS/(Length*2);
    double V2 = Width*tanS/(Length*2);

    V = (float)V1;
    if(Auxiliary_CorneringLeft_flag == 1 && Auxiliary_CorneringRight_flag == 0)    //���������������
    {
        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/4;
        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/4;
    }
    else if(Auxiliary_CorneringLeft_flag == 0 && Auxiliary_CorneringRight_flag == 1)
    {
        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/4;
        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/4;
    }
//    else if(Replace_Coner == 1 && CornerLeft_flag == 1 && (AfterI_Voltage < 175 || State == ChargeFinsh_State))
//    {
////        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
////        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/8;
//        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/20;
//        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/20;
//        //Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
//    }
//    else if(Replace_Coner == 1 && CornerRight_flag == 1 && (AfterI_Voltage < 175 || State == ChargeFinsh_State))
//    {
////        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/8;
////        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
//        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/20;
//        //Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
//        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/20;
//    }
    else if(need_cornerL == 1 && Auxiliary_CorneringLeft_flag == 0 && Auxiliary_CorneringRight_flag == 0)
    {
        if(Trifork_flag == 1 && CircleBig == 0 && (AfterI_Voltage < 175 || State == ChargeFinsh_State))
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/25;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/25;
        }
//        else if(CircleBig == 1 && Trifork_flag == 0)
//        {
//            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/23;
//            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/23;
//        }
        else if(Trifork_flag == 0 && CircleBig == 0 && SlalomRight_flag == 0)
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/32;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/32;
        }
        else if(Trifork_flag == 0 && CircleBig == 0 && SlalomRight_flag == 1)
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) - Pre_Speed/8;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/8;
        }
        else
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
        }
    //        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
    //        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) + Pre_Speed/8;
    }
    else if(need_cornerR == 1 && Auxiliary_CorneringRight_flag == 0 && Auxiliary_CorneringLeft_flag == 0)
    {
        if(Trifork_flag == 1 && CircleBig == 0 && (AfterI_Voltage < 175 || State == ChargeFinsh_State))
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/25;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/25;
        }
//        else if(Trifork_flag == 0 && CircleBig == 1)
//        {
//            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/23;
//            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/23;
//        }
        else if(Trifork_flag == 0 && CircleBig == 0 && SlalomLeft_flag == 0)
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/35;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/35;
        }
        else if(Trifork_flag == 0 && CircleBig == 0 && SlalomLeft_flag == 1)
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1) + Pre_Speed/8;
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2) - Pre_Speed/8;
        }
        else
        {
            Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
            Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
        }
    }
    else
    {
        Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
        Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
    }

//    Exp_SpeedONE = Pre_Speed + Pre_Speed * Position_PID(V1);
//    Exp_SpeedTWO = Pre_Speed - Pre_Speed * Position_PID(V2);
    if(Pre_Speed >= 0)
    {
        Exp_SpeedONE = Exp_SpeedONE > (10 * Pre_Speed) ? (10*Pre_Speed) : Exp_SpeedONE;
        Exp_SpeedTWO = Exp_SpeedTWO > (10 * Pre_Speed) ? (10*Pre_Speed) : Exp_SpeedTWO;
    }
    else
    {
        Exp_SpeedONE = Exp_SpeedONE < (10 * Pre_Speed) ? (10*Pre_Speed) : Exp_SpeedONE;
        Exp_SpeedTWO = Exp_SpeedTWO < (10 * Pre_Speed) ? (10*Pre_Speed) : Exp_SpeedTWO;
    }

    //Exp_

}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ٶȻ�
//  @param      MotorONE   ���ֵ�pwm���
//  @param      MotorTWO   ���ֵ�pwm���
//  @param
//  @param
//  @return     void
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
void Motor_SPEEDLOOP(void)    //�ٶȻ�  ����ʽPID
{

//    Encoder_coder();
    //Encoder_FindCharge(20000,80);
    MotorONE = Incrementalone_PI ((float)CoderONE,Exp_SpeedONE);
    MotorTWO = Incrementaltwo_PI ((float)CoderTWO,Exp_SpeedTWO);

//    if(Ostu < 130)
//    {
//        MotorONE = 0;
//        MotorTWO = 0;
//    }
//    Incrementalone_PI ((float)CoderONE,Exp_SpeedONE) = Incrementalone_PI ((float)CoderONE,Exp_SpeedONE) < (0) ? : Incrementalone_PI ((float)CoderONE,Exp_SpeedONE);
//    Incrementaltwo_PI ((float)CoderTWO,Exp_SpeedTWO) = Incrementaltwo_PI ((float)CoderTWO,Exp_SpeedTWO) < (0) ? : Incrementaltwo_PI ((float)CoderTWO,Exp_SpeedTWO);
//
//    MotorONE = MotorONE > 7000 ? (7000) : (MotorONE);
//    MotorTWO = MotorTWO > 7000 ? (7000) : (MotorTWO);
//
//    MotorONE = MotorONE < (0) ? (0) : (MotorONE);
//    MotorTWO = MotorTWO < (0) ? (0) : (MotorTWO);
//    MotorONE = -100;
//    MotorTWO = -100;
    if(MotorONE < 0)  //��ת
    {
        pwm_duty(ONE, dirONE);
        pwm_duty(one,-MotorONE);
//        pwm_duty(ONE, 100);
//        pwm_duty(one, dirONE);
    }
    else
    {
        pwm_duty(ONE, MotorONE);
        pwm_duty(one, dirONE);
    }
    if(MotorTWO < 0)
    {
        pwm_duty(TWO, dirTWO);
        pwm_duty(two,-MotorTWO);
//        pwm_duty(two, dirTWO);
//        pwm_duty(TWO, 100);
    }
    else
    {
        pwm_duty(two, dirTWO);
        pwm_duty(TWO, MotorTWO);
    }
//    pwm_duty(ONE, 1500);
//    pwm_duty(one, dirONE);
//    pwm_duty(two, dirTWO);
//    pwm_duty(TWO, 1500);
//    gpt12_clear(GPT12_T2);    //���������

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ݵ��ݵ�ѹ�ж��Ƿ�����Ȧ����Ҫͣ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
void Retrieval(float V , float Speed)
{
    if(V <= 12.5)
    {
        Pre_Speed = 0;
        if(MODE == 2)
        {
            Replace_Speed = 125;
        }
        else if(MODE == 3)
        {
            Replace_Speed = 133;
        }
    }

    else if(V > 12.5 && V <= 14)
    {
        Pre_Speed = 25;
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �޷���16���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
int Emo_Uint16(uint16 a,uint16 b)
{
    int c = (int)a;
    int d = (int)b;

    return c-d;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������Ҫ���ٶ����Ĵ���
//  @param      end_Bat   �����ɿ��Ƶ�ͣ����ѹ�������Ƿ���Ҫ���Դ���Ȧ
//  @param
//  @param
//  @param
//  @return     void
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
void Decelerateone(float V , float Speed)
{
    //�����ѹ����8V�����м���
    if(V >= end_Bat)  //���Դ���Ȧ
    {
        limitspeedone();
        Read_Battery_Voltage_flag = 0;
        Coner_Charge = 0;
        Element_Charge = 0;
    }
    else
    {
        if(Speed <= 110 && Pre_Speed < 108)
        {
            if(V < 6)
            {
                if(Speed >= 25 && Real_ChDistance <= 1200 && Pre_Speed >= 26)
                {
                    Pre_Speed = Lagrange_interpolation(0.0,Speed,1200.0,25.0,(float)Real_ChDistance);
                    Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
                }
                else
                {
                    Pre_Speed = Pre_Speed > 25 ? 25 : Pre_Speed;
                }
                if(LAV >= 1800)
                {
                    if(CS_flag == 1)
                    {
                        Encoderlow_flag = 1;
                    }
                }
                if(Real_lowDistance >= (Predistance + lowdistance))
                {
                    FindCharge_flag = 1;
                    //EncoderCharge_flag = 0;
                    CCC++;
                    Pre_Speed = 0;
                    Encoderlow_flag = 0;
                }
            }
            else
            {
                if(Speed >= 70 && Real_ChDistance <= 800 && Pre_Speed >= 71)
                {
                    Pre_Speed = Lagrange_interpolation(0.0,Speed,800.0,70.0,(float)Real_ChDistance);
        //            Pre_Speed = Pre_Speed - 5;
                    Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
                    //Speed = 100;
                }
                else
                {
                    Pre_Speed = Pre_Speed > 70 ? 70 : Pre_Speed;
                }
                if(LAV >= 1800)
                {
                    if(CS_flag == 1)
                    {
                        //Encoderlow_flag = 1;   //��ͣ������
                        //EncoderCharge_flag = 1;
                        Pre_Speed = 0;
                        FindCharge_flag = 1;
                        CS_flag = 0;
                        CCC++;
                    }
        //            }
                }
            }
        }
        else
        {
            if(Speed >= 25 && Real_ChDistance <= 1200 && Pre_Speed >= 26)
            {
                Pre_Speed = Lagrange_interpolation(0.0,Speed,1200.0,25.0,(float)Real_ChDistance);
                Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
                //Pre_Speed = 25;
            }
            else
            {
                Pre_Speed = Pre_Speed > 25 ? 25 : Pre_Speed;
            }
            if(LAV >= 1800)
            {
                if(CS_flag == 1)
                {
                    Encoderlow_flag = 1;
                }
            }
            if(V >= 6)
            {
                if(Real_lowDistance >= (Predistance + highdistance))
                {
                    FindCharge_flag = 1;
                    //EncoderCharge_flag = 0;
                    Pre_Speed = 0;
                    Encoderlow_flag = 0;
                    CCC++;
                }
            }
            else
            {
                if(Real_lowDistance >= (Predistance + lowdistance))
                {
                    FindCharge_flag = 1;
                    //EncoderCharge_flag = 0;
                    Pre_Speed = 0;
                    Encoderlow_flag = 0;
                    CCC++;
                }
            }
        }
    }
}

void Deceleratetwo(float V , float Speed)
{
    //�����ѹ����8V�����м���

    if(V >= end_Bat)
    {
        limitspeedtwo();
        Read_Battery_Voltage_flag = 0;
        Coner_Charge = 0;
        Element_Charge = 0;
    }
    else if(V < 6 && V < end_Bat)
    {
//        Pre_Speed = (Speed-35)/(Dec - AIN) * (float)AfterI_Voltage + 35*(Dec - AIN)/(AIN*(Speed - 35));
//        if(Real_ChDistance % 100 == 0)
//        {
//            Pre_Speed = Pre_Speed - 5;
//            Pre_Speed = Pre_Speed < 20 ? 20 : Pre_Speed;
//            // x1 DEC y1 Speed  x2 AMAX y2 25
////            if(AfterI_Voltage < )
////            {
//                //Pre_Speed =25 * (((float)AfterI_Voltage - Dec)/((AMAX-500) - Dec)) + Speed * (((float)AfterI_Voltage - (AMAX-500))/(Dec - (AMAX-200)));
////            }
//            //Pre_Speed =25 * (((float)AfterI_Voltage - Dec)/((AIN-Speed) - Dec)) + Speed * (((float)AfterI_Voltage - (AIN-Speed))/(Dec - (AIN-Speed)));
//        }
        if(Pre_Speed > 90)
        {
            Pre_Speed = 90;
        }
        if(Speed >= 25 && Real_ChDistance <= 1000 && Pre_Speed >= 26)
        {
            Pre_Speed = Lagrange_interpolation(0.0,Speed,1000.0,25.0,(float)Real_ChDistance);
            Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
        }
        else
        {
            Pre_Speed = Pre_Speed > 25 ? 25 : Pre_Speed;
        }
        if(LAV >= 1800)
        {
            if(Emo_Uint16(AfterI_Voltage,LAV) <= -7)
            {
                Encoderlow_flag = 1;
            }
        }
        if(Real_lowDistance >= (Predistance + lowdistance))
        {
            FindCharge_flag = 1;
            CCC++;
            //EncoderCharge_flag = 0;
            Pre_Speed = 0;
            Encoderlow_flag = 0;
        }
//        if(Real_ChDistance >= (distance+Predistance+lowdistance))
//        {
//            FindCharge_flag = 1;
//            //EncoderCharge_flag = 0;
//            Pre_Speed = 0;
//            Encoderlow_flag = 0;
////            EncoderCharge_flag = 1;
//        }
//        if(AfterI_Voltage < 1130)
//        {
//            if(Real_ChDistance > (distance+Predistance))
//            {
//                EncoderCharge_flag = 0;
//            }
//        }
    }
    else if(V >= 6 && V < end_Bat)
    {
//        if(Speed > 90)
//        {
//            exspeee = 90;
//        }
//        else
//        {
//            exspeee = Speed;
//        }

        if(Speed >= 70 && Speed < 110 && Real_ChDistance <= 800 && Pre_Speed >= 71)
        {
            Pre_Speed = Lagrange_interpolation(0.0,Speed,800.0,70.0,(float)Real_ChDistance);
//            Pre_Speed = Pre_Speed - 5;
            Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
            //Speed = 100;
        }
        else if(Speed >= 110)
        {
            Pre_Speed -= 20;
            Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
        }
        else
        {
            Pre_Speed = Pre_Speed > 70 ? 70 : Pre_Speed;
        }
//        if(Real_ChDistance >= (distance + lowdistance))   //��ֹ�Ʋ�����
//        {
//            EncoderCharge_SumClear();
//            EncoderCharge_flag = 0;
//        }
//        if(Real_ChDistance <= 1200)
//        {
//            if(CornerRight_flag == 1 || CornerLeft_flag == 1)
//            {
//                Coner_Charge = 1;
//            }
//        }
        if(LAV >= 1800)
        {
//            if(Coner_Charge == 1)
//            {
//                if(CS_flag == 1)
//                {
//                    Pre_Speed = 0;
//                    FindCharge_flag = 1;
//                    Coner_Charge = 0;
//                    CS_flag = 0;
//                }
//            }
//            else
//            {
            if(CS_flag == 1)
            {
                //Encoderlow_flag = 1;   //��ͣ������
                //EncoderCharge_flag = 1;
                Pre_Speed = 0;
                FindCharge_flag = 1;
                CCC++;
                CS_flag = 0;
                //Read_AF = 0;
                //EncoderCharge_flag = 0;
            }
//            }
        }
//
//        if(AfterI_Voltage < 1130)
//        {
//            if(Real_ChDistance > distance)
//            {
//                EncoderCharge_flag = 0;
//            }
//        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �µ��ٶȴ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
void RAMP_Speed(void)
{
    if(Replace_Speed >= 120)
    {
        if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 86)
        {
            if(Pre_Speed >= 86)
            {
                Pre_Speed -= 4;
                Pre_Speed = Pre_Speed < 86 ? 86 : Pre_Speed;
            }
        }
    }
    else
    {
        if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 70)
        {
            if(Pre_Speed >= 70)
            {
                Pre_Speed -= 4;
                Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Ԫ�ؿ��ٲ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ������Ϊ�ٶȻ��ͽṹԭ���ٶȿ����ת��ʱ����
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
void Element_speedone(void)
{
    if(Element_Charge == 0 && Replace_Speed >= 120 && (SlalomLeft_flag == 1 || SlalomRight_flag == 1))
    {
        if(Pre_Speed >= 120)
        {
            Pre_Speed -= 2;
            Pre_Speed = Pre_Speed < 120 ? 120 : Pre_Speed;
        }
    }
    else if(Element_Charge == 0 && Replace_Speed >= 120 && (CircleLeft_flag == 1 || CircleRight_flag == 1))
    {
        if(Pre_Speed >= 120)
        {
            Pre_Speed -= 4;
            Pre_Speed = Pre_Speed < 120 ? 120 : Pre_Speed;
        }
    }
    RAMP_Speed();
}

void Element_speedtwo(void)
{
    if(Element_Charge == 0 && Replace_Speed >= 130 && (SlalomLeft_flag == 1 || SlalomRight_flag == 1))
    {
        if(Pre_Speed >= 130)
        {
            Pre_Speed -= 2.5;
            Pre_Speed = Pre_Speed < 130 ? 130 : Pre_Speed;
        }
    }
//    else if(Element_Charge == 0 && Replace_Speed >= 110 && (CircleLeft_flag == 1 || CircleRight_flag == 1))
//    {
//        if(Pre_Speed >= 110)
//        {
//            Pre_Speed -= 2.5;
//            Pre_Speed = Pre_Speed < 110 ? 110 : Pre_Speed;
//        }
//    }
    RAMP_Speed();
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������������
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ���Ŀ����˲ʱ��������ɳ���̧ͷ���˼���������������̧ͷ
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
void starspeedone(void)
{
    if(Pre_Speed <= Replace_Speed && Element_Charge == 0)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
    }
    else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed >= 120)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > 120 ? 120 : Pre_Speed;
    }
    else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed < 120)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
    }
    Element_speedone();
}

void starspeedtwo(void)
{
    if(Pre_Speed <= Replace_Speed && Element_Charge == 0)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
    }
    else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed >= 120)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > 120 ? 120 : Pre_Speed;
    }
    else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed < 120)
    {
        Pre_Speed += 1;
        Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
    }
    Element_speedtwo();
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ٺ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ���ݵ�ѹ�Ľ��ͻ��ǵ���޷��ﵽ�����ٶȣ����Խ��pwm���޷����߶��ٶ��޷�
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
void limitspeedone(void)
{
    if(Replace_Speed >= 90)
    {
        if(Battery_Voltage <= 4.3 &&  Battery_Voltage >= 3.3)
        {
            if(Battery_Voltage <= 4 && Pre_Speed >= 110)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 110 ? 110 : Pre_Speed;
            }
            else if(Battery_Voltage <= 4 && Pre_Speed <= 110)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 110 ? 110 : Pre_Speed;
            }
            else if(Battery_Voltage > 4.3)
            {
                starspeedone();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 3.3 &&  Battery_Voltage >= 2.5)
        {
            if(Battery_Voltage <= 3 && Pre_Speed >= 100)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage <= 3 && Pre_Speed <= 100)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage > 3.3)
            {
                starspeedone();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 2.5 && Battery_Voltage >= 1.8)
        {
            if(Battery_Voltage <= 2.3 && Pre_Speed >= 70)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
            }
            else if(Battery_Voltage <= 2.3 && Pre_Speed <= 70)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 70 ? 70 : Pre_Speed;
            }
            else if(Battery_Voltage > 2.5)
            {
                starspeedone();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 1.8)
        {
            if(Battery_Voltage <= 2 && Pre_Speed >= 25)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
            }
            else if(Battery_Voltage > 1.8)
            {
                starspeedone();
            }
//            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
//            {
//               if(Pre_Speed >= 50)
//               {
//                   Pre_Speed -= 20;
//                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
//               }
//            }
        }
//        else if(Battery_Voltage <= 3.5)
//        {
//            if(Battery_Voltage <= 3 && Pre_Speed >= 50)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 50 ? 50 : Pre_Speed;
//            }
//            else
//            {
//                starspeed();
//            }
////            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
////            {
////               if(Pre_Speed >= 50)
////               {
////                   Pre_Speed -= 20;
////                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
////               }
////            }
//        }
        else if(Battery_Voltage > 4.3)
        {
            starspeedone();
        }
    }
    else
    {
        if(Pre_Speed <= Replace_Speed)
        {
            Pre_Speed += 1;
            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
        }
        RAMP_Speed();
    }
}

void limitspeedtwo(void)
{
    if(Replace_Speed >= 90)
    {
        if(Battery_Voltage <= 4.3 &&  Battery_Voltage >= 2.3)
        {
            if(Battery_Voltage <= 4 && Pre_Speed >= 120)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 120 ? 120 : Pre_Speed;
            }
            else if(Battery_Voltage <= 4 && Pre_Speed <= 120)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 120 ? 120 : Pre_Speed;
            }
            else if(Battery_Voltage > 4.3)
            {
                starspeedtwo();
            }
            RAMP_Speed();
        }
//        if(Battery_Voltage <= 3.3 &&  Battery_Voltage >= 2.3)
//        {
//            if(Battery_Voltage <= 3 && Pre_Speed >= 100)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 100 ? 100 : Pre_Speed;
//            }
//            else if(Battery_Voltage <= 3 && Pre_Speed <= 100)
//            {
//                Pre_Speed += 1;
//                Pre_Speed = Pre_Speed > 100 ? 100 : Pre_Speed;
//            }
//            else if(Battery_Voltage > 3.3)
//            {
//                starspeedtwo();
//            }
//            RAMP_Speed();
//        }
        else if(Battery_Voltage <= 2.3 && Battery_Voltage >= 1.8)
        {
            if(Battery_Voltage <= 2 && Pre_Speed >= 100)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage <= 2 && Pre_Speed <= 100)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage > 2.3)
            {
                starspeedtwo();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 1.8)
        {
            if(Battery_Voltage <= 2 && Pre_Speed >= 25)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
            }
            else if(Battery_Voltage > 1.8)
            {
                starspeedtwo();
            }
//            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
//            {
//               if(Pre_Speed >= 50)
//               {
//                   Pre_Speed -= 20;
//                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
//               }
//            }
        }
//        else if(Battery_Voltage <= 3.5)
//        {
//            if(Battery_Voltage <= 3 && Pre_Speed >= 50)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 50 ? 50 : Pre_Speed;
//            }
//            else
//            {
//                starspeed();
//            }
////            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
////            {
////               if(Pre_Speed >= 50)
////               {
////                   Pre_Speed -= 20;
////                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
////               }
////            }
//        }
        else if(Battery_Voltage > 5.3)
        {
            starspeedtwo();
        }
    }
    else
    {
        if(Pre_Speed <= Replace_Speed)
        {
            Pre_Speed += 1;
            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
        }
        RAMP_Speed();
    }
}

void limitspeedthr(void)
{
    if(Replace_Speed >= 90)
    {
//        if(Battery_Voltage <= 5 &&  Battery_Voltage >= 4.2)
//        {
//            if(Battery_Voltage <= 4.8 && Pre_Speed >= 120)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 120 ? 120 : Pre_Speed;
//            }
//            else if(Battery_Voltage <= 4.8 && Pre_Speed <= 120)
//            {
//                Pre_Speed += 1;
//                Pre_Speed = Pre_Speed > 120 ? 120 : Pre_Speed;
//            }
//            else if(Battery_Voltage > 5)
//            {
//                starspeedone();
//            }
//            RAMP_Speed();
//        }
//        else if(Battery_Voltage <= 4.2 &&  Battery_Voltage >= 3.3)
//        {
//            if(Battery_Voltage <= 4 && Pre_Speed >= 110)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 110 ? 110 : Pre_Speed;
//            }
//            else if(Battery_Voltage <= 4 && Pre_Speed <= 110)
//            {
//                Pre_Speed += 1;
//                Pre_Speed = Pre_Speed > 110 ? 110 : Pre_Speed;
//            }
//            else if(Battery_Voltage > 4.2)
//            {
//                starspeedone();
//            }
//            RAMP_Speed();
//        }
        if(Battery_Voltage <= 3.3 &&  Battery_Voltage >= 2.5)
        {
            if(Battery_Voltage <= 3 && Pre_Speed >= 100)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage <= 3 && Pre_Speed <= 100)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 100 ? 100 : Pre_Speed;
            }
            else if(Battery_Voltage > 3.3)
            {
                starspeedone();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 2.5 && Battery_Voltage >= 1.8)
        {
            if(Battery_Voltage <= 2.3 && Pre_Speed >= 70)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 70 ? 70 : Pre_Speed;
            }
            else if(Battery_Voltage <= 2.3 && Pre_Speed <= 70)
            {
                Pre_Speed += 1;
                Pre_Speed = Pre_Speed > 70 ? 70 : Pre_Speed;
            }
            else if(Battery_Voltage > 2.5)
            {
                starspeedone();
            }
            RAMP_Speed();
        }
        else if(Battery_Voltage <= 1.8)
        {
            if(Battery_Voltage <= 2 && Pre_Speed >= 25)
            {
                Pre_Speed -= 1;
                Pre_Speed = Pre_Speed < 25 ? 25 : Pre_Speed;
            }
            else if(Battery_Voltage > 1.8)
            {
                starspeedone();
            }
//            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
//            {
//               if(Pre_Speed >= 50)
//               {
//                   Pre_Speed -= 20;
//                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
//               }
//            }
        }
//        else if(Battery_Voltage <= 3.5)
//        {
//            if(Battery_Voltage <= 3 && Pre_Speed >= 50)
//            {
//                Pre_Speed -= 1;
//                Pre_Speed = Pre_Speed < 50 ? 50 : Pre_Speed;
//            }
//            else
//            {
//                starspeed();
//            }
////            if(Element_Charge == 0 && Ramp_flag == 1 && Replace_Speed >= 65)
////            {
////               if(Pre_Speed >= 50)
////               {
////                   Pre_Speed -= 20;
////                   Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
////               }
////            }
//        }
        else if(Battery_Voltage > 5)
        {
            starspeedone();
        }
    }
    else
    {
        if(Pre_Speed <= Replace_Speed)
        {
            Pre_Speed += 1;
            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
        }
        RAMP_Speed();
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ƺ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ����״̬������ʱ�����еĳ���״̬
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
void MotorControlone(void)
{
    switch(State)
    {
        case Stop_State :   //�ڿ�
            Pre_Speed = 0;
            break;
        case Charge_State :   //���
            if(FindCharge_flag == 0)
            {
                Decelerateone(Read_Battery_Voltage,Read_Speed);
            }
            else
            {
                Retrieval(Read_Battery_Voltage,Read_Speed);
            }
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case ChargeFinsh_State :     //��������
            //MotorTime++;
            limitspeedone();
            //LimitSpeed(Battery_Voltage);
            //Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case Run_State :           //����
            if(Garage_Out_flag == 1 && Garage_In_flag == 0)
            {
                Garage_Out();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 0)
            {
                limitspeedone();
              //  LimitSpeed(Battery_Voltage);//26s   18
//                if(Pre_Speed < Replace_Speed)
//                {
//                    Pre_Speed += 1;
//                    Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//                }

                Motor_Direction();
                Motor_SPEEDLOOP();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 1)
            {
                Garage_In();
            }
            break;
    }
}

//������Ƽ���
void MotorControltwo(void)
{
    switch(State)
    {
        case Stop_State :   //�ڿ�
            Pre_Speed = 0;
            break;
        case Charge_State :   //���
            if(FindCharge_flag == 0)
            {
                Deceleratetwo(Read_Battery_Voltage,Read_Speed);
            }
            else
            {
                Retrieval(Read_Battery_Voltage,Read_Speed);
            }
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case ChargeFinsh_State :     //��������
            //MotorTime++;
            limitspeedtwo();
            //LimitSpeed(Battery_Voltage);
            //Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case Run_State :           //����
            if(Garage_Out_flag == 1 && Garage_In_flag == 0)
            {
                Garage_Out();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 0)
            {
                limitspeedtwo();
              //  LimitSpeed(Battery_Voltage);//26s   18
//                if(Pre_Speed < Replace_Speed)
//                {
//                    Pre_Speed += 1;
//                    Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//                }

                Motor_Direction();
                Motor_SPEEDLOOP();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 1)
            {
                Garage_In();
            }
            break;
    }
}

//������Ƽ���
void MotorControlthr(void)
{
    switch(State)
    {
        case Stop_State :   //�ڿ�
            Pre_Speed = 0;
            break;
        case Charge_State :   //���
            if(FindCharge_flag == 0)
            {
                Deceleratetwo(Read_Battery_Voltage,Read_Speed);
            }
            else
            {
                Retrieval(Read_Battery_Voltage,Read_Speed);
            }
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case ChargeFinsh_State :     //��������
            //MotorTime++;
            limitspeedthr();
            //LimitSpeed(Battery_Voltage);
            //Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
            Motor_Direction();
            Motor_SPEEDLOOP();
            break;
        case Run_State :           //����
            if(Garage_Out_flag == 1 && Garage_In_flag == 0)
            {
                Garage_Out();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 0)
            {
                limitspeedthr();
              //  LimitSpeed(Battery_Voltage);//26s   18
//                if(Pre_Speed < Replace_Speed)
//                {
//                    Pre_Speed += 1;
//                    Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//                }

                Motor_Direction();
                Motor_SPEEDLOOP();
            }
            if(Garage_Out_flag == 0 && Garage_In_flag == 1)
            {
                Garage_In();
            }
            break;
    }
}

////�����н׶εĿ���
//void SpeedControl(void)
//{
//    if(Replace_Speed >= 90 && Battery_Voltage <= 6.5 )
//    {
//        if(Battery_Voltage <= 6 && Pre_Speed >= 90)
//        {
//            Pre_Speed -= 1;
//            Pre_Speed = Pre_Speed < 90 ? 90 : Pre_Speed;
//        }
//    }
//    else if(Replace_Speed >= 90 && Battery_Voltage <= 5.5 )
//    {
//        if(Battery_Voltage <= 5 && Pre_Speed >= 80)
//        {
//            Pre_Speed -= 1;
//            Pre_Speed = Pre_Speed < 80 ? 80 : Pre_Speed;
//        }
//    }
//    else if(Replace_Speed >= 90 && Battery_Voltage <= 4.5)
//    {
//        if(Battery_Voltage <= 4 && Pre_Speed >= 60)
//        {
//            Pre_Speed -= 1;
//            Pre_Speed = Pre_Speed < 60 ? 60 : Pre_Speed;
//        }
//    }
//    else if(Battery_Voltage > 6.5)
//    {
//        if(Pre_Speed <= Replace_Speed && Element_Charge == 0)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//        }
//        else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed >= 80)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > 80 ? 80 : Pre_Speed;
//        }
//        else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed < 80)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//        }
//        Element_speed();
//    }
//    else if(Battery_Voltage <= 6.5 && Replace_Speed < 90)
//    {
//        if(Pre_Speed <= Replace_Speed && Element_Charge == 0)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//        }
//        else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed >= 80)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > 80 ? 80 : Pre_Speed;
//        }
//        else if(Element_Charge == 1 && Pre_Speed <= Replace_Speed && Replace_Speed < 80)
//        {
//            MotorTime++;
//            if(MotorTime % 5 == 0)
//            {
//                Pre_Speed += 5;
//                MotorTime = 0;
//            }
//            Pre_Speed = Pre_Speed > Replace_Speed ? Replace_Speed : Pre_Speed;
//        }
//        Element_speed();
//    }
//
//}




///*************************��ƫ��***************************/
//void Row_error(void)
//{
//
//}


///*******************����ƫ��************************/
////�����ǰ�����ĵ����ʵõ�����ת��뾶�����·���ߵĽǶ�ƫ�������ٶȻ�
//void Curvature_error(void)
//{
//
//}


//PID Speed;
//
//float RealSpeed = 0;                //��ʵ�ٶ�
//float LeftRealSpeed;
//float RighRealSpeed;
//float SpeedFilter = 0;          //�����˲��ٶ�
////float ExpectSpeed = 3500;     //�����ٶ�  3500
//float SpeedError;               //�ٶ�ƫ��
//float SpeedErrorTemp[5] = {0};
//float SpeedErrorInteg = 0;
//int32 Leftpulse = 0,Righpulse = 0;
//int32 LeftPWM, RighPWM;
////�ٶȿ���
//float speedControl_P = 280;     //�ٶ�P  280
//float speedControl_I = 100;     //�ٶ�I
//float SpeedControlOut = 0;      //�ٶ����
//
//float Distance = 0;
//float DistanceIn = 0;
//float DistanceOut = 0;
///**
// * @file        �����ٶ�ƫ��
// * @note        ����ȫ�ֱ���g_fSpeedError
// * @date        2017
// */
//void CalSpeedError(void)
//{
//    static float SpeedOld = 0, SpeedNew = 0;
//
//    Leftpulse = ftm_count_get(ftm1);//��ȡ��������
//    ftm_count_clean(ftm1);
//    Righpulse = ftm_count_get(ftm0);//��ȡ��������
//    ftm_count_clean(ftm0);
//
//    if (gpio_get(ENCODER_DIRL) == 0)
//        Leftpulse = -Leftpulse;
//    if (gpio_get(ENCODER_DIRR) == 1)
//        Righpulse = -Righpulse;
//
//
//    DistanceIn+= (Leftpulse + Righpulse) / (2 * 5772.0f);
//    DistanceOut+= (Leftpulse + Righpulse) / (2 * 5772.0f);
//    Distance+= (Leftpulse + Righpulse) / (2 * 5772.0f);
//
//    LeftRealSpeed = Leftpulse * 207/(1175*0.02);
//    LeftRealSpeed = (LeftRealSpeed>4000?4000:LeftRealSpeed);        //���������������
//    RighRealSpeed = Righpulse * 207/(1175*0.02);
//    RighRealSpeed = (RighRealSpeed>4000?4000:RighRealSpeed);        //���ұ�����������
//
//    RealSpeed = (LeftRealSpeed + RighRealSpeed) / 2;                //��ʵ�ٶ�
//
//    //�ٶȲɼ��ݶ�ƽ����ÿ�βɼ����仯200
//    SpeedOld = SpeedFilter;
//    SpeedNew = RealSpeed;
//
//    if(SpeedNew>=SpeedOld)
//       SpeedFilter = ((SpeedNew-SpeedOld)>300?(SpeedOld+300):SpeedNew);
//    else
//       SpeedFilter = ((SpeedNew-SpeedOld)<-300?(SpeedOld-300):SpeedNew);
//
//    //flash�в���
////  g_fExpectSpeed = float05;  //2800
//
//    SpeedError =  ExpectSpeed - SpeedFilter;
//    SpeedErrorTemp[4] = SpeedErrorTemp[3];
//    SpeedErrorTemp[3] = SpeedErrorTemp[2];
//    SpeedErrorTemp[2] = SpeedErrorTemp[1];
//    SpeedErrorTemp[1] = SpeedErrorTemp[0];
//    SpeedErrorTemp[0] = SpeedError;
//
//}
//
//
///**
// * @file        �ٶȿ���
// * @note        �ٶ��ݶ�ƽ��
// * @date        2017
// */
//void SpeedControl(void)
//{
//        Speed.KP = speedControl_P;
//        Speed.KI = speedControl_I;
//
//    int8 index=1;
//
//    CalSpeedError();    //�����ٶ�ƫ��
//    SpeedError = (SpeedError>800?800:SpeedError);//�ٶ�ƫ���޷�
//
////        SpeedError = LIMIT_MAX(SpeedError, 800);
//
//
//    //���ַ���
//    if((SpeedError<=300)&&(SpeedError>=-300))
//    index=1;
//    else
//    index=0;
//    SpeedErrorInteg = index * 0 * SpeedError * 0.00001;
//
///*  if(Flag_Stop == OFF||Flag_Speed == OFF)
//    {
//        SpeedErrorInteg = 0;    //ͣ����������
//    }
//*/
//    //SpeedErrorInteg = (SpeedErrorInteg < 0.0? 0.0: SpeedErrorInteg);//��������
//    //SpeedErrorInteg = (SpeedErrorInteg > 400.0? 400.0: SpeedErrorInteg);//��������
//    //�ٶȿ����㷨������ʽPI��
//    Speed.Out += Speed.KP *0.005*(SpeedErrorTemp[0]-SpeedErrorTemp[1]) + SpeedErrorInteg;
////        Speed.Out += Speed.KP *0.005*(SpeedErrorTemp[0]-SpeedErrorTemp[1]);
//
//        Speed.Out = LIMIT_MAX(Speed.Out, 6000);
//}



