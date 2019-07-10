
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
	\see See quanser.h for the header of the function.
*/
int initPID(float initialAngle, float finalAngle)
{
	g_pid.integral = 0;
	g_pid.lastAngle = initialAngle;
	g_pid.finalAngle = finalAngle;
	g_pid.kp = KP;
	g_pid.ki = KI;
	g_pid.kd = KD;
	
	return OK;
}

/*! \fn float tensaoPID(float dt, float currentAngle)
	\brief Calculate the voltage to be applied to the motor based on the PID controller.
	\param dt Time interval.
	\param currentAngle Current position of the QUANSER arm.
	\return Voltage calculated.
	\see See quanser.h for the header of the function.
*/
float tensaoPID(float dt, float currentAngle)
{
	float derivada, erro, tensao;
	
	derivada = (g_pid.lastAngle - currentAngle) / dt;
	g_pid.lastAngle = currentAngle;

	erro = g_pid.finalAngle - currentAngle;
	g_pid.integral = g_pid.integral + erro*dt;

	// formula do PID
	tensao = (g_pid.kp * erro) + (g_pid.ki * g_pid.integral) + (g_pid.kd * derivada);

	// não ultrapassar o limite de tensão da fonte
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
	\param None.
	\return Difference calculated.
	\see See quanser.h for the header of the function.
*/
float diffPID()
{
	return g_pid.finalAngle - g_pid.lastAngle;
}

/*! \fn int voltage_to_dutycycle(float voltage)
	\brief Map the voltage interval of the power source (in V) to the duty cycle interval of the PWM signal (in ns).
	\param voltage Value to be mapped (in V).
	\return Duty cycle calculated.
	\see See quanser.h for the header of the function.
*/
int voltage_to_dutycycle(float voltage)
{
  
    float dutycycle;
	
	dutycycle = LOWER_DUTYCYCLE + (voltage - LOWER_VOLTAGE)/(HIGHER_VOLTAGE - LOWER_VOLTAGE) * (HIGHER_DUTYCYCLE - LOWER_DUTYCYCLE);
	
	return (int)dutycycle;
 
}

/*! \fn int bridgeEnable(int enable)
	\brief Choose if you want to enable or disable the H-bridge.
	\param enable 1 enable and 0 disable.
	\return OK or ERRO.
	\see See quanser.h for the header of the function.
*/
int bridgeEnable(int enable)
{
	int n = -1;
	
	if(enable == 0)
		n = pputs("/sys/class/gpio/gpio13/value","0");
	else if(enable == 1)
		n = pputs("/sys/class/gpio/gpio13/value","1");
	else
		printf("Utilize 0 ou 1!\n");
	
	if(n < 0)
	{
		printf("Erro no bridgeEnable!\n");
		return ERRO;
	}
	else
		return OK;
}


/*! \fn float getPositionRad()
	\brief Read the raw value of the quadrature decoder counter and transform into radians.
	\param None.
	\return The position of the Quanser arm in radians.
	\see See quanser.h for the header of the function.
*/
float getPositionRad()
{
	int result;
	result = readDecoder();
	
	return 2 * 3.14159265 * result / 4096;
}

/*! \fn int setMotorVoltage(float value)
	\brief Set the motor voltage.
	\param value Voltage.
	\return OK or ERRO.
	\see See quanser.h for the header of the function.
*/
int setMotorVoltage(float value)
{
	if(bridgeEnable(0) == ERRO)
	{
		printf("Erro no setMotorVoltage!\n");
		return ERRO;
	}
	//pwm_init();
	pwm_enable(0);
	
    pwm_duty_cycle(voltage_to_dutycycle(value));
	
	pwm_enable(1);
	
	if(bridgeEnable(1) == ERRO)
	{
		printf("Erro no setMotorVoltage!\n");
		return ERRO;
	}
	
	return OK;
}

/*! \fn int resetPosition()
	\brief Reset the Quanser position and the decoder to the initial position.
	\param None.
	\return OK or ERRO.
	\see See quanser.h for the header of the function.
*/
int resetPosition()
{
	if(setMotorVoltage(-5.0) == ERRO)
	{
		printf("Erro no resetPosition!\n");
		return ERRO;
	}
	
	while(limitSwitch(0) == 0 && limitSwitch(1) == 0)
	{
		// wait until the Quanser is not in the limit
	}
	
	if(setMotorVoltage(0) == ERRO)
	{
		printf("Erro no resetPosition!\n");
		return ERRO;
	}
	
	if(bridgeEnable(0) == ERRO)
	{
		printf("Erro no resetPosition!\n");
		return ERRO;
	}
	
	resetDecoder();	
	
	return OK;
}

/*! \fn void quanserInit()
	\brief Initialize the PWM and the decoder LS7366R that will be used by the Quanser.
	\param None.
	\see See quanser.h for the header of the function.
*/
void quanserInit()
{
	pwm_init();
	setupDecoder();
	bridgeEnable(0);
}


