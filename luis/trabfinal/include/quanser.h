
// QUANSER HEADER FOR THE QUANSER PROJECT
//
// Group members: 	Luís Miguel Santos Batista
//					Gabriel Stefaniak Niemiec
//					Nicolas Eymael da Silva

#pragma once

#define KP 0.05
#define KI 0.05
#define KD 0.01

#define ERRO -1
#define OK 0

#define HIGHER_VOLTAGE 27.0
#define LOWER_VOLTAGE -27.0
#define HIGHER_DUTYCYCLE 20000000.0
#define LOWER_DUTYCYCLE 0.0

typedef struct PID
{
	float finalAngle;
	float lastAngle; // para calcular a derivada
	float integral;
} PID;


PID g_pid;


int initPID(float initialAngle, float finalAngle);

float tensaoPID(float dt, float currentAngle);

float diffPID();

int voltage_to_dutycycle(float voltage);

void bridgeEnable(int enable);

float getCounter();

float counterToRad(float value);







