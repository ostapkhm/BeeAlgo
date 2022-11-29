#ifndef BEESALGO_ROSENBROKBEE_H
#define BEESALGO_ROSENBROKBEE_H

// Z = 100 * (Y - X**2)**2 + (X - 1)**2

#include "Bee.h"

class RosenbrokBee: public Bee {
public:
    RosenbrokBee();

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


#endif //BEESALGO_ROSENBROKBEE_H
