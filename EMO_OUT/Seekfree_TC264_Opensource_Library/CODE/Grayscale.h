/*
 * Grayscale.h
 *
 *  Created on: 2022��8��26��
 *      Author: YYM
 */

#ifndef CODE_GRAYSCALE_H_
#define CODE_GRAYSCALE_H_

#include "headfile.h"
#include "SEEKFREE_MT9V03X.h"

#define RThresholdr  -30
#define LThresholdr  -30
#define RThresholde  -5
#define LThresholde  -5

extern uint8 Grayscale_imag[120][188],
             Grayscale_Right[120],
             Grayscale_Left[120],
             Grayscale_Middle[120];


void get_grayscaleimag(void);
void get_grayscale_line(void);
void grayscale_pro(void);



#endif /* CODE_GRAYSCALE_H_ */
