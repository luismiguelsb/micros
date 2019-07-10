//LEITURA EM RAD DO DECODER
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	float result;
	
	setupDecoder();
	
	while(1)
	{
		result = getPositionRad();
		
		printf("decoder raw = %f\n", result);
	}
	
	return OK;
}