# A hypervisor based fault tolerant strategy for heterogeneous real-time systems

This project targets on a fault recovery approach for heterogenous real-time critical systems in the automotive area using hypervisor techniques.
The demonstrator shows how bare-metal software running on a microcontroller board can be backed up by a microprocessor based board.
For more information concerning the theorethical background, please read the documentation in the Docs directory.                                                    

## Raspberry Pi and Arduino Demonstrator
For easy reconstruction of the demonstrator setup, the two most popular "playground-boards" were used: the Raspberry Pi 4 and the Arduino UNO.
The microcontroller based Arduino UNO provides a PWM-Signal, which should be backed up with the microprocessor based Raspberry Pi 4.


## General Setup:



## ARDUINO UNO
Download Arduino studio and open the Project located at: <link>
It is a very simple programm which simply toggles the digital pin 13 (and an LED) using a software pwm.


## RASPBERRY PI 4
I: create a RPI 4 Image capable of running jailhouse:

Unfortunately, the jailhouse setup for the raspberry pi 4 is not quite straight forward. (This is due to the fact of missing upstream support for the Raspberry Pi)
The easiest way to get Jailhouse running on your Raspberry Pi is to use the predefined minimalistic image from:
https://github.com/siemens/jailhouse-images

Afterwards, you can install the image on your RPI (flash it to the sd-card), start it up and do your first tests with Jailhouse.
User: root, pw: root
You will see some example commands after login.

If you want to be able to toggle some pins on your Raspberry pi as well, you need to install libgpiod. You can find the .deb packages in <link>. Copy them to your Raspberry Pi and install them with:
dpkg -i libgpiod2_1.6.2-1_arm64.deb
dpkg -i gpiod_1.6.3-1+b2_arm64.deb

Afterwards you can set/clear the pin 5 with:
gpioset pinctrl-bcm2711 5=0

On boards with upstream support, you can use your favourite Linux version and build the jailhouse hypervisor by yourself. See:
https://github.com/siemens/jailhouse


II: create your own "inmate"

To build your own jailhouse inmate, please download the 
https://github.com/siemens/jailhouse
project.

Copy the -inmate- to -jh-inmate-
Copy the -demo- to -arm64-demo-

Generate the cell config and the jailhouse inmate using the command (in case you use another board with upstream Linux, just exchange the path to the Kernel dirs here):
make ARCH=arm64 CROSS_COMPILE=aarch-linux-gnu- KDIR=<path-to-Jailhouse-image-from-I>/build/tmp/work/jailhouse-demo-arm64/buildchroot-host/1.0-r0/rootfs/usr/src/linux-headers-5.10.31/

When you start this inmate, you should see a toggling PIN 23.

III: set up "enviroment"

-bash script
-install libgpio

