
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

/*! \def MDR0
	\brief First SPI mode of the LS7366R decoder.
*/
//QUADRX4|FREE_RUN|DISABLE_INDX|FILTER_2
#define MDR0 0x83

/*! \def MDR1
	\brief Second SPI mode of the LS7366R decoder.
*/
//BYTE_2|EN_CNTR|NO_FLAGS
#define MDR1 0x02

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
	\brief Write a single byte.
	\param op SPI mode to be used.
	\param data Data to be written.
*/
void writeDecoder(char op, char data);

/*! \fn char readDecoder(char op);
	\brief Read a single byte using the SPI communication with the LS7366R decoder.
	\param op SPI mode to be used.
	\return Byte received.
*/
char readDecoder(char op);

/*! \fn int readDecoderCounter();
	\brief Read the quadrature decoder counter.
	\return Counter value.
*/
int readDecoderCounter();

/*! \fn void resetDecoder()
	\brief Reset the quadrature decoder counter.
*/
void resetDecoder();

/*! \fn void closeDecoder()
	\brief Close the file descriptor of the SPI device.
*/
void closeDecoder();

