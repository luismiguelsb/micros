/*! \file decoder.c
    \brief Implement all the procedures needed for communication with the decoder LS7366R through the SPI protocol.
    This file implements initialization, read counter, conversion from position
    to radians, clear counter, finalization.
*/
#include <stdio.h>
#include <string.h>
#include <spi.h>

#include <common.h>
#include <galileo2io.h>
#include <decoder.h>

//!  Initialize the interface of communication with the decoder.
/*!
  This function initializes the communication with the decoder LS7366R.
  \return Execution status.
  \see See common.h for all possible execution status.
*/
int decoder_init()
{
    int ret = RET_SUCCESS;
    ret |= spi_init();

    #ifdef DEBUG
    printf("Writing MDR0...\n");
    #endif
    unsigned char wr_data[2];

    // For writing
    wr_data[0] = WRITE_MDR0;
    wr_data[1] = QUADRX1 | FREE_RUN | DISABLE_INDX | FILTER_2; // w-stage filter

    ret |= spi_transfer((uint8_t * ) wr_data, NULL, 2, 0);

    #ifdef DEBUG
    printf("Writing MDR1...\n");
    #endif

    wr_data[0] = WRITE_MDR1;
    wr_data[1] = NO_FLAGS | BYTE_4 | EN_CNTR; // Enable counter

    ret |= spi_transfer((uint8_t * ) wr_data, NULL, 2, 0);

    #ifdef DEBUG
    printf("Reading MDR0...\n");
    #endif
    unsigned char wr = READ_MDR0;
    unsigned char rd;
    ret |= spi_transfer((uint8_t * ) & wr, (uint8_t * ) & rd, 1, 1);

    #ifdef DEBUG
    printf("Reading MDR1...\n");
    #endif
    wr = READ_MDR1;
    ret |= spi_transfer((uint8_t * ) & wr, (uint8_t * ) & rd, 1, 1);
    ret |= decoder_clear_counter();

    return ret;
}

//!  Read data from the decoder.
/*!
  Read the 2-byte data from the counter.
  \return Counting data.
*/
unsigned int decoder_read_counter()
{
    unsigned char wr_data = READ_CNTR;
    unsigned char rd_data[4];
    spi_transfer((uint8_t * ) & wr_data, (uint8_t * ) rd_data, 1, 4);
    // Shift and or for getting 16 bits ([0, 2^16 -1])
    // - <=> +
    unsigned int current_byte = rd_data[0];
    unsigned int count = 0;
    count |= current_byte << 24;
    current_byte = rd_data[1];
    count |= current_byte << 16;
    current_byte = rd_data[2];
    count |= current_byte << 8;
    current_byte = rd_data[3];
    count |= current_byte;

    return count;
}

//!  Convert position to radians.
/*!
  Get the position of the decoder (number of bits towards the left or right) and convert to radians.
  \return Position in radians.
*/
double decoder_position_to_radians()
{
    int position = decoder_read_counter();
    double radians = (double) position * POSITION_TO_RADIANS_FACTOR;

    return radians;
}

//!  Clear counter of the decoder.
/*!
  Put zero into the decoder via SPI protocol.
  \return Status of the SPI transfer.
  \see See spi.h for the implementation of the function spi_transfer.
*/
int decoder_clear_counter()
{
    unsigned char wr_data = CLR_CNTR;

    return spi_transfer((uint8_t * ) & wr_data, NULL, 1, 0);
}

//!  Finalize the communication with the decoder.
/*!
  This function calls the finalization method from the spi interface.
  \see See spi.h for the definition of spi_finalize().
*/
int decoder_finalize()
{
    return spi_finalize();
}