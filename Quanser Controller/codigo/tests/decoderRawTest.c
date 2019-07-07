//LEITURA RAW DO DECODER
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	int result;
	int result2;
	
	setupDecoder();
	
	while(1)
	{
		result = readDecoder();
		result2 = readCounterLauren();
		printf("decoder raw = %d\t", result);
		printf("decoder raw = %d\n", result2);
	}
	
	return OK;
}