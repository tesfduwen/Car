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

void main()
{
    speed1 = 0;
    speed2 = 0;
    Timer0_Init();
    while (1)
    {
        auto_control();
    }
}