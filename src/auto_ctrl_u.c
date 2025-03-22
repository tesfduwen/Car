#include <car.h>
#include <speed_control.h>

// 调试输出函数
void debug_print(const char *message) {
    // 使用串口输出调试信息
    while (*message) {
        SBUF = *message++;  // 发送字符到串口
        while (!TI);        // 等待发送完成
        TI = 0;             // 清除发送标志
    }
    SBUF = '\n';            // 发送换行符
    while (!TI);
    TI = 0;
}

// 定义传感器状态结构体
typedef struct {
    unsigned char tr10;
    unsigned char tr20;
    unsigned char tr30;
    unsigned char tr40;
} SensorState;

#define FILTER_SIZE 5
static unsigned char tr10_history[FILTER_SIZE] = {0};
static unsigned char tr20_history[FILTER_SIZE] = {0};
static unsigned char tr30_history[FILTER_SIZE] = {0};
static unsigned char tr40_history[FILTER_SIZE] = {0};

unsigned char filter_sensor(unsigned char history[], unsigned char new_value) {
    // 滑动平均滤波
    unsigned char sum = 0;
    unsigned char i;
    for (i = 1; i < FILTER_SIZE; i++) {
        history[i - 1] = history[i];
        sum += history[i];
    }
    history[FILTER_SIZE - 1] = new_value;
    sum += new_value;
    return (sum > (FILTER_SIZE / 2)) ? 1 : 0;
}

void update_sensor_state(SensorState *state) {
    state->tr10 = filter_sensor(tr10_history, TR10);
    state->tr20 = filter_sensor(tr20_history, TR20);
    state->tr30 = filter_sensor(tr30_history, TR30);
    state->tr40 = filter_sensor(tr40_history, TR40);
}

#define OBSTACLE        (ST0 == 0)
#define STRAIGHT_COND(state)   ((!state.tr10&&!state.tr40&&state.tr20&&state.tr30) || (state.tr10&&state.tr20&&state.tr30&&state.tr40))
#define LEFT_DEVIATION(state)  (!state.tr10&&!state.tr20&&state.tr30&&!state.tr40)
#define RIGHT_DEVIATION(state) (!state.tr10&&state.tr20&&!state.tr30&&!state.tr40)
#define SHARP_LEFT(state)      (state.tr10&&!state.tr40)  // 左侧传感器离线
#define SHARP_RIGHT(state)     (!state.tr10&&state.tr40)  // 右侧传感器离线
#define ALL_WHITE(state)       (!state.tr10&&!state.tr20&&!state.tr30&&!state.tr40)

void auto_ctrl_u()
{
    SensorState state;
    update_sensor_state(&state);

    // 输出传感器状态
    debug_print("Sensor State:");
    debug_print("TR10="); debug_print(state.tr10 ? "1" : "0");
    debug_print("TR20="); debug_print(state.tr20 ? "1" : "0");
    debug_print("TR30="); debug_print(state.tr30 ? "1" : "0");
    debug_print("TR40="); debug_print(state.tr40 ? "1" : "0");

    /* 优先级1: 避障 */
    if(OBSTACLE) {
        debug_print("Obstacle detected! Turning left...");
        turn_left(25,1000);
        return; // 立即返回确保避障优先
    }

    /* 优先级2: 直行条件 */
    if(STRAIGHT_COND(state)) {
        debug_print("Straight condition detected. Moving straight...");
        straight(100);
    }
    /* 优先级3: 小幅偏离修正 */
    else if(LEFT_DEVIATION(state)) {
        debug_print("Left deviation detected. Correcting to the right...");
        turn_right(20,500);
        if(ALL_WHITE(state)) straight(100); // 防抖处理
    } 
    else if(RIGHT_DEVIATION(state)) {
        debug_print("Right deviation detected. Correcting to the left...");
        turn_left(20,500);
        if(ALL_WHITE(state)) straight(100);
    }
    /* 优先级4: 大角度转向 */
    else if(SHARP_LEFT(state)) {
        debug_print("Sharp left detected. Turning left...");
        turn_left(99,1000);
    } 
    else if(SHARP_RIGHT(state)) {
        debug_print("Sharp right detected. Turning right...");
        turn_right(99,1000);
    }
}
