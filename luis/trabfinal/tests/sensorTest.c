//Teste para os sensores de fim de curso
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	printf("Sensor 0: %d\nSensor 1: %d\n",limitSwitch(0),limitSwitch(1));

    return 0;
}