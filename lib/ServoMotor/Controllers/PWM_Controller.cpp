#include "PWM_Controller.h"
#include <pico/stdlib.h>
#include <hardware/pwm.h>

void PWM_Controller::init(byte pin, int minUs, int maxUs)
{
    _pwm_slice_number = pwm_gpio_to_slice_num(pin);
    _pwm_channel_number = pwm_gpio_to_channel(pin);

    unsigned long sys_clock_hz = clock_get_hz(clk_sys);
    unsigned long pwm_clock_hz = 1000000UL;

    float clock_divider = (float)(sys_clock_hz) / (float)(pwm_clock_hz);

    // set system clock to 1MHz
    pwm_set_clkdiv(_pwm_slice_number, clock_divider);

    // set system period to 20 ms
    pwm_set_wrap(_pwm_slice_number, PWM_PERIOD);

    // set initial output value to neutral position
    pwm_set_chan_level(_pwm_slice_number, _pwm_channel_number, (minUs + maxUs) / 2);

    // enable PWM
    pwm_set_enabled(_pwm_slice_number, true);

    // configure gpio for output
    gpio_set_function(pin, GPIO_FUNC_PWM);
}

void PWM_Controller::writeMicroseconds(int microseconds)
{
    pwm_set_chan_level(_pwm_slice_number, _pwm_channel_number, microseconds);
}