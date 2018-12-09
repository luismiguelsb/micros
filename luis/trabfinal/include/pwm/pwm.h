// HEADER DO PWM KKK

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