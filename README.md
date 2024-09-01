# Proiectarea algoritmilor

Student: Andronache Madalina-Georgiana

Grupa: 322CC

Urmatorul fisier contine informatii despre rezolvarea problemelor propuse in 
tema 2 de la PA.

Cea mai mare provocare intalnita a fost rezolvarea corecta si cat mai eficienta
a problemei propuse intr-un timp cat mai scurt. Aceasta tema a fost rezolvata
pe parcursul a 5 zile: in total am lucrat la aceasta tema 30 h, dintre care 2 h
fiind necesare pentru scrierea fisierului README, iar restul pentru codarea si 
testarea problemelor. In viitor, imi doresc rezolvarea mai rapida a cerintelor. 

Cuprins:
1. Numarare
2. Trenuri
3. Drumuri
4. Scandal

# 1. Numarare

Prima sursa pe care am implementat-o avea o abordare de tip backtracking, 
generand toate aranjamentele multumii de noduri de la {1, ... , n}, avand
pe prima pozitie nodul 1 si pe ultima pozitie nodul n. Adaugam la solutie 
nodul k, doar daca intre ultimul nod al solutiei si nodul k exista muchie 
orientata atat in primul graf, cat si in al doilea. Totusi, aceasta rezolvare 
nu era suficient de buna, deoarce pentru a genera aranjamenetele, foloseam 
recursivitate.

A doua sursa pe care am implementat-o s-a transformat in solutia finala, 
ideea mi-a venit de la articolul de pe `stack overflow` mentionat la resurse
si are urmatoarea abordare: 
1) Facem o sortare topologica a primului graf folosindu-ne de parcurgerea in
adancime (DFS). Functia principala 
`vector<int> topo_sort_dfs(vector<int> adj[])` primeste ca parametru o lista 
de adiacenta si verifica pentru fiecare nod de la 1 la n, daca a fost vizitat 
sau nu. In cazul in care nodul nu a fost inca vizitat, se porneste o 
parcurge DFS din nodul respectiv.
    - Am pornit de la implementarea din laborator a sortarii topologice, insa 
aceasta implementare, folosea DFS recursiv, obtinand doar 10 puncte =(.
    - Dupa ceva debugging, mi-am dat seama ca testele picau deoarece nu mai 
ramanea memorie pe stiva, de aici, venind ideea ce a implementa versiunea
de DFS iterativ. Functia 
`void dfs_iterative(int start, vector<int> &topo_sort, vector<int> adj[])`
primeste ca parametru nodul de `start`, vectorul `topo_sort` si lista de
adiacenta a grafului `adj`. Cu ajutorul acestei functii, obtinem si sortarea
topologica a grafului.
2) Rezultatul sortarii topologice, in ordine inversa, este memorat
in vectorul `topo_sort`. **Sortarea topologica asigura faptul ca, 
pentru orice pereche de noduri (u, v), unde exista o muchie de la u la v, 
atunci, in sortarea topologica u apare inaintea lui v in ordonare.** 
Deci, datorita faptului ca sortarea mea topologica este reversed, 
pentru orice pereche de noduri (u, v), unde exista o muchie de la u la v, in vectorul `topo_sort` v apare inaintea lui u in ordonare. 
Acest vector este procesat mai departe de functia 
`int compute_num_of_paths(vector<int> topo_sort)` care reprezinta o abordare 
folosind metoda programarii dinamice. Initializam vectorul dp cu 0, unde
`dp[i]` reprezinta numarul de lanturi elementare de la i la n.
    - Cazul de baza: nodul este n, `dp[n] = 1;`, exista un singur drum de la 
n la n.
    - Pentru fiecare nod de la 1 la n, parcurse in odinea in care se gasesc in
`topo_sort`, daca exista muchie orientata atat in primul graf, cat si in al doilea
graf (folosim `find` pentru eficienta), actualizam numarul de lanturi elementare
de la nodul `node` la n, folosindu-ne de drumurile existente de la nodul 
`neighbour` pana la n:  `dp[node] += dp[neighbour];`. Calculam 
rezultatul modulo 10^9 + 7.

Complexitatea este:
* *Complexitate temporala*: `O(V + E)` - `V` reprezinta numarul de noduri, 
iar `E` reprezinta numarul de muchii. Aceasta complexitate este data de sortarea
topologica, la care se adauga calcularea numarului de lanturi elementare, care
se face in timp liniar, deoarece iteram prin fiecare nod si fiecare vecin al 
sau.
* *Complexitate spatiala*: `O(V + E)` - deorece pentru stocarea celor doua 
grafuri folosim doua liste de adiacenta `adj1` si `adj2`, la care se adauga 
vectorii `used, topo_sort, dp` de complexitate spatiala `O(V)`. Deci, totalul
ramane `O(V + E)`.

Resurse:
* https://stackoverflow.com/questions/5164719/number-of-paths-between-two-nodes-in-a-dag 
* https://stackoverflow.com/questions/18087559/topological-sort-to-find-the-number-of-paths-to-t
* Implementarea sortarii topologice din laboratorul 6, postate pe 
Teams la resurse.

# 2. Trenuri

Aceasta problema mi-a iesit surprinzator de repede =). Mi-a venit din prima
ideea de a aplica DFS pe graf, iar mai apoi de a combina DFS cu programarea
dinamica. Pot imparti implementarea in 2 parti importante:
1) Transformarea datelor de intrare, numele oraselor intr-un DAG (**Directed 
Acyclic Graph**), pentru care am folosit un `unordered_map<string, int> cities`.
Sursa va fi intotdeauna nodul 1, iar destinatia nodul 0.
2) Aplicarea parcurgerii DFS din nodul sursa, nodul cu numarul 1. In vectorul
`dp[i]` retinem numarul maxim de orase/noduri in care putem ajunge din nodul i
cu extremitate in nodul destinatie (nodul 0).
    - Caz de baza: daca ajungem la destinatie (nodul 0), `dp[node] = 1;`
    - Altfel, pentru fiecare nod, ii parcurgem vecinii si folosim formula:
`dp[node] = max(dp[node], 1 + max(dp[neighbour1], dp[neighbour2], dp[neighbour3]..))`
(Am gasit aceasta idee mentionata pe Stack Overflow).

Complexitatea este:
* *Complexitate temporala*:  `O(V + E)` - `V` reprezinta numarul de noduri, 
iar `E` reprezinta numarul de muchii. Aceasta complexitate este data de 
parcurgerea DFS, moment in care se construieste si vectorul `dp`. 
Operatiile pe unordered_map sunt constante `O(1)`, deci nu influenteaza.
* *Complexitate spatiala*: `O(V + E)` - deoarece pentru stocarea 
grafului folosim o lista de adiacenta `adj`, la care se adauga 
vectorii `used, dp` de complexitate spatiala `O(V)` si map-ul
`unordered_map<string, int> cities;` de complexitate spatiala 
`O(V)`. Deci, totalul ramane `O(V + E)`.

Resurse: 
* https://stackoverflow.com/questions/598174/longest-path-between-from-a-source-to-certain-nodes-in-a-dag

# 3. Drumuri

Rezolvarea acestei probleme a fost destul de straight-forward, deoarece
m-am prins de faptul ca trebuia aplicat un algoritm care sa determine distanta
minima de la o sursa la destinatie. Am ales Dijkstra. Initial, am considerat 
faptul ca distanta minima este chiar suma distantelor de la nodul x la nodul 
z si cea de la nodul y la nodul z. Insa, aceasta sursa lua doar 32 de puncte.
Apoi, mi-a venit ideea de a gasi nodul in care cei doua "trasee" se imbina. 
Astfel, algoritmul final se bazeaza pe urmatoarea idee:
1) Aplic de doua ori algoritmul lui Dijkstra din nodurile x si y pentru a gasi
distantele minime la celelalte noduri ale grafului, folosindu-ma de lista de 
adiacenta a grafului dat initial.
2) Folosindu-ma de lista de adiacenta a grafului inversat ( ***Un arc oarecare de 
la un nod u la un nod v, devine un arc de la v la u*** ), aplic Dijkstra din 
nodul z, astfel afland practic distanta minima de la orice nod al grafului la
nodul z. 
3) Deoarece imi doresc sa determin distanta minima, calculez minimul dintre
`dx[i] + dy[i] + dz[i]` unde i este un nod de la 1 la n (numarul maxim de noduri)
si `dx` si `dy` vectorii de distante aflati din 1), respectiv `dz` vectorul de 
distanta aflat din 2).

Complexitatea este:
* *Complexitate temporala*:  `O((V + E) log V)` - 
`V` reprezinta numarul de noduri, iar `E` reprezinta numarul de muchii. 
Aceasta complexitate este data de aplicarea algoritmului Dijkstra, 
pentru fiecare dintre nodurile x, y, z. Citirea si construirea listelor
de adiacenta sunt `O(E)`, iar calcularea distantei minime `O(V)`.
Complexitatea totala este prin urmare: `O((V + E) log V)`.
* *Complexitate spatiala*: `O(V + E)` - deoarece pentru stocarea 
grafului folosim doua liste de adiacenta `adj` si `adj_rev` 
complexitate `O(E)`, la care se adauga vectorii `dx, dy, dz` de 
complexitate spatiala `O(V)` si coada de prioritati `pq` 
din cadrul functiei 
`vector<long long> dijkstra(int source, vector<pair<int, int>>* adj, int n)`
de complexitate spatiala `O(V)`, deoarece in cazul cel mai nefavorabil are retine
toate nodurile grafului. Deci, totalul ramane `O(V + E)`.

# 4. Scandal

Observatie: in cele ce urmeaza, prin scrierea `!x` ma refer la `x negat`.

Aceasta problema se reduce la a modela graful 2SAT, o idee cunoscuta de la 
cursul de ***Analiza Algoritmilor***, insa destul de greu de deslusit daca 
nu ai experienta asa mare cu programarea competitiva. Este problema la care 
m-am chinuit cel mai mult pana cand sa gasesc tehnica corecta de rezolvare.

Conform cu 2SAT, regulile de tipul (x, y, c) se reduc la:

Concepte de logica: implicatia logica `A -> B`, daca A este adevarat, atunci si B 
este adevarat, este echivalenta cu `!A ∨ B`
* daca c = 0 <=> `x ∨ y` - x sau y participa la petrecere.
* daca c = 1 <=> daca x nu participa, nici y nu participa, are implicatia 
logica `!x -> !y`, echivalenta cu `x ∨ !y`.
* daca c = 2 <=> daca y nu participa, nici x nu participa, analog rezulta
`!x ∨ y`.
* daca c = 3 <=> `!x  ∨ !y` - cel putin unul dintre x si y nu participa.

Din cei n prieteni, vom forma 2 grafuri reprezentate prin liste de adiacenta:
`adj` si `adj_rev` - graful transpus, care vor contine de fapt relatii intre 
2 * n noduri a.i. pentru fiecare nod x sa il putem codifica atat pe `x`, cat si pe
`!x`.

1) Constructia listelor de adiacenta - functia 
`void add_edge(bool nx, int x, bool ny, int y)`: Aleg sa consider ca cele n 
"prietenii" sunt indexate de la 0 la n - 1. Astfel, pentru a putea reprezenta
atat variabilele, cat si negatiile lor, vom avea stari de la 0 
la 2 * n - 1. Pentru o relatie de tipul `x ∨ y` vom adauga in graf 2 muchii, 
una de la (!x, y) si una de la (x, !y). Facem acest lucru atat pentru graful 
normal `adj`, cat si pentru cel transpus `adj_rev`.
2) Aplicam algoritmul lui Kosaraju: `void kosaraju()`
    - Parcurgem DFS graful normal, adaugand in vectorul `traversal_list` nodurile
in ordine inversa a finalizarii DFS. De aici si nevoia de a da `reverse` pe 
acest vector.
    - Aplicam DFS pe graful transpus, urmarind sa respectam ordinea din 
vectorul `traversal_list` si numarand in acelasi timp numarul de componente 
tari conexe.
    - Daca exista doua noduri `x` si `!x` care fac parte din aceeasi componenta
conexa, atunci problema nu este satisfiabila.
    - Pentru fiecare nod de la `0` la `n - 1`, daca valoarea de adevar al nodului
este `true`, atunci nodul face parte din raspuns. Afisam numarul total de invitati
si indicii acestora.

Complexitatea este:
*  *Complexitate temporala*: `O(V + E)` - 
`V` reprezinta numarul de noduri, iar `E` reprezinta numarul de muchii. Aceasta 
complexitate este data de aplicarea algoritmului Kosaraju pentru gasirea 
componentelor tari conexe. Citirea si construirea listelor
de adiacenta sunt `O(E)`, parcurgerea grafului folosind DFS de 2 ori este
`O(V + E)`, iar verificarea satisfiabilitatii si determinarea valorilor 
variabilelor sunt `O(V)`. Complexitatea totala este prin urmare: 
`O(V + E)`.
*  *Complexitate spatiala*: `O(V + E)` - 
Deoarece pentru stocarea grafului 
folosim doua liste de adiacenta `adj` și `adj_rev` cu complexitate `O(E)`,
la care se adaugă vectorii `used, answer, traversal_list, și component_id` de
complexitate spațială `O(V)`. Totalul este `O(V + E)`.

Referinte:
* https://codeforces.com/blog/entry/16205?mobile=true
* https://iq.opengenus.org/kosarajus-algorithm-for-strongly-connected-components/

# Observatii

* Tema destul de draguta, insa bonusul a fost mult mai greu decat la prima 
tema din punctul meu de vedere. 
* Per total, cred ca temele la PA au fost cel mai enjoyable de semestru asta, 
deci:

![alt text](./cat-thumbs-up.gif)
