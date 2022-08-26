/*
 * OLED.h
 *
 *  Created on: 2021��11��13��
 *      Author: YYM
 */
#ifndef CODE_DISPLAY_H_
#define CODE_DISPLAY_H_

#include "headfile.h"

extern unsigned char displayflag;

void Display_Init(void);
void Draw_Line(uint8 *p,uint16 color);
void IPS_display(void);




#endif /* CODE_DISPLAY_H_ */
