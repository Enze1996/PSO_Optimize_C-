//#include "ObjectiveFunction.h"
//#include <cmath>

// 示例目标函数：Sphere Function
//double ObjectiveFunction(const std::vector<double>& variables) {
 //   double sum = 0.0;
 //   for (const auto& x : variables) {
 //       sum += x * x;
 //   }
 //   return sum;

//}


#include "ObjectiveFunction.h"
#include <cmath>
#include <vector>

// 示例目标函数：修改后的复杂目标函数
double ObjectiveFunction(const std::vector<double>& variables) {
    double sum = 0.0;
    for (size_t i = 0; i < variables.size(); ++i) {
        double x = variables[i];
        sum += std::sin(x) * std::exp(-x * x) + std::pow(x, 4) + 0.5 * (x - 1) * (x + 2);
        if (i > 0) {
            sum += 0.1 * x * variables[i - 1];  // 引入变量之间的交叉项
        }
    }
    return sum;
}

