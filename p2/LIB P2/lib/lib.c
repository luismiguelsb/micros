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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <byteswap.h>
#include <stdint.h>
#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

#include <i2cutil.h>
#include <jhdlcd.h>

#include <galileo2io.h>


int i2c_write_reg(int fd,unsigned char reg,unsigned char data)
{
        unsigned char buf[]={reg,data};
        
        return write(fd,buf,sizeof buf);
}

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

const char *getgpio(int port)
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

//INTERRUPÇÕES

void setinterrupt(int port, char mode)
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

//PWM

void exportpwm(const char *pwmpin)
{
  pputs("/sys/class/pwm/pwmchip0/export", pwmpin);
}

void unexportpwm(const char *pwmpin)
{
  pputs("/sys/class/pwm/pwmchip0/unexport", pwmpin);
}

void pwm_period(const char *period)
{
  //periodo é dado em nanosegundos
  pputs("/sys/class/pwm/pwmchip0/device/pwm_period", period);
}

void pwm_dutycycle(const char *dutycycle)
{
  //dutycycle duração do ciclo de trabalho do PWM em nanosegundos (deve ser menor que o periodo)
  pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", dutycycle);
}

void pwm_enable(const char *enable)
{
  //enable 1 liga, 0 desliga, só aceita esses 2 valores em forma de string
  pputs("/sys/class/pwm/pwmchip0/pwm1/enable", enable);
}

int pwm_angle_to_dutycycle(const char *degree)
{
  double rad;
  int duty_cycle;

  rad = atof(degree) * M_PI / 180.0;

  if ((rad > M_PI_2) || (rad < -M_PI_2))
    return -1;

  duty_cycle = rad / M_PI_2 * 1000000 + 1500000;

  return duty_cycle;
}

//CONVERSOR ADC

double conversor_oneshot(int channel, int N)
{
  //channel depende da tabela gpio
  int fd;
  char data_str[80];
  char path_str[80];
  double scale;
  int raw;
  double medium = 0;

  snprintf(path_str, sizeof path_str, "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw", channel);
  fd = open(path_str, O_RDONLY);
  if (fd < 0)
  {
    return -1;
  }

  snprintf(path_str, sizeof path_str, "/sys/bus/iio/devices/iio:device0/in_voltage%d_scale", channel);
  pgets(data_str, sizeof data_str, path_str);
  scale = atof(data_str) / 1000.0;

  for (int i = 0; i < N; i++)
  {
    lseek(fd, 0, SEEK_SET);
    read(fd, data_str, sizeof data_str);
    raw = atoi(data_str);
    medium += raw*scale;

    //printf("Raw=%d\tScale=%f\tVoltage=%fV\n", raw, scale, raw * scale);
  }

  close(fd);

  return medium / N;
}

struct sensors
{
  uint16_t pot;      /* be:u12/16>>0 */
  uint16_t light;    /* be:u12/16>>0 */
  uint16_t sound;    /* be:u12/16>>0 */
  uint16_t temp;     /* be:u12/16>>0 */
  int64_t timestamp; /* le:s64/64>>0 */
};

#define SAMPLING_PERIOD 1e-3
#define DATA_POINTS 1000 //numero de amostras

/*double *media;
double *desvio;
conversor_continuous(media, desvio);
*/
void conversor_continuous(double *media, double *desvio)
{

  char data_str[80];
  int fd;
  static struct sensors data[DATA_POINTS];
  int i;
  int samples;
  FILE *file;
  char path_str[80];
  double scale[4];

  pputs("/sys/bus/iio/devices/iio:device0/buffer/enable", "0");
  for (i = 0; i < 4; i++)
  {
    snprintf(path_str, sizeof path_str, "/sys/bus/iio/devices/iio:device0/in_voltage%d_scale", i);
    pgets(data_str, sizeof data_str, path_str);
    scale[i] = atof(data_str) / 1000.0;

    snprintf(path_str, sizeof path_str, "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage%d_en", i);
    pputs(path_str, "1");
  }
  pputs("/sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en", "1");

  snprintf(data_str, sizeof data_str, "%d", DATA_POINTS);
  pputs("/sys/bus/iio/devices/iio:device0/buffer/length", data_str);

#ifdef TRIG_SYSFS
  pgets(data_str, sizeof data_str, "/sys/bus/iio/devices/trigger0/name");
  pputs("/sys/bus/iio/devices/iio:device0/trigger/current_trigger", data_str);
#else
  pgets(data_str, sizeof data_str, "/sys/bus/iio/devices/trigger1/name");
  pputs("/sys/bus/iio/devices/iio:device0/trigger/current_trigger", data_str);

  snprintf(data_str, sizeof data_str, "%d", (int)round(1.0 / SAMPLING_PERIOD));
  pputs("/sys/bus/iio/devices/trigger1/frequency", data_str);
#endif

  pputs("/sys/bus/iio/devices/iio:device0/buffer/enable", "1");

#ifdef TRIG_SYSFS
  for (i = 0; i < DATA_POINTS; i++)
  {
    pputs("/sys/bus/iio/devices/trigger0/trigger_now", "1");
    usleep(ceil(SAMPLING_PERIOD * 1e6));
  }
#else
  sleep(ceil(DATA_POINTS * SAMPLING_PERIOD));
#endif

  pputs("/sys/bus/iio/devices/iio:device0/buffer/enable", "0");

  pputs("/sys/bus/iio/devices/iio:device0/trigger/current_trigger", "\n");

  if ((fd = open("/dev/iio:device0", O_RDONLY)) < 0)
  {
    return;
  }

  samples = read(fd, data, sizeof data) / sizeof(struct sensors);
  close(fd);

  pputs("/sys/bus/iio/devices/iio:device0/buffer/length", "2");

  for (i = 0; i < 4; i++)
  {
    snprintf(path_str, sizeof path_str, "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage%d_en", i);
    pputs(path_str, "0");
  }
  pputs("/sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en", "0");

  /*if ((file = fopen(argv[1], "w")) == NULL)
  {
    perror("Opening output file:");
    return -1;
  }
  */

  for (i = 0; i < samples; i++)
  {
    data[i].pot = bswap_16(data[i].pot);
    data[i].light = bswap_16(data[i].light);
    data[i].sound = bswap_16(data[i].sound);
    data[i].temp = bswap_16(data[i].temp);

    /*fprintf(file, "%f\t%f\t%f\t%f\t%f\n",
            data[i].pot * scale[0],
            data[i].light * scale[1],
            data[i].sound * scale[2],
            data[i].temp * scale[3],
            (data[i].timestamp - data[0].timestamp) * 1e-9);*/

    *media += data[i].pot * scale[0];
  }

  *media = *media / samples;

  for (i = 0; i < samples; i++)
  {

    data[i].pot = bswap_16(data[i].pot);
    *desvio += pow(data[i].pot*scale[0] - *media, 2);
    //printf("media=%f v= %f desvio=%f\n",media,data[i].potscale[0],desvio);
    //
  }
  *desvio /= 100;
  //*desvio = sqrtf(*desvio);

  fclose(file);
}

//LCD

void lcd_write(const char *line1, const char *line2)
{
  int n1, n2;
  int fd;
  int i;

  if ((fd = open("/dev/i2c-0", O_WRONLY)) < 0)
    return;
  usleep(30000); /* Wait for 30 ms after power on */

  /* LCD initialization */
  if (ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0)
    return;

  i2c_write_reg(fd, LCD_C0, LCD_FUNCTIONSET | LCD_2LINE);
  usleep(40); /* Wait for more than 39 us */

  i2c_write_reg(fd, LCD_C0, LCD_DISPLAYSWITCH | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
  usleep(40); /* Wait for more then 39 us */

  i2c_write_reg(fd, LCD_C0, LCD_SCREENCLEAR);
  usleep(1600); /* Wait for more then 1.53 ms */

  i2c_write_reg(fd, LCD_C0, LCD_INPUTSET | LCD_ENTRYLEFT | LCD_DECREMENT);

  /* Backlight initialization */
  if (ioctl(fd, I2C_SLAVE, BL_ADDR) < 0)
    return;
  i2c_write_reg(fd, BL_MODE1, 0);
  i2c_write_reg(fd, BL_LEDOUT, BL_RED_GRPPWM | BL_GREEN_GRPPWM | BL_BLUE_GRPPWM);
  i2c_write_reg(fd, BL_MODE2, BL_DMBLNK);

  i2c_write_reg(fd, BL_RED, 127);
  i2c_write_reg(fd, BL_GREEN, 0);
  i2c_write_reg(fd, BL_BLUE, 127);

  /* Write string */
  n1 = strlen(line1);
  n2 = strlen(line2);

  if (ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0)
    return;

  for (i = 0; i < n1; i++)
    i2c_write_reg(fd, LCD_RS, line1[i]);

  for (i = 0; i < 40 - n1; i++)
    i2c_write_reg(fd, LCD_RS, ' ');

  for (i = 0; i < n2; i++)
    i2c_write_reg(fd, LCD_RS, line2[i]);

  close(fd);
}