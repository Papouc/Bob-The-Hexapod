#pragma once
#include "StepCounter.h"

class RotationStepCounter : public StepCounter
{
public:
    RotationStepCounter();
    StepContainer GetStepInfo(int stepNumber) override;
    CounterType GetCounterType() override;
};

