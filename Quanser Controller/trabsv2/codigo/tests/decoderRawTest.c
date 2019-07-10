//LEITURA RAW DO DECODER
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	int result;
	
	setupDecoder();
	
	while(1)
	{
		result = readDecoder();
		printf("decoder raw = %d\t", result);
	}
	
	return OK;
}