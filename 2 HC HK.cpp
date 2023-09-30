#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

class Graph {
public:
    Graph() {
        adjList.resize(26);
    }

    void addEdge(char src, char dest, int cost) {
        adjList[src - 'A'].emplace_back(dest, cost);
        adjList[dest - 'A'].emplace_back(src, cost);
    }

    bool hillClimbing(char start, char goal, unordered_map<char, char>& solution) {
        char current = start;

        while (current != goal) {
            char bestNeighbor = '\0';
            int bestCost = INT_MAX;

            for (const auto& edge : adjList[current - 'A']) {
                char neighbor = edge.first;
                int edgeCost = edge.second;

                if (edgeCost < bestCost) {
                    bestNeighbor = neighbor;
                    bestCost = edgeCost;
                }
            }

            if (bestNeighbor == '\0') {
                return false; 
            }

            solution[current] = bestNeighbor;
            current = bestNeighbor;
        }

        return true; 
    }

private:
    vector<vector<pair<char, int>>> adjList;
};

int main() {
    Graph graph;

    graph.addEdge('S', 'A', 4);
    graph.addEdge('S', 'B', 6);
    graph.addEdge('S', 'C', 3);
    // Add the rest of the edges here...

    char start = 'S';
    char goal = 'G';

    unordered_map<char, char> solution;

    if (graph.hillClimbing(start, goal, solution)) {
        cout << "Path found!" << endl;
        cout << "Path: ";
        char current = start;
        while (current != goal) {
            cout << current << " -> ";
            current = solution[current];
        }
        cout << goal << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
