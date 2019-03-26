
# testar a configuração de pinos

#	IO2		OUT	Bridge Enable
	cat /sys/class/gpio/gpio13/direction
	
	cat /sys/class/gpio/gpio34/direction
	cat /sys/class/gpio/gpio34/value
	
	cat /sys/class/gpio/gpio77/direction
	cat /sys/class/gpio/gpio77/value
	
#	IO3		OUT	PWM
	cat /sys/class/pwm/pwmchip0/device/pwm_period
	cat /sys/class/pwm/pwmchip0/pwm1/duty_cycle
	cat /sys/class/pwm/pwmchip0/pwm1/enable
	
	cat /sys/class/gpio/gpio16/direction
	cat /sys/class/gpio/gpio16/value
	
	cat /sys/class/gpio/gpio17/direction
	
	cat /sys/class/gpio/gpio76/value
	
	cat /sys/class/gpio/gpio64/value
	
#	IO4		OUT	Decoder Enable
	cat /sys/class/gpio/gpio6/direction
	cat /sys/class/gpio/gpio6/value
	
	cat /sys/class/gpio/gpio36/direction
	cat /sys/class/gpio/gpio36/value
	
#	IO5		IN	Limit Switch 0
	cat /sys/class/gpio/gpio0/direction
	cat /sys/class/gpio/gpio0/value
	
	cat /sys/class/gpio/gpio18/direction
	cat /sys/class/gpio/gpio18/value
	
	cat /sys/class/gpio/gpio66/direction
	cat /sys/class/gpio/gpio66/value
	
#	IO6		IN	Limit Switch 1
	cat /sys/class/gpio/gpio1/direction
	cat /sys/class/gpio/gpio1/value
	
	cat /sys/class/gpio/gpio20/direction
	cat /sys/class/gpio/gpio20/value
	
	cat /sys/class/gpio/gpio68/direction
	cat /sys/class/gpio/gpio68/value
	
#	IO10	OUT	Decoder SS
	cat /sys/class/gpio/gpio26/direction
	cat /sys/class/gpio/gpio26/value
	
	cat /sys/class/gpio/gpio27/direction
	cat /sys/class/gpio/gpio27/value
	
	cat /sys/class/gpio/gpio74/value
	
#	IO11	OUT	SPI MOSI
	cat /sys/class/gpio/gpio24/direction
	cat /sys/class/gpio/gpio24/value
	
	cat /sys/class/gpio/gpio25/direction
	
	cat /sys/class/gpio/gpio44/direction
	cat /sys/class/gpio/gpio44/value
	
	cat /sys/class/gpio/gpio72/value
	
#	IO12	IN	SPI MISO
	cat /sys/class/gpio/gpio42/direction
	cat /sys/class/gpio/gpio42/value
	
	cat /sys/class/gpio/gpio43/direction
	
#	IO13	OUT	SPI SCK
	cat /sys/class/gpio/gpio30/direction
	cat /sys/class/gpio/gpio30/value
	
	cat /sys/class/gpio/gpio31/direction
	cat /sys/class/gpio/gpio31/value
	
	cat /sys/class/gpio/gpio46/direction
	cat /sys/class/gpio/gpio46/value
	








