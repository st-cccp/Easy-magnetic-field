#include <iostream>
using namespace std;

#include "MagnetProb.h"

int main()
{
    double RR = 8;
    double Rmax = 8;
    double rr = 0.03;
    double h = 6;
    /*
    BaseComponents base1(Vect_3d(RR - rr, 0, h));
    //使用BaseCompnents类规定开始的位置
    Solenoid a(&base1, Vect_3d(0, 0, h), Vect_3d(0,0,2), RR - rr, 2 * rr, 20, 360, 30);
    //Solenoid类是螺线管元件，第一个参数是从。。连接到，元件设计为首尾相连电流连续
    //如果相互独立，可用后面的Pass类，不受影响跳过去。
    //第二个参数为低部截面圆心。
    //第三个参数为轴向指向，它是一个Vect_3ddir类型（Vect_3d三维矢量类的子类）。
    //它有两种初始化方法，一种是用一个普通矢量初始化（如上），另一种为用球坐标中θ,ψ初始化，方便与z轴有小偏角的分析和知道精确角度的情况。
    //第四个参数是初始半径，鉴于元件相当于是从上一个元件尾巴上拉出来的导线，如果不匹配会很尴尬。
    //第五个参数是步进，就是一圈在z轴上沿轴向前进多少，这里就直径了。如果填0那就是平面。
    //第六个是圈数，它真的可以就是个实数，比方说3.45圈什么的。
    //第七个涉及计算，计算方法就是切片，所以这里意味着一圈线圈切成多少段，默认值是1°一段（360）。
    //第八个参数是电流大小，由于后面可以使用最后一个元件的ChangeCurrent(...)全部修改，这里可填可不填了，默认为1Ampere。
    //第九个参数（这里用了默认值）是顺时针还是逆时针绕，按照顺着轴向看去的截面旋转方向定。类型为CLOCKWISE，顺时针CW，逆时针CCW。
    Pass ataa(&a, Vect_3d(RR - rr, 0, -h));
    //连接a，直接跳到第二个参数的位置（不计电流影响）。
    Solenoid aa(&ataa, Vect_3d(0, 0, -h), Vect_3ddir(PI, 0), RR - rr, 2 * rr, 20, 360, 30, CLOCKWISE::CCW);
    //第二个螺线管，参数同上。

    BaseComponents base2(Vect_3d(Rmax - rr, 0, h));
    Mosquito b(&base2, Vect_3d(0, 0, h), Vect_3d(0,0,2), Rmax - rr, 2 * rr, 10, 360, 30);
    //蚊香盘型类型，参数与螺线管几乎相同，此处步进指的是径向步进，以向内为正。
    Mosquito binv(&b, Vect_3d(0, 0, h + rr), Vect_3d(0,0,2), Rmax - 21 * rr, -2 * rr, 10, 360, 30);
    Pass btbb(&binv, Vect_3d(Rmax - rr, 0, -h));
    Mosquito bb(&btbb, Vect_3d(0, 0, -h), Vect_3d(0,0,-2), Rmax - rr, 2 * rr, 10, 360, 30, CLOCKWISE::CCW);
    Mosquito bbinv(&bb, Vect_3d(0, 0, -h - rr), Vect_3d(0,0,-2), Rmax - 21 * rr, -2 * rr, 10, 360, 30, CLOCKWISE::CCW);
    cout << aa.Magfield(Vect_3d()) << endl;
    //Vect_3d的默认构造函数得到的是原点{0,0,0}，此处意为aa螺线管（和它前面连接的所有元件）在原点产生的磁场。
    double enhance = 150 / norm_2(aa.Magfield(Vect_3d()));
    //norm_2为2-范数
    aa.ChangeCurrent(aa.current * enhance);
    //利用对励磁电流的线性性，把原点处的磁场强度统一到150Gauss。
    cout << bbinv.Magfield(Vect_3d()) << endl;
    enhance = 150 / norm_2(bbinv.Magfield(Vect_3d()));
    bbinv.ChangeCurrent(bbinv.current * enhance);
    MagnetProb prob;
    //MagnetProb顾名思义，就是用来解决磁场问题的一个总引擎。
    prob.setComponent(&aa);
    //设置问题所用元件，在本系统的设计模式中，最后一个元件包含了其自身和其直接间接连接的所有元件的信息和效应
    CubePlace cube1(Vect_3d(-0.2,-0.2,-0.2),Vect_3d(0.2,0.2,0.2),3);
    //一种研究点集合，给出立方体中的点，第一个和第二个参数分别是立方体对角的点，给出一个与坐标轴平行的立方体。
    //第三个参数是一条边切成几片，给出立方体内部(n-1)^3个点。
    auto result = prob.getField(cube1);
    //给出绑定的电路系统在需要的位置的磁场，得到的是一个std::map类型，map元素的第一和第二个元素分别代表位置和磁场。
    vector<double> fieldintense1;
    for(auto i : result)
    {
        cout << i.first << " : " << i.second << endl;
        fieldintense1.push_back(norm_2(i.second));//磁场强度都存起来了
    }
    auto resultgrad = prob.getGrad(cube1);
    for(auto i : resultgrad)
    {
        cout << i.first << " : \n" << i.second << endl;
    }

    cout << "--------------------------------------------\n";
    prob.setComponent(&bbinv);
    CubePlace cube2(Vect_3d(-0.2,-0.2,-0.2),Vect_3d(0.2,0.2,0.2),2);
    result = prob.getField(cube2);
    for(auto i : result)
    {
        cout << i.first << " : " << i.second << endl;
    }
    resultgrad = prob.getGrad(cube2);
    for(auto i : resultgrad)
    {
        cout << i.first << " : \n" << i.second << endl;
    }
    */
    BaseComponents base(Vect_3d(1,0,0));
    Solenoid a(&base, Vect_3d(0, 0, 0), Vect_3d(0,0,1), 1, 0, 1, 360, 1);
    Mosquito b(&base, Vect_3d(0, 0, 0), Vect_3d(0,0,1), 1, 0, 1, 360, 1);
    cout << a.Magfield(Vect_3d(0.5,0.5,2)) << endl;
    cout << b.Magfield(Vect_3d(0.5,0.5,2)) << endl;
    cout << a.MagGrad(Vect_3d(0.5,0.5,2)) << endl;
    cout << b.MagGrad(Vect_3d(0.5,0.5,2)) << endl;
    //这些是比较基本的测试代码，现在没啥用了
    
    return 0;
}


