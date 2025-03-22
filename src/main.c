/*************************************
 * 
 *      智能车控制程序
 * 
 * CPU: stc89C52rc
 * FREQ: 11.0592MHz
 * PIN: P00
 * 
 * ***********************************
*/

#include <stc89c52.h>
#include <car.h>
#include <auto_ctrl.h>
#include <pwm.h>
#include <intrins.h>

void Delay2000ms(void)	// 延时2s
{
	unsigned char data i, j, k;

	_nop_();
	i = 15;
	j = 2;
	k = 235;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void motor_init() {     //电机初始化
    speed1 = 0;
    speed2 = 0;
    IN11 = 0;
    IN12 = 0;
    IN21 = 0;
    IN22 = 0;
}

void main()
{
    motor_init();
    Delay2000ms();
    Timer0_Init();
    while (1)
    {
        auto_control();
        if (runing_time>350000 && END8 && TR10 && TR20 && TR30 && TR40) {   //运行时间大于8s，且检测全黑，结束检测模块有信号输入，初始化电机，并将结束标志设为1
            motor_init();
            end_flag = 1;
        }
        if (end_flag) {            //结束标志为1，循环初始化电机，以达到停车效果（不在上面的if设置循环的原因：防止小车冲过头导致不停车）
            while (1)
            {
                motor_init();
            }
        }
    }
}