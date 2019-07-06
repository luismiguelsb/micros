//Teste para o motor
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

#include <time.h>

int main(int argc,char * argv[])
{
	float voltage;
	
	float tempo = 1.0;
	
	if(argc != 2)
	{
		puts("Usage: pidTest <posicao desejada em radianos>");
		return -1;
	}
	
	float desiredAngle = atof(argv[1]);

	if(desiredAngle > 2 * 3.14159265 || desiredAngle < 0){
		printf("Angulo improprio\n");
		return ERRO;
	}
	
	quanserInit();
	
	initPID(getPositionRad(), desiredAngle);
	
	// coloca o braço na posiçao inicial e reseta o contador do decoder
	resetPosition();


	while(diffPID() > 0.1 || diffPID() < -0.1)
	{
		
		voltage = tensaoPID(tempo , getPositionRad());
		
		setMotorVoltage(voltage);

		sleep(tempo);

		if(limitSwitch(0) == 1 || limitSwitch(1) == 1)
					break;

	}

    return OK;
}