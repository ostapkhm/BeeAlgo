#include <utility>
#include "Hive.h"


Hive::Hive(int scout_bee_count, int selected_bee_count, int best_bee_count, int selected_sites_count, int best_sites_count,
           Function* objective_func, std::vector<double> search_range, double shrinking_koef, int stagnation_cycles_lim,
           bool visualize, bool maximization) {

    scout_bee_count_ = scout_bee_count;
    selected_bee_count_ = selected_bee_count;
    best_bee_count_ = best_bee_count;
    selected_sites_count_ = selected_sites_count;
    best_sites_count_ = best_sites_count;
    func_ = objective_func;
    search_range_ = std::move(search_range);
    shrinking_koef_ = shrinking_koef;
    stagnation_cycles_lim_ = stagnation_cycles_lim;
    maximization_ = maximization;

    if(objective_func->get_objective_func_2d_()){
        visualize_ = visualize;
    }
    else{
        visualize_ = false;
    }

    int bee_count = scout_bee_count_ + selected_bee_count_ * selected_sites_count_ + best_bee_count_ * best_sites_count_;

    // Initialize flower patches
    for(int i = 0; i < bee_count; i++){
        swarm_.push_back(new Bee(objective_func, maximization));
    }

    // For the first time analyze info only from scouts
    sort(swarm_.begin(), swarm_.begin() + scout_bee_count, Bee::Compare);
    best_position_ = swarm_[0]->get_position();
    best_fitness_ = swarm_[0]->get_fitness();

    statistics_ = new Statistics(this);
}

int Hive::SendBees(const std::vector<double>& position, int idx, int count) {
    // Performing local search
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

    // Updating scouts
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
    // Waggle dance
    int bee_index = 1;

    for(auto best_bee: best_sites_){
        bee_index = SendBees(best_bee->get_position(), bee_index, best_bee_count_);
    }

    for(auto medium_bee: selected_sites_){
        bee_index = SendBees(medium_bee->get_position(), bee_index, selected_bee_count_);
    }

    // Spread the rest of bees randomly
    // Performing global search using these bees that are not working currently
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

void Hive::Optimize(double eps) {
    double best_func_val = 1e9;
    int stagnation_counter = 0;

    while (std::abs(best_func_val - func_->get_global_min()) > eps) {
        Step();

        statistics_->IncreaseIterationAmount();

        if (get_best_fitness() != best_func_val) {
            best_func_val = get_best_fitness();

            if(visualize_){
                statistics_->MakePlot();
                statistics_->Info();
            }
        }
        else {
            stagnation_counter += 1;

            if (stagnation_counter == stagnation_cycles_lim_) {
                std::transform(search_range_.begin(), search_range_.end(), search_range_.begin(),
                               std::bind(std::multiplies<>(), std::placeholders::_1, shrinking_koef_));

                stagnation_counter = 0;
            }
        }
    }
}
