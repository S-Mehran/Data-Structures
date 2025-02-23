//#include <iostream>
//#include <vector>
//#include <queue>
//
//using namespace std;
//
//void addEdge(vector<vector<int>>& adjList, int u, int v) {
//    adjList[u].push_back(v);
//    adjList[v].push_back(u); 
//}
//
//void BFS(int start, vector<bool>& visited, vector<int>& parent, vector<vector<int>>& adjList) {
//    queue<int> q;
//    q.push(start);
//    visited[start] = true;
//
//    while (!q.empty()) {
//        int u = q.front();
//        q.pop();
//
//        cout << u << " ";
//
//        for (int v : adjList[u]) {
//            if (!visited[v]) {
//                visited[v] = true;
//                parent[v] = u;
//                q.push(v);
//            }
//        }
//    }
//}
//
//bool isConnected(vector<vector<int>>& adjList, int N) {
//    vector<bool> visited(N, false);
//    vector<int> parent(N, -1);
//    BFS(0, visited, parent, adjList); 
//
//    for (bool v : visited) {
//        if (!v) {
//            return false;
//        }
//    }
//    return true;
//}
//
//int countConnectedComponents(vector<vector<int>>& adjList, int N) {
//    vector<bool> visited(N, false);
//    vector<int> parent(N, -1);
//    int count = 0;
//
//    for (int i = 0; i < N; i++) {
//        if (!visited[i]) 
//        {
//            BFS(i, visited, parent, adjList);
//            count++;
//        }
//    }
//
//    return count;
//}
//
//void printBFSTree(vector<int>& parent, int root) {
//    for (int i = 1; i < parent.size(); i++) {
//        cout << "Parent: " << parent[i] << ", Child: " << i << endl;
//    }
//}
//
//int main() {
//    int N, E;
//    cout << "Enter the number of vertices: ";
//    cin >> N;
//    cout << "Enter the number of edges: ";
//    cin >> E;
//
//    vector<vector<int>> adjList(N);
//
//    cout << "Enter the 1 edges (u v):\n";
//    for (int i = 0; i < E; i++) {
//        int u, v;
//        cin >> u >> v;
//        addEdge(adjList, u, v);
//    }
//
//    int startVertex;
//    cout << "Enter the starting vertex for BFS: ";
//    cin >> startVertex;
//
//    vector<bool> visited(N, false);
//    vector<int> parent(N, -1); 
//
//    cout << "BFS traversal: ";
//    BFS(startVertex, visited, parent, adjList);
//    cout << endl;
//
//    if (isConnected(adjList, N)) {
//        cout << "The graph is connected." << endl;
//    }
//    else {
//        int components = countConnectedComponents(adjList, N);
//        cout << "The graph has " << components << " connected components." << endl;
//    }
//
//    cout << "BFS Spanning Tree:\n";
//    printBFSTree(parent, startVertex);
//
//    return 0;
//}