#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
#include <math.h>

using namespace std;

const int NUM_CITIES = 5;
const int NUM_ANTS = 10;
const double ALPHA = 1.0;   // Pheromone importance
const double BETA = 2.0;    // Distance importance
const double RHO = 0.5;     // Pheromone evaporation rate
const double Q = 100.0;     // Pheromone deposit factor

class City {
public:
    double x, y;
};

class Ant {
public:
    vector<int> tour;
    double tourLength;

    Ant() : tourLength(0.0) {}
};

double distance(const City& city1, const City& city2) {
    double dx = city1.x - city2.x;
    double dy = city1.y - city2.y;
    return sqrt(dx * dx + dy * dy);
}

void initializePheromone(vector<vector<double>>& pheromone) {
    int numCities = pheromone.size();
    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numCities; ++j) {
            pheromone[i][j] = 0.1;  // Initial pheromone level
        }
    }
}

int selectNextCity(const Ant& ant, const vector<vector<double>>& pheromone, const vector<City>& cities) {
    int currentCity = ant.tour.back();
    double totalProbability = 0.0;
    vector<double> probabilities;

    for (size_t i = 0; i < cities.size(); ++i) {
        if (find(ant.tour.begin(), ant.tour.end(), i) == ant.tour.end()) {
            double pheromoneFactor = pow(pheromone[currentCity][i], ALPHA);
            double distanceFactor = pow(1.0 / distance(cities[currentCity], cities[i]), BETA);
            double probability = pheromoneFactor * distanceFactor;
            probabilities.push_back(probability);
            totalProbability += probability;
        } else {
            probabilities.push_back(0.0);
        }
    }

    // Select the next city using roulette wheel selection
    double random = (static_cast<double>(rand()) / RAND_MAX) * totalProbability;
    double sum = 0.0;
    for (size_t i = 0; i < probabilities.size(); ++i) {
        sum += probabilities[i];
        if (sum >= random) {
            return i;
        }
    }

    // In case of rounding errors, return the first unvisited city
    for (size_t i = 0; i < cities.size(); ++i) {
        if (find(ant.tour.begin(), ant.tour.end(), i) == ant.tour.end()) {
            return i;
        }
    }

    return -1;  // All cities visited
}

void antColonyOptimization(vector<City>& cities, vector<vector<double>>& pheromone) {
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<Ant> ants(NUM_ANTS);
    Ant bestAnt;
    bestAnt.tourLength = numeric_limits<double>::max();

    for (int iteration = 0; iteration < 1000; ++iteration) {
        for (auto& ant : ants) {
            ant.tour.clear();
            ant.tourLength = 0.0;
        }

        for (size_t i = 0; i < cities.size(); ++i) {
            for (auto& ant : ants) {
                if (ant.tour.empty()) {
                    ant.tour.push_back(rand() % cities.size());  // Start from a random city
                } else {
                    int nextCity = selectNextCity(ant, pheromone, cities);
                    ant.tour.push_back(nextCity);
                    ant.tourLength += distance(cities[ant.tour[ant.tour.size() - 2]], cities[nextCity]);
                }
            }
        }

        // Update the best ant's tour
        for (const auto& ant : ants) {
            if (ant.tourLength < bestAnt.tourLength) {
                bestAnt = ant;
            }
        }

        // Update pheromone levels
        for (size_t i = 0; i < cities.size(); ++i) {
            for (size_t j = 0; j < cities.size(); ++j) {
                pheromone[i][j] *= (1.0 - RHO);  // Evaporation
            }
        }

        for (size_t i = 1; i < bestAnt.tour.size(); ++i) {
            int city1 = bestAnt.tour[i - 1];
            int city2 = bestAnt.tour[i];
            pheromone[city1][city2] += (Q / bestAnt.tourLength);  // Pheromone deposit
        }
    }

    // Output the best tour found
    cout << "Best Tour: ";
    for (int city : bestAnt.tour) {
        cout << city << " ";
    }
    cout << endl;
    cout << "Best Tour Length: " << bestAnt.tourLength << endl;
}

int main() {
    vector<City> cities(NUM_CITIES);
    vector<vector<double>> pheromone(NUM_CITIES, vector<double>(NUM_CITIES));

    // Initialize cities (you can provide your own coordinates)
    cities[0].x = 0.0; cities[0].y = 0.0;
    cities[1].x = 1.0; cities[1].y = 2.0;
    cities[2].x = 2.0; cities[2].y = 1.0;
    cities[3].x = 3.0; cities[3].y = 3.0;
    cities[4].x = 4.0; cities[4].y = 2.0;

    initializePheromone(pheromone);
    antColonyOptimization(cities, pheromone);

    return 0;
}