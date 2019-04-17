/*
  tx.c: Serial transmission in non-canonical mode.
  
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

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	int fd;
	struct termios tty;
	char c;
	
	if(argc != 2)
	{
		printf("Noncanonical mode transmission\n");
		printf("\tUsage:\t%s <device>\n",argv[0]);
		return -1;
	}
	if((fd=open(argv[1],O_RDWR))==-1)
	{
		perror(argv[0]);
		return -errno;
	}
	
	if(tcgetattr(fd,&tty))
	{
		perror(argv[0]);
		return -errno;
	}	
	
	if(cfsetspeed(&tty,B9600))
	{
		perror(argv[0]);
		return -errno;
	}	        
	
	cfmakeraw(&tty);
	
        if (tcsetattr(fd,TCSANOW,&tty))
	{
		perror(argv[0]);
		return -errno;
	}
	
	do
	{
		c=getchar();

		if(write(fd,&c,1)==-1)
		{
			perror(argv[0]);
			return -errno;
		}
	} while (c != 0x2b);

	if(tcdrain(fd))
	{
		perror(argv[0]);
		return -errno;
	}

	if(close(fd))
	{
		perror(argv[0]);
		return -errno;
	}
	
	return 0;
}
