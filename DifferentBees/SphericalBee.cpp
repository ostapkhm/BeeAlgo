#include "SphericalBee.h"

int SphericalBee::count_ = 2;

SphericalBee::SphericalBee() {
    min_pos_range_ = std::vector<double> (count_, -150.0);
    max_pos_range_ = std::vector<double> (count_, 150.0);

    for(int i = 0; i < count_; i++){
        position_.push_back(Utils::Uniform(min_pos_range_[i], max_pos_range_[i]));
    }

    Calculate();
}


void SphericalBee::CalculateFitness() {
    fitness_ = 0;
    for(auto val: position_){
        fitness_ -= val * val / 2;
    }
}

void SphericalBee::Calculate() {
    CalculateFitness();
}


