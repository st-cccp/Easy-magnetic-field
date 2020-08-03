#include "Vect.h"

Vect::Vect(int dim):dimension(dim){}

Vect::~Vect(){}

namespace VectFunc
{

bool __inzerototwo(int a)
{
    if(a > 2 || a < 0)return false;
    return true;
}
bool __sametwo(int a,int b)
{
    return a == b;
}

bool delta(int a,int b)
{
    if(__sametwo(a,b))
    return true;
    else return false;
}

int epsilon(int a,int b,int c)
{
    if(__inzerototwo(a) && __inzerototwo(b) && __inzerototwo(c))
    {
        if(__sametwo(a,b)||__sametwo(b,c)||__sametwo(c,a))
        return false;
        else
        {
            if((b-a)*(c-b)*(a-c) > 0)
            return -1;
            else return 1;
        }//检查算法正确性
    }
    else return 0;
}

}