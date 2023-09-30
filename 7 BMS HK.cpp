#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

class Graph {
public:
    Graph() {
        adjList.resize(26);
    }

    void addEdge(char src, char dest) {
        int srcIndex = src - 'A';
        int destIndex = dest - 'A';
        adjList[srcIndex].emplace_back(dest);
        adjList[destIndex].emplace_back(src);
    }

    bool bfs(char start, char goal, unordered_map<char, char>& parent) {
        vector<bool> visited(26, false);
        queue<char> q;

        q.push(start);

        while (!q.empty()) {
            char current = q.front();
            q.pop();

            if (current == goal) {
                return true;
            }

            if (visited[current - 'A']) {
                continue;
            }

            visited[current - 'A'] = true;

            for (const auto& neighbor : adjList[current - 'A']) {
                if (!visited[neighbor - 'A']) {
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        return false;
    }

private:
    vector<vector<char>> adjList;
};

int main() {
    Graph graph;

    graph.addEdge('S', 'A');
    graph.addEdge('S', 'B');
    graph.addEdge('S', 'C');
    graph.addEdge('A', 'D');
    graph.addEdge('A', 'E');
    graph.addEdge('B', 'F');
    graph.addEdge('B', 'G');
    graph.addEdge('C', 'H');
    graph.addEdge('C', 'J');
    graph.addEdge('G', 'H');
    graph.addEdge('D', 'K');
    graph.addEdge('E', 'M');
    graph.addEdge('F', 'O');
    graph.addEdge('G', 'O');
    graph.addEdge('K', 'M');
    graph.addEdge('M', 'O');
    graph.addEdge('J', 'R');
    graph.addEdge('J', 'T');
    graph.addEdge('R', 'T');

    char start = 'S';
    char goal = 'G';

    unordered_map<char, char> parent;

    if (graph.bfs(start, goal, parent)) {
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
