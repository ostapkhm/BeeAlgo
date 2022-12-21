#ifndef BEESALGO_FUNCTION_H
#define BEESALGO_FUNCTION_H

#include <utility>
#include <vector>
#include <functional>

class Function {
public:
    Function() = default;

    Function(double (*objective_func)(std::vector<double>), int variables_amount,
             const std::vector<double>& min_X, const std::vector<double>& max_X, double global_min):
             objective_func_(objective_func), max_X_(max_X), min_X_(min_X), variables_amount_(variables_amount),
             global_min_(global_min), objective_func_2d_(nullptr){    }


    Function(double (*objective_func_2d)(double, double), const std::vector<double>& min_X,
             const std::vector<double>& max_X, double global_min):
             objective_func_2d_(objective_func_2d), max_X_(max_X), min_X_(min_X), global_min_(global_min){

        variables_amount_ = 2;
        objective_func_ = [this](std::vector<double> X) {return objective_func_2d_(X[0], X[1]);};
    }

    std::vector<double> get_max_X(){
        return max_X_;
    }

    std::vector<double> get_min_X(){
        return min_X_;
    }

    int get_variables_amount(){
        return variables_amount_;
    }

    auto get_objective_func_(){
        return objective_func_;
    }

    auto get_objective_func_2d_(){
        return objective_func_2d_;
    }

    double get_global_min(){
        return global_min_;
    }

private:
    std::function<double(std::vector<double>)> objective_func_;
    std::function<double(double, double)> objective_func_2d_;
    std::vector<double> min_X_;
    std::vector<double> max_X_;
    int variables_amount_;

    double global_min_;
};


#endif //BEESALGO_FUNCTION_H
