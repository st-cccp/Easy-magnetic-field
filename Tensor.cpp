#include "Tensor.h"

Tensor::Tensor(){}

Vect_3d& Tensor::operator[](int index)
    {
        assert(index >= 0 && index < 3);
        return elems[index];
    }

Vect_3d Tensor::elem(int index) const
    {
        assert(index >= 0 && index < 3);
        return elems[index];
    }

Tensor Tensor::operator+(const Tensor& t)
    {
        Tensor ans;
        for(int i = 0; i < 3; ++i)
        {
            ans[i] = elems[i] + t.elem(i);
        }
        return ans;
    }

Tensor Tensor::operator-(const Tensor& t)
    {
        Tensor ans;
        for(int i = 0; i < 3; ++i)
        {
            ans[i] = elems[i] - t.elem(i);
        }
        return ans;
    }

Tensor Tensor::operator-()
    {
        Tensor ans;
        for(int i = 0; i < 3; ++i)
        {
            ans[i] = -elems[i];
        }
        return ans;
    }

Tensor Tensor::operator*(double n) const
    {
        Tensor ans;
        for(int i = 0; i < 3; ++i)
        {
            ans[i] = elems[i] * n;
        }
        return ans;
    }

Tensor::~Tensor(){}

Tensor operator|(const Vect_3d& a, const Vect_3d& b)
{
    Tensor result;
    for(int i = 0; i < 3; ++i)
    {
        result[i] = b * a.elem(i);
    }
    return result;
}

Vect_3d dot(const Vect_3d& v, Tensor& t)
{
    Vect_3d ans;
    for(int i = 0; i < 3; ++i)
    {
        ans = ans + t[i] * v.elem(i);
    }
    return ans;
}

Vect_3d dot(Tensor& t, const Vect_3d& v)
{
    Vect_3d ans;
    for(int i = 0; i < 3; ++i)
    {
        ans[i] = dot(t[i], v);
    }
    return ans;
}

ostream& operator<<(ostream& os, const Tensor& t)
{
    Tensor& tt = const_cast<Tensor&>(t);
    return os << "{ " << tt[0] << ",\n " << tt[1] << ",\n " << tt[2] << "}";
}
