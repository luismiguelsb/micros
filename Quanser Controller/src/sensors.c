
// SENSORS SOURCE CODE FOR THE QUANSER PROJECT
//
// Group members: 	Luís Miguel Santos Batista
//					Gabriel Stefaniak Niemiec
//					Nicolas Eymael da Silva

/*! \file sensors.c
	\brief Source code with the sensors functions of the Quanser Project.
*/

#include "../include/sensors.h"
#include "../include/quanser.h"

/*! \fn int limitSwitch(int which_switch)
	\brief Inform if the limit switch is in the end of course.
	\param which_switch 0 is the left limit and 1 is the right limit.
	\return ERROR or the switch value (1 if the arm is in the end of course).
*/
int limitSwitch(int which_switch)
{
	char data_str[80];
	int value;
	
	// switch 1 --> IO 5 --> gpio 0 	BUT	 IO4 --> GPIO 6
	// switch 2 --> IO 6 --> gpio 1		BUT	 IO5 --> GPIO 0
	
	if( which_switch == 1)
	{
		if ( pgets(data_str,sizeof data_str,"/sys/class/gpio/gpio6/value") == NULL)
			return ERRO;
		
        value = atoi(data_str);
		
		return !(value); // os sensores de fim de curso do quanser tem a logica invertida (quando é 1, ta desligado, quando é 0, ta ligado)
		// o ! ajusta isso
	}
	else
	{
		if ( pgets(data_str,sizeof data_str,"/sys/class/gpio/gpio0/value") == NULL)
			return ERRO;
		
        value = atoi(data_str);
		
		return !(value); // os sensores de fim de curso do quanser tem a logica invertida (quando é 1, ta desligado, quando é 0, ta ligado)
		// o ! ajusta isso
	}
}

/*! \fn void setupDecoder()
	\brief Initialize the SPI communication with the LS7366R decoder.
*/
void setupDecoder()
{
	uint8_t mode=SPI_MODE_0;
	uint8_t lsb=0;
	uint8_t bpw=8;
	uint32_t rate=5000000;
	
	// initialize the spi communication
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
	
	// configure the decoder mode
	writeDecoder(WRITE_MDR0, QUADRX4|FREE_RUN|DISABLE_INDX|FILTER_2); // ou QUADRX1 ?
	writeDecoder(WRITE_MDR1, BYTE_2|EN_CNTR|NO_FLAGS); // ou BYTE_4 ?
	
	resetDecoder(CLR_CNTR);
}	

/*! \fn void writeDecoder(char op, char data)
	\brief Write a single byte.
	\param op SPI mode to be used.
	\param data Data to be written.
*/
void writeDecoder(char op, char data)
{
	// the HIGH-LOW transition is the signal to start the communication
	pputs("/sys/class/gpio/gpio26/value","1");
	pputs("/sys/class/gpio/gpio26/value","0");

	if(write(devspi, &op, sizeof(op))<0){
		printf("Erro ao escrever opcode\n");
		return;
	}
	if(write(devspi, &data, sizeof(data))<0){
		printf("Erro ao escrever data\n");
		return;
	}

	pputs("/sys/class/gpio/gpio26/value","1");
}

/*! \fn char readDecoder(char op);
	\brief Read a single byte using the SPI communication with the LS7366R decoder.
	\param op SPI mode to be used.
	\return Byte received.
*/
char readDecoder(char op)
{
	int n = 0;
	char data;
	// the HIGH-LOW transition is the signal to start the communication
	pputs("/sys/class/gpio/gpio26/value","1");
	pputs("/sys/class/gpio/gpio26/value","0");

	if(write(devspi, &op, sizeof(op))<0){
		printf("Erro ao escrever opcode\n");
		return 0;
	}

	lseek(devspi, 0, SEEK_SET);
	while(n != 1)
		n = read(devspi, &data, 1);

	pputs("/sys/class/gpio/gpio26/value","1");
	return data;
}

/*! \fn int readDecoderCounter();
	\brief Read the quadrature decoder counter.
	\return Counter value.
*/
int readDecoderCounter()
{
	int n = 0;
	int data, datalsb, datamsb;
	char op = 0x60;
	// the HIGH-LOW transition is the signal to start the communication
	pputs("/sys/class/gpio/gpio26/value","1");
	pputs("/sys/class/gpio/gpio26/value","0");

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

	pputs("/sys/class/gpio/gpio26/value","1");

	data = (datamsb << 8) | datalsb;
	return data;
}

/*! \fn void resetDecoder()
	\brief Reset the quadrature decoder counter.
*/
void resetDecoder(char op)
{
	// the HIGH-LOW transition is the signal to start the communication
	pputs("/sys/class/gpio/gpio26/value","1");
	pputs("/sys/class/gpio/gpio26/value","0");

	if(write(devspi, &op, sizeof(op))<0){
		printf("Erro ao escrever opcode\n");
		return;
	}

	pputs("/sys/class/gpio/gpio26/value","1");
}

/*! \fn void closeDecoder()
	\brief Close the file descriptor of the SPI device.
*/
void closeDecoder()
{
	close(devspi);
}

