//Teste para o motor
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	if(argc != 2)
	{
		puts("Usage: motorVoltTest <voltagem>");
		return -1;
	}
	
	quanserInit();
	
	float x = atof(argv[1]);

	if(x > 27.0 || x < -27.0){
		printf("Voltagem impropria\n");
		return -1;
	}
	   
	setMotorVoltage(x);

    return OK;
}
