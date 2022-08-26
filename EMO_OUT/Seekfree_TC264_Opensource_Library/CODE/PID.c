/*
 * PID.c
 *
 *  Created on: 2021��11��12��
 *      Author: YYM
 */

#include "PID.h"

/***********�������************/
float Position_KP = 2.32;
float Position_KI = 0;
float Position_KD = 0.43;
float Velocity_KP = 135;
float Velocity_KI = 7.8;

//����PID�������
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����PID�������
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//  @note       Pre_Speed���ҵ������ٶ�
//-------------------------------------------------------------------------------------------------------------------
static void PHI_Position_PID(void)
{
    if(Pre_Speed < 10)
    {
        Position_KP = 0.6;
        Position_KI = 0;
        Position_KD = 0;
    }
    else if(Pre_Speed >= 10 && Pre_Speed < 20)
    {
        Position_KP = 0.62;
        Position_KI = 0;
        Position_KD = 0;
    }
    else if(Pre_Speed >= 20 && Pre_Speed < 30)
    {
        Position_KP = 0.6;
        Position_KI = 0;
        Position_KD = 0;
    }
    else if(Pre_Speed >= 30 && Pre_Speed < 40)
    {
        Position_KP = 0.6;
        Position_KI = 0;
        Position_KD = 0;
    }
    else if(Pre_Speed >= 40 && Pre_Speed < 50)
    {
        Position_KP = 0.55;
        Position_KI = 0;
        Position_KD = 0;
    }
    else if(Pre_Speed >= 50 && Pre_Speed < 60)
    {
        Position_KP = 0.53;
        Position_KI = 0;
        Position_KD = 0;
    }
    else if(Pre_Speed >= 60 && Pre_Speed < 70)
    {
        Position_KP = 0.55;
        Position_KI = 0;
        Position_KD = 0;
    }
    else if(Pre_Speed >= 70 && Pre_Speed < 80)
    {
        Position_KP = 0.58;//0.78
        Position_KI = 0;
        Position_KD = 0;//0.38
    }
    else if(Pre_Speed >= 80 && Pre_Speed < 85)
    {
        Position_KP = 0.61;//0.83
        Position_KI = 0;
        Position_KD = 0;//0.5
    }
    else if(Pre_Speed >= 85 && Pre_Speed < 90)
    {
        Position_KP = 0.63;//1.12   0.85
        Position_KI = 0;
        Position_KD = 0.2;//       0.58
    }
    else if(Pre_Speed >= 90 && Pre_Speed < 95)   //��������
    {
        Position_KP = 0.66;//
        Position_KI = 0;
        Position_KD = 0.5;//
    }
    else if(Pre_Speed >= 95 && Pre_Speed < 100)
    {
        Position_KP = 0.68;
        Position_KI = 0;
        Position_KD = 0.55;
    }
    else if(Pre_Speed >= 100 && Pre_Speed < 105)
    {
        Position_KP = 0.72;
        Position_KI = 0;
        Position_KD = 0.7;
    }
    else if(Pre_Speed >= 105 && Pre_Speed < 110)
    {
        Position_KP = 0.74;   //1.12
        Position_KI = 0;
        Position_KD = 0.75;
    }
    else if(Pre_Speed >= 110 && Pre_Speed < 115)
    {
        Position_KP = 0.76;   //1.23
        Position_KI = 0;
        Position_KD = 0.818;  //1.03
    }
    else if(Pre_Speed >= 115 && Pre_Speed < 120)
    {
        Position_KP = 0.80;   //1.23  1.07
        Position_KI = 0;
        Position_KD = 0.86;  //1.03   0.83
    }
    else if(Pre_Speed >= 120 && Pre_Speed < 125)
    {
        Position_KP = 0.84;
        Position_KI = 0;
        Position_KD = 0.9;
    }
    else if(Pre_Speed >= 125 && Pre_Speed < 130)
    {
        Position_KP = 0.87;
        Position_KI = 0;
        Position_KD = 0.93;
    }
    else if(Pre_Speed >= 130 && Pre_Speed < 140)
    {
        Position_KP = 0.94;
        Position_KI = 0;
        Position_KD = 1;
    }
    else if(Pre_Speed >= 140 && Pre_Speed < 150)
    {
        Position_KP = 1.36;
        Position_KI = 0;
        Position_KD = 1.32;
    }
    else if(Pre_Speed >= 150 && Pre_Speed < 160)
    {
        Position_KP = 1.48;
        Position_KI = 0;
        Position_KD = 1.43;
    }
    else if(Pre_Speed >= 160 && Pre_Speed < 170)
    {
        Position_KP = 1.55;
        Position_KI = 0;
        Position_KD = 1.43;
    }
    else if(Pre_Speed >= 170 && Pre_Speed < 180)
    {
        Position_KP = 1.65;
        Position_KI = 0;
        Position_KD = 1.5;
    }
    Position_KP = Position_KP + Replace_DircetionP;
    Position_KD = Position_KD + Replace_DircetionP;
}

//���ڽ���ɸ��ٽ�Ϊ������ɸ���PID���ڵ���ʱ��ɳ���
void IncrementPID_Transition(void)
{
    float KP = 125;
    float KI = 7.5;
    if(State == Charge_State && FindCharge_flag == 1 && Read_Battery_Voltage >= 7)
    {
        KP = 125;
        KI = 7.5;
    }
    else if(State == Charge_State && FindCharge_flag == 1 && Read_Battery_Voltage < 7 && Read_Battery_Voltage >= 4)
    {
        KP = 125;
        KI = 7.5;
    }
    else if(State == Charge_State && FindCharge_flag == 1 && Read_Battery_Voltage < 4)
    {
        KP = 125;
        KI = 7.5;
    }
    else
    {
        KP = 115;
        KI = 6;
    }
//    else if(FindCharge_flag == 1 && Pre_Speed < 80)
//    {
//        KP = KP*1.24;
//        KI = KI*1.24;
//    }
    Velocity_KP = KP;
    Velocity_KI = KI;

}


/**************************************************************************
�������ܣ�λ��ʽPID������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����  ֵ�����PWM
����λ��ʽ��ɢPID��ʽ
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)��������ƫ��
e(k-1)������һ�ε�ƫ��
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
**************************************************************************/

static float Bias,Pwm,Last_Bias;
//target�����������������ǵĽǶ�����
float Position_PID(float error)
{
//     Position_KP = flash_read(EEPROM_Direction,0,float);
//     Position_KD = Position_KP/7;
     //Encoder_SpeedSmooth();
//    if(MODE == 3) //1 OFF 2 ON���ռ�
//    {
//        PHI_Position_PID_live();
//    }
//    else
//    {
        PHI_Position_PID();
//    }
     Bias=error;                                  //����ƫ��
//     Integral_bias+=Bias;                                    //���ƫ��Ļ���
//     if(Integral_bias > 0.2 || Integral_bias < -0.2)
//     {
//         Integral_bias = 0;
//     }
     Pwm=Position_KP*Bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
     Last_Bias=Bias;                                       //������һ��ƫ��
     return Pwm;                                           //���
}


/**************************************************************************
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)��������ƫ��
e(k-1)������һ�ε�ƫ��  �Դ�����
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
static float BiasO,PwmO,Last_biasO;
int Incrementalone_PI (float Encoder,float Target)
{
    IncrementPID_Transition();
    BiasO=Target - Encoder;                                  //����ƫ��
    PwmO+=Velocity_KP*(BiasO-Last_biasO)+Velocity_KI*BiasO;   //����ʽPI������
    if(Battery_Voltage <= 5)
    {
        PwmO = PwmO >9600 ? 9600 : PwmO;
    }
    else
    {
        PwmO = PwmO >7000 ? 7000 : PwmO;
    }
    PwmO = PwmO <(-9000) ? (-9000) : PwmO;
    //  Pwm = Pwm < (0) ? 0 : Pwm;
    Last_biasO=BiasO;                                       //������һ��ƫ��
    return PwmO;                                           //�������
}

static float BiasT,PwmT,Last_biasT;
int Incrementaltwo_PI (float Encoder,float Target)
{
    IncrementPID_Transition();
    BiasT=Target - Encoder;                                  //����ƫ��
    PwmT+=Velocity_KP*(BiasT-Last_biasT)+Velocity_KI*BiasT;   //����ʽPI������
    if(Battery_Voltage <= 5)
    {
        PwmT = PwmT >9600 ? 9600 : PwmT;
    }
    else
    {
        PwmT = PwmT >7000 ? 7000 : PwmT;
    }
    PwmT = PwmT <(-9000) ? (-9000) : PwmT;
    //  Pwm = Pwm < (0) ? 0 : Pwm;
    Last_biasT=BiasT;                                       //������һ��ƫ��
    return PwmT;                                           //�������
}

/////////////////�ٶȵݼ�����ֹ����ٶȱ仯������ɺĵ磩////////////////////


/*
float increment_pid_solve(pid_param_t *pid, float error)
{

    pid->out_d = MINMAX(pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error), -pid->d_max, pid->d_max);
        //(*pid).out_d;

    pid->out_p = MINMAX(pid->kp * (error - pid->pre_error), -pid->p_max, pid->p_max);

    pid->out_i = MINMAX(pid->ki * error, -pid->i_max, pid->i_max);

    pid->pre_pre_error = pid->pre_error;
    pid->pre_error = error;



    return pid->out_p + pid->out_i + pid->out_d;
}
*/

//����ʽPID
//float increment_pid_solve(pid_param_t *pid, float error)
//{
//    float out = 0;
//    float last_out = 0;
//
//    pid->out_d = MINMAX(pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error), -pid->d_max, pid->d_max);
//        //(*pid).out_d;
//
//    pid->out_p = pid->kp * (error - pid->pre_error);
//
//    pid->out_i = pid->ki * error;
//    out = pid->out_p + pid->out_i + pid->out_d + last_out;
//
//    pid->pre_pre_error = pid->pre_error;
//    pid->pre_error = error;
//    last_out = out;
//
//
//
//    return out;
//}

//float last_error;
////λ��ʽPID
//float pid_solve(pid_param_t *pid, float error)
//{
//    pid->out_d = (error - last_error);
//
//    pid->out_p = error;
//
//    pid->out_i += error;
//    //if(pid->ki != 0) pid->out_i = MINMAX(pid->out_i, -pid->i_max / pid->ki, pid->i_max / pid->ki);
//
//    last_error = error;
//    return (pid->kp * pid->out_p + pid->ki * pid->out_i + pid->kd * pid->out_d);
//}
