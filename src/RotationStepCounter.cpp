#include "RotationStepCounter.h"

RotationStepCounter::RotationStepCounter()
{
    _ForwardPoint = Point(45, 45);
    _StancePoint = Point(50, 60);
    _ForwardStancePoint = Point(_ForwardPoint.X, _StancePoint.Z);
}

StepContainer RotationStepCounter::GetStepInfo(int stepNumber)
{
    StepContainer result = StepContainer();

    if (stepNumber % 3 == 0)
    {
        result.EvenMoveTo = _ForwardPoint;
        result.OddMoveTo = _StancePoint;
        result.EvenRotation = 15;
        result.OddRotation = -15;
    }
    else if (stepNumber % 3 == 1)
    {
        result.EvenMoveTo = _ForwardStancePoint;
        result.OddMoveTo = _ForwardStancePoint;
        result.EvenRotation = 15;
        result.OddRotation = -15;
    }
    else if (stepNumber % 3 == 2)
    {
        result.EvenMoveTo = _StancePoint;
        result.OddMoveTo = _StancePoint;
        result.EvenRotation = 0;
        result.OddRotation = 0;
    }

    return result;
}