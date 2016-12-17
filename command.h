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
    int valve_off;
    int injector_on;
    int injector_off;
    int spark_on;
    int spark_off;
    int repeat;
    GetCtrlCommand(PinName tx, PinName rx, int baud);
    ~GetCtrlCommand();
};

#endif
