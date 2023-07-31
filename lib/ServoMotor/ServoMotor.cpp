#include <ServoMotor.h>
#include "Controllers/PWM_Controller.h"
#include "Controllers/PIO_Controller.h"

ServoMotor::ServoMotor(byte pin) : ServoMotor(pin, MIN_PULSE_WIDTH_DEFAULT, MAX_PULSE_WIDTH_DEFAULT)
{
}

ServoMotor::ServoMotor(byte pin, int minPulseWidth, int maxPulseWidth)
{
    _minPulseWidth = minPulseWidth;
    _maxPulseWidth = maxPulseWidth;

    if (_instanceNo < 8)
    {
        _controller = new PIO_Controller();
    }
    else
    {
        _controller = new PWM_Controller();
    }

    (*_controller).init(pin, _minPulseWidth, _maxPulseWidth);

    _instanceNo++;
}

ServoMotor::~ServoMotor()
{
    delete _controller;
    _instanceNo--;
}

void ServoMotor::write(byte angle)
{
    if (angle >= 0 && angle <= 180)
    {
        int microseconds = map(angle, 0, 180, _minPulseWidth, _maxPulseWidth);
        (*_controller).writeMicroseconds(microseconds);
    }
}

byte ServoMotor::_instanceNo = 0;