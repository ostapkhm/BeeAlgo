#include "Statistics.h"
#include "../Hive/Hive.h"

Statistics::Statistics(Hive *hive) {
    iteration_nb_ = 0;
    plot_id_ = 0;
    hive_ = hive;
    objective_func_ = hive->get_objective_function();
}

void Statistics::IncreaseIterationAmount() {
    iteration_nb_++;
}

void Statistics::MakePlot() {
    std::vector<double> x1;
    std::vector<double> x2;
    std::vector<double> y1;
    std::vector<double> y2;
    std::vector<double> z1;
    std::vector<double> z2;

    for(auto el:hive_->get_best_sites()){
        x1.push_back(el->get_position()[0]);
        y1.push_back(el->get_position()[1]);
        z1.push_back(el->get_fitness());
    }

    for(auto el:hive_->get_selected_sites()){
        x2.push_back(el->get_position()[0]);
        y2.push_back(el->get_position()[1]);
        z2.push_back(el->get_fitness());
    }

    plot(std::make_tuple(x1, y1, z1), std::make_tuple(x2, y2, z2));
    plot_id_++;
}

void Statistics::plot(const std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> &data1,
                 const std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> &data2) {

    auto [X, Y] = plt::meshgrid(plt::linspace(objective_func_.get_min_X()[0] - 1, objective_func_.get_max_X()[0] + 1, 320),
                                plt::linspace(objective_func_.get_min_X()[1] - 1, objective_func_.get_max_X()[1] + 1, 320));

    plt::vector_2d Z;
    Z = plt::transform(X, Y, objective_func_.get_objective_func_2d_());

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
    std::string filename = "../plots/plot_" + std::to_string(plot_id_) + ".jpg";
    fig->save(filename);
    graph->clear();
}

void Statistics::Info() {
    std::streamsize ss = std::cout.precision();
    std::cout.precision(10);
    std::cout << std::endl;
    std::cout << "Iteration number->" << iteration_nb_ << std::endl;
    std::cout << "Best position->" << hive_->get_best_position()[0] << " " << hive_->get_best_position()[1] << std::endl;
    std::cout << "Best fitness->" << hive_->get_best_fitness() << std::endl;
    std::cout << std::endl;
    std::cout.precision(ss);
}


