#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("trenuri.in");
ofstream fout("trenuri.out");

#define NMAX 400005

// Map intre numele orasului si numarul atribuit in graf
unordered_map<string, int> cities;

// Listele de adiacenta a grafului
vector<int> adj[NMAX];

// used[node] = true, daca nodul a fost deja vizitat, false in caz contrar
bool used[NMAX];

// dp[i] = numarul maxim de orase in care putem ajunge din nodul i cu
// extremitate in nodul destinatie (nodul 0).
int dp[NMAX];

void dfs(int node) {
    // Marcam nodul curent ca vizitat
    used[node] = true;

    // Daca am ajuns la nodul destinatie, lungimea este 1
    if (node == 0) {
        dp[node] = 1;
    }

    // Parcurgem toti vecinii nodului
    for (int neighbour : adj[node]) {
        if (!used[neighbour]) {
            dfs(neighbour);
        }

        // Actualizam vectorul dp[]
        dp[node] = max(dp[node], 1 + dp[neighbour]);
    }
}

int main() {
    int m;
    int node = 1;

    string source, destination, x, y;

    // Citim denumirile sursei si a destinatiei
    fin >> source >> destination;

    // Destinatia va fi reprezentata de nodul 0
    cities[destination] = 0;

    // Sursa va fi reprezentata de nodul 1
    cities[source] = 1;

    fin >> m;

    for (int i = 1; i <= m; i++) {
        fin >> x >> y;

        // Daca orasul x nu are deja atribuit un numar de nod
        if (cities.count(x) == 0) {
            node++;
            cities[x] = node;
        }

        // Daca orasul y nu are deja atribuit un numar de nod
        if (cities.count(y) == 0) {
            node++;
            cities[y] = node;
        }

        int nodex = cities[x];
        int nodey = cities[y];

        // Putem ajunge din orasul x in orasul y
        adj[nodex].push_back(nodey);
    }

    // Parcurgem DFS din nodul cu numarul 1 <=> nodul sursa
    dfs(1);

    // Afisam numarul maxim de noduri din nodul 1 cu extremitate in nodul 0
    fout << dp[1] << '\n';

    fin.close();
    fout.close();
    return 0;
}
