//Teste para o motor
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	float voltage;
	float tempo = 0.0;
	bridgeEnable(0);
	pwm_init();
	setupDecoder();	
        
	if(argc != 2)
	{
		puts("Usage: pidTest <posicao desejada em radianos>");
		return -1;
	}
	
	float x = atof(argv[1]);

	if(x > 2 * 3.14159265 || x < 0){
		printf("Angulo improprio\n");
		return -1;
	}
	initPID(counterToRad(getCounter()),x);

	while(diffPID() > 0.1 || diffPID() < -0.1){
		voltage = tensaoPID(tempo,counterToRad(getCounter()));
		tempo = 1.0;
		pwm_enable(0);
		pwm_duty_cycle(voltage_to_dutycycle(voltage));
		pwm_enable(1);

		bridgeEnable(1);

		sleep(tempo);

		bridgeEnable(0);

		pwm_enable(0);
	}

    return 0;
}