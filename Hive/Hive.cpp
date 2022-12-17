#include <utility>
#include "Hive.h"

Hive::Hive(int scout_bee_count, int selected_bee_count, int best_bee_count, int selected_sites_count,
           int best_sites_count, double (*objective_func)(std::vector<double>), std::vector<double> search_range,
           double min_x_bees_pos, double min_y_bees_pos, bool maximization) {

    scout_bee_count_ = scout_bee_count;
    selected_bee_count_ = selected_bee_count;
    best_bee_count_ = best_bee_count;
    selected_sites_count_ = selected_sites_count;
    best_sites_count_ = best_sites_count;
    search_range_ = std::move(search_range);

    int bee_count = scout_bee_count_ + selected_bee_count_ * selected_sites_count_ + best_bee_count_ * best_sites_count_;

    for(int i = 0; i < bee_count; i++){
        swarm_.push_back(new Bee(min_x_bees_pos, min_y_bees_pos, objective_func, maximization));
    }

    // For the first time analyzing info only from scout bees
    sort(swarm_.begin(), swarm_.begin() + scout_bee_count_, Bee::Compare);
    best_position_ = swarm_[0]->get_position();
    best_fitness_ = swarm_[0]->get_fitness();
}

int Hive::SendBees(const std::vector<double>& position, int idx, int count) {
    Bee* current_bee;

    for(int i = 0; i < count; i++){
        if(idx == swarm_.size()){
            break;
        }

        current_bee = swarm_[idx];

        if(!BeeWasUsed(current_bee)){
            current_bee->GoTo(position, search_range_);
        }
        idx++;
    }

    return idx;
}

bool Hive::BeeWasUsed(Bee* bee) {
    if (std::find(best_sites_.begin(), best_sites_.end(), bee) != best_sites_.end()) {
        return true;
    }

    if (std::find(selected_sites_.begin(), selected_sites_.end(), bee) != selected_sites_.end()) {
        return true;
    }

    return false;
}

void Hive::Step() {
    // Choose those bees that found best_sites

    best_sites_ = { swarm_[0] };

    Bee* current_bee;
    int current_idx = 1;

    for(; current_idx < swarm_.size(); current_idx++){
        current_bee = swarm_[current_idx];

        if(current_bee->HasUniqueSite(best_sites_, search_range_)){
            best_sites_.push_back(current_bee);
        }

        if(best_sites_.size() == best_sites_count_){
            current_idx++;
            break;
        }
    }

    selected_sites_ = {};

    for(; current_idx < swarm_.size();){
        current_bee = swarm_[current_idx];

        current_bee->HasUniqueSite(best_sites_, search_range_);
        current_bee->HasUniqueSite(selected_sites_, search_range_);

        if(current_bee->HasUniqueSite(best_sites_, search_range_) && current_bee->HasUniqueSite(selected_sites_, search_range_) ){
            selected_sites_.push_back(current_bee);
        }

        if(selected_sites_.size() == selected_sites_count_){
            break;
        }
        current_idx++;
    }

    // Send bees on a mission

    int bee_index = 1;

    for(auto best_bee: best_sites_){
        bee_index = SendBees(best_bee->get_position(), bee_index, best_bee_count_);
    }

    for(auto medium_bee: selected_sites_){
        bee_index = SendBees(medium_bee->get_position(), bee_index, selected_bee_count_);
    }

    // Spread the rest of bees randomly
    for(int i = bee_index; i < swarm_.size(); i++){
        swarm_[i]->GoToRandom();
    }

    // Sorting and obtain new best position and fitness

    sort(swarm_.begin(), swarm_.end(), Bee::Compare);
    best_position_ = swarm_[0]->get_position();
    best_fitness_ = swarm_[0]->get_fitness();
}

void Hive::SwarmInfo() {
    std::cout << "-------------------------" << std::endl;
    for(auto bee:swarm_){
        std::cout << bee->ToString() << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
}
