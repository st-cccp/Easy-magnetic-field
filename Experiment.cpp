#include "Experiment.h"
#include <utility>
using namespace std;

#define __PIECESPERTURN 7200
#define __INITCURRENT 1

pair<AddComponents*, AddComponents*> Experiment()
{
    double RR = 0.045;
    double Rmin = 0.045;
    double rr = 0.00325 / 2;
    // double rr = 0;
    double h = 0.066;
    
    BaseComponents* base1 = new BaseComponents(Vect_3d(RR + rr, 0, h));//加
    //使用BaseCompnents类规定开始的位置
    Components* sole[8];
    sole[0] = base1;
    for(int i = 0; i < 3;i++)
    {
        sole[2 * i + 1] = new Solenoid(sole[2 * i], Vect_3d(0, 0, h), Vect_3d(0,0,1), RR + (4 * i + 1) * rr, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
        sole[2 * i + 2] = new Solenoid(sole[2 * i + 1], Vect_3d(0, 0, h + 2 * 7 * rr), Vect_3d(0,0,-1), RR + (4 * i + 3) * rr, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
        //需要加上pass的量，螺线管的
    }
    sole[7] = new Solenoid(sole[2 * 3], Vect_3d(0, 0, h), Vect_3d(0,0,1), RR + (4 * 3 + 1) * rr, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
    Components* upper1;
    upper1 = sole[7];
    Pass* passso1 = new Pass(upper1, Vect_3d(RR + rr, 0, -h));
    Components* soledown[8];
    soledown[0] = passso1;
    for(int i = 0; i < 3;i++)
    {
        soledown[2 * i + 1] = new Solenoid(soledown[2 * i], Vect_3d(0, 0, -h), Vect_3d(0,0,-1), RR + (4 * i + 1) * rr, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
        soledown[2 * i + 2] = new Solenoid(soledown[2 * i + 1], Vect_3d(0, 0, -h - 2 * 7 * rr), Vect_3d(0,0,1), RR + (4 * i + 3) * rr, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
    }
    soledown[7] = new Solenoid(soledown[2 * 3], Vect_3d(0, 0, -h), Vect_3d(0,0,-1), RR + (4 * 3 + 1) * rr, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
    Components* downer1;
    downer1 = soledown[7];
    AddComponents* solenoid = dynamic_cast<AddComponents*>(downer1);
    
    BaseComponents* basetemp = new BaseComponents(Vect_3d(RR, 0, h));//加
    Solenoid* soletemp = new Solenoid(basetemp, Vect_3d(0, 0, h), Vect_3d(0,0,1), RR + rr, 2 * rr, 1, __PIECESPERTURN, __INITCURRENT);
    Pass * passtemp = new Pass(soletemp, Vect_3d(RR, 0, -h));
    Solenoid* soledowntemp = new Solenoid(passtemp, Vect_3d(0, 0, -h), Vect_3d(0,0,-1), RR + rr, 2 * rr, 1 , __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);

    BaseComponents* base2 = new BaseComponents(Vect_3d(Rmin + rr, 0, h));
    Components* sole2[8];
    sole2[0] = base2;
    for(int i = 0; i < 3;i++)
    {
        sole2[2 * i + 1] = new Mosquito(sole2[2 * i], Vect_3d(0, 0, h + (4 * i) * rr), Vect_3d(0,0,1), RR + rr, -2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
        sole2[2 * i + 2] = new Mosquito(sole2[2 * i + 1], Vect_3d(0, 0, h + (4 * i + 2) * rr), Vect_3d(0,0,1), RR + 15 * rr, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
    }
    sole2[7] = new Mosquito(sole2[6], Vect_3d(0, 0, h + 16 * rr), Vect_3d(0,0,1), RR + rr, -2 * rr, 7, __PIECESPERTURN, __INITCURRENT);
    Components* upper2 = sole2[7];
    Pass* passso2 = new Pass(upper2, Vect_3d(-Rmin - rr, 0, -h));
    Components* soledown2[8];
    soledown2[0] = passso2;
    for(int i = 0; i < 3;i++)
    {
        soledown2[2 * i + 1] = new Mosquito(soledown2[2 * i], Vect_3d(0, 0, -h - (4 * i) * rr), Vect_3d(0,0,-1), RR + rr, -2 * rr, 7, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
        soledown2[2 * i + 2] = new Mosquito(soledown2[2 * i + 1], Vect_3d(0, 0, -h - (4 * i + 2) * rr), Vect_3d(0,0,-1), RR + 15 * rr, 2 * rr, 7, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
    }
    soledown2[7] = new Mosquito(soledown2[6], Vect_3d(0, 0, -h - 16 * rr), Vect_3d(0,0,-1), RR + rr, -2 * rr, 7, __PIECESPERTURN, __INITCURRENT, CLOCKWISE::CCW);
    Components* downer2 = soledown2[7];
    AddComponents* mosquito = dynamic_cast<AddComponents*>(downer2);
    return make_pair(soledowntemp, mosquito);
}
