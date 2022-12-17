#ifndef BEESALGO_HIVE_H
#define BEESALGO_HIVE_H

#include <bits/stdc++.h>
#include <utility>

#include "../Bee/Bee.h"

class Hive {
public:
    Hive(int scout_bee_count, int selected_bee_count, int best_bee_count, int selected_sites_count, int best_sites_count,
         double (*objective_func)(std::vector<double>), std::vector<double> search_range, double min_x_bees_pos, double min_y_bees_pos,
         bool maximisation=false);

    int SendBees(const std::vector<double>& position, int idx, int count);

    void Step();

    double get_best_fitness(){
        return best_fitness_;
    }

    void set_range(std::vector<double> search_range){
        search_range_ = std::move(search_range);
    }

    std::vector<double> get_range(){
        return search_range_;
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

    void SwarmInfo();

private:
    int scout_bee_count_;
    int selected_bee_count_;
    int best_bee_count_;
    int selected_sites_count_;
    int best_sites_count_;

    std::vector<double> search_range_;
    std::vector<double>  best_position_;
    double best_fitness_;
    std::vector<Bee*> best_sites_;
    std::vector<Bee*> selected_sites_;

    std::vector<Bee*> swarm_;

    bool BeeWasUsed(Bee* bee);
};


#endif //BEESALGO_HIVE_H
