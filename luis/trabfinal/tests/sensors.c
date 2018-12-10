// LIB DOS SENSORES (DECODER E FIM DE CURSO) KKK

#include "../include/sensors.h"
#include "../include/quanser.h"

int limitSwitch(int which_switch)
{
	char data_str[80];
	int value;
	
	// switch 1 --> IO 5 --> gpio 0
	// switch 2 --> IO 6 --> gpio 1
	
	if( which_switch == 1)
	{
		if ( pgets(data_str,sizeof data_str,"/sys/class/gpio/gpio0/value") == NULL)
			return ERRO;
		
        value = atoi(data_str);
		
		return value;
	}
	else
	{
		if ( pgets(data_str,sizeof data_str,"/sys/class/gpio/gpio1/value") == NULL)
			return ERRO;
		
        value = atoi(data_str);
		
		return value;
	}
}
	