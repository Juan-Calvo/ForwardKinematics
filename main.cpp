
#include "dh.h"
#include <iostream>
#define PI 3.14159265359

using namespace std;
int main()
{
    //EXAMPLE OF DENAVIT-HARTENBERG 
    double theta[7] = {0, 1.2, 3.44, 5, 6, 7,8.999};
    double alpha[7] = {0, 1.2, 3.44, 5, 6, 7,8.999};
    double a[7] = {0, 1.2, 3.44, 5, 6, 7,8.999};
    double d[7] = {0, 1.2, 3.44, 5, 6, 7,8.999};

    DH Robot1(theta,alpha,a, d);

    //GET FORWARD KINEMATICS MATRIX
    Matrix <double> T08(4,4);
    T08 = Robot1.GetForwardKinematics();
    T08.PrintResult();

    //GET ROTATION MATRIX
    Matrix <double> R08(3,3);
    R08 = Robot1.GetRotationKinematics();
    R08.PrintResult();

    return 0;
}

