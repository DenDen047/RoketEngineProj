#include "command.h"

GetCtrlCommand::GetCtrlCommand(
    PinName tx, PinName rx, int baud
) : _serial(tx, rx) {

    _serial.baud(baud);

    char c;
    int comma_cnt = 0;
    int i = 0;
    int strlen = 10;
    char str[strlen];

    do {
        _serial.printf(
            "\n[ValveOn, ValveOff, InjectorOn, InjectorOff, SparkOn, SparkOff, Repeat]\n");
        while(1) {
            if (!_serial.readable()) continue;
            c = _serial.getc();

            if (c==',' || c=='\n') {
                switch (comma_cnt++) {
                    case 0:
                        delay = atoi(str);
                        break;
                    case 1:
                        valve_on = atoi(str);
                        break;
                    case 2:
                        valve_off = atoi(str);
                        break;
                    case 3:
                        injector_on = atoi(str);
                        break;
                    case 4:
                        injector_off = atoi(str);
                        break;
                    case 5:
                        spark_on = atoi(str);
                        break;
                    case 6:
                        spark_off = atoi(str);
                        break;
                    case 7:
                        repeat = atoi(str);
                        break;
                    default:
                        break;
                }

                if (comma_cnt < 8) {
                    for (i=0; i<strlen; i++) str[i] = ' ';
                    i = 0;
                    continue;
                }
                else
                    break;
            }

            if ('0' <= c && c <= '9' || c == '.') {
                str[i++] = c;
            }
            else {
                continue;
            }
        }
    } while (!_check());
}

bool GetCtrlCommand::_check () {
    _serial.printf("\n[%ds  %d %d  %d %d  %d %d   %d] -> ok? [y/N]\n",
        delay,
        valve_on,
        valve_off,
        injector_on,
        injector_off,
        spark_on,
        spark_off,
        repeat
    );
    char c;
    while(1) {
        if (!_serial.readable()) continue;

        c = _serial.getc();
        if (c == 'y') {
            _serial.printf("\nGO!\n");
            return true;
        }
        else if (c == 'N') {
            return false;
        }
    }
}

GetCtrlCommand::~GetCtrlCommand() {
    ;
}
