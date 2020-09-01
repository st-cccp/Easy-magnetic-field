#pragma once 

#include "Elec_Mag_Block.h"

#include <map>
using std::map;
#include <functional>
using std::function;

class __CalculatePlace {
    protected:
    vector<Vect_3d> places;
    public:
    vector<Vect_3d>::iterator begin(){return places.begin();}
    vector<Vect_3d>::iterator end(){return places.end();}
    auto size(){return places.size();}
};

class CubePlace : public __CalculatePlace {
    public:
    CubePlace(Vect_3d corner1, Vect_3d corner2, int PiecesPerLine = 10)
    {
        Vect_3d Delta = corner2 - corner1;
        double dx = Delta[0] / PiecesPerLine;
        double dy = Delta[1] / PiecesPerLine;
        double dz = Delta[2] / PiecesPerLine;
        for(int i = 1; i < PiecesPerLine; i++)
        {
            for(int j = 1; j < PiecesPerLine; j++)
            {
                for(int k = 1; k < PiecesPerLine; k++)
                {
                    places.push_back(Vect_3d(corner1[0] + i * dx, corner1[1] + j * dy, corner1[2] + k * dz));
                }
            }
        }
    }
};

class PlanePlace : public __CalculatePlace{
    public:
    PlanePlace(Vect_3d center, Vect_3d reladir1, Vect_3d reladir2, int PiecesPerLine = 100)
    {
        Vect_3d Delta1 = reladir1 - center;
        Vect_3d Delta2 = reladir2 - center;
        for(int i = 1; i < PiecesPerLine; i++)
        {
            for(int j = 1; j < PiecesPerLine; j++)
            {
                places.push_back(center - Delta1 - Delta2 + Delta1 * i * (2.0 / PiecesPerLine) + Delta2 * j * (2.0 / PiecesPerLine));
            }
        }
    }
};

class LinePlace : public __CalculatePlace {
    public:
    LinePlace(Vect_3d corner1, Vect_3d corner2, int PiecesOnLine = 100)
    {
        Vect_3d Delta = corner2 - corner1;
        for(int i = 1; i < PiecesOnLine; i++)
        {
            places.push_back(corner1 + Delta * i * (1.0 / PiecesOnLine));
        }
    }
};

class PointPlace : public __CalculatePlace {
    public:
    PointPlace(Vect_3d theplace)
    {
        places.push_back(theplace);
    }
};

bool operator< (const Vect_3d& a, const Vect_3d& b);

class MagnetProb{
    Components* components;
    map<Vect_3d, Gause> field;
    map<Vect_3d, Tensor> grad;
    public:
    void setComponent(Components* component){components = component;}
    const map<Vect_3d, Gause>& getField(__CalculatePlace& calc){
        field.clear();
        for(auto i : calc)
        {
            field[i] = components->Magfield(i);
        }
        return field;
    }
    const map<Vect_3d, Tensor>& getGrad(__CalculatePlace& calc){
        grad.clear();
        for(auto i : calc)
        {
            grad[i] = components->MagGrad(i);
        }
        return grad;
    }
    Vect_3d find(function<double(Gause)> f)
    {
        if(field.empty())
        return Vect_3d();
        else
        {
            bool begining = true;
            double min = 0.0;
            Vect_3d minplace;
            for(auto i : field)
            {
                if(begining)
                {
                    begining = false;
                    min = f(i.second);
                    minplace = i.first;
                }
                else
                {
                    if(f(i.second) < min)
                    {
                        min = f(i.second);
                        minplace = i.first;
                    }
                }
            }
            return minplace;
        }
        
    }
};

namespace FINDINGFUNC{

double fieldmin(Gause B);

double fieldmax(Gause B);

double Bzmin(Gause B);

double Bzmax(Gause B);

double Bangel2z(Gause B);

}
