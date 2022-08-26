/*
 * PID.c
 *
 *  Created on: 2021年11月12日
 *      Author: YYM
 */

#include "PID.h"

/***********定义变量************/
float Position_KP = 2.32;
float Position_KI = 0;
float Position_KD = 0.43;
float Velocity_KP = 135;
float Velocity_KI = 7.8;

//方向环PID参数查表
//-------------------------------------------------------------------------------------------------------------------
//  @brief      方向环PID查表函数
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//  @note       Pre_Speed是我的期望速度
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
    else if(Pre_Speed >= 90 && Pre_Speed < 95)   //三档测速
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

//用于解决由高速降为低速造成高速PID调节低速时造成超调
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
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差
e(k-1)代表上一次的偏差
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/

static float Bias,Pwm,Last_Bias;
//target可以用来添加陀螺仪的角度期望
float Position_PID(float error)
{
//     Position_KP = flash_read(EEPROM_Direction,0,float);
//     Position_KD = Position_KP/7;
     //Encoder_SpeedSmooth();
//    if(MODE == 3) //1 OFF 2 ON：终极
//    {
//        PHI_Position_PID_live();
//    }
//    else
//    {
        PHI_Position_PID();
//    }
     Bias=error;                                  //计算偏差
//     Integral_bias+=Bias;                                    //求出偏差的积分
//     if(Integral_bias > 0.2 || Integral_bias < -0.2)
//     {
//         Integral_bias = 0;
//     }
     Pwm=Position_KP*Bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
     Last_Bias=Bias;                                       //保存上一次偏差
     return Pwm;                                           //输出
}


/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差
e(k-1)代表上一次的偏差  以此类推
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
static float BiasO,PwmO,Last_biasO;
int Incrementalone_PI (float Encoder,float Target)
{
    IncrementPID_Transition();
    BiasO=Target - Encoder;                                  //计算偏差
    PwmO+=Velocity_KP*(BiasO-Last_biasO)+Velocity_KI*BiasO;   //增量式PI控制器
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
    Last_biasO=BiasO;                                       //保存上一次偏差
    return PwmO;                                           //增量输出
}

static float BiasT,PwmT,Last_biasT;
int Incrementaltwo_PI (float Encoder,float Target)
{
    IncrementPID_Transition();
    BiasT=Target - Encoder;                                  //计算偏差
    PwmT+=Velocity_KP*(BiasT-Last_biasT)+Velocity_KI*BiasT;   //增量式PI控制器
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
    Last_biasT=BiasT;                                       //保存上一次偏差
    return PwmT;                                           //增量输出
}

/////////////////速度递减（防止电机速度变化过快造成耗电）////////////////////


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

//增量式PID
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
////位置式PID
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

