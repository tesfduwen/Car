#include <car.h>
#include <motor_ctrl.h>

extern unsigned char white_num;      // 记录全白次数（虚线优化会用到）
bit end_flag = 0;                    // 结束标志位

//下面是传感器状态定义
#define LINE_CENTER (TR10==0 && TR20==1 && TR30==1 && TR40==0)  //轨道位于中心
#define LINE_LEFT (TR10==0 && TR20==1 && TR30==0 && TR40==0)    //轨道偏左
#define LINE_RIGHT (TR10==0 && TR20==0 && TR30==1 && TR40==0)   //轨道偏右
#define LEFT (TR10==1 && TR20==0 && TR30==0 && TR40==0)         //需要左转
#define RIGHT (TR10==0 && TR20==0 && TR30==0 && TR40==1)        //需要右转
#define ALL_BLACK (TR10==1 && TR20==1 && TR30==1 && TR40==1)    //四个传感器全检测到黑线
#define ALL_WHITE (TR10==0 && TR20==0 && TR30==0 && TR40==0)    //四个传感器全检测到白色
#define CENTER_WHITE (TR10==1 && TR20==0 && TR30==0 && TR40==1) //中心两传感器检测到白色（非正常状态）

void auto_control() {
    if (CENTER_WHITE) {
        all_stop();
        return;
    }
    if (LINE_CENTER || ALL_BLACK) {
        go_straight(255);
        return;
    }
    if (LINE_LEFT) {
        set_speed(24,255);
        if (ALL_WHITE) {
            go_straight(255);   //防抖
            return;
        }else {
            return;
        }
        return;
    }
    if (LINE_RIGHT) {
        set_speed(255,24);
        if (ALL_WHITE) {
            go_straight(255);   //防抖
            return;
        }else {
            return;
        }
        return;
    }
    if (LEFT) {
            left_turn(64,255);
            return;
    }
    if (RIGHT) {
            right_turn(255,64);
            return;
    }
    //下面是虚线优化
    if (ALL_WHITE) {
        if (white_num){     //防止短时间内多次触发虚线优化
            white_num = 0;
        }else if (!white_num) {
            straight_time(100,255);
        }
    }
}