//Teste para PWM
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	pwm_init();
	
        
        if(argc != 2)
        {
                puts("Usage: pwmTest <duty cycle em porcentagem>");
                return -1;
        }
        
        float x = atof(argv[1]) / 100 * atof(PWM_PERIOD);
	
	//printf("x=%f atoi=%f atoi=%f	\n",x,atof(argv[1]),atof(PWM_PERIOD));
        
        pwm_duty_cycle((int)x);
        
	pwm_enable(1);

        return 0;
}