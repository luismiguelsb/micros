// LIB DO PWM KKK

#include "../include/pwm.h"

void pwm_init()
{	
    char buffer[100];
	
	// SETA O ENABLE DA GALILEO COMO 0
    snprintf(buffer,sizeof buffer,"0");
    pputs("/sys/class/pwm/pwmchip0/pwm1/enable",buffer);
    
    // SETA O PWM PERIOD DA GALILEO
    snprintf(buffer,sizeof buffer,PWM_PERIOD);
    pputs("/sys/class/pwm/pwmchip0/device/pwm_period",buffer);
    
    // SETA O DUTY CYCLE DA GALILEO EM 50%
    snprintf(buffer,sizeof buffer,PWM_PERIOD_2);
    pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",buffer); 
}

void pwm_enable(int enable)
{
  
    char buffer[100];
    
    // SETA O ENABLE DA GALILEO COMO 0
    snprintf(buffer,sizeof buffer,"%d\n",enable);
    pputs("/sys/class/pwm/pwmchip0/pwm1/enable",buffer);
  
}


void pwm_duty_cycle(int duty_cycle)
{
     char buffer[100];
     
    // SETA O DUTY CYCLE DA GALILEO EM 50%
     
    snprintf(buffer,sizeof buffer,"%d\n",duty_cycle);
    printf("olha so: %s,  %d\n",buffer,duty_cycle);
    pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",buffer);
  
}
