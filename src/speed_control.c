extern unsigned char speed1,speed2;
extern bit is_turning;
extern bit is_stop;
extern unsigned char turn_time;
extern unsigned char stop_time;
extern unsigned char ori_speed1,ori_speed2;

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
    if (is_turning == 0){
        is_turning = 1;
        turn_time = time;
        ori_speed1 = speed1;
        ori_speed2 = speed2;
        left(differ);
    }
}

void turn_right (unsigned char differ,unsigned char time)
{
    if (is_turning == 0){
        is_turning = 1;
        turn_time = time;
        ori_speed1 = speed1;
        ori_speed2 = speed2;
        right(differ);
    }
}

void stop (unsigned char time)
{
    if (is_stop == 0){
        is_stop = 1;
        stop_time = time;
        speed1 = 0;
        speed2 = 0;
    }
}