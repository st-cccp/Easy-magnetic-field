#pragma once

class Vect{
    protected:
    int dimension;
    public:
    Vect(int dim);
    virtual double& operator[](int dim) = 0;
    virtual double elem(int dim) const = 0;
    virtual ~Vect() = 0;
    friend double dot(const Vect& a,const Vect& b);
};

namespace VectFunc
{
    bool __inzerototwo(int a);
    bool __sametwo(int a,int b);
    bool delta(int a,int b);
    int epsilon(int a,int b,int c);
} // namespace VectFunc

