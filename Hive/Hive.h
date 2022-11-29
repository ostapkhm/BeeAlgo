#ifndef BEESALGO_HIVE_H
#define BEESALGO_HIVE_H

#include <bits/stdc++.h>

#include <utility>

#include "../Bee/Bee.h"
#include "../DifferentBees/SphericalBee.h"
#include "../DifferentBees/RastriginBee.h"
#include "../DifferentBees/RosenbrokBee.h"
#include "../DifferentBees/LeviBee.h"

class Hive {
public:
    Hive(int scout_bee_count, int selected_bee_count, int best_bee_count, int selected_sites_count, int best_sites_count,
         std::vector<double> range, BeeType type);

    int SendBees(const std::vector<double>& position, int idx, int count);

    void Step();

    double get_best_fitness(){
        return best_fitness_;
    }

    void set_range(std::vector<double> range){
        range_ = std::move(range);
    }

    std::vector<double> get_range(){
        return range_;
    }

    std::vector<double> get_best_position(){
        return best_position_;
    }

    std::vector<Bee*> get_best_sites(){
        return best_sites_;
    }

private:
    int scout_bee_count_;
    int selected_bee_count_;
    int best_bee_count_;
    int selected_sites_count_;
    int best_sites_count_;

    BeeType type_;
    std::vector<double> range_;

    std::vector<double>  best_position_;
    double best_fitness_;

    std::vector<Bee*> swarm_;

    std::vector<Bee*> best_sites_;
    std::vector<Bee*> selected_sites_;

    bool BeeWasUsed(Bee* bee);
    void SwarmInfo();
};


#endif //BEESALGO_HIVE_H
