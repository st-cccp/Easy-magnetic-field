#pragma once

#include "Vect_3d.h"

class Tensor;

class Tensor
{
private:
    Vect_3d elems[3];
public:
    Tensor();
    Vect_3d& operator[](int index);
    Vect_3d elem(int index) const;
    Tensor operator+(const Tensor& t);
    Tensor operator-(const Tensor& t);
    virtual Tensor operator-();
    Tensor operator*(double n) const;
    ~Tensor();
};

Tensor operator|(const Vect_3d& a, const Vect_3d& b);
Vect_3d dot(const Vect_3d& v, Tensor& t);
Vect_3d dot(Tensor& t, const Vect_3d& v);
ostream& operator<<(ostream& os, const Tensor& t);