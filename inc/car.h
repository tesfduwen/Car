#include <stc89c52.h>
#ifndef __CAR_H__
#define __CAR_H__

sbit TR10 = P1^0;    //左侧循迹模块
sbit TR20 = P1^1;    //中间左循迹模块
sbit TR30 = P1^2;    //中间右循迹模块
sbit TR40 = P1^3;    //循迹模块
sbit EN1 = P1^4;     //左电机使能
sbit EN2 = P1^5;     //右电机使能
sbit END8 = P1^6;    //结束检测
sbit IN11 = P2^0;    //左电机in1口
sbit IN12 = P2^1;    //左电机in2口
sbit IN21 = P2^3;    //右电机in1口
sbit IN22 = P2^4;    //右电机in2口
sbit ST0 = P2^7;     //避障模块（未实装，预留接口）

#endif