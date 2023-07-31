#pragma once
#include <Arduino.h>

class BaseController
{
public:
    virtual void writeMicroseconds(int microseconds) = 0;
    virtual void init(byte pin, int minUs, int maxUs) = 0;
};