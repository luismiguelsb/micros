#ifndef SPI_H_
#define SPI_H_

#define BITS_PER_TRANSACTION 8
#define NOT_LSB_FIRST 0
#define MAX_SPEED 8000000 // 8MHz

#include <stdint.h>

void pabort(const char *s);
int spi_init();
int spi_finalize();
int transfer(int fd, uint8_t *tx, uint8_t *rx, int tx_size, int rx_size);
int spi_transfer(uint8_t *tx, uint8_t *rx, int tx_size, int rx_size);
void spi_stat();
int spi_start_command();
int spi_end_command();

#endif