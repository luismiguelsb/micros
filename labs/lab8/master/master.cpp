/*
  spi_slave_rx.c: Receives a string using an SPI bus implemented in software.
  
  Copyright (c) 2016 Walter Fetter Lages <w.fetter@ieee.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/

#include <iostream>

#include <spislave.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
	
int main(int argc,char *argv[])
{
	int fd,fd2;
	char buffer[4]="oi!";
	char zero = '0';
	if((fd=open("/dev/spidev1.0",O_RDWR))==-1)
	{
		perror("Can't open device");
		return -1;
	}
	if((fd2=open("/sys/class/gpio/gpio26/value",O_RDWR))==-1)
	{
		perror("Can't open device2");
		return -1;
	}
	write(fd2, &zero, 1);
	close(fd2);
	  
	write(fd, buffer, 4);
	
	

	return 0;
}
