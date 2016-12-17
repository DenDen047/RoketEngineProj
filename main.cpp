#include "mbed.h"
#include "command.h"

DigitalOut fuel_valve(PA_2);
DigitalOut injector(PA_12);
DigitalOut spark(PA_8);
DigitalOut led(LED1);


int main() {
    // init
    int i = 0;
    fuel_valve = 0;
    spark = 0;
    // power on
    led = 1;

    while(1) {
        fuel_valve = 0;
        spark = 0;
        // wait command from computer
        GetCtrlCommand command(D1, D0, 115200);
        // GetCtrlCommand command(USBTX, USBRX, 9600);

        // start pulse
        for (i=0; i<command.repeat; i++) {
            wait(command.delay);
            // valve on
            fuel_valve = 1;
            wait_ms(command.valve_on);
            fuel_valve = 0;
            wait_ms(command.valve_off);
            // injector on
            injector = 1;
            wait_ms(command.injector_on);
            injector = 0;
            wait_ms(command.injector_off);
            // spark!
            spark = 1;
            wait_ms(command.spark_on);
            spark = 0;
            wait_ms(command.spark_off);
        }

        // end
    }
}
