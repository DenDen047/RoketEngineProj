#ifndef GETCOMMAND_H
#define GETCOMMAND_H

#include <cstdlib>
#include "mbed.h"

class GetCtrlCommand {
private:
    Serial _serial;
    bool _check();
public:
    float valve_on;
    float wait_valve;
    float pulse_time;
    float wait_next;
    int repeat;
    GetCtrlCommand(PinName tx, PinName rx, int baud);
    ~GetCtrlCommand();
};

#endif