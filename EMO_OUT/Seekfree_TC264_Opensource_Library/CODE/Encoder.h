/*
 * Encoder.h
 *
 *  Created on: 2021年11月12日
 *      Author: YYM
 */

#ifndef CODE_ENCODER_H_
#define CODE_ENCODER_H_

#include "headfile.h"

#define GarageOutStraightDistance  2000
#define GarageOutLeftTurnDistance  3000
#define GarageOutRightTurnDistance 1700
#define GarageInLeftTurnDistance   4300
#define GarageInRightTurnDistance  3000


/*************申明变量***********/
extern int16 CoderONE,CoderTWO,CoderSpeed;
extern int CoderSumONE,CoderSumTWO,Real_Distance,CoderChSumONE,CoderChSumTWO,Real_ChDistance
,CoderRaSumONE,CoderRaSumTWO,Real_RaDistance,CoderGaSumONE,CoderGaSumTWO,Real_GaDistance,Real_lowDistance;
extern float SpeedError;
extern unsigned char EncoderSum_flag,EncoderCharge_flag,EncoderRamp_flag,EncoderGa_flag,Encoderlow_flag;

void Encoder_Init(void);
int16 Encoder_MTM(GPTN_enum gptn,int n);
void Encoder_coder(void);
void Encoder_Summation(void);
void Encoder_SumClear(void);
void EncoderRamp_Summation(void);
void EncoderRamp_SumClear(void);
void EncoderCharge_SumClear(void);
void EncoderCharge_Summation(void);
void Encoder_Distance(int TargetDistanceONE,int TargetDistanceTWO,float Time,float TargetSpeedONE,float TargetSpeedTWO);
void Encoder_FindCharge(int TargetDistance,float Speed);
void Garage_Out(void);
void Garage_In(void);
void Encoder_SpeedSmooth(void);
void EncoderGar_Summation(void);
void EncoderGar_SumClear(void);

#endif /* CODE_ENCODER_H_ */
