#pragma once
#include <ServoMotor.h>
#include "Point.h"
#include "JointInfo.h"

#define TIBIA_FOOT_DISTANCE 80.920
#define FEMUR_TIBIA_DISTANCE 42.815
#define LEG_BEND_DISTANCE 65.613
#define LEG_BEND_ANGLE 126.3

class Leg
{
private:
    ServoMotor *_CoxaJoint;
    ServoMotor *_FemurJoint;
    ServoMotor *_TibiaJoint;

    JointInfo _CoxaInfo;
    JointInfo _FemurInfo;
    JointInfo _TibiaInfo;

    bool _Left;

public:
    bool OnPosition;
    Leg(byte coxaPin, byte femurPin, byte tibiaPin, bool left);
    ~Leg();
    void SetDefaultPos(int coxaAngle, int femurAngle, int tibiaAngle);
    void DetermineServoAngles(Point point);
    void DetermineServoAngles(Point point, int coxaAngle);
    void ExecuteMovement();
};