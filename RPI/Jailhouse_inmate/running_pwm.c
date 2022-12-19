/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) ARM Limited, 2014
 *
 * Authors:
 *  Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <inmate.h>

//JOLE: add blinking LED like : https://www.valvers.com/open-software/raspberry-pi/bare-metal-programming-in-c-part-1/

#define GPIO_BASE       0xFE200000UL

    /* The RPi4 model has the ACT LED attached to GPIO 42
       https://github.com/raspberrypi/linux/blob/rpi-4.19.y/arch/arm/boot/dts/bcm2838-rpi-4-b.dts */
    #define LED_GPFSEL      GPIO_GPFSEL4
    #define LED_GPFBIT      6
    #define LED_GPSET       GPIO_GPSET0
    #define LED_GPCLR       GPIO_GPCLR0
    #define LED_GPIO_BIT    5

	#define GPIO_GPFSEL0    0
#define GPIO_GPFSEL1    1
#define GPIO_GPFSEL2    2
#define GPIO_GPFSEL3    3
#define GPIO_GPFSEL4    4
#define GPIO_GPFSEL5    5

#define GPIO_GPSET0     7
#define GPIO_GPSET1     8

#define GPIO_GPCLR0     10
#define GPIO_GPCLR1     11

#define GPIO_GPLEV0     13
#define GPIO_GPLEV1     14

#define GPIO_GPEDS0     16
#define GPIO_GPEDS1     17

#define GPIO_GPREN0     19
#define GPIO_GPREN1     20

#define GPIO_GPFEN0     22
#define GPIO_GPFEN1     23

#define GPIO_GPHEN0     25
#define GPIO_GPHEN1     26

#define GPIO_GPLEN0     28
#define GPIO_GPLEN1     29

#define GPIO_GPAREN0    31
#define GPIO_GPAREN1    32

#define GPIO_GPAFEN0    34
#define GPIO_GPAFEN1    35

#define GPIO_GPPUD      37
#define GPIO_GPPUDCLK0  38
#define GPIO_GPPUDCLK1  39


/** GPIO Register set */
volatile unsigned int* gpio;

/** Simple loop variable */
volatile unsigned int tim;



void inmate_main(void)
{
	unsigned int i = 0;
    printk("starting: Backup RT-Task");
	/* Assign the address of the GPIO peripheral (Using ARM Physical Address) */
    gpio = (unsigned int*)GPIO_BASE;
    /* Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
       peripheral register to enable GPIO16 as an output */
    //gpio[LED_GPFSEL] |= (1 << LED_GPFBIT);

	/*
	 * The cell config can set up a mapping to access UARTx instead of UART0
	 */
	while(++i) {
        
        /* Set the LED GPIO pin low ( Turn OK LED on for original Pi, and off
           for plus models )*/
		for(tim = 0; tim < 213; tim++)
            gpio[LED_GPCLR] = (1 << LED_GPIO_BIT);

        
        
        /* Set the LED GPIO pin high ( Turn OK LED off for original Pi, and on
           for plus models )*/
        for(tim = 0; tim < 213; tim++)
            gpio[LED_GPSET] = (1 << LED_GPIO_BIT);


        

		//for (j = 0; j < 100000000; j++);
		//printk("JOLE Hello %d from cell! JOLE\n", i);
	}

	/* lr should be 0, so a return will go back to the reset vector */
}
