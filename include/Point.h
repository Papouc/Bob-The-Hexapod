#pragma once

struct Point
{
    double X;
    double Z;

    Point(double x, double z) : X(x), Z(z) {}
    Point() : X(0), Z(0) {}
};