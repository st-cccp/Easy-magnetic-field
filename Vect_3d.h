#pragma once

#include <assert.h>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#include "Vect.h"

class Vect_3d:public Vect{
    double data[3];
    public:
    Vect_3d();
    Vect_3d(double x, double y, double z);
    virtual double& operator[](int dim) override;
    virtual double elem(int dim) const override; 
    Vect_3d operator+(const Vect_3d& v);
    Vect_3d operator-(const Vect_3d& v);
    virtual Vect_3d operator-();
    Vect_3d operator*(double n) const;
    Vect_3d operator*(const Vect_3d& v);
};

double dot(const Vect& a,const Vect& b);
double angle(const Vect_3d& a,const Vect_3d& b);
double norm_2(const Vect_3d& v);
Vect_3d normalize(const Vect_3d& v);
ostream& operator<<(ostream& os, const Vect_3d& v);