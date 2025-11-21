#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int vertices) {
        V = vertices;
        adjMatrix.assign(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int w, bool directed = false) {
        adjMatrix[u][v] = w;
        if (!directed)
            adjMatrix[v][u] = w;
    }

    void display() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++)
                cout << adjMatrix[i][j] << " ";
            cout << "\n";
        }
    }

    void Dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);
        dist[src] = 0;

        for (int count = 0; count < V; count++) {
            int u = -1;
            int minDist = INT_MAX;
            for (int i = 0; i < V; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }

            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !visited[v] && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                }
            }
        }

        cout << "Shortest distances from node " << src << ":\n";
        for (int i = 0; i < V; i++)
            cout << "Node " << i << " : " << dist[i] << endl;
    }
};

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    int choice;
    while (true) {
        cout << "\n--- Dijkstra Menu ---\n";
        cout << "1. Add Edge\n2. Display Adjacency Matrix\n";
        cout << "3. Compute Dijkstra's Shortest Path\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 4) break;

        switch (choice) {
            case 1: {
                int u, v, w;
                cout << "Enter edge (u v weight): ";
                cin >> u >> v >> w;
                g.addEdge(u, v, w);
                break;
            }
            case 2:
                g.display();
                break;
            case 3: {
                int src;
                cout << "Enter source vertex: ";
                cin >> src;
                g.Dijkstra(src);
                break;
            }
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
