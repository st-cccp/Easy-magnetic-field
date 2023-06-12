#include "Experiment.h"
#include <utility>
using namespace std;

#define __PIECESPERTURN 500
#define __INITCURRENT 1

static const double __solenoidxmove = 0;
static const double __solenoidymove = 0;
static const double __solenoidzmove = 0;
// static const double __solenoidxmove = 0.00e-5;
// static const double __solenoidymove = -3.38e-5;
static const double __mosquitoxmove = 0.5e-3;
static const double __mosquitoymove = 0;
// static const double __mosquitoxmoves = -3.5834e-3;
// static const double __mosquitoymove = 0;
static const double __errorxmove = -0;
static const double __errorymove = -0;
static const double __errorzmove = -0;
static const double __errortheta = 0;
// static const double __errorxmove = 1e-3;
// static const double __errorymove = 1e-3;
// static const double __errortheta = PI / 360;

AddComponents* Experiment(int type, double index)
{
    double RR = 0.060;
    double Rmin = 0.060;
    switch (type)
    {
        case 0:
        if(index)
            RR = index;
        break;
        case 1:
        if(index)
            Rmin = index;
        break;
        default:
        return nullptr;
    }
    double rr = 0.00325 / 2;
    // double rr = 0;
    double h = 0.066;
    
    BaseComponents* base1 = new BaseComponents(Vect_3d(RR + __solenoidxmove, __solenoidymove, __solenoidzmove + h + 2 * 15 * rr));//加
    //使用BaseCompnents类规定开始的位置
    Components* sole[9];
    sole[0] = base1;
    for(int i = 0; i < 1;i++)
    {
        sole[2 * i + 1] = new Solenoid(sole[2 * i], Vect_3d(__solenoidxmove, __solenoidymove, __solenoidzmove + h + 2 * 15 * rr), Vect_3d(0,0,-1), RR + (4 * i) * rr, 2 * rr, 15, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
        sole[2 * i + 2] = new Solenoid(sole[2 * i + 1], Vect_3d(__solenoidxmove, __solenoidymove, __solenoidzmove + h), Vect_3d(0,0,1), RR + (4 * i + 2) * rr, 2 * rr, 15, __PIECESPERTURN, __INITCURRENT);
        //需要加上pass的量，螺线管的
    }
    Solenoid* sole3 = new Solenoid(sole[2 * 1], Vect_3d(__solenoidxmove, __solenoidymove, __solenoidzmove + h + 2 * 15 * rr), Vect_3d(0,0,-1), RR + (4 * 1) * rr, 2 * rr, 15, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
    Components* upper1;
    upper1 = sole3;//7*6情况，注意修改
    Pass* passso1 = new Pass(upper1, Vect_3d(-RR + __errorxmove + __solenoidxmove, __solenoidymove + __errorymove, __solenoidzmove + __errorzmove -h - 2 * 15 * rr));
    Components* soledown[9];
    soledown[0] = passso1;
    for(int i = 0; i < 1;i++)
    {
        soledown[2 * i + 1] = new Solenoid(soledown[2 * i], Vect_3d(__errorxmove + __solenoidxmove, __solenoidymove + __errorymove, __solenoidzmove + __errorzmove -h - 2 * 15 * rr), Vect_3d(0,0,1), RR + (4 * i) * rr, 2 * rr, 15, __PIECESPERTURN, __INITCURRENT);
        soledown[2 * i + 2] = new Solenoid(soledown[2 * i + 1], Vect_3d(__errorxmove + __solenoidxmove, __solenoidymove + __errorymove, __solenoidzmove + __errorzmove -h), Vect_3d(0,0,-1), RR + (4 * i + 2) * rr, 2 * rr, 15, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
    }
    Solenoid* soledown3 = new Solenoid(soledown[2 * 1], Vect_3d(__errorxmove + __solenoidxmove, __solenoidymove + __errorymove, __solenoidzmove + __errorzmove -h - 2 * 15 * rr), Vect_3d(0,0,1), RR + (4 * 1) * rr, 2 * rr, 15, __PIECESPERTURN, __INITCURRENT);
    Components* downer1;
    downer1 = soledown3;//7*6情况，注意修改
    AddComponents* solenoid = dynamic_cast<AddComponents*>(downer1);
    
    BaseComponents* basetemp = new BaseComponents(Vect_3d(RR, 0, h));//加
    Solenoid* soletemp = new Solenoid(basetemp, Vect_3d(0, 0, h), Vect_3d(0,0,1), RR, 2 * rr, 1, __PIECESPERTURN, __INITCURRENT);
    Pass * passtemp = new Pass(soletemp, Vect_3d(RR, 0, -h));
    Solenoid* soledowntemp = new Solenoid(passtemp, Vect_3d(0, 0, -h), Vect_3d(0,0,-1), RR, 2 * rr, 1 , __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);

//加rr
    BaseComponents* base2 = new BaseComponents(Vect_3d(Rmin + __mosquitoxmove, __mosquitoymove, h));
    Components* sole2[9];
    sole2[0] = base2;
    for(int i = 0; i < 4;i++)
    {
        sole2[2 * i + 1] = new Mosquito(sole2[2 * i], Vect_3d(__mosquitoxmove, __mosquitoymove, h + (4 * i) * rr), Vect_3d(0,0,1), RR, -2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
        sole2[2 * i + 2] = new Mosquito(sole2[2 * i + 1], Vect_3d(__mosquitoxmove, __mosquitoymove, h + (4 * i + 2) * rr), Vect_3d(0,0,1), RR + 2 * 7 * rr, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
    }
    Mosquito* sole2_7 = new Mosquito(sole2[6], Vect_3d(__mosquitoxmove, __mosquitoymove, h + 4 * 3 * rr), Vect_3d(0,0,1), RR, -2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
    Components* upper2 = sole2[8];//7*6情况，注意修改
    Pass* passso2 = new Pass(upper2, Vect_3d(-Rmin + __errorxmove + __mosquitoxmove, __mosquitoymove + __errorymove, -h));
    Components* soledown2[9];
    soledown2[0] = passso2;
    for(int i = 0; i < 4;i++)
    {
        soledown2[2 * i + 1] = new Mosquito(soledown2[2 * i], Vect_3d(__errorxmove + __mosquitoxmove, __mosquitoymove + __errorymove, -h - (4 * i) * rr), Vect_3d(0,0,1), RR, -2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
        soledown2[2 * i + 2] = new Mosquito(soledown2[2 * i + 1], Vect_3d(__errorxmove + __mosquitoxmove, __mosquitoymove + __errorymove, -h - (4 * i + 2) * rr), Vect_3d(0,0,1), RR + 2 * 7 * rr, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
    }
    Mosquito* soledown2_7 = new Mosquito(soledown2[6], Vect_3d(__errorxmove + __mosquitoxmove, __errorymove + __mosquitoymove, -h - 4 * 3 * rr), Vect_3d(0,0,1), RR, -2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
    Components* downer2 = soledown2[8];//7*6情况，注意修改
    AddComponents* mosquito = dynamic_cast<AddComponents*>(downer2);
/*
    BaseComponents* base3 = new BaseComponents(Vect_3d(RR, 0, h + 2 * 7 * rr));//加
    Solenoid* solemixup = new Solenoid(base3, Vect_3d(0, 0, h + 2 * 7 * rr), Vect_3d(0,0,-1), RR, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
    AddComponents* up3[8];
    up3[0] = solemixup;
    for(int i = 0; i < 3;i++)
    {
        up3[2 * i + 1] = new Mosquito(up3[2 * i], Vect_3d(0, 0, h + (4 * i) * rr), Vect_3d(0,0,1), RR + 2 * rr, -2 * rr, 6, __PIECESPERTURN, __INITCURRENT);
        up3[2 * i + 2] = new Mosquito(up3[2 * i + 1], Vect_3d(0, 0, h + (4 * i + 2) * rr), Vect_3d(0,0,1), RR + 14 * rr, 2 * rr, 6, __PIECESPERTURN, __INITCURRENT);
    }
    up3[2 * 3 + 1] = new Mosquito(up3[2 * 3], Vect_3d(0, 0, h + (4 * 3) * rr), Vect_3d(0,0,1), RR + 2 * rr, -2 * rr, 6, __PIECESPERTURN, __INITCURRENT);
    AddComponents* upper3 = up3[7];
    Pass* pass3 = new Pass(upper3, Vect_3d(-RR, 0, -h - 2 * 7 * rr));
    AddComponents* down3[8];
    Solenoid* solemixdown = new Solenoid(pass3, Vect_3d(0, 0, -h - 2 * 7 * rr), Vect_3d(0,0,1), RR, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
    down3[0] = solemixdown;
    for(int i = 0; i < 3;i++)
    {
        down3[2 * i + 1] = new Mosquito(down3[2 * i], Vect_3d(0, 0, -h - (4 * i) * rr), Vect_3d(0,0,-1), RR + 2 * rr, -2 * rr, 6, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
        down3[2 * i + 2] = new Mosquito(down3[2 * i + 1], Vect_3d(0, 0, -h - (4 * i + 2) * rr), Vect_3d(0,0,-1), RR + 14 * rr, 2 * rr, 6, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
    }
    down3[2 * 3 + 1] = new Mosquito(down3[2 * 3], Vect_3d(0, 0, -h - (4 * 3) * rr), Vect_3d(0,0,-1), RR + 2 * rr, -2 * rr, 6, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
    Components* downer3 = down3[7];
    AddComponents* mixed = dynamic_cast<AddComponents*>(downer3);
*/
    switch (type)
    {
        case 0:
        return solenoid;
        case 1:
        return mosquito;
        default:
        return nullptr;
    }
}
