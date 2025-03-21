#include <car.h>
#include <speed_control.h>

// 定义传感器状态宏
#define OBSTACLE        (ST0 == 0)
#define STRAIGHT_COND   ((!TR10&&!TR40&&TR20&&TR30) || (TR10&&TR20&&TR30&&TR40))
#define LEFT_DEVIATION  (!TR10&&!TR20&&TR30&&!TR40)
#define RIGHT_DEVIATION (!TR10&&TR20&&!TR30&&!TR40)
#define SHARP_LEFT      (TR10&&!TR40)  // 左侧传感器离线
#define SHARP_RIGHT     (!TR10&&TR40)  // 右侧传感器离线
#define ALL_WHITE       (!TR10&&!TR20&&!TR30&&!TR40)

void auto_ctrl_u()
{
    /* 优先级1: 避障 */
    if(OBSTACLE) {
        turn_left(25,1000);
        return; // 立即返回确保避障优先
    }

    /* 优先级2: 直行条件 */
    if(STRAIGHT_COND) {
        straight(100);
    }
    /* 优先级3: 小幅偏离修正 */
    else if(LEFT_DEVIATION) {
        turn_right(20,500);
        if(ALL_WHITE) straight(100); // 防抖处理
    } 
    else if(RIGHT_DEVIATION) {
        turn_left(20,500);
        if(ALL_WHITE) straight(100);
    }
    /* 优先级4: 大角度转向 */
    else if(SHARP_LEFT) {
        turn_left(99,1000);
    } 
    else if(SHARP_RIGHT) {
        turn_right(99,1000);
    }
}
