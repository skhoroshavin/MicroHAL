
#include <hal.h>

int main(void)
{
	halInit();

	while(1)
	{
		halProcess();
		LED_set();
		LED_clr();
	}

	return 0;
}
