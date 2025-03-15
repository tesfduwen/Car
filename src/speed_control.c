#include <delay1ms.h>

extern unsigned char speed1,speed2;

void straight (unsigned char speed)
{
    speed1 = speed;
    speed2 = speed;
}

void left (unsigned char differ)
{
    speed1 = speed2 - differ;
}

void right (unsigned char differ)
{
    speed2 = speed1 - differ;
}

void turn_left (unsigned char differ,unsigned char time)
{
    left(differ);
    Delay1ms(time);
    speed1 = speed1 + differ;
}

void turn_right (unsigned char differ,unsigned char time)
{
    right(differ);
    Delay1ms(time);
    speed2 = speed2 + differ;
}

void stop (unsigned char time)
{
    unsigned char s1 = speed1;
    unsigned char s2 = speed2;
    speed1 = 0;
    speed2 = 0;
    Delay1ms(time);
    speed1 = s1;
    speed2 = s2;
}