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
    virtual void ChangeCurrent(Ampere curr){
        current = curr;
        for(auto& i : segments)
        {
            i.Value() = current;
        }
        components->ChangeCurrent(curr);
    }
    virtual Volt Voltage(double lambda)
    {
        Volt v = 0;
        for(auto i : segments)
        {
            v = v + i.Voltdiff(lambda);
        }
        return v;
    }
    virtual double Len()
    {
        double l = 0;
        for(auto i : segments)
        {
            l = l + norm_2(i.Length());
        }
        return l;
    }
};

class SocketComponents : public AddComponents{
    Vect_3d pos;
    vector<AddComponents*> inputs;
    public:
    SocketComponents(Vect_3d p):AddComponents(nullptr), pos(p){clear();}
    SocketComponents(Vect_3d p, Components* component):AddComponents(component), pos(p){}
    void insert(AddComponents* ins){
        inputs.push_back(ins);
    }
    AddComponents* back(){
        if(!inputs.empty())
            return inputs.back();
        else return nullptr;
    }
    void clear(){inputs.clear();}
    virtual Gause Magfield(Vect_3d r) override{
        Gause answer;
        for (auto input : inputs)
        {
            answer = answer + input->Magfield(r);
        }
        return answer;
    }
    virtual Tensor MagGrad(Vect_3d r) override{
        Tensor answer;
        for (auto input : inputs)
        {
            answer = answer + input->MagGrad(r);
        }
        return answer;
    }
    virtual Vect_3d Endpoint() override { return pos; }
    virtual void ChangeCurrent(Ampere curr) override {
        current = curr;
        for(auto input : inputs)
        {
            input->ChangeCurrent(curr);
        }
    }
    virtual Volt Voltage(double lambda) override
    {
        Volt v = 0;
        for(auto input : inputs)
        {
            v = v + input->Voltage(lambda);
        }
        return v;
    }
    virtual double Len() override
    {
        double l = 0;
        for(auto input : inputs)
        {
            l = l + input->Len();
        }
        return l;
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
    int layers;
    double thick;
    bool inward;
    Vect_3d endpoint;
    public:
    Solenoid(Components* component, Vect_3d cent, Vect_3d ax, double r, double step, double turn, int pieces = 360, Ampere curr = 1, CLOCKWISE clw = CW, int layer_num = 1, bool inward_bool = false, double thickness = 0):
    AddComponents(component),bottom_center(cent),axle(ax),radius(r),Step(step),turns(turn),
    piecesperturn(pieces),clock(clw),layers(layer_num),inward(inward_bool),thick(thickness){
        current = curr;
        Vect_3d end = components->Endpoint();
        for(int layer = 0; layer < layers; layer++)
        {
            double rad = radius + layer * pow(-1, inward) * thick;
            Vect_3d cent = bottom_center + (axle * step * turns) * (layer % 2);
            Vect_3ddir ax = axle * pow(-1, layer % 2);
            CLOCKWISE cloc = clock;
            if(layer % 2) cloc = CLOCKWISE(!cloc);
            Vect_3d Beginr = end - cent;
            Vect_3ddir Begindir(ax * Beginr * ax);
            segments.push_back(CurrentSegment(curr, Begindir * rad - Beginr, Beginr + cent));
            Beginr = Begindir * rad;
            Vect_3ddir torotate(ax * Beginr);
            if(cloc != CW)
                torotate = -torotate;
            Vect_3ddir lastdir = Begindir;
            for(int i = 0; i < floor(piecesperturn * turns); i++)
            {
                Vect_3ddir thisdir(Begindir * cos((i + 1) * 2 * PI / piecesperturn) + torotate * sin((i + 1) * 2 * PI / piecesperturn));
                segments.push_back(CurrentSegment(curr, Vect_3d((thisdir - lastdir) * rad + ax * (Step / piecesperturn)), cent + lastdir * rad + ax * (Step * i / piecesperturn)));
                lastdir = thisdir;
            }
            end = cent + lastdir * rad + ax * (Step * turns);//lastdir不是这个意思，包括endpoint需要改
        }
        endpoint = end;
    }
    virtual Vect_3d Endpoint() override
    {
        return endpoint;
    }
};


class __Solenoid: public AddComponents{
    protected:
    CLOCKWISE clock;//沿着轴向向前的方向看
    Vect_3d bottom_center;
    Vect_3ddir axle;
    double radius;
    double Step;
    double turns;
    int piecesperturn;
    Vect_3d endpoint;
    public:
    __Solenoid(Components* component, Vect_3d cent, Vect_3d ax, double r, double step, double turn, int pieces = 360, Ampere curr = 1, CLOCKWISE clw = CW):
    AddComponents(component),bottom_center(cent),axle(ax),radius(r),Step(step),turns(turn),
    piecesperturn(pieces),clock(clw){
        current = curr;
        Vect_3d Beginr = components->Endpoint() - bottom_center;
        Vect_3ddir Begindir(axle * Beginr * axle);
        segments.push_back(CurrentSegment(curr, Begindir * radius - Beginr, Beginr + bottom_center));
        Beginr = Begindir * radius;
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
        endpoint = bottom_center + lastdir * radius + axle * (Step * turns);
    }
    virtual Vect_3d Endpoint() override
    {
        return endpoint;
        /*
        Vect_3d Beginr = components->Endpoint() - bottom_center;
        Vect_3ddir Begindir(axle * Beginr * axle);
        Vect_3ddir torotate(axle * Begindir);
        if(clock != CW)
        torotate = -torotate;
        return bottom_center + (Begindir * radius * cos(turns * 2 * PI) + torotate * radius * sin(turns * 2 * PI)) + axle * (Step * turns);
        */
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
        Vect_3ddir Begindir(axle * Beginr * axle);
        segments.push_back(CurrentSegment(curr, Begindir * radius - Beginr, Beginr + bottom_center));
        Beginr = Begindir * radius;
        Vect_3ddir torotate(axle * Begindir);
        if(clock != CW)
        torotate = -torotate;
        Vect_3d lastr = Beginr;
        for(int i = 0; i < floor(piecesperturn * turns); i++)
        {
            Vect_3ddir thisdir(Begindir * cos((i + 1) * 2 * PI / piecesperturn) + torotate * sin((i + 1) * 2 * PI / piecesperturn));
            Vect_3d thisr = thisdir * (radius - Step * (i + 1) / piecesperturn);
            segments.push_back(CurrentSegment(curr, thisr - lastr, lastr + bottom_center));
            lastr = thisr;
        }
    }
    virtual Vect_3d Endpoint() override
    {
        Vect_3d Beginr = components->Endpoint() - bottom_center;
        Vect_3ddir Begindir(axle * Beginr * axle);
        Vect_3ddir torotate(axle * Begindir);
        if(clock != CW)
        torotate = -torotate;
        return bottom_center + (Begindir * cos(turns * 2 * PI) + torotate * sin(turns * 2 * PI)) * (radius - Step * turns);
    }
};

class StraightWire: public AddComponents{
    protected:
    Vect_3d Beginr;
    Vect_3d Endr;
    int pieces;
    public:
    StraightWire(Components* component, Vect_3d end, Ampere curr = 1, int piece = 100):
    AddComponents(component),Beginr(component->Endpoint()),Endr(end),pieces(piece)
    {
        current = curr;
        for(int i = 0; i < pieces; i++)
        {
            segments.push_back(CurrentSegment(current, (Endr - Beginr) * (1.0 / pieces), Beginr + (Endr - Beginr) * (i * 1.0 / pieces)));
        }
        cout << this->AddMagfield(Vect_3d()) << endl;
    }
    virtual Vect_3d Endpoint() override
    {
        return Endr;
    }
};

class Solenoid_Square: public SocketComponents{
    protected:
    CLOCKWISE clock;//沿着轴向向前的方向看
    Vect_3d begin_corner;
    Vect_3ddir axle;
    Vect_3d xside;
    Vect_3d yside;
    double Step;
    double turns;
    int layers;
    int piecesperside;
    double thick;
    bool inward;
    Vect_3d endpoint;
    public:
    Solenoid_Square(Components* component, Vect_3d xs, Vect_3d ys, Vect_3d ax, double step, double turn, int pieces = 360, Ampere curr = 1, int layer_num = 1, bool inward_bool = false, double thickness = 0):
    SocketComponents(Vect_3d()),begin_corner(component->Endpoint()),xside(xs),yside(ys),axle(ax),Step(step),turns(turn),piecesperside(pieces),
    layers(layer_num),inward(inward_bool),thick(thickness){
        current = curr;
        Vect_3d end = begin_corner;
        int hdirsign = 1;
        for(int layer = 0; layer < layers; layer++)
        {
            for(int i = 0; i < turns; i++)
            {
                if(back()!=nullptr)
                    {insert(new StraightWire(back(), end + xside + axle * (step * 1/4 * hdirsign), current, piecesperside));end = end + xside + axle * (step * 1/4 * hdirsign);}
                else {insert(new StraightWire(component, end + xside + axle * (step * 1/4 * hdirsign), current, piecesperside));end = end + xside + axle * (step * 1/4 * hdirsign);}
                insert(new StraightWire(back(), end + yside + axle * (step * 1/4 * hdirsign), current, piecesperside));end = end + yside + axle * (step * 1/4 * hdirsign);
                insert(new StraightWire(back(), end - xside + axle * (step * 1/4 * hdirsign), current, piecesperside));end = end - xside + axle * (step * 1/4 * hdirsign);
                insert(new StraightWire(back(), end - yside + axle * (step * 1/4 * hdirsign), current, piecesperside));end = end - yside + axle * (step * 1/4 * hdirsign);
            }
            hdirsign *= -1;
            if(inward){
                end = end + Vect_3ddir(xside) * thick + Vect_3ddir(yside) * thick;
                xside = xside - Vect_3ddir(xside) * thick * 2;
                yside = yside - Vect_3ddir(yside) * thick * 2;
            }
            else{
                end = end - Vect_3ddir(xside) * thick - Vect_3ddir(yside) * thick;
                xside = xside + Vect_3ddir(xside) * thick * 2;
                yside = yside + Vect_3ddir(yside) * thick * 2;
            }
            //修改end的位置，和边长
        }
        endpoint = back()->Endpoint();
    }
    virtual Vect_3d Endpoint() override
    {
        return endpoint;
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


//以下为双向元件
class StraightCable {
    Components* componentsforward;
    Components* componentsbackward;
    Vect_3d vec_begin, vec_end;
    Vect_3d lean;
    StraightWire* wire_forward;
    StraightWire* wire_backward;
    public:
    StraightCable(Components* component, Vect_3d end):componentsforward(component), vec_begin(component->Endpoint()), vec_end(end), componentsbackward(nullptr){
        wire_forward = new StraightWire(componentsforward, vec_end);
    }
    void SetBackward(Components* component)
    {
        if(componentsbackward == nullptr)
        {
            componentsbackward = component;
        }
        else
        {
        }
    }
};
