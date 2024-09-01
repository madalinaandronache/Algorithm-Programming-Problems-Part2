#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

ifstream fin("numarare.in");
ofstream fout("numarare.out");

// Numarul maxim de noduri
#define NMAX 100005
#define MOD 1000000007

// Listele de adiacenta ale celor 2 grafuri
vector<int> adj1[NMAX];
vector<int> adj2[NMAX];

// Numarul de noduri ale grafurilor
int n;

// used[node] = 1, daca nodul a fost deja vizitat, 0 in caz contrar
int used[NMAX];

void dfs_iterative(int start, vector<int> &topo_sort, vector<int> adj[]) {
    // Adaugam in stiva nodul pe care dorim sa il procesam
    stack<int> stack;

    // Pornim din nodul start
    stack.push(start);

    while (!stack.empty()) {
        // Extragem elementul din varful stivei
        int node = stack.top();
        stack.pop();

        // Daca nodul nu a fost inca vizitat
        if (!used[node]) {
            // Marcam nodul ca fiind vizitat
            used[node] = 1;

            // Si il adaugam in stiva pentru a fi procesat
            stack.push(node);

            for (int i = 0; i < adj[node].size(); i++) {
                int neighbour = adj[node][i];

                // Daca vecinul de pe pozitia i nu a fost inca procesat
                if (!used[neighbour]) {
                    // Il adaugam in stiva
                    stack.push(neighbour);
                    break;
                }
            }
        } else {
            // Daca nodul a fost deja vizitat, se adauga la rezultat
            topo_sort.push_back(node);
        }
    }

    return;
}

vector<int> topo_sort_dfs(vector<int> adj[]) {
    // Sortarea topologica rezultata, dar in ordine inversa
    vector<int> topo_sort;

    // Pentru fiecare nod din lista de noduri
    for (int node = 1; node <= n; node++) {
        // Daca nodul este nevizitat, pornim o parcurgere DFS
        if (!used[node]) {
            dfs_iterative(node, topo_sort, adj);
        }
    }

    return topo_sort;
}

int compute_num_of_paths(vector<int> topo_sort) {
    int dp[n + 1] = {0};
    dp[n] = 1;

    // Pentru fiecare nod din sortarea topologica reversed
    for (auto &node : topo_sort) {
        // Pentru fiecare vecin al nodului actual
        for (auto &neighbour : adj1[node]) {
            // Daca exista muchie de la (node, neighbour) si in graful numarul 2
            if ((find(adj2[node].begin(), adj2[node].end(), neighbour))
                        != adj2[node].end()) {
                // Actualizam numarul de lanturi elementare
                dp[node] += dp[neighbour];
                dp[node] %= MOD;
            }
        }
    }

    return dp[1];
}

int main() {
    int m, x, y;

    // Citim numarul de noduri si de muchii
    fin >> n >> m;

    // Citim m perechi de noduri (x, y)
    for (int i = 1; i <= m; i++) {
        fin >> x >> y;
        // Adaugam in lista de adiacenta a nodului x, nodul y
        adj1[x].push_back(y);
    }

    // Citim m perechi de noduri (x, y)
    for (int i = 1; i <= m; i++) {
        fin >> x >> y;
        // Adaugam in lista de adiacenta a nodului x, nodul y
        adj2[x].push_back(y);
    }
    // Calculam sortarea topologica a primului graf
    vector<int> topo_sort = topo_sort_dfs(adj1);

    // Afisam numarul de lanturi elementare de la nodul 1 la n
    fout << compute_num_of_paths(topo_sort) << '\n';

    fin.close();
    fout.close();
    return 0;
}
