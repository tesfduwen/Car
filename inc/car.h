#include <stc89c52.h>
#ifndef __CAR_H__
#define __CAR_H__

sbit TR10 = P1^0;
sbit TR20 = P1^1;
sbit TR30 = P1^2;
sbit TR40 = P1^3;    //循迹模块
sbit EN1 = P1^4;
sbit EN2 = P1^5;    //电机使能
sbit END8 = P1^6;
sbit IN11 = P2^0;
sbit IN12 = P2^1;
sbit IN21 = P2^3;
sbit IN22 = P2^4;   //电机in口
sbit ST0 = P2^7;    //避障模块

#endif