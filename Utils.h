#ifndef BEESALGO_UTILS_H
#define BEESALGO_UTILS_H

#include <iostream>
#include "cstdlib"
#include "ctime"

class Utils{
public:
    static double Uniform(double a, double b){
        double t = rand() / double(RAND_MAX);
        return (1-t) * a + t * b;
    }


    static double LeviFunc(double x, double y){
        return pow(sin(3 * M_PI * x), 2) + pow((x - 1), 2) * (1 + pow(sin(3 * M_PI * y), 2))
        + pow((y - 1), 2) * (1 + pow(sin(2 * M_PI * y), 2));
    }

    static double EgholderFunc(double x, double y){
        return -(y + 47) * sin(sqrt(std::abs(x/2 + y + 47))) - x*sin(sqrt(std::abs(x - (y + 47))));
    }

    static double RastriginFunc(double x, double y){
        return 10 * 2 + (x*x - 10*cos(2 * M_PI * x)) + (y*y - 10*cos(2 * M_PI * y));
    }

    static double RosenbrokFunc(double x, double y){
        return 100 * pow((y - x*x), 2) + pow(x - 1, 2);
    };

    static double DeJoungFunc(double x, double y){
        return x*x + y*y;
    };
};


#endif //BEESALGO_UTILS_H
