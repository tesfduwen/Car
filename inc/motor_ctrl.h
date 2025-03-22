#ifndef __MOTOR_CTRL_H__
#define __MOTOR_CTRL_H__
void left_motor_f ();           //左侧电机正转
void left_motor_b ();           //左侧电机反转
void left_motor_stop ();        //左侧电机停止

void right_motor_f ();          //右侧电机正转
void right_motor_b ();          //右侧电机反转
void right_motor_stop ();       //右侧电机停止

void all_stop ();               //全部电机停止

void dif_motor_turn_left ();    //左轮倒转，右轮正转

void dif_motor_turn_right ();   //左轮正转，右轮倒转

void go_straight (unsigned char speed);                                //直行，参数为速度（0-256）

void set_speed (unsigned char l_speed,unsigned char r_speed);          //设置速度，参数依次为左右轮速度（0-256）

void left_turn (unsigned char l_speed,unsigned char r_speed);           //左转，参数依次为左轮倒转速度、右轮正转速度（0-256）

void right_turn (unsigned char l_speed,unsigned char r_speed);          //右转，参数依次为左轮正转速度、右轮倒转速度（0-256）

void straight_time (unsigned char time,unsigned char speed);             //以一定速度直行一段时间，时间到后直行速度设为196，参数依次为时间（单位：ms）、速度（0-256），用于虚线优化
#endif