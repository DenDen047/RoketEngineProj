#include "mbed.h"
#include "command.h"

Serial pc(USBTX, USBRX);    // tx, rx
DigitalOut led(LED1);
DigitalOut fuel_valve(LED2);


int main() {
    // power on
    pc.baud(9600);
    pc.printf("Hello, Naoya!\n\n");

    while(1) {
        // wait command from computer
        led = 1;
        GetCtrlCommand command(USBTX, USBRX, 9600);
        pc.printf("\n%f %f %f %f\n",
            command.valve_on,
            command.wait_valve,
            command.pulse_time,
            command.wait_next
        );
        led = 0;

        // start pulse

        // end
    }
}
