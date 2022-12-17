#include <iostream>
#include <matplot/matplot.h>
#include "Hive/Hive.h"

namespace plt = matplot;

void plot(const std::function<double(double, double)>& objective_func,
          const std::tuple<std::vector<double>, std::vector<double>, std::vector<double>>& data1,
          const std::tuple<std::vector<double>, std::vector<double>, std::vector<double>>& data2,
          int plot_idx){

    auto [X, Y] = plt::meshgrid(plt::linspace(-100, 100, 180), plt::linspace(-100, 100, 180));

    plt::vector_2d Z;
    Z = plt::transform(X, Y, objective_func);

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
    graph->view(45, 60);
    std::string filename = "../plots/plot_" + std::to_string(plot_idx) + ".jpg";
    fig->save(filename);
    graph->clear();
}


void plot_sites(Hive* hive, int count, const std::function<double(double, double)>& objective_func){
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

    plot(objective_func, std::make_tuple(x1, y1, z1), std::make_tuple(x2, y2, z2), count);
}

double (*LeviFunc_)(double, double){
    [](double x, double y){
        return pow(sin(3 * M_PI * x), 2) + pow((x - 1), 2) * (1 + pow(sin(3 * M_PI * y), 2))
               + pow((y - 1), 2) * (1 + pow(sin(2 * M_PI * y), 2));
    }
};

double LeviFunc(std::vector<double> X){
    return LeviFunc_(X[0], X[1]);
}

int main() {
    srand (static_cast <unsigned> (time(nullptr)));

    int scout_bee_count = 300;
    int selected_bee_count =  10;
    int best_bee_count = 30;
    int selected_sites_count = 15;
    int best_sites_count = 5;
    double min_x_pos = -100;
    double max_x_pos = 100;

    int max_iteration = 1000;
    int max_func_counter = 10;
    std::vector<double> koefs = Bee::get_koef_range();
    int func_counter;

    Hive hive(scout_bee_count, selected_bee_count, best_bee_count, selected_sites_count, best_sites_count,
              &LeviFunc, Bee::get_search_range(), min_x_pos, max_x_pos);

    double best_func_val = -1.0e9;
    func_counter = 0;
    int counter = 0;

    for(int i = 0; i < max_iteration; i++){
        hive.Step();

        if(hive.get_best_fitness() != best_func_val){
            best_func_val = hive.get_best_fitness();

            std::cout << "\nIteration number->" << i << std::endl;
            std::cout << "Best position->" << hive.get_best_position()[0] << " " << hive.get_best_position()[1] << std::endl;
            std::cout << "Best fitness->" << hive.get_best_fitness() << std::endl;

            plot_sites(&hive, counter, LeviFunc_);
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

                std::cout << "\n***Iteration number->" << i << std::endl;
                std::cout << "New Range -> " << new_range[0] << " , " << new_range[1] << std::endl;
                std::cout << "Best position->" << hive.get_best_position()[0] << " " << hive.get_best_position()[1] << std::endl;
                std::cout << "Best fitness->" << hive.get_best_fitness() << std::endl;
            }
        }
    }

    return 0;
}