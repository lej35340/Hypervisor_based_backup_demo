echo "starting hypervisor based backup"

gpioset pinctrl-bcm2711 5=0

jailhouse enable /etc/jailhouse/rpi4.cell

echo "hello world"
RESULT=$(gpioget pinctrl-bcm2711 23)

echo "start monitoring"
while [ $RESULT -eq 1 ]
do
        RESULT=$(gpioget pinctrl-bcm2711 23)
done

echo "Fault detected"
jailhouse cell create /etc/jailhouse/rpi-pwm-demo.cell
jailhouse cell load inmate-demo /usr/libexec/jailhouse/demos/software_pwm_locked.bin
jailhouse cell start inmate-demo
echo "Fault recovered"
