#ifndef BEESALGO_STATISTICS_H
#define BEESALGO_STATISTICS_H

#include "matplot/matplot.h"
#include "../Function.h"

namespace plt = matplot;

class Hive;

class Statistics {
public:
    Statistics(Hive* hive);

    void Info();
    void MakePlot();
    void IncreaseIterationAmount();

    int get_iteration_amount(){
        return iteration_nb_;
    }

private:
    int iteration_nb_;
    int plot_id_;
    Hive* hive_;
    Function objective_func_;

    void plot(const std::tuple<std::vector<double>, std::vector<double>, std::vector<double>>& data1,
              const std::tuple<std::vector<double>, std::vector<double>, std::vector<double>>& data2);
};


#endif //BEESALGO_STATISTICS_H
