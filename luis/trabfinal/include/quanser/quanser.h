// HEADER QUE INTEGRA AS LIB KKK

#define KP 0.05
#define KI 0.05
#define KD 0.01

#define ERRO -1
#define OK 0

typedef struct PID
{
	float finalAngle;
	float lastAngle; // para calcular a derivada
	float integral;
} PID;


PID g_pid;


// inicializa o pid
int initPID(float finalAngle);


// controlador PID que retorna a tensão a ser aplicada no motor
float tensaoPID(float dt, float currentAngle);


// mapeia a tensão (recebida pelo PID) para ciclo de trabalho do PWM
int voltage_to_dutycycle(float voltage);






