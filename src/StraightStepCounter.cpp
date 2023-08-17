#include "StraightStepCounter.h"

StraightStepCounter::StraightStepCounter()
{
    _ForwardPoint = Point(45, 50);
    _StancePoint = Point(50, 60);
    _ForwardStancePoint = Point(_ForwardPoint.X, _StancePoint.Z);
}

StepContainer StraightStepCounter::GetStepInfo(int stepNumber)
{
    StepContainer result = StepContainer();

   if (stepNumber % 3 == 0)
    {
        if (_Flipped)
        {
            result.EvenMovetTo = _StancePoint;
            result.OddMoveTo = _ForwardPoint;
            result.EvenRotation = 0;
            result.OddRotation = 15;
        }
        else
        {
            result.EvenMovetTo = _ForwardPoint;
            result.OddMoveTo = _StancePoint;
            result.EvenRotation = 15;
            result.OddRotation = 0;
        }
    }
    else if (stepNumber % 3 == 1)
    {
        if (_Flipped)
        {
            result.EvenMovetTo = _StancePoint;
            result.OddMoveTo  = _ForwardStancePoint;
            result.EvenRotation = 0;
            result.OddRotation = 15;
        }
        else
        {
            result.EvenMovetTo = _ForwardStancePoint;
            result.OddMoveTo = _StancePoint;
            result.EvenRotation = 15;
            result.OddRotation = 0;
        }
    }
    else if (stepNumber % 3 == 2)
    {
        if (_Flipped)
        {
            result.EvenMovetTo = _StancePoint;
            result.OddMoveTo = _StancePoint;
            result.EvenRotation = -4;
            result.OddRotation = 0;
        }
        else
        {
            result.EvenMovetTo = _StancePoint;
            result.OddMoveTo = _StancePoint;
            result.EvenRotation = 0;
            result.OddRotation = -4;
        }
    }

    return result;
}