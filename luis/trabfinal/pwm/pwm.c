// NÃO SEI MUTCHO LOKO PWM DO PROJETO OU NAO
// LIB DO PWM KKK

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <galileo2io.h>

#define PWM_PERIOD 	"20000000"
#define PWM_PERIOD_2 	"10000000"


void pwm_init();
void pwm_enable(int enable);
void pwm_duty_cycle(int duty_cycle);


int main(int argc,char * argv[])
{
	pwm_init();
	
        
        if(argc != 2)
        {
                puts("Usage: pwm <duty cycle em porcentagem>");
                return -1;
        }
        
        float x = atof(argv[1]) / 100 * atof(PWM_PERIOD);
	
	printf("x=%f atoi=%f atoi=%f	\n",x,atof(argv[1]),atof(PWM_PERIOD));
        
        pwm_duty_cycle((int)x);
        
	pwm_enable(1);

        return 0;
}

void pwm_init()
{	
    char buffer[100];
    
    // SETA O PWM PERIOD DA GALILEO
    snprintf(buffer,sizeof buffer,PWM_PERIOD);
    pputs("/sys/class/pwm/pwmchip0/device/pwm_period",buffer);
    
    // SETA O DUTY CYCLE DA GALILEO EM 50%
    snprintf(buffer,sizeof buffer,PWM_PERIOD_2);
    pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",buffer);
    
    // SETA O ENABLE DA GALILEO COMO 0
    snprintf(buffer,sizeof buffer,"0");
    pputs("/sys/class/pwm/pwmchip0/pwm1/enable",buffer);
    
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
