#include "Elec_Mag.h"

#ifdef __GAUSIAN__
const double mu_0 = 1;
const double c_vacant = 29979245800;
#endif
#ifdef __SI__
const double mu_0 = 4 * PI * 1e-7;
const double c_vacant = 299792458;
#endif

const int plus3(int a, int b)
{
    return (a + b) % 3;
}