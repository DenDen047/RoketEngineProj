#ifndef GETCOMMAND_H
#define GETCOMMAND_H

#include <cstdlib>
#include "mbed.h"

class GetCtrlCommand {
private:
    Serial _serial;
    bool _check();
public:
    int valve_on;
    int wait_valve;
    int pulse_time;
    int wait_next;
    int pulse_count;
    int repeat;
    GetCtrlCommand(PinName tx, PinName rx, int baud);
    ~GetCtrlCommand();
};

#endif