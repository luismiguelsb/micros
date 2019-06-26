# SCRIPT DE INICIALIZAÇÃO DO PROJETO QUANSER
# Integrantes:	Luís Miguel Santos Batista
#				Gabriel Stefaniak Niemiec
#				Nicolas Eymael da Silva
# 
#	IO2		OUT	Bridge Enable
#	IO3		OUT	PWM
#	IO4		OUT	Decoder Enable
#	IO5		IN	Limit Switch 0
#	IO6		IN	Limit Switch 1
#	IO10	OUT	Decoder SS
#	IO11	OUT	SPI MOSI
#	IO12	IN	SPI MISO
#	IO13	OUT	SPI SCK


case "$1" in
    start|restart|force-reload)
	
	#	IO2		OUT	Bridge Enable
	if [ ! -d /sys/class/gpio/gpio13 ] ; then
	    echo -n "13" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio13/direction
	chgrp projeto /sys/class/gpio/gpio13/value
	chmod g+rw /sys/class/gpio/gpio13/value
	
	if [ ! -d /sys/class/gpio/gpio34 ] ; then
	    echo -n "34" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio34/direction
	echo -n "0" > /sys/class/gpio/gpio34/value
	
	if [ ! -d /sys/class/gpio/gpio77 ] ; then
	    echo -n "77" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio77/direction
	echo -n "0" > /sys/class/gpio/gpio77/value
	
	
	#	IO3		OUT	PWM
	if [ ! -d /sys/class/pwm/pwmchip0/pwm1 ] ; then
	    echo -n "1" > /sys/class/pwm/pwmchip0/export
	fi
	chgrp projeto /sys/class/pwm/pwmchip0/device/pwm_period
	chmod g+w /sys/class/pwm/pwmchip0/device/pwm_period
	chgrp projeto /sys/class/pwm/pwmchip0/pwm1/duty_cycle
	chmod g+w /sys/class/pwm/pwmchip0/pwm1/duty_cycle
	chgrp projeto /sys/class/pwm/pwmchip0/pwm1/enable
	chmod g+w /sys/class/pwm/pwmchip0/pwm1/enable
        
	if [ ! -d /sys/class/gpio/gpio16 ] ; then
	    echo -n "16" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio16/direction
	echo -n "0" > /sys/class/gpio/gpio16/value

	if [ ! -d /sys/class/gpio/gpio17 ] ; then
	    echo -n "17" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio17/direction
        
	if [ ! -d /sys/class/gpio/gpio76 ] ; then
	    echo -n "76" > /sys/class/gpio/export
	fi
	echo -n "0" > /sys/class/gpio/gpio76/value
        
	if [ ! -d /sys/class/gpio/gpio64 ] ; then
	    echo -n "64" > /sys/class/gpio/export
	fi
	echo -n "1" > /sys/class/gpio/gpio64/value
	
	
	#	IO4		OUT	Decoder Enable
	if [ ! -d /sys/class/gpio/gpio6 ] ; then
	    echo -n "6" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio6/direction
	chgrp projeto /sys/class/gpio/gpio6/value
	chmod g+rw /sys/class/gpio/gpio6/value
	
	if [ ! -d /sys/class/gpio/gpio36 ] ; then
	    echo -n "36" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio36/direction
	echo -n "0" > /sys/class/gpio/gpio36/value
	
	
	#	IO5		IN	Limit Switch 0
	if [ ! -d /sys/class/gpio/gpio0 ] ; then
	    echo -n "0" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio0/direction
	chgrp projeto /sys/class/gpio/gpio0/value
	chmod g+rw /sys/class/gpio/gpio0/value
	
	if [ ! -d /sys/class/gpio/gpio18 ] ; then
	    echo -n "18" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio18/direction
	echo -n "1" > /sys/class/gpio/gpio18/value
	
	if [ ! -d /sys/class/gpio/gpio66 ] ; then
	    echo -n "66" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio66/direction
	echo -n "0" > /sys/class/gpio/gpio66/value
	
	
	#	IO6		IN	Limit Switch 1
	if [ ! -d /sys/class/gpio/gpio1 ] ; then
	    echo -n "1" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio1/direction
	chgrp projeto /sys/class/gpio/gpio1/value
	chmod g+rw /sys/class/gpio/gpio1/value
	
	if [ ! -d /sys/class/gpio/gpio20 ] ; then
	    echo -n "20" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio20/direction
	echo -n "1" > /sys/class/gpio/gpio20/value
	
	if [ ! -d /sys/class/gpio/gpio68 ] ; then
	    echo -n "68" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio68/direction
	echo -n "0" > /sys/class/gpio/gpio68/value
	
	
	#	IO10	OUT	Decoder SS
	if [ ! -d /sys/class/gpio/gpio26 ] ; then
	    echo -n "26" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio26/direction
	echo -n "0" > /sys/class/gpio/gpio26/value
	
	if [ ! -d /sys/class/gpio/gpio27 ] ; then
	    echo -n "27" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio27/direction
	echo -n "1" > /sys/class/gpio/gpio27/value
	
	if [ ! -d /sys/class/gpio/gpio74 ] ; then
	    echo -n "74" > /sys/class/gpio/export
	fi
	echo -n "0" > /sys/class/gpio/gpio74/value
	
	
	#	IO11	OUT	SPI MOSI
	if [ ! -d /sys/class/gpio/gpio24 ] ; then
	    echo -n "24" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio24/direction
	echo -n "0" > /sys/class/gpio/gpio24/value
	
	if [ ! -d /sys/class/gpio/gpio25 ] ; then
	    echo -n "25" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio25/direction
	
	if [ ! -d /sys/class/gpio/gpio44 ] ; then
	    echo -n "44" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio44/direction
	echo -n "1" > /sys/class/gpio/gpio44/value
	
	if [ ! -d /sys/class/gpio/gpio72 ] ; then
	    echo -n "72" > /sys/class/gpio/export
	fi
	echo -n "0" > /sys/class/gpio/gpio72/value

	
	#	IO12	IN	SPI MISO
	if [ ! -d /sys/class/gpio/gpio42 ] ; then
	    echo -n "42" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio42/direction
	echo -n "1" > /sys/class/gpio/gpio42/value
	
	if [ ! -d /sys/class/gpio/gpio43 ] ; then
	    echo -n "43" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio43/direction

	
	#	IO13	OUT	SPI SCK
	if [ ! -d /sys/class/gpio/gpio30 ] ; then
	    echo -n "30" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio30/direction
	echo -n "0" > /sys/class/gpio/gpio30/value
	
	if [ ! -d /sys/class/gpio/gpio31 ] ; then
	    echo -n "31" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio31/direction
	echo -n "0" > /sys/class/gpio/gpio31/value
	
	if [ ! -d /sys/class/gpio/gpio46 ] ; then
	    echo -n "46" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio46/direction
	echo -n "1" > /sys/class/gpio/gpio46/value

    chgrp projeto /dev/spidev1.0
    chmod g+rw /dev/spidev1.0
    	
	
	;;
    stop)
	
	# IO2
    echo -n "13" > /sys/class/gpio/unexport
    echo -n "0" > /sys/class/gpio/gpio13/value
	echo -n "34" > /sys/class/gpio/unexport
	echo -n "77" > /sys/class/gpio/unexport
	
	# IO3
	echo -n "0" > /sys/class/pwm/pwmchip0/pwm1/enable
	echo -n "1" > /sys/class/pwm/pwmchip0/unexport
	echo -n "16" > /sys/class/gpio/unexport
	echo -n "17" > /sys/class/gpio/unexport
    echo -n "64" > /sys/class/gpio/unexport
    echo -n "76" > /sys/class/gpio/unexport
	
	# IO4
	echo -n "6" > /sys/class/gpio/unexport
    echo -n "0" > /sys/class/gpio/gpio6/value
	echo -n "36" > /sys/class/gpio/unexport
	
	# IO5
    echo -n "0" > /sys/class/gpio/unexport
	echo -n "18" > /sys/class/gpio/unexport
	echo -n "66" > /sys/class/gpio/unexport
	
	# IO6
    echo -n "1" > /sys/class/gpio/unexport
	echo -n "20" > /sys/class/gpio/unexport
	echo -n "68" > /sys/class/gpio/unexport
	
	# IO10
	echo -n "26" > /sys/class/gpio/unexport
	echo -n "27" > /sys/class/gpio/unexport
	echo -n "74" > /sys/class/gpio/unexport
	
	# IO11
	echo -n "24" > /sys/class/gpio/unexport
	echo -n "25" > /sys/class/gpio/unexport
	echo -n "44" > /sys/class/gpio/unexport
	echo -n "72" > /sys/class/gpio/unexport
	
	# IO12
	echo -n "42" > /sys/class/gpio/unexport
	echo -n "43" > /sys/class/gpio/unexport

	# IO13
	echo -n "30" > /sys/class/gpio/unexport
	echo -n "31" > /sys/class/gpio/unexport
	echo -n "46" > /sys/class/gpio/unexport
	
	;;
    status)
    	ls -d /sys/class/gpio/gpio*
	;;
    *)
	echo -n "Usage: $0 " 
	echo "{start|stop|restart|force-reload|status}"
	exit 1
	;;
esac

exit 0