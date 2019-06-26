
// PWM HEADER FOR THE QUANSER PROJECT
//
// Group members: 	Luís Miguel Santos Batista
//					Gabriel Stefaniak Niemiec
//					Nicolas Eymael da Silva

/*! \file pwm.h
	\brief Header with the PWM functions of the Quanser Project.
*/


#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "galileo2io.h"

/*! \def PWM_PERIOD
	\brief Period of the PWM signal (in ns) generated by the Galileo Board.
*/
#define PWM_PERIOD 	"20000000"

/*! \def PWM_PERIOD_2
	\brief Half of the period of the PWM signal (in ns) generated by the Galileo Board.
*/
#define PWM_PERIOD_2 	"10000000" 

/*! \fn void pwm_init()
	\brief Initialize the period and the duty cycle of the PWM signal.
*/
void pwm_init();

/*! \fn void pwm_enable(int enable)
	\brief Choose if you want to enable or disable the PWM signal.
	\param enable 1 enable and 0 disable.
*/
void pwm_enable(int enable);

/*! \fn void pwm_duty_cycle(int duty_cycle)
	\brief Set the duty cycle of the PWM signal.
	\param duty_cycle Value in ns (must be lower than PWM_PERIOD)
*/
void pwm_duty_cycle(int duty_cycle);