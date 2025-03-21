#include <reg52.h>

// 定义电机控制引脚
sbit LeftMotorEnable = P1^4;  // 左电机使能
sbit RightMotorEnable = P1^5; // 右电机使能

// 定义红外循迹传感器引脚
sbit Sensor1 = P1^0; // 左外侧
sbit Sensor2 = P1^1; // 左内侧
sbit Sensor3 = P1^2; // 右内侧
sbit Sensor4 = P1^3; // 右外侧

// 定义电机速度控制变量
unsigned char leftSpeed = 0;
unsigned char rightSpeed = 0;

// 延时函数
void delay(unsigned int ms) {
    unsigned int i, j;
    for (i = ms; i > 0; i--)
        for (j = 110; j > 0; j--);
}

// 初始化定时器0用于PWM输出
void Timer0_Init() {
    TMOD = 0x01; // 定时器0模式1
    TH0 = 0xFC;  // 初始值
    TL0 = 0x18;
    ET0 = 1;     // 使能定时器0中断
    EA = 1;      // 开启总中断
    TR0 = 1;     // 启动定时器0
}

// 定时器0中断服务函数，用于生成PWM信号
void Timer0_ISR() interrupt 1 {
    static unsigned char leftCounter = 0;
    static unsigned char rightCounter = 0;
    static bit leftState = 0;
    static bit rightState = 0;

    TH0 = 0xFC; // 重装定时器
    TL0 = 0x18;

    // 左电机PWM
    if (leftCounter < leftSpeed) {
        leftState = 1;
    } else {
        leftState = 0;
    }
    LeftMotorEnable = leftState;
    leftCounter++;
    if (leftCounter >= 256) leftCounter = 0;

    // 右电机PWM
    if (rightCounter < rightSpeed) {
        rightState = 1;
    } else {
        rightState = 0;
    }
    RightMotorEnable = rightState;
    rightCounter++;
    if (rightCounter >= 256) rightCounter = 0;
}

// 设置电机速度
void SetMotorSpeed(unsigned char left, unsigned char right) {
    leftSpeed = left;
    rightSpeed = right;
}

// 循迹逻辑
void TrackLogic() {
    unsigned char sensorState = 0;

    // 读取传感器状态
    sensorState = ((Sensor1 ? 1 : 0) << 3) | ((Sensor2 ? 1 : 0) << 2) | ((Sensor3 ? 1 : 0) << 1) | ((Sensor4 ? 1 : 0) << 0);

    switch (sensorState) {
        // 黑线在中间，直行
        case 0x0C: // 00001100
            SetMotorSpeed(128, 128);
            break;

        // 黑线偏左，右转
        case 0x01: // 00000001
            SetMotorSpeed(64, 128);
            break;

        // 黑线偏右，左转
        case 0x02: // 00000010
            SetMotorSpeed(128, 64);
            break;

        // 黑线在左外侧，右转
        case 0x00: // 00000000
            SetMotorSpeed(64, 128);
            break;

        // 黑线在右外侧，左转
        case 0x04: // 00000100
            SetMotorSpeed(128, 64);
            break;

        // 其他情况（可能为交叉口或错误状态），减速并重新检测
        default:
            SetMotorSpeed(32, 32);
            delay(100);
            break;
    }
}

void main() {
    // 初始化
    Timer0_Init();
    LeftMotorEnable = 0;
    RightMotorEnable = 0;

    while (1) {
        TrackLogic();
    }
}