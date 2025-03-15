#include <stc89c52.h>
#ifndef __CAR_H__
#define __CAR_H__

sbit TR10 = P1^0;
sbit TR20 = P1^1;
sbit TR30 = P1^2;
sbit TR40 = P1^3;    //循迹模块
sbit EN1 = P1^4;
sbit EN2 = P1^5;
sbit EN3 = P1^6;
sbit EN4 = P1^7;    //电机使能
sbit ST0 = P2^7;    //避障模块

#endif