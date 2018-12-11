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

void setupDecoder(){
	uint8_t mode=SPI_MODE_0;
	uint8_t lsb=0;
	uint8_t bpw=8;
	uint32_t rate=5000000;
	
	if((devspi=open("/dev/spidev1.0",O_RDWR))==-1)
	{
		perror("Can't open device");
		return;
	}
	if(ioctl(devspi,SPI_IOC_WR_MODE,&mode))
	{
		perror("Can't write clock mode");
		return;
	}
	if(ioctl(devspi,SPI_IOC_WR_LSB_FIRST,&lsb))
	{
		perror("Can't read LSB mode");
		return;
	}
	if(ioctl(devspi,SPI_IOC_WR_BITS_PER_WORD,&bpw))
	{
		perror("Can't read bits per word");
		return;
	}
	if(ioctl(devspi,SPI_IOC_WR_MAX_SPEED_HZ,&rate))
	{
		perror("Can't read maximal rate");
		return;
	}
	writeDecoder(0x88, MDR0);
	writeDecoder(0x90, MDR1);
}	

void writeDecoder(char op, char data){
	pputs("/sys/class/gpio/gpio10/value","1");
	pputs("/sys/class/gpio/gpio10/value","0");

	if(write(devspi, &op, sizeof(op))<0){
		printf("Erro ao escrever opcode\n");
		return;
	}
	if(write(devspi, &data, sizeof(data))<0){
		printf("Erro ao escrever data\n");
		return;
	}

	pputs("/sys/class/gpio/gpio10/value","1");
}

char readDecoder(char op){
	int n = 0;
	char data;
	pputs("/sys/class/gpio/gpio10/value","1");
	pputs("/sys/class/gpio/gpio10/value","0");

	if(write(devspi, &op, sizeof(op))<0){
		printf("Erro ao escrever opcode\n");
		return 0;
	}

	lseek(devspi, 0, SEEK_SET);
	while(n != 1)
		n = read(devspi, &data, 1);

	pputs("/sys/class/gpio/gpio10/value","1");
	return data;
}

int readDecoderCounter(){
	int n = 0;
	int data, datalsb, datamsb;
	char op = 0x60;
	pputs("/sys/class/gpio/gpio10/value","1");
	pputs("/sys/class/gpio/gpio10/value","0");

	if(write(devspi, &op, sizeof(op))<0){
		printf("Erro ao escrever opcode\n");
		return 0;
	}

	lseek(devspi, 0, SEEK_SET);
	while(n != 1)
		n = read(devspi, &datamsb, 1);
	n = 0;
	while(n != 1)
		n = read(devspi, &datalsb, 1);

	pputs("/sys/class/gpio/gpio10/value","1");

	data = (datamsb << 8) | datalsb;
	return data;
}

void resetDecoder(){
	char op = 0x20;
	pputs("/sys/class/gpio/gpio10/value","1");
	pputs("/sys/class/gpio/gpio10/value","0");

	if(write(devspi, &op, sizeof(op))<0){
		printf("Erro ao escrever opcode\n");
		return;
	}

	pputs("/sys/class/gpio/gpio10/value","1");
}

void closeDecoder(){
	close(devspi);
}