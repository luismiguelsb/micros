
// QUANSER HEADER FOR THE QUANSER PROJECT
//
// Group members: 	Luís Miguel Santos Batista
//					Gabriel Stefaniak Niemiec
//					Nicolas Eymael da Silva

/*! \file quanser.h
	\brief Header with general functions of the Quanser Project.
*/


#pragma once

/*! \def KP
	\brief Proportional Gain of the PID controller.
*/
#define KP 0.05

/*! \def KI
	\brief Integral Gain of the PID controller.
*/
#define KI 0.05

/*! \def KD
	\brief Derivative Gain of the PID controller.
*/
#define KD 0.01

/*! \def ERRO
	\brief Value returned when there is an error.
*/
#define ERRO -1

/*! \def OK
	\brief Value returned when there is NO error.
*/
#define OK 0

/*! \def HIGHER_VOLTAGE
	\brief Higher voltage of the power source (in V).
*/
#define HIGHER_VOLTAGE 27.0

/*! \def LOWER_VOLTAGE
	\brief Lower voltage of the power source (in V).
*/
#define LOWER_VOLTAGE -27.0

/*! \def HIGHER_DUTYCYCLE
	\brief Higher duty cycle of the PWM signal (in ns).
*/
#define HIGHER_DUTYCYCLE 20000000.0

/*! \def LOWER_DUTYCYCLE
	\brief Lower duty cycle of the PWM signal (in ns).
*/
#define LOWER_DUTYCYCLE 0.0

/*! \var struct PID
	\brief Struct with variables used in the PID controller.
*/
typedef struct PID
{
	float finalAngle;
	float lastAngle; // para calcular a derivada
	float integral;
} PID;

/*! \var g_pid
	\brief Global instance of the PID struct.
*/
PID g_pid;

/*! \fn int initPID(float initialAngle, float finalAngle)
	\brief Initialize the PID struct.
	\param initialAngle Current position of the QUANSER arm.
	\param finalAngle Desired position of the QUANSER arm.
	\return OK or ERRO.
*/
int initPID(float initialAngle, float finalAngle);

/*! \fn float tensaoPID(float dt, float currentAngle)
	\brief Calculate the voltage to be applied to the motor based on the PID controller.
	\param dt Time interval.
	\param currentAngle Current position of the QUANSER arm.
	\return Voltage calculated.
*/
float tensaoPID(float dt, float currentAngle);

/*! \fn float diffPID()
	\brief Calculate the difference between the desired position and the current position of the QUANSER arm.
	\return Difference calculated.
*/
float diffPID();

/*! \fn int voltage_to_dutycycle(float voltage)
	\brief Map the voltage interval of the power source (in V) to the duty cycle interval of the PWM signal (in ns).
	\param voltage Value to be mapped (in V).
	\return Duty cycle calculated.
*/
int voltage_to_dutycycle(float voltage);

/*! \fn void bridgeEnable(int enable)
	\brief Choose if you want to enable or disable the H-bridge.
	\param enable 1 enable and 0 disable.
*/
void bridgeEnable(int enable);

/*! \fn float getCounter()
	\brief Read the quadrature decoder counter.
*/
float getCounter();

/*! \fn float counterToRad(float value)
	\brief Transform the raw value of the quadrature decoder counter into radians.
	\param value Raw value.
*/
float counterToRad(float value);







