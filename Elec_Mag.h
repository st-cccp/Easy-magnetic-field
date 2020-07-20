#pragma once

#include "Vect_3d.h"
#include "Vect_3ddir.h"

template <typename T>
class Segment{
    protected:
    T value;
    Vect_3d _start, _length;
    public:
    Segment(T v):_start(),_length(),value(v){}
    Segment(T v, const Vect_3d& length, const Vect_3d& start = Vect_3d()):_start(start),_length(length),value(v){}
    Vect_3d& Start() { return _start; }
    Vect_3d& Length() { return _length; }
    Vect_3d Middle() { return _start + _length * (1/2);}
    T& Value() { return value; }
};

typedef double Ampere;

typedef Vect_3d Gause;

const double mu_0 = 1;
const double c_vacant = 29979245800;

class CurrentSegment : public Segment<Ampere> {
    public:
    using Segment<Ampere>::Segment;
    Gause Magfield(Vect_3d r)
    {
        Vect_3d R = r - Middle();
        double RLen = norm_2(R);
        return (_length * R * value) * (1 / (RLen * RLen * RLen));
    }
    //实际的位置，因为电流绝对位置已有，假设电流段非常小
};

