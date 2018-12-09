// LIB QUE INTEGRA AS LIB KKK

#include "../include/pwm.h"
#include "../include/quanser.h"





// inicializa o pid
int initPID(float finalAngle)
{
	g_pid.integral = 0;
	g_pid.lastAngle = 0;
	g_pid.finalAngle = finalAngle;
	
	return OK;
}

// controlador PID que retorna a tensão a ser aplicada no motor
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

// mapeia a tensão (recebida pelo PID) para ciclo de trabalho do PWM
int voltage_to_dutycycle(float voltage)
{
  
    float dutycycle;
	
	dutycycle = LOWER_DUTYCYCLE + (voltage - LOWER_VOLTAGE)/(HIGHER_VOLTAGE - LOWER_VOLTAGE) * (HIGHER_DUTYCYCLE - LOWER_DUTYCYCLE);
	
	return (int)dutycycle;
 
}




