#include "Body.h"
#include "PinLayout.h"

Body::Body()
{
    _Legs.reserve(NUMBER_OF_LEGS);

    _Legs.push_back(new Leg(LEG_1_COXA_PIN, LEG_1_FEMUR_PIN, LEG_1_TIBIA_PIN, true));
    _Legs.push_back(new Leg(LEG_2_COXA_PIN, LEG_2_FEMUR_PIN, LEG_2_TIBIA_PIN, true));
    _Legs.push_back(new Leg(LEG_3_COXA_PIN, LEG_3_FEMUR_PIN, LEG_3_TIBIA_PIN, true));
    _Legs.push_back(new Leg(LEG_4_COXA_PIN, LEG_4_FEMUR_PIN, LEG_4_TIBIA_PIN, false));
    _Legs.push_back(new Leg(LEG_5_COXA_PIN, LEG_5_FEMUR_PIN, LEG_5_TIBIA_PIN, false));
    _Legs.push_back(new Leg(LEG_6_COXA_PIN, LEG_6_FEMUR_PIN, LEG_6_TIBIA_PIN, false));
}

void Body::ReachInitialPosition()
{
    _Legs.at(0)->SetDefaultPos(94, 96, 90);
    _Legs.at(1)->SetDefaultPos(90, 93, 90);
    _Legs.at(2)->SetDefaultPos(89, 89, 98);
    _Legs.at(3)->SetDefaultPos(90, 98, 90);
    _Legs.at(4)->SetDefaultPos(90, 102, 79);
    _Legs.at(5)->SetDefaultPos(90, 104, 92);

    _OnPosition = true;
}

void Body::SetStancePosition()
{
    Point stancePoint = Point(50, 60);

    for (Leg *leg : _Legs)
    {
        leg->DetermineServoAngles(stancePoint);
    }
}

void Body::StandUp()
{
    for (Leg *leg : _Legs)
    {
        if (!leg->OnPosition)
        {
            leg->ExecuteMovement();
        }
    }
}