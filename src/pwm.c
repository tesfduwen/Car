#include <stc89c52.h>
#include <car.h>
#include <motor_ctrl.h>

void Timer0_Init(void)		//25微秒@11.0592MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0xE9;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
    ET0 = 1;                //定时器0中断允许开关
    EA = 1;                 //定时器总开关
    PT0 = 0;                //定时器0中断优先级
}

volatile unsigned char compare = 0;      //PWM程序内部比较值
volatile unsigned char speed1,speed2;    //speed1左侧两轮速度,speed2右侧两轮速度
volatile bit is_turning = 0;             //是否正在转向
volatile unsigned char turn_time = 0;    //转向时间
volatile unsigned char tick = 0;         //转向时间计数
volatile unsigned char white_num = 0;
volatile long runing_time = 0;

void Time0_Runtine (void) interrupt 1
{
    TL0 = 0xE9;
    TH0 = 0xFF;             //从下面开始是PWM程序
    compare++;
    if (runing_time<400000){
        runing_time++;
    }
    if (compare>=256) compare = 0;
    if (speed2>compare)
        {
            EN2 = 1;
        }else
        {
            EN2 = 0;
        }
    if (speed1>=compare)
        {
            EN1 = 1;
        }else
        {
            EN1 = 0;
        }
        if (++tick>=40){
            tick = 0;
            if (is_turning&&(turn_time>0)){
                turn_time--;
                if (turn_time==0){
                    go_straight(196);
                    white_num++;
                    is_turning = 0;
                }
            }
        }
}