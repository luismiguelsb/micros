//Teste para o motor
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	bridgeEnable(0);
	pwm_init();
	
        
	if(argc != 2)
	{
		puts("Usage: motorVoltTest <voltagem>");
		return -1;
	}
	
	float x = atof(argv[1]);

	if(x > 27.0 || x < -27.0){
		printf("Voltagem impropria\n");
		return -1;
	}
	   
	pwm_enable(0);
    pwm_duty_cycle(voltage_to_dutycycle(x));
	pwm_enable(1);

	bridgeEnable(1);


    return 0;
}
