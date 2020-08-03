#include "Vect_3ddir.h"

const double PI = 3.14159265358979323846;

Vect_3ddir::Vect_3ddir(double theta, double phi):Vect_3d(sin(theta)*sin(phi),sin(theta)*cos(phi),cos(theta)){}
Vect_3ddir::Vect_3ddir(const Vect_3d& v):Vect_3d(normalize(v)){}