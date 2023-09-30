#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
public:
    Graph() {
        adjList.resize(26);
    }

    void addEdge(char src, char dest, int cost) {
        int srcIndex = src - 'A';
        int destIndex = dest - 'A';
        adjList[srcIndex].emplace_back(dest, cost);
        adjList[destIndex].emplace_back(src, cost);
    }

    bool beamSearch(char start, char goal, unordered_map<char, char>& parent, int beamWidth) {
        vector<bool> visited(26, false);
        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            char current = pq.top().second;
            int currentCost = pq.top().first;
            pq.pop();

            if (current == goal) {
                return true;
            }

            if (visited[current - 'A']) {
                continue;
            }

            visited[current - 'A'] = true;

            for (const auto& edge : adjList[current - 'A']) {
                char neighbor = edge.first;
                int edgeCost = edge.second;

                if (!visited[neighbor - 'A']) {
                    int newCost = currentCost + edgeCost;
                    pq.emplace(newCost, neighbor);
                    parent[neighbor] = current;
                }
            }
        }

        return false;
    }

private:
    vector<vector<pair<char, int>>> adjList;
};

int main() {
    Graph graph;

    graph.addEdge('S', 'A', 4);
    graph.addEdge('S', 'B', 6);
    graph.addEdge('S', 'C', 3);
    graph.addEdge('A', 'D', 8);
    graph.addEdge('A', 'E', 7);
    graph.addEdge('B', 'F', 4);
    graph.addEdge('B', 'G', 7);
    graph.addEdge('C', 'H', 9);
    graph.addEdge('C', 'J', 8);
    graph.addEdge('G', 'H', 2);
    graph.addEdge('D', 'K', 2);
    graph.addEdge('E', 'M', 5);
    graph.addEdge('F', 'O', 3);
    graph.addEdge('G', 'O', 5);
    graph.addEdge('K', 'M', 1);
    graph.addEdge('M', 'O', 4);
    graph.addEdge('J', 'R', 5);
    graph.addEdge('J', 'T', 4);
    graph.addEdge('R', 'T', 3);

    char start = 'S';
    char goal = 'G';

    unordered_map<char, char> parent;

    int beamWidth = 10; // Set the beam width here

    if (graph.beamSearch(start, goal, parent, beamWidth)) {
        cout << "Path found!" << endl;
        cout << "Path: ";
        char current = goal;
        while (current != start) {
            cout << current << " <- ";
            current = parent[current];
        }
        cout << start << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
