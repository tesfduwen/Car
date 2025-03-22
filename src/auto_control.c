#include <car.h>
#include <motor_ctrl.h>

unsigned flag_b = 0;

#define LINE_CENTER (TR10==1 && TR20==0 && TR30==0 && TR40==1)
#define LINE_LEFT (TR10==1 && TR20==0 && TR30==1 && TR40==0)
#define LINE_RIGHT (TR10==1 && TR20==1 && TR30==0 && TR40==1)
#define LEFT (TR10==0 && TR20==1 && TR30==1 && TR40==1)
#define RIGHT (TR10==1 && TR20==1 && TR30==1 && TR40==0)
#define CROSS ((flag_b==2 || flag_b==3 || flag_b==4 || flag_b==5) && TR10==1 && TR20==1 && TR30==1 && TR40==1)
#define START (flag_b==1 && TR10==1 && TR20==1 && TR30==1 && TR40==1)
#define END (flag_b==6 && TR10==1 && TR20==1 && TR30==1 && TR40==1)
#define ALL_BLACK (TR10==0 && TR20==0 && TR30==0 && TR40==0)
#define ALL_WHITE (TR10==1 && TR20==1 && TR30==1 && TR40==1)

void auto_control() {
    if (ALL_BLACK) {
        flag_b++;
    }
    if (START) {
        go_straight(255);
    }
    if (END) {
        all_stop();
    }
    if (LINE_CENTER) {
        go_straight(255);
    }else if(LINE_LEFT || LINE_RIGHT) {
        if (LINE_LEFT) {
            set_speed(188,255);
            if (ALL_WHITE) {
                go_straight(255);
            }
    }
        if (LINE_RIGHT) {
            set_speed(255,188);
            if (ALL_WHITE) {
                go_straight(255);
            }
    }
    }else if (LEFT || RIGHT) {
        if (LEFT) {
            left_turn(64,255);
            return;
            }
        if (RIGHT) {
            right_turn(255,64);
            return;
        }
    }
}

