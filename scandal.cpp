#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("scandal.in");
ofstream fout("scandal.out");

// Numarul maxim de noduri
#define NMAX 100005
#define FLAG -1

// Listele de adiacenta ale celor 2 grafuri
vector<int> adj[(NMAX << 1)];
vector<int> adj_rev[(NMAX << 1)];

int n;

vector<bool> used = {}, answer = {};
vector<int> traversal_list = {}, component_id = {};

void init(int value_n) {
    // Numarul total de noduri este 2 * n
    n = (value_n << 1);

    for (int i = 0; i < n; ++i) {
        used.push_back(false);
        answer.push_back(false);
        component_id.push_back(FLAG);
    }

    return;
}

void add_edge(bool nx, int x, bool ny, int y) {
    // Aflam indicii corespunzatori, in functie
    // de starile nx si ny (daca sunt negati sau nu)
    x = (nx ^ (x << 1));
    y = (ny ^ (y << 1));

    // Negam pentru a obtine !x si !y
    int negate_x = (x ^ 1);
    int negate_y = (y ^ 1);

    // Adaugam muchiile in graf (x ∨ y)
    adj[negate_x].push_back(y);
    adj[negate_y].push_back(x);

    // Adaugam muchiile in graful transpus
    adj_rev[y].push_back(negate_x);
    adj_rev[x].push_back(negate_y);
}

// Parcurgere DFS a grafului
void dfs(int node) {
    // Marcam nodul curent ca vizitat
    used[node] = true;

    // Pentru fiecare vecin al nodului curent
    for (auto &neighbour : adj[node]) {
        // Daca nodul nu a fost inca vizitat
        if (!used[neighbour]) {
            dfs(neighbour);
        }
    }

    // Adaugam nodul in lista de noduri parcurse
    traversal_list.push_back(node);

    return;
}

// Parcurgere DFS a grafului transpus
void dfs_t(int node, int idx) {
    // Adaugam nodul in componenta tare conexa cu numarul idx
    component_id[node] = idx;

    for (auto &neighbour : adj_rev[node]) {
        // Daca nodul nu a fost deja adaugat intr-o componenta tare conexa
        if (component_id[neighbour] == FLAG) {
            dfs_t(neighbour, idx);
        }
    }

    return;
}

void kosaraju() {
    // Aplicam DFS pe graful normal
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }

    // Inversam vectorul de noduri parcurse
    reverse(traversal_list.begin(), traversal_list.end());

    int curr_id = 0;

    // Aplicam DFS pe graful transpus, calculand si numarul de
    // componente tari conexe
    for (int i = 0; i < n; ++i) {
        int node = traversal_list[i];
        // Daca nodul nu a fost deja adaugat intr-o componenta tare conexa
        if (component_id[node] == FLAG) {
            // Crestem numarul de componente
            curr_id++;
            dfs_t(node, curr_id);
        }
    }

    for (int i = 0; i < n; i += 2) {
        // Pentru fiecare nod i de la 0 la n, se verifica daca i si !i fac
        // parte din componente tari conexe diferite
        if (component_id[i] != component_id[(i + 1)]) {
            // Determinam daca variabila i / 2 este adevarata sau falsa
            answer[(i >> 1)] = (component_id[(i + 1)] < component_id[i]);
        } else {
            // Expresia este nesatisfiabila
            return;
        }
    }

    vector<int> satisfied_var = {};

    // Pentru fiecare nod de la 0 la n - 1
    for (int i = 0; i < (n >> 1); ++i) {
        // Daca are valoarea true, este parte din raspuns
        if (answer[i]) {
            satisfied_var.push_back((i + 1));
        }
    }

    // Afisam numarul de invitati la petrecere
    fout << (int)satisfied_var.size() << '\n';

    // Afisam nr. de ordine ale invitatilor invitatii
    for (auto &node : satisfied_var) {
        fout << node << '\n';
    }
    return;
}

int main() {
    int n, m, x, y, c;

    fin >> n >> m;

    init(n);

    for (int i = 1; i <= m; ++i) {
        fin >> x >> y >> c;

        // Determinam daca termenul x sau y trebuie negat
        bool negate_x = false, negate_y = false;

        if (c == 1) {
            negate_y = true;
        } else if (c == 2) {
            negate_x = true;
        } else if (c == 3) {
            negate_x = negate_y = true;
        }

        // Consideram nodurile grafului indexate de la 0.
        x--;
        y--;

        // Contruim listele de adiacenta ale grafului normal si
        // ale grafului transpus
        add_edge(negate_x, x, negate_y, y);
    }

    kosaraju();

    fin.close();
    fout.close();
    return 0;
}
