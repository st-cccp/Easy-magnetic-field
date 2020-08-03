#pragma once

#include "Vect_3d.h"
#include "Vect_3ddir.h"
#include "Tensor.h"

#define __SI__

template <typename T>
class Segment{
    protected:
    T value;
    Vect_3d _start, _length;
    public:
    Segment(T v):_start(),_length(),value(v){}
    Segment(T v, const Vect_3d& length, const Vect_3d& start):_start(start),_length(length),value(v){}
    inline Vect_3d& Start() { return _start; }
    inline Vect_3d& Length() { return _length; }
    inline Vect_3d Middle() { return _start + _length * (1/2);}
    inline T& Value() { return value; }
};

typedef double Ampere;

typedef Vect_3d Gause;

extern const double mu_0;
extern const double c_vacant;

const int plus3(int a, int b);

class CurrentSegment : public Segment<Ampere> {
    public:
    using Segment<Ampere>::Segment;
    Gause Magfield(Vect_3d r)
    {
        Vect_3d R = r - Middle();
        double RLen = norm_2(R);
        #ifdef __GAUSIAN__
        return (_length * R * value) * (1 / pow(RLen, 3));
        #endif
        #ifdef __SI__
        return (_length * R * value) * (mu_0 * 10000 / (4 * PI * pow(RLen, 3)));
        #endif
    }
    //实际的位置，因为电流绝对位置已有，假设电流段非常小
    Tensor MagGrad(Vect_3d r)
    {
        Tensor grad;
        Vect_3d R = r - Middle();
        double RLen = norm_2(R);
        #ifdef __GAUSIAN__
        grad = (R | Magfield(r)) * (-3 / pow(RLen, 2));
        for(int i = 0; i < 3; ++i)
        {
            grad[plus3(i, 1)][i] += - (value * _length[plus3(i, 2)]) / (pow(RLen, 3));
            grad[plus3(i, 2)][i] += (value * _length[plus3(i, 1)]) / (pow(RLen, 3));
        }
        #endif
        #ifdef __SI__
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                for(int k = 0; k < 3; ++k)
                {
                    for(int t = 0; t < 3; ++t)
                    {
                        grad[i][t] += (_length[j] * value * VectFunc::epsilon(j, k, t) * (3 * R[i] * R[k] - dot(R,R) * VectFunc::delta(i, k))) * (mu_0 * 10000 / (4 * PI * pow(RLen, 5)));
                    }
                }
            }
        }
        #endif
        return grad;
    }
};

