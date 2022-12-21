#include <iostream>
#include "Hive/Hive.h"

int main() {
    srand (static_cast <unsigned> (time(nullptr)));

    int scout_bee_count = 50;
    int selected_bee_count = 5;
    int best_bee_count = 10;
    int selected_sites_count = 15;
    int best_sites_count = 10;
    std::vector<double> search_range = {1, 1};
    int stagnation_lim = 10;
    double shrinking_koef = 0.8;


    //Function func(Utils::RastriginFunc, {-5.12, -5.12}, {5.12, 5.12}, Utils::RastriginFunc(0, 0));
    //Function func(Utils::DeJoungFunc, {-50, -50}, {50, 50}, Utils::DeJoungFunc(0, 0));
    //Function func(Utils::RosenbrokFunc, {-1.5, -0.5}, {2, 3}, Utils::RosenbrokFunc(1, 1));
    //Function func(Utils::EgholderFunc, {-512, -512}, {512, 512}, Utils::EgholderFunc(512, 404.2319));
    Function func(Utils::LeviFunc,  {-10, -10}, {10, 10}, Utils::LeviFunc(1, 1));

    Hive hive(scout_bee_count, selected_bee_count, best_bee_count, selected_sites_count, best_sites_count, &func,
              search_range, shrinking_koef, stagnation_lim, true);

    hive.Optimize(1e-6);

    std::cout << "Total iterations nb ->" << hive.get_iteration_amount() << std::endl;
    std::cout.precision(10);
    std::cout << "Bees global min -> " <<  hive.get_best_fitness() << std::endl;
    std::cout << "Real global min -> " <<  func.get_global_min() << std::endl;

    return 0;
}