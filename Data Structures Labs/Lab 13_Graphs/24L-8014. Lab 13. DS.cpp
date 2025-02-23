#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
    int V; 
    vector<list<int>> adj; 

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    void DFSHelp(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSHelp(neighbor, visited);
            }
        }
    }


    void DFS() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                DFSHelp(i, visited);
                cout << endl;
            }
        }
    }

    bool isCyclicUtil(int v, vector<bool>& visited, int parent) {
        visited[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                if (isCyclicUtil(neighbor, visited, v)) {
                    return true;
                }
            } else if (neighbor != parent) {
                return true; 
            }
        }

        return false;
    }

    bool isCyclic() {
        vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                if (isCyclicUtil(i, visited, -1)) {
                    return true;
                }
            }
        }

        return false;
    }

    void spanningTree() {
        vector<bool> visited(V, false);
        int edges[V - 1][2]; 
        int edgeCount = 0;

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                constructSpanningTree(i, visited, edges, edgeCount);
            }
        }

        cout << "Spanning Tree Edges:\n";
        for (int i = 0; i < edgeCount; ++i) {
            cout << edges[i][0] << " - " << edges[i][1] << endl;
        }
    }

private:

    void constructSpanningTree(int v, vector<bool>& visited, int edges[][2], int& edgeCount) {
        visited[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                edges[edgeCount][0] = v;
                edges[edgeCount][1] = neighbor;
                edgeCount++;
                constructSpanningTree(neighbor, visited, edges, edgeCount);
            }
        }
    }
};

int main() {

    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(1, 4);
    g1.addEdge(3, 4);

    cout << "\nDFS Traversal:\n";
    g1.DFS();

    cout << "\nCycle Detection:\n";
    if (g1.isCyclic()) {
        cout << "Graph contains a cycle.\n";
    } else {
        cout << "Graph does not contain a cycle.\n";
    }

    cout << "\nSpanning Tree:\n";
    g1.spanningTree();

    return 0;
}

