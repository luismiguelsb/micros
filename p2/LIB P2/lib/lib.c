/*
  pgets.c: Gets a string from a file, given its path.
  
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

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include <galileo2io.h>

char *pgets(char *s, int size, const char path[])
{
  int fd;

  if ((fd = open(path, O_RDONLY)) == -1)
    return NULL;
  read(fd, s, size);
  close(fd);
  return s;
}

int pputs(const char path[], const char s[])
{
  int fd;
  ;
  int n;

  if ((fd = open(path, O_WRONLY)) == -1)
    return -1;
  n = write(fd, s, strlen(s));
  close(fd);
  return n;
}

//port é a porta do pino
//mode l - low; h - high; i - input
void setgpio(int port, char mode)
{
  char data_str[80];

  switch (mode)
  {
  case 'l':
    snprintf(data_str, sizeof data_str, "/sys/class/gpio/gpio%d/direction", port);
    pputs(data_str, "out");

    snprintf(data_str, sizeof data_str, "/sys/class/gpio/gpio%d/value", port);
    pputs(data_str, "0");

    break;
  case 'h':
    snprintf(data_str, sizeof data_str, "/sys/class/gpio/gpio%d/direction", port);
    pputs(data_str, "out");

    snprintf(data_str, sizeof data_str, "/sys/class/gpio/gpio%d/value", port);
    pputs(data_str, "1");

    break;
  case 'i':
    snprintf(data_str, sizeof data_str, "/sys/class/gpio/gpio%d/direction", port);
    pputs(data_str, "in");

    break;
  }
}

const char *getgpio(char *port)
{
  char path_str[80];
  char data_str[80];


  snprintf(path_str, sizeof path_str, "/sys/class/gpio/gpio%d/value", port);
  pgets(data_str, sizeof data_str, path_str);

  return data_str;
}

void exportgpio(char *port)
{
  pputs("/sys/class/gpio/export", port);
}

void unexportgpio(char *port)
{
  pputs("/sys/class/gpio/unexport", port);
}

void setpermissions(char *filepath, char *group)
{
  snprintf(path_str, sizeof path_str, "/sys/class/gpio/gpio%d/value", port);


  chmod(filepath)
  chgrp pwm /sys/class/pwm/pwmchip0/pwm1/duty_cycle
	chmod g+w /sys/class/pwm/pwmchip0/pwm1/duty_cycle
}

//INTERRUPÇÕES

void setinterrupt (int port, char mode)
{
  char data_str[80];

  snprintf(data_str, sizeof data_str, "/sys/class/gpio/gpio%d/edge", port);

  switch (mode)
  {
  case 'r':
    pputs(data_str, "rising");
    break;
  case 'f':
    pputs(data_str, "falling");
    break;
  case 'b':
    pputs(data_str, "both");
    break;
  case 'n':
    pputs(data_str, "none");
    break;
  }
}

