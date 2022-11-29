#include "RosenbrokBee.h"

int RosenbrokBee::count_ = 2;
// Z = 100 * (Y - X**2)**2 + (X - 1)**2

RosenbrokBee::RosenbrokBee() {
    min_pos_range_ = std::vector<double> (count_, -150.0);
    max_pos_range_ = std::vector<double> (count_, 150.0);

    for(int i = 0; i < count_; i++){
        position_.push_back(Utils::Uniform(min_pos_range_[i], max_pos_range_[i]));
    }

    Calculate();
}

void RosenbrokBee::Calculate() {
    CalculateFitness();
}

void RosenbrokBee::CalculateFitness() {
    fitness_ = -(100 * pow((position_[1] - position_[0] * position_[0]), 2) + pow((position_[0] - 1), 2));
}


