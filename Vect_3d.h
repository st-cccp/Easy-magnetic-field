#pragma once

#include <assert.h>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#include "Vect.h"

class Vect_3d:public Vect{
    //三维向量类
    double data[3];
    public:
    Vect_3d();
    Vect_3d(double x, double y, double z);
    virtual double& operator[](int dim) override;//取第dim个维度，从0开始，可编辑
    virtual double elem(int dim) const override; //取第dim个维度，从0开始，不可编辑

    //实现了加法，减法，取负，数乘，叉乘运算，可以直接以数学形式编写
    Vect_3d operator+(const Vect_3d& v);
    Vect_3d operator-(const Vect_3d& v);
    virtual Vect_3d operator-();
    Vect_3d operator*(double n) const;
    friend Vect_3d operator*(double n, Vect_3d& v);
    Vect_3d operator*(const Vect_3d& v);//叉乘运算，可直接用*号书写表达式
};

double dot(const Vect& a,const Vect& b);//点乘运算
double angle(const Vect_3d& a,const Vect_3d& b);//计算与z轴之间的夹角
double norm_2(const Vect_3d& v);//取模
Vect_3d normalize(const Vect_3d& v);//将向量归一化
ostream& operator<<(ostream& os, const Vect_3d& v);//输出