#include <iostream>
#include <iomanip>

#include <matplot/matplot.h>
#include "Hive/Hive.h"

namespace plt = matplot;

void plot(Function* func,
          const std::tuple<std::vector<double>, std::vector<double>, std::vector<double>>& data1,
          const std::tuple<std::vector<double>, std::vector<double>, std::vector<double>>& data2,
          int plot_idx){

    auto [X, Y] = plt::meshgrid(plt::linspace(func->get_min_X()[0] - 1, func->get_max_X()[0] + 1, 320),
                                plt::linspace(func->get_min_X()[1] - 1, func->get_max_X()[1] + 1, 320));

    plt::vector_2d Z;
    Z = plt::transform(X, Y, func->get_objective_func_2d_());

    auto [x1, y1, z1] = data1;
    auto [x2, y2, z2] = data2;

    matplot::figure_handle fig = matplot::figure(true);
    fig->size(1720,1080);

    auto graph = fig->current_axes();
    graph->colororder(std::vector<std::string> {"red", "green"});

    graph->hold(plt::on);
    graph->surf(X, Y, Z);
    graph->colormap(plt::palette::winter());
    graph->scatter3(x1, y1, z1, "filled");
    graph->scatter3(x2, y2, z2, "filled");
    graph->hold(plt::off);
    graph->view(55, 65);
    std::string filename = "../plots/plot_" + std::to_string(plot_idx) + ".jpg";
    fig->save(filename);
    graph->clear();
}


void plot_sites(Hive* hive, int count, Function* func){
    std::vector<double> x1;
    std::vector<double> x2;
    std::vector<double> y1;
    std::vector<double> y2;
    std::vector<double> z1;
    std::vector<double> z2;

    for(auto el:hive->get_best_sites()){
        x1.push_back(el->get_position()[0]);
        y1.push_back(el->get_position()[1]);
        z1.push_back(el->get_fitness());
    }

    for(auto el:hive->get_selected_sites()){
        x2.push_back(el->get_position()[0]);
        y2.push_back(el->get_position()[1]);
        z2.push_back(el->get_fitness());
    }

    plot(func, std::make_tuple(x1, y1, z1), std::make_tuple(x2, y2, z2), count);
}

int main() {
    srand (static_cast <unsigned> (time(nullptr)));

    int scout_bee_count = 60;
    int selected_bee_count = 20;
    int best_bee_count = 30;
    int selected_sites_count = 15;
    int best_sites_count = 10;
    std::vector<double> search_range = {60, 60};



    //Function func(RastriginFunc, 2, {-5.12, -5.12}, {5.12, 5.12}, RastriginFunc({0, 0}));
    //Function func(DeJoungFunc, 2, {-50, -50}, {50, 50}, DeJoungFunc({0, 0}));
    //Function func(RosenbrokFunc, 2, {-50, -50}, {50, 50}, RosenbrokFunc({1, 1}));
    Function func(Utils::EgholderFunc, {-512, -512}, {512, 512}, Utils::EgholderFunc(512, 404.2319));
    //Function func(LeviFunc, 2, {-10, -10}, {10, 10}, LeviFunc({1, 1}));

    Hive hive(scout_bee_count, selected_bee_count, best_bee_count, selected_sites_count, best_sites_count, &func, search_range);

    int max_func_counter = 10;
    int func_counter = 0;
    std::vector<double> koefs = {0.9, 0.9};

    double best_func_val = 1.0e9;
    int counter = 0;

    double eps = 1e-6;
    int iteration_nb = 0;

    while(std::abs(best_func_val - func.get_global_min()) > eps){
        hive.Step();

        if(hive.get_best_fitness() != best_func_val){
            best_func_val = hive.get_best_fitness();
            std::cout << "\nIteration number->" << iteration_nb << std::endl;
            std::cout.precision(10);
            std::cout << "Best position->" << hive.get_best_position()[0] << " " << hive.get_best_position()[1] << std::endl;
            std::cout << "Best fitness->" <<  hive.get_best_fitness() << std::endl;

            plot_sites(&hive, counter, &func);
            counter++;
        }
        else{
            func_counter += 1;

            if(func_counter == max_func_counter){
                std::vector<double> new_range;
                std::vector<double> old_range = hive.get_range();

                for(int k = 0; k < old_range.size(); k++){
                    new_range.push_back(old_range[k] * koefs[k]);
                }

                hive.set_range(new_range);
                func_counter = 0;

                std::cout << "\n***Iteration number->" << iteration_nb << std::endl;
                std::cout << "New Range -> " << new_range[0] << " , " << new_range[1] << std::endl;
                std::cout.precision(10);
                std::cout << "Best position->" << hive.get_best_position()[0] << " " << hive.get_best_position()[1] << std::endl;
                std::cout << "Best fitness->" << hive.get_best_fitness() << std::endl;
            }
        }
        iteration_nb++;
    }

    std::cout << std::endl;
    std::cout << "Total iteration nb->" << iteration_nb << std::endl;
    std::cout.precision(10);
    std::cout << "Real global min -> " <<  func.get_global_min() << std::endl;

    return 0;
}