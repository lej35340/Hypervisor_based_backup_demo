# A hypervisor based fault tolerant strategy for heterogeneous real-time systems

This project targets on a fault recovery approach for heterogenous real-time critical systems in the automotive area using hypervisor techniques.
The demonstrator shows how bare-metal software running on a microcontroller board can be backed up by a microprocessor based board.
For more information concerning the theorethical background, please read the documentation in the Docs directory.                                                    

## Raspberry Pi and Arduino Demonstrator
For easy reconstruction of the demonstrator setup, the two most popular "playground-boards" were used: the Raspberry Pi 4 and the Arduino UNO.
The microcontroller based Arduino UNO provides a PWM-Signal, which should be backed up with the microprocessor based Raspberry Pi 4.
Therefore, the microprocess (Raspberry Pi) monitors the microcontroller (the VCC of the Arduino UNO). In case of a fault (a missing VCC), the microprocessor system is partitioned by the jailhouse hypervisor and a bare metal task recovering the PWM Signal is loaded in the newly created partition.

## General Setup:

![Alt text](https://github.com/lej35340/Hypervisor_based_backup_demo/blob/main/Documentation/Experimental_Setup_Scheme.png)

## ARDUINO UNO
Download Arduino studio and open the Project located at: [Arduino/PWM_of_50khz](Arduino) <br>
It is a simple programm which toggles the digital PIN 13 (and an LED) using a software PWM. You can connect this Pin with an oscilloscope as shown in the above picture.


## RASPBERRY PI 4
### 1: create a RPI 4 Image capable of running jailhouse:

Unfortunately, the jailhouse setup for the raspberry pi 4 is not quite straight forward. (This is due to the fact of missing upstream support for the Raspberry Pi) <br>
The easiest way to get Jailhouse running on your Raspberry Pi is to use the predefined minimalistic image from:
https://github.com/siemens/jailhouse-images

Afterwards, you can install the image on your RPI (flash it to the sd-card), start it up and do your first tests with Jailhouse.
User: root, pw: root
You will see some example commands after login.

If you want to be able to toggle some pins on your Raspberry pi as well, you need to install libgpiod. You can find the .deb packages in RPI/Debian_Packages. Copy them to your Raspberry Pi and install them with: <br>
dpkg -i libgpiod2_1.6.2-1_arm64.deb <br>
dpkg -i gpiod_1.6.3-1+b2_arm64.deb

Afterwards you can set/clear the pin 5 with: <br>
gpioset pinctrl-bcm2711 5=0

On boards with upstream support, you can use your favourite Linux version and build the jailhouse hypervisor by yourself. See:
https://github.com/siemens/jailhouse


### 2: create your own "inmate"

To build your own jailhouse inmate, please download the 
https://github.com/siemens/jailhouse
project.

Copy the [Inmate](RPI/Jailhouse_inmate/running_pwm.c) to <jailhouse_install_dir>/inmates/demos/arm/ <br>
Copy the [cell_config](RPI/Jailhouse_inmate/rpi-inmate-demo.c) to <jailhouse_install_dir>/configs/arm64/ <br>

Generate the cell config and the jailhouse inmate using the command:
make ARCH=arm64 CROSS_COMPILE=aarch-linux-gnu- KDIR=<path-to-Jailhouse-image-from-I>/build/tmp/work/jailhouse-demo-arm64/buildchroot-host/1.0-r0/rootfs/usr/src/linux-headers-5.10.31/ <br>
(In case you use another board with upstream Linux, just exchange the path to the Kernel dirs here)

After successfull build, you will find the files <jailhouse_install_dir>/configs/arm64/rpi-inmate-demo.cell and <jailhouse_install_dir>/inmates/demos/arm64/running_pwm.bin
When you start this inmate, you should see a toggling PIN 23.

### 3: set up the monitoring of the Arduino Board
The Raspberry Pi monitors the VCC of the Arduino Board. Therefore, VCC (3.3V) from ARDUINO UNO and Pin 5 from Raspberry Pi are connected with each other like shown in the picture. On the Raspberry Pi side, the monitoring is done with a [bash script](RPI/Bash/Hypervisor_based_Backup.sh)
<br>
Adapt the paths to your cell config and your binary(line 17 and 18).
Copy the script to your target (Raspberry Pi) and make it exeuctable (chmod +X).
Afterwards, the script will monitor Pin 5 of the Raspberry Pi (to which the VCC of ARDUINO UNO is connected) and will initiate the backup strategy in case of a voltage drop.
