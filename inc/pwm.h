#ifndef __PWM_H__
#define __PWM_H__
extern unsigned char compare;      //PWM程序内部比较值
extern unsigned char speed1,speed2;    //speed1左侧两轮速度,speed2右侧两轮速度
void Timer0_Init(void);
extern bit is_turning;
extern unsigned char turn_time;
#endif