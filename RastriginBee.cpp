#include "RastriginBee.h"

int RastriginBee::count_ = 2;

RastriginBee::RastriginBee() {
    min_pos_range_ = std::vector<double> (count_, -150.0);
    max_pos_range_ = std::vector<double> (count_, 150.0);

    for(int i = 0; i < count_; i++){
        position_.push_back(Utils::Uniform(min_pos_range_[i], max_pos_range_[i]));
    }

    Calculate();
}

void RastriginBee::Calculate() {
    CalculateFitness();
}

void RastriginBee::CalculateFitness() {
    fitness_ = -(20 + position_[0] * position_[0] - 10 * cos(2 * M_PI * position_[0]) +
             position_[1] * position_[1] - 10 * cos(2 * M_PI * position_[1]));
}


