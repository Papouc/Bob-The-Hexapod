#include "Body.h"
#include "PinLayout.h"
#include "StraightStepCounter.h"
#include "RotationStepCounter.h"

Body::Body()
{
    _Legs.reserve(NUMBER_OF_LEGS);

    _Legs.push_back(new Leg(LEG_1_COXA_PIN, LEG_1_FEMUR_PIN, LEG_1_TIBIA_PIN, true));
    _Legs.push_back(new Leg(LEG_2_COXA_PIN, LEG_2_FEMUR_PIN, LEG_2_TIBIA_PIN, true));
    _Legs.push_back(new Leg(LEG_3_COXA_PIN, LEG_3_FEMUR_PIN, LEG_3_TIBIA_PIN, true));
    _Legs.push_back(new Leg(LEG_4_COXA_PIN, LEG_4_FEMUR_PIN, LEG_4_TIBIA_PIN, false));
    _Legs.push_back(new Leg(LEG_5_COXA_PIN, LEG_5_FEMUR_PIN, LEG_5_TIBIA_PIN, false));
    _Legs.push_back(new Leg(LEG_6_COXA_PIN, LEG_6_FEMUR_PIN, LEG_6_TIBIA_PIN, false));

    _StepCounter = new StraightStepCounter();
}

void Body::ReachInitialPosition()
{
    // fine tune those values to suit your specific build
    _Legs.at(0)->SetDefaultPos(56, 96, 92);
    _Legs.at(1)->SetDefaultPos(90, 93, 92);
    _Legs.at(2)->SetDefaultPos(102, 89, 100);
    _Legs.at(3)->SetDefaultPos(90, 98, 83);
    _Legs.at(4)->SetDefaultPos(90, 102, 75);
    _Legs.at(5)->SetDefaultPos(90, 104, 88);

    _OnPosition = true;
}

void Body::SetStancePosition()
{
    Point stancePoint = Point(50, 60);

    for (int i = 0; i < _Legs.size(); i++)
    {
        _Legs.at(i)->DetermineServoAngles(stancePoint, _StanceAngles[i]);
    }

    _OnPosition = false;
}

void Body::SetNextStepPosition(enum Direction direction)
{
    if (_StepCounter->GetCounterType() != CounterType::STRAIGHT)
    {
        delete _StepCounter;
        _StepCounter = new StraightStepCounter();
    }

    if (_StepNumber % 3 == 0)
    {
        _StepCounter->Flip();
    }

    StepContainer info = _StepCounter->GetStepInfo(_StepNumber);

    info.EvenRotation *= (direction == Direction::FORWARD) ? 1 : -1;
    info.OddRotation *= (direction == Direction::FORWARD) ? 1 : -1;

    for (int i = 0; i < _Legs.size(); i += 2)
    {
        _Legs.at(i)->DetermineServoAngles(info.EvenMoveTo, _StanceAngles[i] + info.EvenRotation);
    }

    for (int i = 1; i < _Legs.size(); i += 2)
    {
        _Legs.at(i)->DetermineServoAngles(info.OddMoveTo, _StanceAngles[i] + info.OddRotation);
    }

    _OnPosition = false;
    _StepNumber++;
}

void Body::SetNextTurnPosition(enum Rotation rotation)
{
    if (_StepCounter->GetCounterType() != CounterType::ROTATION)
    {
        delete _StepCounter;
        _StepCounter = new RotationStepCounter();
    }

    if (_StepNumber % 3 == 0)
    {
        _StepCounter->Flip();
    }

    StepContainer info = _StepCounter->GetStepInfo(_StepNumber);

    info.EvenRotation *= (rotation == Rotation::RIGHT) ? 1 : -1;
    info.OddRotation *= (rotation == Rotation::RIGHT) ? 1 : -1;

    if (_StepCounter->IsFlipped())
    {
        _Legs.at(0)->DetermineServoAngles(info.EvenMoveTo, _StanceAngles[0] + info.EvenRotation);
        _Legs.at(2)->DetermineServoAngles(info.EvenMoveTo, _StanceAngles[2] + info.EvenRotation);
        _Legs.at(4)->DetermineServoAngles(info.EvenMoveTo, _StanceAngles[4] + info.OddRotation);
    }
    else
    {
        _Legs.at(1)->DetermineServoAngles(info.EvenMoveTo, _StanceAngles[1] - info.OddRotation);
        _Legs.at(3)->DetermineServoAngles(info.EvenMoveTo, _StanceAngles[3] - info.EvenRotation);
        _Legs.at(5)->DetermineServoAngles(info.EvenMoveTo, _StanceAngles[5] - info.EvenRotation);
    }

    _OnPosition = false;
    _StepNumber++;
}

void Body::MoveToPosistion()
{
    bool onPos = true;

    for (Leg *leg : _Legs)
    {
        if (leg->OnPosition)
        {
            continue;
        }

        leg->ExecuteMovement();
        onPos = false;
    }

    _OnPosition = onPos;
}