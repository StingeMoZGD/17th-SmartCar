/*
 * Beep.h
 *
 *  Created on: 2022Äê2ÔÂ5ÈÕ
 *      Author: YYM
 */

#ifndef LIBRARIES_SEEKFREE_LIBRARIES_BEEP_H_
#define LIBRARIES_SEEKFREE_LIBRARIES_BEEP_H_

#include "headfile.h"


#define Beep_Pin   P10_3
#define BeepCircle 1
#define BeepSlalom 2
#define BeepThreefork 3
#define Beepon 4

extern uint8 Beepindex;

void Beep_Init(void);
void Beep_ON(void);
void Beep_OFF(void);
void Beep_onepoint(void);
void Beep_twopoint(void);
void Beep_threepoint(void);
void Beep_Customize(void);


#endif /* LIBRARIES_SEEKFREE_LIBRARIES_BEEP_H_ */
