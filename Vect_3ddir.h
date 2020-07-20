#pragma once

#include "Vect_3d.h"
#include <cmath>
using namespace std;

const double PI = 3.14159265358979323846;

class Vect_3ddir : public Vect_3d {
    public:
    Vect_3ddir(double theta, double phi):Vect_3d(sin(theta)*sin(phi),sin(theta)*cos(phi),cos(theta)){}
    Vect_3ddir(const Vect_3d& v):Vect_3d(normalize(v)){}
};

