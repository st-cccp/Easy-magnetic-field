#include "MagnetProb.h"

bool operator< (const Vect_3d& a, const Vect_3d& b)
{
    // if(norm_2(a) < norm_2(b))return true;
    // if(norm_2(a) > norm_2(b))return false;
    if(a.elem(0) < b.elem(0))return true;
    if(a.elem(0) > b.elem(0))return false;
    if(a.elem(1) < b.elem(1))return true;
    if(a.elem(1) > b.elem(1))return false;
    if(a.elem(2) < b.elem(2))return true;
    return false;
}

