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

void Delay2000ms(void)	//@11.0592MHz
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

void motor_init() {
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
        if (runing_time>350000 && END8 && TR10 && TR20 && TR30 && TR40) {
            motor_init();
            end_flag = 1;
        }
        if (end_flag) {
            while (1)
            {
                motor_init();
            }
        }
    }
}