#ifndef __PWM_H__
#define __PWM_H__
extern unsigned char compare;           //PWM程序内部比较值
extern unsigned char speed1,speed2;     //speed1左侧两轮速度,speed2右侧两轮速度
void Timer0_Init(void);                 //初始化定时器0
extern bit is_turning;                  //定义即使标志
extern unsigned char turn_time;         //时间
extern long runing_time;                 //运行时间
#endif