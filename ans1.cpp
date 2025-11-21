#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    int V; // number of vertices
    vector<vector<int>> adjMatrix;

public:
    Graph(int vertices) {
        V = vertices;
        adjMatrix.assign(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, bool directed = false) {
        adjMatrix[u][v] = 1;  // weight = 1 for unweighted graph
        if (!directed)
            adjMatrix[v][u] = 1;
    }

    void display() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++)
                cout << adjMatrix[i][j] << " ";
            cout << "\n";
        }
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal starting from node " << start << ": ";
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << " ";

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    int choice;
    while (true) {
        cout << "\n--- BFS Graph Menu ---\n";
        cout << "1. Add Edge\n2. Display Adjacency Matrix\n";
        cout << "3. Perform BFS\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 4) break;

        switch (choice) {
            case 1: {
                int u, v;
                cout << "Enter edge (u v): ";
                cin >> u >> v;
                g.addEdge(u, v);
                break;
            }
            case 2:
                g.display();
                break;
            case 3: {
                int start;
                cout << "Enter start vertex for BFS: ";
                cin >> start;
                g.BFS(start);
                break;
            }
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
