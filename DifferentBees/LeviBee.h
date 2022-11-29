#ifndef BEESALGO_LEVIBEE_H
#define BEESALGO_LEVIBEE_H


#include "../Bee/Bee.h"

class LeviBee: public Bee {
public:
    LeviBee();

    static std::vector<double> get_start_range(){
        std::vector<double> res(count_, 150.0);
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


#endif //BEESALGO_LEVIBEE_H
