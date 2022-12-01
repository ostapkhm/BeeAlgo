#include <iostream>
#include <utility>
#include <matplot/matplot.h>
#include "Hive/Hive.h"

namespace plt = matplot;

void plot(std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> data, BeeType type, int plot_idx){
    auto [X, Y] = plt::meshgrid(plt::linspace(-100, 100, 180), plt::linspace(-100, 100, 180));

    plt::vector_2d Z;

    if(type == BeeType::kRastrigin){
        Z = plt::transform(X, Y, [](double x, double y) {
            return 10 * 2 + (x*x - 10*cos(2 * plt::pi * x)) + (y*y - 10*cos(2 * plt::pi * y));
        });
    }

    if(type == BeeType::kRosenbrok){
        Z = plt::transform(X, Y, [](double x, double y) {
            return 100 * pow((y - x*x), 2) + pow(x - 1, 2);
        });
    }

    if(type == BeeType::kLeviBee){
        Z = plt::transform(X, Y, [](double x, double y) {
            return pow(sin(3 * M_PI * x), 2) + pow((x - 1), 2) * (1 + pow(sin(3 * M_PI * y), 2))
                   + pow((y - 1), 2) * (1 + pow(sin(2 * M_PI * y), 2));
        });
    }


    auto [x, y, z] = std::move(data);

    matplot::figure_handle fig = matplot::figure(false);
    fig->size(1720,1080);

    auto graph = fig->current_axes();
    graph->colororder(std::vector<std::string> {"magenta"});

    graph->hold(plt::on);
    graph->surf(X, Y, Z);
    graph->scatter3(x, y, z, "filled");
    graph->hold(plt::off);
    graph->view(45, 60);
    std::string filename = "../plots/plot_" + std::to_string(plot_idx) + ".jpg";
    fig->save(filename);
    graph->clear();
}


void plot_best_sites(Hive* hive, BeeType type, int count){
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;

    for(auto el:hive->get_best_sites()){
        x.push_back(el->get_position()[0]);
        y.push_back(el->get_position()[1]);
        z.push_back(el->get_fitness());
    }

    plot(std::make_tuple(x, y, z), type, count);
    x.clear();
    y.clear();
    z.clear();
}


int main() {
    srand (static_cast <unsigned> (time(nullptr)));

    int scout_bee_count = 300;
    int selected_bee_count =  10;
    int best_bee_count = 30;
    int selected_sites_count = 15;
    int best_sites_count = 5;
    BeeType type = BeeType::kLeviBee;

    int max_iteration = 1000;
    int max_func_counter = 10;
    std::vector<double> koefs = LeviBee::get_koef_range();
    int func_counter;

    Hive hive(scout_bee_count, selected_bee_count, best_bee_count, selected_sites_count, best_sites_count,
              LeviBee::get_start_range(), type);


    double best_func_val = -1.0e9;
    func_counter = 0;
    int counter = 0;

    hive.Step();

    for(int i = 0; i < max_iteration; i++){
        hive.Step();

        if(hive.get_best_fitness() != best_func_val){
            best_func_val = hive.get_best_fitness();

            std::cout << "\nIteration number->" << i << std::endl;
            std::cout << "Best position->" << hive.get_best_position()[0] << " " << hive.get_best_position()[1] << std::endl;
            std::cout << "Best fitness->" << hive.get_best_fitness() << std::endl;
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

                std::cout << "\n***Iteration number->" << i << std::endl;
                std::cout << "New Range -> " << new_range[0] << " , " << new_range[1] << std::endl;
                std::cout << "Best position->" << hive.get_best_position()[0] << " " << hive.get_best_position()[1] << std::endl;
                std::cout << "Best fitness->" << hive.get_best_fitness() << std::endl;
            }
        }

        if(i % 200 == 0){
            plot_best_sites(&hive, type, counter);
            counter++;
        }
    }

    return 0;
}