#ifndef PSO_H
#define PSO_H

#include <vector>
#include <functional>

class Particle {
public:
    std::vector<double> position;
    std::vector<double> velocity;
    std::vector<double> bestPosition;
    double bestFitness;

    Particle(int dimensions, double minPosition, double maxPosition);
};

class PSO {
public:
    PSO(
        int dimensions,
        int swarmSize,
        int maxIterations,
        double minPosition,
        double maxPosition,
        double inertiaWeight,
        double cognitiveCoeff,
        double socialCoeff,
        std::function<double(const std::vector<double>&)> objectiveFunction
    );

    void optimize();
    std::vector<double> getBestPosition() const;
    double getBestFitness() const;

private:
    int dimensions;
    int swarmSize;
    int maxIterations;
    double minPosition;
    double maxPosition;
    double inertiaWeight;
    double cognitiveCoeff;
    double socialCoeff;
    std::function<double(const std::vector<double>&)> objectiveFunction;

    std::vector<Particle> swarm;
    std::vector<double> globalBestPosition;
    double globalBestFitness;

    void initializeSwarm();
    void updateVelocity(Particle& particle);
    void updatePosition(Particle& particle);
    double generateRandom(double min, double max);
};

#endif // PSO_H
#pragma once
