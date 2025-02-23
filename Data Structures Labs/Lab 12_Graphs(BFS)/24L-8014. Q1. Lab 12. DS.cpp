#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adjList;

    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) 
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": ";
            for (int j = 0; j < adjList[i].size(); j++) {
                cout << adjList[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isEdge(int u, int v) {
        for (int i = 0; i < adjList[u].size(); i++) {
            if (adjList[u][i] == v) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

 
    Graph g(V);

    cout << "Enter edges (u v format):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        if (u >= V || v >= V) {
            cout << "Invalid edge: Vertices must be within the graph's range.\n";
            i--;
            continue;
        }
        g.addEdge(u, v);
    }

    g.printGraph();

    cout << "Enter vertices (u v) to check edge existence: ";
    int u, v;
    cin >> u >> v;
    if (g.isEdge(u, v)) {
        cout << "Edge exists between " << u << " and " << v << endl;
    }
    else {
        cout << "Edge does not exist between " << u << " and " << v << endl;
    }

    return 0;
}