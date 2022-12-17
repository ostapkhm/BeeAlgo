#include "Bee.h"


int Bee::count_ = 2;

Bee::Bee(double min_X_value, double max_X_value, double (*calculate_func)(std::vector<double>), bool maximisation) {
    maximisation_ = maximisation;
    calculate_func_ = calculate_func;
    min_pos_range_ = std::vector<double> (count_, min_X_value);
    max_pos_range_ = std::vector<double> (count_, max_X_value);

    for(int i = 0; i < count_; i++){
        position_.push_back(Utils::Uniform(min_pos_range_[i], max_pos_range_[i]));
    }

    CalculateFitness();
}

void Bee::CalculateFitness() {
    if(maximisation_){
        fitness_ = -calculate_func_({position_[0], position_[1]});
    }
    else{
        fitness_ = calculate_func_({position_[0], position_[1]});
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



