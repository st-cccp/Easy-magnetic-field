#pragma once

#include "Vect_3d.h"
#include <cmath>
using namespace std;

extern const double PI;

class Vect_3ddir : public Vect_3d {
    public:
    Vect_3ddir(double theta, double phi);
    Vect_3ddir(const Vect_3d& v);
};

