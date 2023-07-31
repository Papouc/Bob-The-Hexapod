#pragma once
#include <Arduino.h>
#include "Controllers/BaseController.h"

#define MIN_PULSE_WIDTH_DEFAULT 500
#define MAX_PULSE_WIDTH_DEFAULT 2450

class ServoMotor
{
private:
    static byte _instanceNo;
    BaseController* _controller;
    int _minPulseWidth;
    int _maxPulseWidth;

public:
    ServoMotor(byte pin);
    ServoMotor(byte pin, int minPulseWidth, int maxPulseWidth);
    ~ServoMotor();
    void write(byte angle);
};
