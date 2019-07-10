
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
	\brief Default Proportional Gain of the PID controller.
*/
#define KP 0.05

/*! \def KI
	\brief Default Integral Gain of the PID controller.
*/
#define KI 0.05

/*! \def KD
	\brief Default Derivative Gain of the PID controller.
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
	\brief Higher voltage of the power source in V.
*/
#define HIGHER_VOLTAGE 27.0

/*! \def LOWER_VOLTAGE
	\brief Lower voltage of the power source in V.
*/
#define LOWER_VOLTAGE -27.0

/*! \def HIGHER_DUTYCYCLE
	\brief Higher duty cycle of the PWM signal in ns.
*/
#define HIGHER_DUTYCYCLE 20000000.0 // = 20 ms

/*! \def LOWER_DUTYCYCLE
	\brief Lower duty cycle of the PWM signal in ns.
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
	float kp;
	float ki;
	float kd;
} PID;

/*! \var g_pid
	\brief Global instance of the PID struct.
*/
PID g_pid;


int initPID(float initialAngle, float finalAngle);


float tensaoPID(float dt, float currentAngle);


float diffPID();


int voltage_to_dutycycle(float voltage);


int bridgeEnable(int enable);


float getPositionRad();



int setMotorVoltage(float value);



int resetPosition();



void quanserInit();




