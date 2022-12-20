#ifndef BEESALGO_BEE_H
#define BEESALGO_BEE_H

#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "../Utils.h"
#include "../Function.h"

class Bee {
public:
    Bee(Function* func, bool maximisation=false);

    void CalculateFitness();

    bool HasUniqueSite(const std::vector<Bee*>& bees, std::vector<double> range);
    static bool Compare(Bee* bee1, Bee* bee2);
    void GoTo(std::vector<double> position, std::vector<double> position_range);
    void GoToRandom();
    void CheckPosition();

    std::vector<double> get_position(){
        return position_;
    }

    double get_fitness(){
        return fitness_;
    }

    std::string ToString();

protected:
    // fitness_ - value of objective function
    // maximization_ - whether the task is to maximize or minimize an objective function
    // count_ - variables amount in objective function

    std::vector<double> max_pos_range_;
    std::vector<double> min_pos_range_;
    std::vector<double> position_;
    double fitness_;
    bool maximisation_;
    int count_;
    std::function<double(std::vector<double>)> calculate_func_;
};


#endif //BEESALGO_BEE_H
