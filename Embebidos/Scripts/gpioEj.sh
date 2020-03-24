
#!/bin/bash 

sudo echo "17" > /sys/class/gpio/export 
sudo echo "out" > /sys/class/gpio/gpio17/direction
sudo echo "1" > /sys/class/gpio/gpio17/value
sleep 2
sudo echo "0" > /sys/class/gpio/gpio17/value
sudo echo "17" > /sys/class/gpio/unexport 
exit 0
