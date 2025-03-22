#include <car.h>
#include <pwm.h>

void left_motor_f () {
    IN11 = 1;
    IN12 = 0;
}
void left_motor_b () {
    IN11 = 0;
    IN12 = 1;
}
void left_motor_stop () {
    IN11 = 0;
    IN12 = 0;
}

void right_motor_f () {
    IN21 = 1;
    IN22 = 0;
}
void right_motor_b () {
    IN21 = 0;
    IN22 = 1;
}
void right_motor_stop () {
    IN21 = 0;
    IN22 = 0;
}

void all_stop () {
    left_motor_stop();
    right_motor_stop();
}

void dif_motor_turn_left () {
    left_motor_b();
    right_motor_f();
}

void dif_motor_turn_right () {    
    left_motor_f();
    right_motor_b();
}

void set_speed (unsigned char l_speed,unsigned char r_speed) {
    speed1 = l_speed;
    speed2 = r_speed;
}

void go_straight (unsigned char speed) {
    all_stop();
    set_speed(speed,speed);
    left_motor_f();
    right_motor_f();
}

void left_turn (unsigned char l_speed,unsigned char r_speed) {
    dif_motor_turn_left();
    set_speed(l_speed,r_speed);
}

void right_turn (unsigned char l_speed,unsigned char r_speed) {
    dif_motor_turn_right();
    set_speed(l_speed,r_speed);
}
