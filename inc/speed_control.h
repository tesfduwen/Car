#ifndef __SPEED_CONTROL_H__
#define __SPEED_CONTROL_H__
void straight (unsigned char speed);                                    //参数为速度值(此值将作为默认速度)
void left (unsigned char differ);                                       //两轮差速致使小车向左转，参数为两轮转速之差(注意：调用此函数后，转速将永久改变)
void right (unsigned char differ);                                      //效果同上，小车向右转
void turn_left (unsigned char differ,unsigned char time);               //小车左转，参数为两轮差速，转向时间(转向时间过后两两轮转速恢复函数调用前的值)
void turn_right (unsigned char differ,unsigned char time);              //小车右转，效果同上
void stop (unsigned char time);                                         //参数为时间，效果为停止向电机供电，设定时间过后两轮速度值恢复为函数调用之前的值
#endif
//注：速度值指PWM占空比，其范围为0~100，大于100按100计算。时间单位为毫秒。