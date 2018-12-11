
// PWM SOURCE CODE FOR THE QUANSER PROJECT
//
// Group members: 	Luís Miguel Santos Batista
//					Gabriel Stefaniak Niemiec
//					Nicolas Eymael da Silva


/*! \file pwm.c
	\brief Source code with the PWM functions of the Quanser Project.
*/


#include "../include/pwm.h"

/*! \fn void pwm_init()
	\brief Initialize the period and the duty cycle of the PWM signal.
*/
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


/*! \fn pwm_enable(int enable)
	\brief Choose if you want to enable or disable the PWM signal.
	\param enable 1 enable and 0 disable.
*/
void pwm_enable(int enable)
{
    char buffer[100];
    
    // SETA O ENABLE DA GALILEO COMO enable
    snprintf(buffer,sizeof buffer,"%d\n",enable);
    pputs("/sys/class/pwm/pwmchip0/pwm1/enable",buffer);
  
}


/*! \fn pwm_duty_cycle(int duty_cycle)
	\brief Set the duty cycle of the PWM signal.
	\param duty_cycle Value in ns (must be lower than PWM_PERIOD)
*/
void pwm_duty_cycle(int duty_cycle)
{
     char buffer[100];
     
    // SETA O DUTY CYCLE DA GALILEO EM 50%
     
    snprintf(buffer,sizeof buffer,"%d\n",duty_cycle);
    //printf("olha so: %s,  %d\n",buffer,duty_cycle);
    pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",buffer);
  
}
