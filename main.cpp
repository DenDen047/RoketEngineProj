#include "mbed.h"
#include "command.h"

Serial pc(USBTX, USBRX);    // tx, rx
DigitalOut spark(PA_9);
DigitalOut fuel_valve(PA_10);


int main() {
    // init
    int i = 0;
    fuel_valve = 0;
    spark = 0;
    // power on
    pc.baud(9600);
    pc.printf("Hello, Naoya!\n\n");

    while(1) {
        fuel_valve = 0;
        spark = 0;
        // wait command from computer
        GetCtrlCommand command(USBTX, USBRX, 9600);
        pc.printf("\n%d %d %d %d %d\n",
            command.valve_on,
            command.wait_valve,
            command.pulse_time,
            command.wait_next,
            command.pulse_count
        );

        // start pulse
        for (i=0; i<command.pulse_count; i++) {
            // value on
            fuel_valve = 1;
            wait_ms(command.valve_on);
            fuel_valve = 0;
            wait_ms(command.wait_valve);
            // spark!
            spark = 1;
            wait_ms(command.pulse_time);
            spark = 0;
            // wait
            wait_ms(command.wait_next);
        }

        // end
    }
}
