#ifndef BEESALGO_HIVE_H
#define BEESALGO_HIVE_H

#include <bits/stdc++.h>
#include <utility>

#include "../Bee/Bee.h"
#include "../Statistics/Statistics.h"

class Hive {
public:
    Hive(int scout_bee_count, int selected_bee_count, int best_bee_count, int selected_sites_count, int best_sites_count,
         Function* objective_func, std::vector<double> search_range, double shrinking_koef, int stagnation_cycles_lim,
         bool visualize=false, bool maximisation=false);

    ~Hive(){
        delete statistics_;

        for(auto bee:swarm_){
            delete bee;
        }
    }

    int SendBees(const std::vector<double>& position, int idx, int count);


    void Optimize(double eps);
    void Step();

    double get_best_fitness(){
        if(maximization_){
            return -best_fitness_;
        }
        return best_fitness_;
    }

    std::vector<double> get_best_position(){
        return best_position_;
    }

    std::vector<Bee*> get_selected_sites(){
        return selected_sites_;
    }

    std::vector<Bee*> get_best_sites(){
        return best_sites_;
    }

    auto get_objective_function(){
        return *func_;
    }

    int get_iteration_amount(){
        return statistics_->get_iteration_amount();
    }

    void SwarmInfo();

private:
    bool BeeWasUsed(Bee* bee);

    // Algorithm parameters

    int scout_bee_count_;
    int best_bee_count_;
    int selected_bee_count_;
    int best_sites_count_;
    int selected_sites_count_;
    std::vector<double> search_range_;
    int stagnation_cycles_lim_;
    double shrinking_koef_;
    bool maximization_;

    Function* func_;
    std::vector<double>  best_position_;
    double best_fitness_;
    std::vector<Bee*> best_sites_;
    std::vector<Bee*> selected_sites_;

    std::vector<Bee*> swarm_;
    Statistics* statistics_;
    bool visualize_;
};


#endif //BEESALGO_HIVE_H
