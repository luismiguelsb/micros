//Teste para o decoder
#include "pwm.h"
#include "quanser.h"
#include "sensors.h"

int main(int argc,char * argv[])
{
	float decode;
	setupDecoder();
	decode = getCounter();
	printf("Valor do decoder: %f\nConversao em radianos: %f rad\n",decode,counterToRad(decode));

    return 0;
}