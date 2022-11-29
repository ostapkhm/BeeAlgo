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
};


#endif //BEESALGO_UTILS_H
