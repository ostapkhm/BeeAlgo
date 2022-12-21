#include <iostream>
#include "Hive/Hive.h"

int main() {
    srand (static_cast <unsigned> (time(nullptr)));

    int scout_bee_count = 100;
    int selected_bee_count = 20;
    int best_bee_count = 30;
    int selected_sites_count = 15;
    int best_sites_count = 10;
    std::vector<double> search_range = {50, 50};
    int stagnation_lim = 10;
    double shrinking_koef = 0.92;


    //Function func(RastriginFunc, 2, {-5.12, -5.12}, {5.12, 5.12}, RastriginFunc({0, 0}));
    //Function func(DeJoungFunc, 2, {-50, -50}, {50, 50}, DeJoungFunc({0, 0}));
    //Function func(RosenbrokFunc, 2, {-50, -50}, {50, 50}, RosenbrokFunc({1, 1}));
    Function func(Utils::EgholderFunc, {-512, -512}, {512, 512}, Utils::EgholderFunc(512, 404.2319));
    //Function func(LeviFunc, 2, {-10, -10}, {10, 10}, LeviFunc({1, 1}));

    Hive hive(scout_bee_count, selected_bee_count, best_bee_count, selected_sites_count, best_sites_count, &func,
              search_range, shrinking_koef, stagnation_lim, true);

    hive.Optimize(1e-6);

    std::cout << "Total iterations nb ->" << hive.get_iteration_amount() << std::endl;
    std::cout.precision(10);
    std::cout << "Bees global min -> " <<  hive.get_best_fitness() << std::endl;
    std::cout << "Real global min -> " <<  func.get_global_min() << std::endl;

    return 0;
}