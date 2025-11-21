#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Graph {
    int V; // number of vertices
    vector<vector<int>> adjMatrix;

public:
    Graph(int vertices) {
        V = vertices;
        adjMatrix.assign(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w; // undirected graph
    }

    void display() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++)
                cout << adjMatrix[i][j] << " ";
            cout << "\n";
        }
    }

    /*----------------- Prim's MST --------------------*/
    void PrimMST() {
        vector<int> key(V, INT_MAX);
        vector<int> parent(V, -1);
        vector<bool> inMST(V, false);
        key[0] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = -1;
            int minKey = INT_MAX;
            for (int i = 0; i < V; i++) {
                if (!inMST[i] && key[i] < minKey) {
                    minKey = key[i];
                    u = i;
                }
            }

            inMST[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        cout << "Prim's MST edges (u - v : weight):\n";
        int totalWeight = 0;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " : " << adjMatrix[i][parent[i]] << endl;
            totalWeight += adjMatrix[i][parent[i]];
        }
        cout << "Total weight: " << totalWeight << endl;
    }

    /*----------------- Kruskal's MST ----------------*/
    struct Edge {
        int u, v, w;
        bool operator<(const Edge& other) const {
            return w < other.w;
        }
    };

    int findParent(int u, vector<int>& parent) {
        if (parent[u] != u)
            parent[u] = findParent(parent[u], parent);
        return parent[u];
    }

    void KruskalMST() {
        vector<Edge> edges;

        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (adjMatrix[i][j] != 0)
                    edges.push_back({i, j, adjMatrix[i][j]});
            }
        }

        sort(edges.begin(), edges.end());

        vector<int> parent(V);
        for (int i = 0; i < V; i++)
            parent[i] = i;

        vector<Edge> mst;
        int totalWeight = 0;

        for (Edge e : edges) {
            int uParent = findParent(e.u, parent);
            int vParent = findParent(e.v, parent);
            if (uParent != vParent) {
                mst.push_back(e);
                totalWeight += e.w;
                parent[uParent] = vParent;
            }
        }

        cout << "Kruskal's MST edges (u - v : weight):\n";
        for (auto e : mst)
            cout << e.u << " - " << e.v << " : " << e.w << endl;
        cout << "Total weight: " << totalWeight << endl;
    }
};

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    int choice;
    while (true) {
        cout << "\n--- MST Menu ---\n";
        cout << "1. Add Edge\n2. Display Adjacency Matrix\n";
        cout << "3. Prim's MST\n4. Kruskal's MST\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 5) break;

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
            case 3:
                g.PrimMST();
                break;
            case 4:
                g.KruskalMST();
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
