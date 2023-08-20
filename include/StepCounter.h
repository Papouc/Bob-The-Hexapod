#pragma once
#include "Point.h"
#include "StepContainer.h"
#include "CounterType.h"

class StepCounter
{
protected:
    Point _ForwardPoint;
    Point _StancePoint;
    Point _ForwardStancePoint;
    bool _Flipped{false};

public:
    virtual StepContainer GetStepInfo(int stepNumber) = 0;
    virtual CounterType GetCounterType() = 0;
    inline void Flip() { _Flipped = !_Flipped; }
    inline bool IsFlipped() { return _Flipped; }
};