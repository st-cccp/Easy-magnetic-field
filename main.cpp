#include <iostream>
using namespace std;

#include "MagnetProb.h"

int main()
{
    double RR = 8;
    double Rmax = 8;
    double rr = 0.03;
    double h = 6;
    BaseComponents base1(Vect_3d(RR - rr, 0, h));
    Solenoid a(&base1, Vect_3d(0, 0, h), Vect_3d(0,0,2), RR - rr, 2 * rr, 20, 360, 30);
    Pass ataa(&a, Vect_3d(RR - rr, 0, -h));
    Solenoid aa(&ataa, Vect_3d(0, 0, -h), Vect_3d(0,0,-2), RR - rr, 2 * rr, 20, 360, 30, CLOCKWISE::CCW);
    BaseComponents base2(Vect_3d(Rmax - rr, 0, h));
    Mosquito b(&base2, Vect_3d(0, 0, h), Vect_3d(0,0,2), Rmax - rr, 2 * rr, 10, 360, 30);
    Mosquito binv(&b, Vect_3d(0, 0, h + rr), Vect_3d(0,0,2), Rmax - 21 * rr, -2 * rr, 10, 360, 30);
    Pass btbb(&binv, Vect_3d(Rmax - rr, 0, -h));
    Mosquito bb(&btbb, Vect_3d(0, 0, -h), Vect_3d(0,0,-2), Rmax - rr, 2 * rr, 10, 360, 30, CLOCKWISE::CCW);
    Mosquito bbinv(&bb, Vect_3d(0, 0, -h - rr), Vect_3d(0,0,-2), Rmax - 21 * rr, -2 * rr, 10, 360, 30, CLOCKWISE::CCW);
    cout << aa.Magfield(Vect_3d()) << endl;
    double enhance = 150 / norm_2(aa.Magfield(Vect_3d()));
    aa.ChangeCurrent(aa.current * enhance);
    cout << bbinv.Magfield(Vect_3d()) << endl;
    enhance = 150 / norm_2(bbinv.Magfield(Vect_3d()));
    bbinv.ChangeCurrent(bbinv.current * enhance);
    MagnetProb prob;
    prob.setComponent(&aa);
    CubePlace cube1(Vect_3d(-0.2,-0.2,-0.2),Vect_3d(0.2,0.2,0.2),4);
    auto result = prob.getField(cube1);
    vector<double> intensely;
    for(auto i : result)
    {
        cout << i.first << " : " << i.second << endl;
        intensely.push_back(norm_2(i.second));
    }

    cout << "--------------------------------------------\n";
    prob.setComponent(&bbinv);
    CubePlace cube2(Vect_3d(-0.2,-0.2,-0.2),Vect_3d(0.2,0.2,0.2),4);
    result = prob.getField(cube2);
    for(auto i : result)
    {
        cout << i.first << " : " << i.second << endl;
    }
    /*
    BaseComponents base(Vect_3d(1,0,0));
    Solenoid a(&base, Vect_3d(0, 0, 0), Vect_3d(0,0,1), 1, 0, 1, 360, 1);
    Mosquito b(&base, Vect_3d(0, 0, 0), Vect_3d(0,0,1), 1, 0, 1, 360, 1);
    cout << a.Magfield(Vect_3d(0,0.5,2)) << endl;
    cout << b.Magfield(Vect_3d(0,0.5,2)) << endl;
    */
    return 0;
}


