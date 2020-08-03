#include <iostream>
using namespace std;

#define __OUTPUT_

#include "MagnetProb.h"

#include "Experiment.h"

int main()
{

#ifdef __OUTPUT_
    freopen("output.csv","w",stdout);
#endif
#ifdef __TESTING_
    freopen("output.txt","w",stdout);
#endif
    AddComponents* solenoid;
    AddComponents* mosquito;
    auto __expelem = Experiment();
    solenoid = __expelem.first;
    mosquito = __expelem.second;
    cout << solenoid->Magfield(Vect_3d()) << endl;
#ifdef __TESTING_
    cout << solenoid->Magfield(Vect_3d()) << endl;
    //Vect_3d的默认构造函数得到的是原点{0,0,0}，此处意为aa螺线管（和它前面连接的所有元件）在原点产生的磁场。
#endif
    // double enhance = 1 / norm_2(solenoid->Magfield(Vect_3d()));
    //norm_2为2-范数
    // solenoid->ChangeCurrent(solenoid->current * enhance);
    //利用对励磁电流的线性性，把原点处的磁场强度统一到150Gauss。
#ifdef __TESTING_
    cout << mosquito->Magfield(Vect_3d()) << endl;
#endif
    // enhance = 1 / norm_2(mosquito->Magfield(Vect_3d()));
    // mosquito->ChangeCurrent(mosquito->current * enhance);
    MagnetProb prob;
    //MagnetProb顾名思义，就是用来解决磁场问题的一个总引擎。
    prob.setComponent(solenoid);
    //设置问题所用元件，在本系统的设计模式中，最后一个元件包含了其自身和其直接间接连接的所有元件的信息和效应
    // CubePlace cube1(Vect_3d(-1e-4,-1e-4,0),Vect_3d(1e-4,1e-4,0),50);
    //一种研究点集合，给出立方体中的点5，第一个和第二个参数分别是立方体对角的点，给出一个与坐标轴平行的立方体。
    //第三个参数是一条边切成几片，给出立方体内部(n-1)^3个点。
    LinePlace line1(Vect_3d(-1.04e-4, 0, 0), Vect_3d(1.04e-4, 0, 0),52);
    //一种研究点集合，给出一条线上的点，第三个参数默认为100
    // PointPlace point1(Vect_3d(1e-4, 1e-4, 0));
    // PointPlace point2(Vect_3d(1e-4, 1.01e-4, 0));
    // PointPlace point1(Vect_3d(1e-4, 1e-4, 0));
    // PointPlace point2(Vect_3d(1e-4, 1.01e-4, 0));
    auto result1 = prob.getField(line1);
    // auto result2 = prob.getField(point2);
    //给出绑定的电路系统在需要的位置的磁场，得到的是一个std::map类型，map元素的第一和第二个元素分别代表位置和磁场。
    vector<double> fieldintense1;
    vector<double> fieldangle1;
    double fieldBzmax = 0;
    double fieldBzmin = 0xffffffff;
    double fieldmean = 0;
    int pointnum = 0;
    for(auto i : result1)
    {
        #ifdef __TESTING_
        cout << i.first << " : " << i.second << endl;
        #endif
        fieldintense1.push_back(i.second.elem(2));//磁场强度都存起来了
        // fieldangle1.push_back(angle(i.second, Vect_3d(0, 0, 1)));
        fieldBzmax = fieldBzmax > i.second.elem(2) ? fieldBzmax : i.second.elem(2);
        fieldBzmin = fieldBzmin < i.second.elem(2) ? fieldBzmin : i.second.elem(2);
        fieldmean += i.second.elem(2);
        pointnum ++;
    }
    fieldmean /= pointnum;
    // for(auto i : result2)
    // {
    //     #ifdef __TESTING_
    //     cout << i.first << " : " << i.second << endl;
    //     #endif
    //     fieldintense1.push_back(i.second.elem(2));//磁场强度都存起来了
    //     fieldangle1.push_back(angle(i.second, Vect_3d(0, 0, 1)));
    // }
    // cout << "delta = " << fieldintense1[0] - fieldintense1[1] << endl;
    #ifdef __TESTING_
    // auto resultgrad1 = prob.getGrad(point1);
    // for(auto i : resultgrad1)
    // {
    //     cout << i.first << " : \n" << i.second << endl;
    // }
    #endif
    #ifdef __TESTING_
    // auto resultgrad2 = prob.getGrad(point2);
    // for(auto i : resultgrad2)
    // {
    //     cout << i.first << " : \n" << i.second << endl;
    // }
    #endif
    for(auto i : fieldintense1)
    {
        cout << setprecision(15) << i << ", ";
    }
    cout << endl;
    cout << "max: " << fieldBzmax << "min: " << fieldBzmin << "mean: " << fieldmean << "for " << pointnum << " points" << endl;
    cout << (fieldBzmax - fieldBzmin) / fieldmean << endl;
#ifdef __TESTING_
    cout << "--------------------------------------------\n";
#endif

    prob.setComponent(mosquito);
    //CubePlace cube2(Vect_3d(-0.0002,-0.0002,-0.0002),Vect_3d(0.0002,0.0002,0.0002),4);
    LinePlace line2(Vect_3d(-1e-4, 0, 0), Vect_3d(1e-4, 0, 0));
    // result1 = prob.getField(point1);
    // result2 = prob.getField(point2);
    auto result2 = prob.getField(line2);
    vector<double> fieldintense2;
    vector<double> fieldangle2;
    fieldBzmax = 0;
    fieldBzmin = 0xffffffff;
    fieldmean = 0;
    // for(auto i : result1)
    // {
    //     #ifdef __TESTING_
    //     cout << i.first << " : " << i.second << endl;
    //     #endif
    //     fieldintense1.push_back(i.second.elem(2));//磁场强度都存起来了
    //     fieldangle1.push_back(angle(i.second, Vect_3d(0, 0, 1)));
    // }
    for(auto i : result2)
    {
        // #ifdef __TESTING_
        // cout << i.first << " : " << i.second << endl;
        // #endif
        fieldintense2.push_back(i.second.elem(2));//磁场强度都存起来了
        // fieldangle1.push_back(angle(i.second, Vect_3d(0, 0, 1)));
        fieldBzmax = fieldBzmax > i.second.elem(2) ? fieldBzmax : i.second.elem(2);
        fieldBzmin = fieldBzmin < i.second.elem(2) ? fieldBzmin : i.second.elem(2);
        fieldmean += i.second.elem(2);
    }
    fieldmean /= result1.size();
    #ifdef __TESTING_
    // resultgrad1 = prob.getGrad(point1);
    // for(auto i : resultgrad1)
    // {
    //     cout << i.first << " : \n" << i.second << endl;
    // }
    #endif
    #ifdef __TESTING_
    // resultgrad2 = prob.getGrad(point2);
    // for(auto i : resultgrad2)
    // {
    //     cout << i.first << " : \n" << i.second << endl;
    // }
    #endif
    for(auto i : fieldintense2)
    {
        cout << setprecision(15) << i << ", ";
    }
    cout << endl;
    cout << "max: " << fieldBzmax << "min: " << fieldBzmin << "mean: " << fieldmean << endl;
    cout << (fieldBzmax - fieldBzmin) / fieldmean << endl;

    /*
    BaseComponents base(Vect_3d(1,0,0));
    Solenoid a(&base, Vect_3d(0, 0, 0), Vect_3d(0,0,1), 1, 0, 1, 3600, 1);
    Mosquito b(&base, Vect_3d(0, 0, 0), Vect_3d(0,0,1), 1, 0, 1, 3600, 1);
    cout << a.Magfield(Vect_3d(0.1,0.1,0)) << endl;
    cout << b.Magfield(Vect_3d(0.1,0.1,0)) << endl;
    cout << a.MagGrad(Vect_3d(0.1,0.1,0)) << endl;
    cout << b.MagGrad(Vect_3d(0.1,0.1,0)) << endl;
    //这些是比较基本的测试代码，现在没啥用了
    */
    return 0;
}


