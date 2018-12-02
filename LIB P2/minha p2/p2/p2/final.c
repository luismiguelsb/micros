/*
  gabriel stefaniak niemiec e nicolas eymael da silva
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <galileo2io.h>

#include <byteswap.h>
#include <fcntl.h>
#include <stdint.h>

#include <errno.h>
#include <string.h>

#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

#include <i2cutil.h>
#include <jhdlcd.h>

static void i2c_error(const char *msg)
{
    perror(msg);
    exit(-errno);
}

int lcd(char* msg, char* msg2)
{
        int fd;
        int i;
        int n,n2;
	//char msg0[20] = "abxc\0";
        

        if((fd=open("/dev/i2c-0",O_WRONLY)) < 0) i2c_error("Opening /dev/i2c-0");
        usleep(30000);	/* Wait for 30 ms after power on */
        
        /* LCD initialization */
        if(ioctl(fd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");

        i2c_write_reg(fd,LCD_C0,LCD_FUNCTIONSET | LCD_2LINE);
        usleep(40);  /* Wait for more than 39 us */

        i2c_write_reg(fd,LCD_C0,LCD_DISPLAYSWITCH | LCD_DISPLAYON | 
                LCD_CURSOROFF | LCD_BLINKOFF);
        usleep(40);	/* Wait for more then 39 us */

        i2c_write_reg(fd,LCD_C0,LCD_SCREENCLEAR);
        usleep(1600);	/* Wait for more then 1.53 ms */
        
        i2c_write_reg(fd,LCD_C0,LCD_INPUTSET | LCD_ENTRYLEFT | LCD_DECREMENT);

        /* Backlight initialization */
        if(ioctl(fd,I2C_SLAVE,BL_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
        i2c_write_reg(fd,BL_MODE1,0);
        i2c_write_reg(fd,BL_LEDOUT,BL_RED_GRPPWM | BL_GREEN_GRPPWM | 
                BL_BLUE_GRPPWM);
        i2c_write_reg(fd,BL_MODE2,BL_DMBLNK);
        
        i2c_write_reg(fd,BL_RED,0);
        i2c_write_reg(fd,BL_GREEN,0);
        i2c_write_reg(fd,BL_BLUE,255);

        /* Write string */
        n=strlen(msg);


        if(ioctl(fd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
        for(i=0;i < n;i++) i2c_write_reg(fd,LCD_RS,msg[i]);
	for(i=0;i < 40-n;i++) i2c_write_reg(fd,LCD_RS,' ');
	n2=strlen(msg2);
	for(i=0;i < n2;i++) i2c_write_reg(fd,LCD_RS,msg2[i]);
        
        close(fd);

	return 0;
}


#define DATA_POINTS 136
#define SAMPLING_PERIOD 1e-3

/* Assumes the data format for Galileo Gen2 */
struct sensors
{
        uint16_t pot;		/* be:u12/16>>0 */
        uint16_t light;		/* be:u12/16>>0 */
        uint16_t sound;		/* be:u12/16>>0 */
        uint16_t temp;		/* be:u12/16>>0 */
        int64_t timestamp;	/* le:s64/64>>0 */
};

int readRotary(float* media, float* desvio)
{
        char data_str[100];
	float array[100];
        double scale[4];
        int fd;
        static struct sensors data[DATA_POINTS];
        int i=0;
        int samples;
        char path_str[100];

        pputs("/sys/bus/iio/devices/iio:device0/buffer/enable","0");
	
        
        //Manha pra pegar o path diferente a cada iteração
         snprintf(path_str,sizeof path_str,"/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
         //Pega os dados do path atual
         pgets(data_str,sizeof data_str,path_str);
         //A escala do canal i passa a ser a que está no /in_voltage<n>_scale
         //Divide por 1000 porque está em milissegundos
         scale[i]=atof(data_str)/1000.0;
                
         //Dá o enable pra cada canal
         snprintf(path_str,sizeof path_str,"/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage0_en");
         pputs(path_str,"1");

        //Dá enable pro modo contínuo
        pputs("/sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en","1");
        //Indica que vai coletar 100 amostras por buffer (DATA_POINTS = 100)
        snprintf(data_str,sizeof data_str,"%d",DATA_POINTS);
	//printf("%s\n",data_str);
        pputs("/sys/bus/iio/devices/iio:device0/buffer/length",data_str);
        

        pgets(data_str,sizeof data_str,"/sys/bus/iio/devices/trigger1/name");
        pputs("/sys/bus/iio/devices/iio:device0/trigger/current_trigger",data_str);
	//printf("current triger %s", data_str);
        //Frequência de trigger é o inverso do 1ms programado
        snprintf(data_str,sizeof data_str,"%d",(int)round(1.0/SAMPLING_PERIOD));
	//printf("fre? %s",data_str);
        pputs("/sys/bus/iio/devices/trigger1/frequency",data_str);
      
        //Dá enable no buffer
        pputs("/sys/bus/iio/devices/iio:device0/buffer/enable","1");


        //Fica off por 1 segundo
        sleep(ceil(DATA_POINTS*SAMPLING_PERIOD));

        
        pputs("/sys/bus/iio/devices/iio:device0/buffer/enable","0");
        
        pputs("/sys/bus/iio/devices/iio:device0/trigger/current_trigger","\n");

        if((fd=open("/dev/iio:device0",O_RDONLY)) < 0)
        {
                perror("Opening /dev/iio:device0:");
                return -1;
        }
        //Lê as amostras do sensores
        samples=read(fd,data,sizeof data)/sizeof(struct sensors);
	//printf("\nsizes %d %d\n",sizeof(data),sizeof(struct sensors));
        close(fd);
        
        //Reseta o buffer
        pputs("/sys/bus/iio/devices/iio:device0/buffer/length","2");
        

        
        //Desabilita todos os canais
        snprintf(path_str,sizeof path_str,"/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage0_en");
        pputs(path_str,"0");
        
        //Reseta a timestamp
        pputs("/sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en","0");
        
	*media=0;
	*desvio=0;
        //Escreve todas as amostras num formato 'lível' pelo GNUPlot
	if(samples>0){
	  for(i=0;i < 100;i++)
	  {
                data[i].pot=bswap_16(data[i].pot);
		array[i]=data[i].pot*scale[0];
		//printf("data %f array %f\n",data[i].pot*scale[0],array[i]);
		
                *media+=array[i];
		
		
	  }
	  *media/=100;
	  for(i=0;i < 100;i++)
	  {
		
                data[i].pot=bswap_16(data[i].pot);   
                *desvio+=pow(array[i]-*media,2);
		//printf("media=%f v= %f desvio=%f\n",*media,data[i].pot*scale[0],*desvio);
// 		
	  }
	  //printf("d1 %f\n",*desvio);
	  *desvio/=100;
	  //printf("d2 %f\n",*desvio);
	  *desvio=sqrtf(*desvio);
	  //printf("d3 %f\n",*desvio);
	}
	//printf("media=%f\n",*media);
	
	//float A = *desvio;
	//A = sqrt(A);
	
	//*desvio = A;
	//float aux = *desvio;
	
	//*desvio = sqrt(aux);
	
        
        return 0;
}

int servo(double angle)
{
        int duty_cycle;
        
        char str[100];
        
        //Converte para radianos
        //Só aceita entre 180°/-180°
	//printf("Mpi=%lf Mpi2=%lf",M_PI, M_PI_2);
        if((angle > M_PI_2) || (angle < - M_PI_2))
        {
                puts("Out of range.");
                return -2;
        }
        //850.000 = usado para converter em frequência
        //1.500.000ns = 1.500 us = frequência do sentido anti-horário
        duty_cycle=angle/M_PI_2*850000+1500000;
        //Período de 20.000.000ns == 20ms
        pputs("/sys/class/pwm/pwmchip0/device/pwm_period","20000000");
        //Formata o duty cylce
        snprintf(str,sizeof str,"%d\n",duty_cycle);
        pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",str);
        pputs("/sys/class/pwm/pwmchip0/pwm1/enable","1");
        
        //sleep(1);

        return 0;
}

#define SIZE 80
int main(int argc,char * argv[]){
  float *media, *desvio; 
  char screen[5*SIZE];
  char screen2[5*SIZE];
  
  double angle, angleRAD;
  
  media=malloc(sizeof(float));
  desvio=malloc(sizeof(float));
  
  *media = 0;
  *desvio = 0;
  
  while(1){
    
    readRotary(media,desvio);
    
    angle=*media; //angulo em volts
    
    angle = -90 + angle*180/5; //angulo em graus
    
    
    
    angleRAD = angle * M_PI/180.0;
    servo(angleRAD);
    
    sprintf(screen,"%.4lf %.4lf",*media, *desvio);
    sprintf(screen2,"%.0lf %.4lf",angle,angleRAD);
    
    lcd(screen,screen2);
    
   
  }
}
