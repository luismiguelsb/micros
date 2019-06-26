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
		puts("Usage: motorPwmTest <duty cycle em porcentagem>");
		return -1;
	}
	
	float x = atof(argv[1]) / 100 * atof(PWM_PERIOD);
	
	pwm_enable(0);
    pwm_duty_cycle((int)x);
	pwm_enable(1);

	bridgeEnable(1);

    return 0;
}