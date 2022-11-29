#include "LeviBee.h"


// Z = 100 * (Y - X**2)**2 + (X - 1)**2

int LeviBee::count_ = 2;

LeviBee::LeviBee() {
    min_pos_range_ = std::vector<double> (count_, -100.0);
    max_pos_range_ = std::vector<double> (count_, 100.0);

    for(int i = 0; i < count_; i++){
        position_.push_back(Utils::Uniform(min_pos_range_[i], max_pos_range_[i]));
    }

    Calculate();
}

void LeviBee::Calculate() {
    CalculateFitness();
}


void LeviBee::CalculateFitness() {
    fitness_ = -(pow(sin(3 * M_PI * position_[0]), 2) + pow((position_[0] - 1), 2) * (1 + pow(sin(3 * M_PI * position_[1]), 2))
            + pow((position_[1] - 1), 2) * (1 + pow(sin(2 * M_PI * position_[1]), 2)));
}