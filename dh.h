#ifndef AA_DH_H
#define AA_DH_H
#include "matrix.h"
#include <iostream>
#include <cmath>

using namespace std;
class DH{
private:
    double *theta;
    double *alpha;
    double *a;
    double *d;
    int dof;

    double STheta;
    double CTheta;

    double SAlpha;
    double CAlpha;

    Matrix <double> T0;
    Matrix <double> R0;
    Matrix <double> *foo;



public:
    DH(){}
    DH(double *_theta, double *_alpha, double *_a, double *_d ):T0(Matrix<double>(4,4)) ,R0(Matrix<double>(3,3)){

        theta = _theta;
        alpha = _alpha;
        a = _a;
        d = _d;
        dof = sizeof(theta);

        foo = new Matrix<double>[dof];
        Matrix<double> C(4, 4);


        for (int i = 0; i < dof; i++) {
            foo[i] = C;
            STheta = sin(theta[i]);
            CTheta = cos(theta[i]);

            SAlpha = sin(alpha[i]);
            CAlpha = cos(alpha[i]);;

            for (int x = 0; x < dof; x++) {
                for (int y = 0; y < dof; y++) {
                    if (x == 0 && y == 0) {
                        foo[i](x, y) = CTheta;
                    } else if (x == 0 && y == 1) {
                        foo[i](x, y) = -1 * CAlpha * STheta;
                    } else if (x == 0 && y == 2) {
                        foo[i](x, y) = SAlpha * STheta;
                    } else if (x == 0 && y == 3) {
                        foo[i](x, y) = a[i] * CTheta;
                    } else if (x == 1 && y == 0) {
                        foo[i](x, y) = STheta;
                    } else if (x == 1 && y == 1) {
                        foo[i](x, y) = CAlpha * CTheta;
                    } else if (x == 1 && y == 2) {
                        foo[i](x, y) = -1 * SAlpha * CTheta;
                    } else if (x == 1 && y == 3) {
                        foo[i](x, y) = a[i] * STheta;
                    } else if (x == 2 && y == 1) {
                        foo[i](x, y) = SAlpha;
                    } else if (x == 2 && y == 2) {
                        foo[i](x, y) = CAlpha;
                    } else if (x == 2 && y == 3) {
                        foo[i](x, y) = d[i];
                    } else if (x == 3 && y == 3) {
                        foo[i](x, y) = 1;
                    }
                }
                R0 = T0;
            }
            if (i == 0){
                T0 =  foo[i];
            }else{
                T0 = T0 * foo[i];
            }
            R0 = T0;
        }
    }
    ~DH() {delete[] foo;}
    Matrix <double> GetRotationKinematics(){
        return R0;
    }
    Matrix <double> GetForwardKinematics(){
        return T0;
    }

    void PrintRotationKinematics(){
        R0.PrintResult("______________ROTATION MATRIX:______________");
    }
    void PrintForwardKinematics(){
        T0.PrintResult("______________TRANSPOSE MATRIX:______________");
    }

};
#endif //AA_DH_H
