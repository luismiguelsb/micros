//LEITURA RAW DO DECODER
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	int result;
	int choice;
	
	setupDecoder();
	result = readDecoder(READ_CNTR);
	
	printf("primeira leitura (teste) = %d\n", result);
	
	printf("deseja permanecer lendo? (1-sim, 0-não)\n");
	fscanf("%d", &choice);
	
	if(choice == 1)
	{
		result = readDecoder(READ_CNTR);
		printf("decoder result = %d\n", result);
	}
	
	return 0;
}