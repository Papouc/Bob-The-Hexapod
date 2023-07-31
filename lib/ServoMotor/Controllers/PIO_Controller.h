#pragma once
#include <Arduino.h>
#include "BaseController.h"
#include <Servo.h>

class PIO_Controller : public BaseController
{
private:
    Servo *_innerServo;

public:
    ~PIO_Controller();
    void writeMicroseconds(int microseconds) override;
    void init(byte pin, int minUs, int maxUs) override;
};