#include "Bee.h"

Bee::Bee(Function *func, bool maximisation) {
    maximisation_ = maximisation;
    calculate_func_ = func->get_objective_func_();
    count_ = func->get_variables_amount();

    min_pos_range_ = func->get_min_X();
    max_pos_range_ = func->get_max_X();

    for(int i = 0; i < count_; i++){
        position_.push_back(Utils::Uniform(min_pos_range_[i], max_pos_range_[i]));
    }

    CalculateFitness();
}


void Bee::CalculateFitness() {
    if(maximisation_){
        fitness_ = -calculate_func_(position_);
    }
    else{
        fitness_ = calculate_func_(position_);
    }
}

bool Bee::HasUniqueSite(const std::vector<Bee*>& bees, std::vector<double> range) {
    if(bees.empty()){
        return true;
    }

    for(auto current_bee: bees){
       std::vector<double> position = current_bee->get_position();

       for(int i = 0; i < position.size(); i++){
           if(std::abs(position_[i] - position[i]) > range[i]){
               return true;
           }
       }
    }

    return false;
}

bool Bee::Compare(Bee *bee1, Bee *bee2) {
    return bee1->fitness_ < bee2->fitness_;
}

void Bee::CheckPosition() {
    // Correct position_ if it exceeds min_pos_range or max_pos_range

    for(int i = 0; i < position_.size(); i++){
        if(position_[i] < min_pos_range_[i]){
            position_[i] = min_pos_range_[i];
        }
        else{
            if(position_[i] > max_pos_range_[i]){
                position_[i] = max_pos_range_[i];
            }
        }
    }
}

void Bee::GoTo(std::vector<double> position, std::vector<double> position_range) {
    // Go to position within some range

    for(int i = 0; i < position.size(); i++){
        position_[i] = position[i] + Utils::Uniform(-position_range[i], position_range[i]);
    }

    CheckPosition();
    CalculateFitness();
}

void Bee::GoToRandom() {
    // Fill position_ with random coordinates

    for(int i = 0; i < position_.size(); i++){
        position_[i] = Utils::Uniform(min_pos_range_[i], max_pos_range_[i]);
    }

    CheckPosition();
    CalculateFitness();
}

std::string Bee::ToString() {
    std::string res;

    res += "Position(";

    for(auto el: position_){
        res += std::to_string(el) + " ";
    }

    res += ")\n";
    res += "Fitness ->";
    res += std::to_string(fitness_);
    res += "\n";

    res += "MaxRange(";

    for(auto el: max_pos_range_){
        res += std::to_string(el) + " ";
    }

    res += ")\n";

    res += "MinRange(";

    for(auto el: min_pos_range_){
        res += std::to_string(el) + " ";
    }

    res += ")\n";
    return res;
}

