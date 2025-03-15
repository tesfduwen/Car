#include <intrins.h>

void Delay1ms(unsigned int a)	//@11.0592MHz
{
	unsigned char i, j;
    while (a)
    {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);
        a--;
    }
}