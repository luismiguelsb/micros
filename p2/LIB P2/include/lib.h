/*
  jhdlcd.h: Definitions for the JHD1214 RGB LCD
  
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

#ifndef LIB_H
#define LIB_H



char *pgets(char *s, int size, const char path[]);
int pputs(const char path[], const char s[]);
void setgpio(int port, char mode);
const char *getgpio(char *port);
void exportgpio(char *port);
void unexportgpio(char *port);
void setinterrupt(int port, char mode);
void exportpwm(const char *pwmpin);
void unexportpwm(const char *pwmpin);
void pwm_period(const char *period);
void pwm_dutycycle(const char *dutycycle);
void pwm_enable(const char *enable);
int pwm_angle_to_dutycycle(const char *degree);
double conversor_oneshot(int channel, int N);
void conversor_continuous(double *media, double *desvio);
void lcd_write(const char *line1, const char *line2);

#endif