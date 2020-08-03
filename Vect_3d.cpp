#include "Vect_3d.h"

Vect_3d::Vect_3d():Vect(3)
{
    data[0] = 0; data[1] = 0; data[2] = 0;
}

Vect_3d::Vect_3d(double x, double y, double z):Vect(3){
    data[0] = x; data[1] = y; data[2] = z;
}

double& Vect_3d::operator[](int dim)
    {
        assert(dim >= 0 && dim < dimension);
        return data[dim];
    }
double Vect_3d::elem(int dim) const
{
    assert(dim >= 0 && dim < dimension);
    return data[dim];
}
    Vect_3d Vect_3d::operator+(const Vect_3d& v)
    {
        Vect_3d ans;
        for(int i = 0; i < dimension; ++i)
        {
            ans[i] = data[i] + v.elem(i);
        }
        return ans;
    }
    Vect_3d Vect_3d::operator-(const Vect_3d& v)
    {
        Vect_3d ans;
        for(int i = 0; i < dimension; ++i)
        {
            ans[i] = data[i] - v.elem(i);
        }
        return ans;
    }
    Vect_3d Vect_3d::operator-()
    {
        Vect_3d ans;
        for(int i = 0; i < dimension; ++i)
        {
            ans[i] = -data[i];
        }
        return ans;
    }
    Vect_3d Vect_3d::operator*(double n) const
    {
        Vect_3d ans;
        for(int i = 0; i < dimension; ++i)
        {
            ans[i] = n * data[i];
        }
        return ans;
    }
    Vect_3d Vect_3d::operator*(const Vect_3d& v)
    {
        Vect_3d ans;
        for(int i = 0; i < dimension; ++i)
        {
            for(int j = 0; j < dimension; ++j)
            {
                for(int k = 0; k < dimension; ++k)
                {
                    ans[k] += data[i] * v.elem(j) * VectFunc::epsilon(i,j,k);
                }
            }
        }
        return ans;
    }

double dot(const Vect& a,const Vect& b)
{
    double ans = 0;
    assert(a.dimension == b.dimension);
    for(int i = 0; i < a.dimension; ++i)
    {
        ans += a.elem(i)*b.elem(i);
    }
    return ans;
}

double angle(const Vect_3d& a,const Vect_3d& b)
{
    return acos(dot(a,b) / (norm_2(a) * norm_2(b)));
}

double norm_2(const Vect_3d& v)
{
    return sqrt(v.elem(0) * v.elem(0) + v.elem(1) * v.elem(1) + v.elem(2) * v.elem(2));
}

Vect_3d normalize(const Vect_3d& v)
{
    return v * (1 / norm_2(v));
}

ostream& operator<<(ostream& os, const Vect_3d& v)
{
    return os << "{ " << "  " << setw(10) << v.elem(0) << "  " << setw(8) << v.elem(1) << "  " << setw(8) << v.elem(2) << "}";
}
