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
        _serial.printf("\n[ValveOn, WaitValve, PulseTime, WaitNext]\n");
        while(1) {
            if (!_serial.readable()) continue;
            c = _serial.getc();

            if (c == ',' || c=='\n') {
                switch (comma_cnt++) {
                    case 0:
                        valve_on = atof(str);
                        break;
                    case 1:
                        wait_valve = atof(str);
                        break;
                    case 2:
                        pulse_time = atof(str);
                        break;
                    case 3:
                        wait_next = atof(str);
                        break;
                    default:
                        break;
                }
                if (comma_cnt < 4) {
                    for (i = 0; i < strlen; i++) str[i] = ' ';
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
    _serial.printf("\n[%f %f %f %f] -> ok? [y/n]\n",
        valve_on,
        wait_valve,
        pulse_time,
        wait_next
    );
    char c;
    while(1) {
        if (!_serial.readable()) continue;

        c = _serial.getc();
        if (c == 'y') {
            return true;
        }
        else if (c == 'n') {
            return false;
        }
        else {}
    }
}

GetCtrlCommand::~GetCtrlCommand() {
    ;
}
