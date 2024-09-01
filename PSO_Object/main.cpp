#include <iostream>
#include "PSO.h"
#include "ObjectiveFunction.h"

int main() {
    // 问题维度，即参数个数
    const int dimensions = 3;

    // PSO参数设置
    int swarmSize = 30;           // 粒子数量
    int maxIterations = 100;      // 最大迭代次数
    double minPosition = -10.0;   // 搜索空间最小值
    double maxPosition = 10.0;    // 搜索空间最大值
    double inertiaWeight = 0.7;   // 惯性权重
    double cognitiveCoeff = 1.5;  // 认知系数
    double socialCoeff = 1.5;     // 社会系数

    // 创建PSO优化器
    PSO optimizer(
        dimensions,
        swarmSize,
        maxIterations,
        minPosition,
        maxPosition,
        inertiaWeight,
        cognitiveCoeff,
        socialCoeff,
        ObjectiveFunction // 目标函数
    );

    // 运行优化
    optimizer.optimize();

    // 输出最优解
    std::cout << "Best Position: ";
    for (const auto& value : optimizer.getBestPosition()) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    std::cout << "Best Fitness: " << optimizer.getBestFitness() << std::endl;

    return 0;
}
