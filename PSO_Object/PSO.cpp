#include "PSO.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include <random>

Particle::Particle(int dimensions, double minPosition, double maxPosition) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minPosition, maxPosition);

    for (int i = 0; i < dimensions; ++i) {
        double pos = dis(gen);
        position.push_back(pos);
        velocity.push_back(0.0);
        bestPosition.push_back(pos);
    }
    bestFitness = std::numeric_limits<double>::max();
}

PSO::PSO(
    int dimensions,
    int swarmSize,
    int maxIterations,
    double minPosition,
    double maxPosition,
    double inertiaWeight,
    double cognitiveCoeff,
    double socialCoeff,
    std::function<double(const std::vector<double>&)> objectiveFunction
)
    : dimensions(dimensions),
    swarmSize(swarmSize),
    maxIterations(maxIterations),
    minPosition(minPosition),
    maxPosition(maxPosition),
    inertiaWeight(inertiaWeight),
    cognitiveCoeff(cognitiveCoeff),
    socialCoeff(socialCoeff),
    objectiveFunction(objectiveFunction),
    globalBestFitness(std::numeric_limits<double>::max())
{
    initializeSwarm();
}

void PSO::initializeSwarm() {
    swarm.clear();
    for (int i = 0; i < swarmSize; ++i) {
        Particle particle(dimensions, minPosition, maxPosition);
        particle.bestFitness = objectiveFunction(particle.position);
        if (particle.bestFitness < globalBestFitness) {
            globalBestFitness = particle.bestFitness;
            globalBestPosition = particle.position;
        }
        swarm.push_back(particle);
    }
}

void PSO::optimize() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int iter = 0; iter < maxIterations; ++iter) {
        for (auto& particle : swarm) {
            updateVelocity(particle);
            updatePosition(particle);

            double fitness = objectiveFunction(particle.position);
            if (fitness < particle.bestFitness) {
                particle.bestFitness = fitness;
                particle.bestPosition = particle.position;
            }
            if (fitness < globalBestFitness) {
                globalBestFitness = fitness;
                globalBestPosition = particle.position;
            }
        }
        // 可选：在此处添加收敛判定或日志输出
    }
}

void PSO::updateVelocity(Particle& particle) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < dimensions; ++i) {
        double r1 = dis(gen);
        double r2 = dis(gen);

        double cognitive = cognitiveCoeff * r1 * (particle.bestPosition[i] - particle.position[i]);
        double social = socialCoeff * r2 * (globalBestPosition[i] - particle.position[i]);
        particle.velocity[i] = inertiaWeight * particle.velocity[i] + cognitive + social;
    }
}

void PSO::updatePosition(Particle& particle) {
    for (int i = 0; i < dimensions; ++i) {
        particle.position[i] += particle.velocity[i];
        // 边界检查
        if (particle.position[i] < minPosition) {
            particle.position[i] = minPosition;
            particle.velocity[i] = 0.0;
        }
        if (particle.position[i] > maxPosition) {
            particle.position[i] = maxPosition;
            particle.velocity[i] = 0.0;
        }
    }
}

std::vector<double> PSO::getBestPosition() const {
    return globalBestPosition;
}

double PSO::getBestFitness() const {
    return globalBestFitness;
}

double PSO::generateRandom(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}
