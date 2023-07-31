#pragma once
#include <Arduino.h>
#include "BaseController.h"

class PWM_Controller : public BaseController
{
private:
    unsigned const int PWM_PERIOD = 20000;
    unsigned int _pwm_slice_number;
    unsigned int _pwm_channel_number;

public:
    void writeMicroseconds(int microseconds) override;
    void init(byte pin, int minUs, int maxUs) override;
};