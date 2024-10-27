#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <utility>
using namespace std;

vector<vector<int>> parseInputArray(string s) {
    vector<vector<int>> result;
    vector<int> row;
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] == ',') {
            result.push_back(row);
            row.clear();
        }
        if (isdigit(s[i])) {
            row.push_back(s[i] - '0');
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            row.push_back(s[i] - 'A');
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            row.push_back(s[i] - 'a' + 26);
        }
    }
    result.push_back(row);
    return result;
}

class DisjointSet {
    vector<int> link;
    vector<int> size;

public:
    DisjointSet(int n) {
        link.resize(n, -1);
        size.resize(n, 1);
    }

    int find(int x) {
        if (link[x] == -1) {
            return x;
        }
        link[x] = find(link[x]);
        return link[x];
    }

    void connect(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (size[rootY] > size[rootX]) {
                link[rootX] = rootY;
                size[rootY] += size[rootX];
            } else {
                size[rootX] += size[rootY];
                link[rootY] = rootX;
            }
        }
    }
};

void dfsTraversal(int node, vector<bool>& visited, vector<vector<int>> graph) {
    visited[node] = true;
    for (int i = 0; i < (int)graph.size(); i++) {
        if (graph[node][i] > 0 || graph[i][node] > 0) {
            if (!visited[i]) {
                dfsTraversal(i, visited, graph);
            }
        }
    }
}

bool isConnected(int start, int end, vector<vector<int>> connections) {
    vector<bool> visited(connections.size(), false);
    dfsTraversal(start, visited, connections);
    return visited[start] && visited[end];
}

int calculateMinCost(vector<vector<int>>& network, vector<pair<int, pair<int, int>>>& destroyEdges, vector<pair<int, pair<int, int>>>& buildEdges) {
    DisjointSet ds(network.size());
    int totalCost = 0;

    for (auto edge : destroyEdges) {
        int city1 = edge.second.first, city2 = edge.second.second;
        if (ds.find(city1) != ds.find(city2)) {
            ds.connect(city1, city2);
        } else {
            totalCost += edge.first;
            network[city1][city2] = 0;
            network[city2][city1] = 0;
        }
    }

    for (auto edge : buildEdges) {
        int city1 = edge.second.first;
        int city2 = edge.second.second;
        if (!isConnected(city1, city2, network) && network[city1][city2] == 0) {
            network[city1][city2] = 1;
            network[city2][city1] = 1;
            totalCost += edge.first;
            ds.connect(city1, city2);
        }
    }
    return totalCost;
}

bool descendingSort(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
    return a.first > b.first;
}
bool ascendingSort(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
    return a.first < b.first;
}

int main(void) {
    vector<vector<int>> existingConnections;
    vector<vector<int>> constructionCosts;
    vector<vector<int>> destructionCosts;
    vector<pair<int, pair<int, int>>> edgesToDestroy;
    vector<pair<int, pair<int, int>>> edgesToBuild;
    string line, part;
    vector<string> parsedInputs;
    getline(cin, line);
    stringstream input(line);

    while (getline(input, part, ' ')) {
        parsedInputs.push_back(part);
    }
    existingConnections = parseInputArray(parsedInputs[0]);
    constructionCosts = parseInputArray(parsedInputs[1]);
    destructionCosts = parseInputArray(parsedInputs[2]);

    vector<vector<int>> processedConnections(existingConnections.size(), vector<int>(existingConnections.size(), 0));
    for (int i = 0; i < (int)existingConnections.size(); i++) {
        for (int j = 0; j < (int)existingConnections[i].size(); j++) {
            if (processedConnections[i][j] == 0 && i != j) {
                if (existingConnections[i][j] > 0) {
                    edgesToDestroy.push_back({destructionCosts[i][j], {min(i, j), max(i, j)}});
                } else {
                    edgesToBuild.push_back({constructionCosts[i][j], {min(i, j), max(i, j)}});
                }
                processedConnections[i][j] = 1;
                processedConnections[j][i] = 1;
            }
        }
    }

    sort(edgesToDestroy.begin(), edgesToDestroy.end(), descendingSort);
    sort(edgesToBuild.begin(), edgesToBuild.end(), ascendingSort);
    int result = calculateMinCost(existingConnections, edgesToDestroy, edgesToBuild);

    cout << result << endl;
    return 0;
}
