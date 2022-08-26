/*
 * PID.h
 *
 *  Created on: 2021年11月12日
 *      Author: YYM
 */

#ifndef CODE_PID_H_
#define CODE_PID_H_

#include "headfile.h"

//#define Min(a, b) (((a) < (b)) ? (a) : (b))
//#define Max(a, b) (((a) > (b)) ? (a) : (b))
//#define MINMAX(input, low, upper) Min(Max(input, low), upper)


/*********************申明变量********************/
extern float Position_KP,
             Position_KI,
             Position_KD,
             Velocity_KP,
             Velocity_KI;
//typedef struct
//{
//    float kp;    //P
//    float ki;    //I
//    float kd;    //D
//    float i_max; //integrator_max
//    float p_max; //integrator_max
//    float d_max; //integrator_max
//
//    float low_pass;
//
//    float out_p;
//    float out_i;
//    float out_d;
//
//    float error;
//    float pre_error;
//    float pre_pre_error;
//} pid_param_t;
//
//#define PID_CREATE(_kp, _ki, _kd, _low_pass, max_p , max_i ,max_d) \
//    {                                    \
//        .kp = _kp,                       \
//        .ki = _ki,                       \
//        .kd = _kd,                       \
//        .low_pass = _low_pass,           \
//        .out_p = 0,                      \
//        .out_i = 0,                      \
//        .out_d = 0,                      \
//        .p_max = max_p,                  \
//        .i_max = max_i,                  \
//        .d_max = max_d,                  \
//    }
//

static void PHI_Position_PID(void);
void IncrementPID_Transition(void);
float Position_PID (float position);
//float pid_solve(pid_param_t *pid, float error);
//float increment_pid_solve(pid_param_t *pid, float error);
//float increment_pid(float error);
int Incrementalone_PI (float Encoder,float Target);
int Incrementaltwo_PI (float Encoder,float Target);



#endif /* CODE_PID_H_ */
