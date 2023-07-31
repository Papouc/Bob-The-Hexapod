#include "PIO_Controller.h"

PIO_Controller::~PIO_Controller()
{
    delete _innerServo;
}

void PIO_Controller::init(byte pin, int minUs, int maxUs)
{
    _innerServo = new Servo();
    (*_innerServo).attach(pin, minUs, maxUs);
}

void PIO_Controller::writeMicroseconds(int microseconds)
{
    (*_innerServo).writeMicroseconds(microseconds);
}
