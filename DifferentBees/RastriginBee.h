#ifndef BEESALGO_RASTRIGINBEE_H
#define BEESALGO_RASTRIGINBEE_H


#include "../Bee/Bee.h"
#include "cmath"

class RastriginBee: public Bee {
public:
    RastriginBee();

    static std::vector<double> get_start_range(){
        std::vector<double> res(count_, 250.0);
        return res;
    }

    static std::vector<double> get_koef_range(){
        std::vector<double> res(count_, 0.98);
        return res;
    }

private:
    static int count_;

    void Calculate();
    void CalculateFitness() override;
};

#endif //BEESALGO_RASTRIGINBEE_H
