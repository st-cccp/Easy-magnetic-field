#pragma once

#include "MagnetProb.h"

PlanePlace xyplane_1000(Vect_3d(0,0,0),Vect_3d(1.2e-3,0,0),Vect_3d(0,1.2e-3,0),12);
PlanePlace xyplane_100(Vect_3d(0,0,0),Vect_3d(1.2e-4,0,0),Vect_3d(0,1.2e-4,0),12);
PlanePlace xyplane_50(Vect_3d(0,0,0),Vect_3d(6e-5,0,0),Vect_3d(0,6e-5,0),12);
PlanePlace xyplane_10(Vect_3d(0,0,0),Vect_3d(1.2e-5,0,0),Vect_3d(0,1.2e-5,0),12);
PlanePlace xyplane_1(Vect_3d(0,0,0),Vect_3d(1.2e-6,0,0),Vect_3d(0,1.2e-6,0),12);

LinePlace linex_10000(Vect_3d(-1.04e-2, 0, 0), Vect_3d(1.04e-2, 0, 0),52);
LinePlace linex_100(Vect_3d(-1.04e-4, 0, 0), Vect_3d(1.04e-4, 0, 0),52);
LinePlace linex_50(Vect_3d(-5.2e-5, 0, 0), Vect_3d(5.2e-5, 0, 0),52);
LinePlace linex_25(Vect_3d(-2.6e-5, 0, 0), Vect_3d(2.6e-5, 0, 0),52);
LinePlace liney_100(Vect_3d(0, -1.04e-4, 0), Vect_3d(0, 1.04e-4, 0),52);
LinePlace liney_50(Vect_3d(0, -5.2e-5, 0), Vect_3d(0, 5.2e-5, 0),52);
LinePlace liney_25(Vect_3d(0, -2.6e-5, 0), Vect_3d(0, 2.6e-5, 0),52);
LinePlace linexy_100(Vect_3d(-1.04e-4, -1.04e-4, 0), Vect_3d(1.04e-4, 1.04e-4, 0),52);
LinePlace linexy_50(Vect_3d(-5.2e-5, -5.2e-5, 0), Vect_3d(5.2e-5, 5.2e-5, 0),52);
LinePlace linexy_25(Vect_3d(-2.6e-5, -2.6e-5, 0), Vect_3d(2.6e-5, 2.6e-5, 0),52);
PlanePlace planexy_100(Vect_3d(0,0,0),Vect_3d(1.04e-4,0,0),Vect_3d(0,1.04e-4,0),52);
PlanePlace planexy_50(Vect_3d(0,0,0),Vect_3d(5.2e-5,0,0),Vect_3d(0,5.2e-5,0),52);

vector<__CalculatePlace*> __placelinechoices{&linex_100,&linex_50,&linex_25,&liney_100,&liney_50,&liney_25,&linexy_100,&linexy_50,&linexy_25};
vector<__CalculatePlace*> __placexlinechoices{&linex_100,&linex_50};
vector<__CalculatePlace*> __placefindchoices{&xyplane_1000,&xyplane_100,&xyplane_10,&xyplane_1};
vector<__CalculatePlace*> __placeplanechoices{&planexy_100,&planexy_50};
vector<__CalculatePlace*> __placeselfchoices{&linexy_100};