#pragma once

#include "Elec_Mag.h"
#include <vector>
using std::vector;

class Components{
    public:
    virtual Gause Magfield(Vect_3d r) = 0;
    virtual Tensor MagGrad(Vect_3d r) = 0;
    virtual Vect_3d Endpoint() = 0;
    virtual ~Components() = 0;
    virtual void ChangeCurrent(Ampere curr) = 0;
};

class BaseComponents:public Components{
    Vect_3d pos;
    public:
    BaseComponents(Vect_3d p):pos(p){}
    virtual Gause Magfield(Vect_3d r) override{ return Gause();}
    virtual Tensor MagGrad(Vect_3d r) override{ return Tensor();}
    virtual Vect_3d Endpoint() override { return pos; }
    virtual void ChangeCurrent(Ampere curr) override {}
};

class AddComponents: public Components{
    protected:
    Components* components;
    vector<CurrentSegment> segments;
    public:
    AddComponents(Components* component) : components(component){}
    virtual Gause AddMagfield(Vect_3d r)
    {
        Gause answer;
        for(auto i : segments)
        {
            answer = answer + i.Magfield(r);
        }
        return answer;
    }
    virtual Tensor AddMagGrad(Vect_3d r)
    {
        Tensor answer;
        for(auto i : segments)
        {
            answer = answer + i.MagGrad(r);
        }
        return answer;
    }
    virtual Gause Magfield(Vect_3d r) override{
        return components->Magfield(r) + AddMagfield(r);
    }
    virtual Tensor MagGrad(Vect_3d r) override{
        return components->MagGrad(r) + AddMagGrad(r);
    }
    Ampere current;
    void ChangeCurrent(Ampere curr){
        current = curr;
        for(auto& i : segments)
        {
            i.Value() = current;
        }
        components->ChangeCurrent(curr);
    }
};


//下面为具体的励磁元件
typedef enum {CW,CCW} CLOCKWISE;//顺时针/逆时针
class Solenoid: public AddComponents{
    protected:
    CLOCKWISE clock;//沿着轴向向前的方向看
    Vect_3d bottom_center;
    Vect_3ddir axle;
    double radius;
    double Step;
    double turns;
    int piecesperturn;
    public:
    Solenoid(Components* component, Vect_3d cent, Vect_3d ax, double r, double step, double turn, int pieces = 360, Ampere curr = 1, CLOCKWISE clw = CW):
    AddComponents(component),bottom_center(cent),axle(ax),radius(r),Step(step),turns(turn),
    piecesperturn(pieces),clock(clw){
        current = curr;
        Vect_3d Beginr = components->Endpoint() - bottom_center;
        Vect_3ddir Begindir(Beginr);
        Vect_3ddir torotate(axle * Beginr);
        if(clock != CW)
        torotate = -torotate;
        Vect_3ddir lastdir = Begindir;
        for(int i = 0; i < floor(piecesperturn * turns); i++)
        {
            Vect_3ddir thisdir(Begindir * cos((i + 1) * 2 * PI / piecesperturn) + torotate * sin((i + 1) * 2 * PI / piecesperturn));
            segments.push_back(CurrentSegment(curr, Vect_3d((thisdir - lastdir) * radius + axle * (Step / piecesperturn)), bottom_center + lastdir * radius + axle * (Step * i / piecesperturn)));
            lastdir = thisdir;
        }
    }
    virtual Vect_3d Endpoint() override
    {
        Vect_3d Beginr = components->Endpoint() - bottom_center;
        Vect_3ddir torotate(axle * Beginr);
        if(clock != CW)
        torotate = -torotate;
        return bottom_center + (Beginr * cos(turns * 2 * PI) + torotate * radius * sin(turns * 2 * PI)) + axle * (Step * turns);
    }
};

class Mosquito: public AddComponents{
    protected:
    CLOCKWISE clock;//沿着轴向向前的方向看
    Vect_3d bottom_center;
    Vect_3ddir axle;
    double radius;
    double Step;
    double turns;
    int piecesperturn;
    public:
    Mosquito(Components* component, Vect_3d cent, Vect_3d ax, double r, double step, double turn, int pieces = 360, Ampere curr = 1, CLOCKWISE clw = CW):
    AddComponents(component),bottom_center(cent),axle(ax),radius(r),Step(step),turns(turn),
    piecesperturn(pieces),clock(clw){
        current = curr;
        Vect_3d Beginr = components->Endpoint() - bottom_center;
        Vect_3ddir Begindir(Beginr);
        Vect_3ddir torotate(axle * Beginr);
        if(clock != CW)
        torotate = -torotate;
        Vect_3d lastr = Beginr;
        for(int i = 0; i < floor(piecesperturn * turns); i++)
        {
            Vect_3ddir thisdir(Begindir * cos((i + 1) * 2 * PI / piecesperturn) + torotate * sin((i + 1) * 2 * PI / piecesperturn));
            Vect_3d thisr = thisdir * (radius - Step * i / piecesperturn);
            segments.push_back(CurrentSegment(curr, thisr - lastr, lastr + bottom_center));
            lastr = thisr;
        }
    }
    virtual Vect_3d Endpoint() override 
    {
        Vect_3d Beginr = components->Endpoint() - bottom_center;
        Vect_3ddir torotate(axle * Beginr);
        if(clock != CW)
        torotate = -torotate;
        return bottom_center + (Vect_3ddir(Beginr) * cos(turns * 2 * PI) + torotate * sin(turns * 2 * PI)) * (radius - Step * turns);
    }
};

class StraightWire: public AddComponents{
    protected:
    Vect_3d Beginr;
    Vect_3d Endr;
    int pieces;
    public:
    StraightWire(Components* component, Vect_3d begin, Vect_3d end, Ampere curr = 1, int piece = 100):
    AddComponents(component),Beginr(begin),Endr(end),pieces(piece)
    {
        current = curr;
        for(int i = 0; i < pieces; i++)
        {
            segments.push_back(CurrentSegment(current, Beginr + (Endr - Beginr) * (1 / pieces), Beginr + (Endr - Beginr) * (i / pieces)));
        }
    }
    virtual Vect_3d Endpoint() override 
    {
        return Endr;
    }
};

class Pass: public AddComponents{
    protected:
    Vect_3d Beginr;
    Vect_3d Endr;
    int pieces;
    public:
    Ampere current;
    Pass(Components* component, Vect_3d end):
    AddComponents(component),Beginr(component->Endpoint()),Endr(end){}
    virtual Vect_3d Endpoint() override 
    {
        return Endr;
    }
};
