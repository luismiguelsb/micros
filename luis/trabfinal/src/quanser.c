
// QUANSER SOURCE CODE FOR THE QUANSER PROJECT
//
// Group members: 	Luís Miguel Santos Batista
//					Gabriel Stefaniak Niemiec
//					Nicolas Eymael da Silva

/*! \file quanser.c
	\brief Source code with general functions of the Quanser Project.
*/

#include "../include/pwm.h"
#include "../include/sensors.h"
#include "../include/quanser.h"

/*! \fn int initPID(float initialAngle, float finalAngle)
	\brief Initialize the PID struct.
	\param initialAngle Current position of the QUANSER arm.
	\param finalAngle Desired position of the QUANSER arm.
	\return OK or ERRO.
*/
int initPID(float initialAngle, float finalAngle)
{
	g_pid.integral = 0;
	g_pid.lastAngle = initialAngle;
	g_pid.finalAngle = finalAngle;
	
	return OK;
}

/*! \fn float tensaoPID(float dt, float currentAngle)
	\brief Calculate the voltage to be applied to the motor based on the PID controller.
	\param dt Time interval.
	\param currentAngle Current position of the QUANSER arm.
	\return Voltage calculated.
*/
float tensaoPID(float dt, float currentAngle)
{
	float derivada, erro, tensao;
	
	derivada = (g_pid.lastAngle - currentAngle) / dt;
	g_pid.lastAngle = currentAngle;

	erro = g_pid.finalAngle - currentAngle;
	g_pid.integral = g_pid.integral + erro*dt;

	tensao = (KP * erro) + (KI * g_pid.integral) + (KD * derivada);

	if(tensao > HIGHER_VOLTAGE)
	{
		tensao = HIGHER_VOLTAGE;	
	}
	else
	{
		if(tensao < LOWER_VOLTAGE)
		{
			tensao = LOWER_VOLTAGE;
		}
	}
	
	return tensao;
}

/*! \fn float diffPID()
	\brief Calculate the difference between the desired position and the current position of the QUANSER arm.
	\return Difference calculated.
*/
float diffPID()
{
	return g_pid.finalAngle - g_pid.lastAngle;
}

/*! \fn int voltage_to_dutycycle(float voltage)
	\brief Map the voltage interval of the power source (in V) to the duty cycle interval of the PWM signal (in ns).
	\param voltage Value to be mapped (in V).
	\return Duty cycle calculated.
*/
int voltage_to_dutycycle(float voltage)
{
  
    float dutycycle;
	
	dutycycle = LOWER_DUTYCYCLE + (voltage - LOWER_VOLTAGE)/(HIGHER_VOLTAGE - LOWER_VOLTAGE) * (HIGHER_DUTYCYCLE - LOWER_DUTYCYCLE);
	
	return (int)dutycycle;
 
}

/*! \fn void bridgeEnable(int enable)
	\brief Choose if you want to enable or disable the H-bridge.
	\param enable 1 enable and 0 disable.
*/
void bridgeEnable(int enable)
{
	if(enable == 0)
		pputs("/sys/class/gpio/gpio13/value","0");
	else
		pputs("/sys/class/gpio/gpio13/value","1");
}

/*! \fn float getCounter()
	\brief Read the quadrature decoder counter.
*/
float getCounter()
{
	float value;
	resetDecoder();
	value = readDecoderCounter();
	closeDecoder();

	return value;
}

/*! \fn float counterToRad(float value)
	\brief Transform the raw value of the quadrature decoder counter into radians.
	\param value Raw value.
*/
float counterToRad(float value)
{
	return 2 * 3.14159265 * value / 4096;
}


