#pragma once 

#include "Elec_Mag_Block.h"

#include <map>
using std::map;

class __CalculatePlace {
    protected:
    vector<Vect_3d> places;
    public:
    vector<Vect_3d>::iterator begin(){return places.begin();}
    vector<Vect_3d>::iterator end(){return places.end();}
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

bool operator< (const Vect_3d& a, const Vect_3d& b)
{
    if(norm_2(a) < norm_2(b))return true;
    if(norm_2(a) > norm_2(b))return false;
    if(a.elem(0) < b.elem(0))return true;
    if(a.elem(1) < b.elem(1))return true;
    return false;
}

class MagnetProb{
    Components* components;
    map<Vect_3d, Gause> field;
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
};

