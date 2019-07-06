//Teste para os sensores de fim de curso
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	while(1)
	{
		printf("Sensor 0: %d\tSensor 1: %d\n",limitSwitch(0),limitSwitch(1));
	}

    return OK;
}