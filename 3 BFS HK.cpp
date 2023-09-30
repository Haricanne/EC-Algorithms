#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
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

    bool aStar(char start, char goal, unordered_map<char, char>& parent) {
        vector<bool> visited(26, false);
        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
        vector<int> gScore(26, INT_MAX);

        pq.push({0, start});
        gScore[start - 'A'] = 0;

        while (!pq.empty()) {
            char current = pq.top().second;
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

                int tentativeGScore = gScore[current - 'A'] + edgeCost;

                if (tentativeGScore < gScore[neighbor - 'A']) {
                    parent[neighbor] = current;
                    gScore[neighbor - 'A'] = tentativeGScore;
                    int fScore = tentativeGScore + heuristic(neighbor, goal);
                    pq.push({fScore, neighbor});
                }
            }
        }

        return false;
    }

private:
    vector<vector<pair<char, int>>> adjList;

    int heuristic(char current, char goal) {
        return abs(current - goal);
    }
};

int main() {
    Graph graph;

    graph.addEdge('S', 'A', 4);
    graph.addEdge('S', 'B', 6);
    graph.addEdge('S', 'C', 3);
    // Add the rest of the edges here...

    char start = 'S';
    char goal = 'G';

    unordered_map<char, char> parent;

    if (graph.aStar(start, goal, parent)) {
        cout << "Path found!" << endl;
        cout << "Path: ";
        while (goal != start) {
            cout << goal << " <- ";
            goal = parent[goal];
        }
        cout << start << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
