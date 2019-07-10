
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
#define PWM_PERIOD 	"20000000" // = 20 ms

/*! \def PWM_PERIOD_2
	\brief Half of the period of the PWM signal (in ns) generated by the Galileo Board.
*/
#define PWM_PERIOD_2 	"10000000" // = 10 ms


void pwm_init();


void pwm_enable(int enable);


void pwm_duty_cycle(int duty_cycle);