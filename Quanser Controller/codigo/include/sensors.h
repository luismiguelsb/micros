
// SENSORS HEADER FOR THE QUANSER PROJECT
//
// Group members: 	Luís Miguel Santos Batista
//					Gabriel Stefaniak Niemiec
//					Nicolas Eymael da Silva

/*! \file sensors.h
	\brief Header with the sensors functions of the Quanser Project.
*/

#pragma once

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "galileo2io.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


/*! \def WRITE_MDR0
	\brief First SPI mode of the LS7366R decoder.
*/
#define WRITE_MDR0 0x88

/*! \def WRITE_MDR1
	\brief Second SPI mode of the LS7366R decoder.
*/
#define WRITE_MDR1 	0x90

/*! \def CLR_CNTR
	\brief Used to clear the LS7366R decoder counter register.
*/
#define CLR_CNTR 0x20

/*! \def READ_CNTR
	\brief Used to read the LS7366R decoder counter register.
*/
#define READ_CNTR 0x60

/*! \def QUADRX4
	\brief Used to configure the LS7366R decoder mode.
*/
#define QUADRX4 0x03

/*! \def QUADRX1
	\brief Used to configure the LS7366R decoder mode.
*/
#define QUADRX1 0x01

/*! \def FREE_RUN
	\brief Used to configure the LS7366R decoder mode.
*/
#define FREE_RUN 0x00

/*! \def DISABLE_INDX
	\brief Used to configure the LS7366R decoder mode.
*/
#define DISABLE_INDX 0x00

/*! \def FILTER_2
	\brief Used to configure the LS7366R decoder mode.
*/
#define FILTER_2 0x80

/*! \def BYTE_2
	\brief Used to configure the LS7366R decoder mode.
*/
#define BYTE_2 0x02

/*! \def BYTE_4
	\brief Used to configure the LS7366R decoder mode.
*/
#define BYTE_4 0x00

/*! \def EN_CNTR
	\brief Used to configure the LS7366R decoder mode.
*/
#define EN_CNTR 0x00

/*! \def NO_FLAGS
	\brief Used to configure the LS7366R decoder mode.
*/
#define NO_FLAGS 0x00

/*! \var devspi
	\brief File descriptor of the SPI device.
*/
int devspi;



/*! \fn int limitSwitch(int which_switch)
	\brief Inform if the limit switch is in the end of course.
	\param which_switch 0 is the left limit and 1 is the right limit.
	\return ERROR or the switch value (1 if the arm is in the end of course).
*/
int limitSwitch(int which_switch);

/*! \fn void setupDecoder()
	\brief Initialize the SPI communication with the LS7366R decoder.
*/
void setupDecoder();

/*! \fn void writeDecoder(char op, char data)
	\brief Write two bytes.
	\param op SPI mode to be used.
	\param data Data to be written.
*/
void writeDecoder(char op, char data);


/*! \fn int readDecoder(char op);
	\brief Read the quadrature decoder counter.
	\param None.
	\return result Counter value.
*/
int readDecoder();

/*! \fn void resetDecoder()
	\brief Reset the quadrature decoder counter.
	\param None.
*/
void resetDecoder();

/*! \fn void closeDecoder()
	\brief Close the file descriptor of the SPI device.
*/
void closeDecoder();

// testar o read da lauren
int readCounterLauren();
