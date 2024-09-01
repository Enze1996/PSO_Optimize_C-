#include <iostream>
#include "PSO.h"
#include "ObjectiveFunction.h"

int main() {
    // ����ά�ȣ�����������
    const int dimensions = 3;

    // PSO��������
    int swarmSize = 30;           // ��������
    int maxIterations = 100;      // ����������
    double minPosition = -10.0;   // �����ռ���Сֵ
    double maxPosition = 10.0;    // �����ռ����ֵ
    double inertiaWeight = 0.7;   // ����Ȩ��
    double cognitiveCoeff = 1.5;  // ��֪ϵ��
    double socialCoeff = 1.5;     // ���ϵ��

    // ����PSO�Ż���
    PSO optimizer(
        dimensions,
        swarmSize,
        maxIterations,
        minPosition,
        maxPosition,
        inertiaWeight,
        cognitiveCoeff,
        socialCoeff,
        ObjectiveFunction // Ŀ�꺯��
    );

    // �����Ż�
    optimizer.optimize();

    // ������Ž�
    std::cout << "Best Position: ";
    for (const auto& value : optimizer.getBestPosition()) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    std::cout << "Best Fitness: " << optimizer.getBestFitness() << std::endl;

    return 0;
}
