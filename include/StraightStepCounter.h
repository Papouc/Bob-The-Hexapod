#pragma once
#include "StepCounter.h"

class StraightStepCounter : public StepCounter
{
private:

public:
    StraightStepCounter();
    
    StepContainer GetStepInfo(int stepNumber) override;
};