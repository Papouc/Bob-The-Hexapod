#pragma once
#include "StepCounter.h"

class StraightStepCounter : public StepCounter
{
public:
    StraightStepCounter();
    StepContainer GetStepInfo(int stepNumber) override;
      CounterType GetCounterType() override;
};