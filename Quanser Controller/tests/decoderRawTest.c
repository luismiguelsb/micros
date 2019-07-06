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
		result = readDecoder(READ_CNTR);
		printf("decoder raw = %d\n", result);
	}
	
	return OK;
}