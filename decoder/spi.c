/*! \file spi.c
    \brief Implement functions regarding the SPI (Serial Peripheral Interface) protocol, which is a synchronous serial communication interface specification used for short distance communication.
    This file implements pabort, initialization, transfer, start command, end command and stat information of the decoder.
*/
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
// It gives a devolopment environment for communication with the used decoder
#include <linux/spi/spidev.h>
#include <string.h>
#include <galileo2io.h>

#include <common.h>
#include <spi.h>

// Definitions of the used constants and variables
const char *device = "/dev/spidev1.0";
uint32_t mode = SPI_MODE_0; // Rising active clock
uint8_t bits = BITS_PER_TRANSACTION; // 1 Byte on each transaction of data
uint8_t lsb_first = NOT_LSB_FIRST; // It starts by the most significant bit
uint32_t speed = MAX_SPEED;
int fd; // File descriptor for getting the initialization data

//!  Abort communication with the decoder.
/*!
  This function throws an error and aborts the communication with the decoder
  via the spi protocol.
  \param [in] *s The error message.
  \see See common.h for all possible execution status.
*/
void pabort(const char * s)
{
    perror(s);
    abort();
}

//!  Open interface of communication with the decoder.
/*!
  This function tries to open the SPI device, write/read the SPI mode,
  write/read the maximum frequency, set/read the number of bits per word,
  set/read less significant bit first.
  \return Status of the attempt of initialization.
  \see See common.h for all possible execution status.
*/
int spi_init()
{
    int ret = RET_SUCCESS;

    fd = open(device, O_RDWR);
    if (fd < 0)
    {
        pabort("Error on opening the SPI device.");
    }

    ret = ioctl(fd, SPI_IOC_WR_MODE, & mode);
    if (ret == RET_ERROR)
    {
        pabort("Error on writing the SPI mode.");
    }

    ret = ioctl(fd, SPI_IOC_RD_MODE, & mode);
    if (ret == RET_ERROR)
    {
        pabort("Error on reading SPI mode.");
    }

    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, & speed);
    if (ret == RET_ERROR)
    {
        pabort("Error writing maximum frequency.");
    }

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, & speed);
    if (ret == RET_ERROR)
    {
        pabort("Error reading maximum frequency.");
    }

    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, & bits);
    if (ret == RET_ERROR)
    {
        pabort("Error on setting the number of bits per word.");
    }

    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, & bits);
    if (ret == RET_ERROR)
    {
        pabort("Error on reading number of bits per word.");
    }

    ret = ioctl(fd, SPI_IOC_WR_LSB_FIRST, & lsb_first);
    if (ret == RET_ERROR)
    {
        pabort("Error on setting LSB first.");
    }

    ret = ioctl(fd, SPI_IOC_RD_LSB_FIRST, & lsb_first);
    if (ret == RET_ERROR)
    {
        pabort("Error on reading LSB first.");
    }

    return ret;
}

//!  Close the SPI communication.
/*!
  This function closes the communication through the serial peripheral interface protocol
  by closing the file descriptor of it.
*/
int spi_finalize()
{
    return close(fd);
}

//!  Transfer data through the SPI protocol.
/*!
  Transfer data (send and receive) via the slave peripheral interface protocol.
  \param [in] fd File descriptor of for the gpio interactions.
  \param [in] *tx Pointer to the transmission buffer.
  \param [in] rx Pointer to the receiving buffer.
  \param [in] tx_size Size of the transmission buffer.
  \param [in] rx_size Size of the receiving buffer.
  \return Status of the writing to the GPIO (spi_start_command() or spi_end_command()).
  \see See pputs.c for seeing the implementation of pputs.
*/
int transfer(int fd, uint8_t * tx, uint8_t * rx, int tx_size, int rx_size)
{
    int ret = RET_SUCCESS;

    ret |= spi_start_command();

    int i;
    for (i = 0; i < tx_size; i++)
    {
        if (write(fd, & tx[i], 1) < 0) // Write info into the defined device
        {
            pabort("Unable to write into the decoder.\n");
        }
    }

    // Read info of the result of the previous writing command
    for (i = 0; i < rx_size; i++)
    {
        if (read(fd, & rx[i], 1) < 0)
        {
            pabort("Unable to read from the decoder.\n");
        }
    }

    ret |= spi_end_command();

    #ifdef DEBUG
    for (i = 0; i < tx_size; i++)
    {
        printf("%x ", tx[i]);
    }
    printf("-> ");
    for (i = 0; i < rx_size; i++)
    {
        printf("%x ", rx[i]);
    }
    printf("\n");
    #endif

    return ret;
}

//!  Transfer data through the SPI protocol with the file descriptor already defined within the scope.
/*!
  Transfer data (send and receive) via the slave peripheral interface protocol.
  \param [in] *tx Pointer to the transmission buffer.
  \param [in] rx Pointer to the receiving buffer.
  \param [in] tx_size Size of the transmission buffer.
  \param [in] rx_size Size of the receiving buffer.
  \return Status of the writing to the GPIO (spi_start_command() or spi_end_command()).
  \see See pputs.c for seeing the implementation of pputs.
*/
int spi_transfer(uint8_t * tx, uint8_t * rx, int tx_size, int rx_size)
{
    return transfer(fd, tx, rx, tx_size, rx_size);
}

//!  Start a SPI command.
/*!
  Make the slave select attribute go from low level to high level in order to do so.
  \return Status of the writing to the GPIO (spi_start_command() or spi_end_command()).
  \see See pputs.c for seeing the implementation of pputs.
*/
//
int spi_start_command()
{
    int ret = pputs("/sys/class/gpio/gpio10/value", "1");
    ret |= pputs("/sys/class/gpio/gpio10/value", "0");

    return ret;
}

//!  Finalize a SPI command.
/*!
  Make the slave select attribute go to high level for doing so once the transfer is done.
  \return Status of the writing to the GPIO (spi_start_command() or spi_end_command()).
  \see See pputs.c for seeing the implementation of pputs.
*/
//
int spi_end_command()
{
    return pputs("/sys/class/gpio/gpio10/value", "1");
}

//!  Get information from the transfer of data on debugging.
/*!
  The collected data are the SPI Mode, bits per word and maximum frequency in Hz.
*/
//
void spi_stat()
{
    #ifdef DEBUG
    printf("SPI Mode: 0x%x\n", mode);
    printf("Bits per word: %d\n", bits);
    printf("Maximum frequency: %d Hz (%d KHz)\n", speed, speed / 1000);
    #endif
}