#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <set>

using namespace std;

ifstream fin("drumuri.in");
ofstream fout("drumuri.out");

#define NMAX 100005
#define INF (1LL << 60)

// Lista de adiacenta a grafului dat
vector<pair<int, int>> adj[NMAX];

// Lista de adiacenta a grafului transpus
vector<pair<int, int>> adj_rev[NMAX];

vector<long long> dijkstra(int source, vector<pair<int, int>>* adj, int n) {
    // Vectorul de distante
    vector<long long> d(n + 1, INF);
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;

    // Distanta de la sursa la ea insasi este 0
    d[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;

        pq.pop();

        if (dist > d[node])
            continue;

        for (auto &[neighbour, weight] : adj[node]) {
            if (d[node] + weight < d[neighbour]) {
                d[neighbour] = d[node] + weight;

                pq.push({d[neighbour], neighbour});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (d[i] == INF) {
            d[i] = -1;
        }
    }

    return d;
}

int main() {
    int n, m, x, y, z;
    vector<long long> dx, dy, dz;

    fin >> n >> m;
    for (int i = 1; i <= m; i++) {
        fin >> x >> y >> z;

        // Construim lista de adiacenta
        adj[x].push_back({y, z});

        // Si lista de adiacenta inversata
        adj_rev[y].push_back({x, z});
    }

    fin >> x >> y >> z;

    // Determinam pentru nodurile x si y, vectorul de distante al grafului dat
    dx = dijkstra(x, adj, n);
    dy = dijkstra(y, adj, n);

    // Determinam pentru nodul z, vectorul de distante al grafului inversat
    dz = dijkstra(z, adj_rev, n);

    // Distanta minima initiala este, suma distantelor de la x la z si y la z
    long long Min = dx[z] + dy[z];

    for (int i = 1; i <= n; ++i) {
        // Daca exista drum de la x la i, y la i si i la z
        if (dx[i] != -1 && dy[i]!= -1 && dz[i]!= -1) {
            Min = min(Min, dx[i] + dy[i] + dz[i]);
        }
    }

    // Afisam distanta minima determinata
    fout << Min << '\n';

    fin.close();
    fout.close();

    return 0;
}
