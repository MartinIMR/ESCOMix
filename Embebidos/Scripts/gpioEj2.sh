
#!/bin/bash 

sudo echo "17" > /sys/class/gpio/export 
sudo echo "out" > /sys/class/gpio/gpio17/direction

for i in 1 2 3 4 5
do
	sudo echo "1" > /sys/class/gpio/gpio17/value
	sleep 2
	sudo echo "0" > /sys/class/gpio/gpio17/value
	sleep 2
done   
sudo echo "17" > /sys/class/gpio/unexport 
exit 0
