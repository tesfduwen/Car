#ifndef __MOTOR_CTRL_H__
#define __MOTOR_CTRL_H__
void left_motor_f ();
void left_motor_b ();
void left_motor_stop ();

void right_motor_f ();
void right_motor_b ();
void right_motor_stop ();

void all_stop ();

void dif_motor_turn_left ();

void dif_motor_turn_right ();

void go_straight (unsigned char speed);

void set_speed (unsigned char l_speed,unsigned char r_speed);

void left_turn (unsigned char l_speed,unsigned char r_speed);

void right_turn (unsigned char l_speed,unsigned char r_speed);
#endif