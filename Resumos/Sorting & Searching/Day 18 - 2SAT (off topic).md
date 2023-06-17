# Day 18 - 2SAT (off topic)

## Reading
CP-Algorithms: https://cp-algorithms.com/graph/2SAT.html#practice-problems
Codeforces 2-SAT Tutorial: https://codeforces.com/blog/entry/16205

recomendo fazer Giant Pizza do zero, sem copiar nada da lib

dica top: dada uma tabela verdade eu consigo fazer qualquer operação com and's de pares de or's:
```
(a or b) // desliga o caso 0 0
(a or !b) // desliga o caso 0 1
(!a or b) // desliga o caso 1 0
(!a or !b) // desliga o caso 1 1
```
se eu quero fazer um a xor b, por exemplo, só preciso desligar o caso `0 0` e o caso `1 1`, então fica:

`(a xor b) = (a or b) and (!a or !b)`
`(a and b) = (a or b) and (!a or b) and (a or !b)`

## Problemas
[CSES] Giant Pizza: https://cses.fi/problemset/task/1684
[GYM] Exam Period: https://codeforces.com/gym/104120/problem/E
[Codeforces] The Door Problem: https://codeforces.com/contest/776/problem/D

## Dicas
### [GYM] Exam Period: https://codeforces.com/gym/104120/problem/E

Dica 1: || como a <= 1, b <= 1 e c <= 2, você pode fazer todas as operações só com tabelas verdades, então é só modelar o problema dessa forma. ||

Dica 2: || alguns casos são equivalentes, como `> 0`, `>= 1` e `!= 0`, no fim ficaram 7 casos pra mim. ||

### [Codeforces] The Door Problem: https://codeforces.com/contest/776/problem/D

Dica 1: || Uma porta é controlada por exatamente **dois** switches. Isso é fundamental. ||

Dica 2: || Os switches são as variáveis do 2-SAT. ||

Dica 3: || Dado que pressiono cada switch uma vez, temos para cada porta:
- Se ela estiver trancada, preciso de **exatamente** uma pressionada em algum switch respectivo para abrí-la.
- Se ela estiver destrancada, preciso de um número par de de pressionadas nos switchs respectivos para manter ela destrancada.
||

Dica 4: || Dado que pressiono cada switch uma vez, temos para cada porta:
- Se ela estiver trancada: `s1 xor s2` (abro ela com exatamente um switch).
- Se ela estiver destrancada: `!(s1 xor s2)` (mantenho ela fechada pressionando cada switch uma vez ou não pressionando nenhum dos dois).
||

Solução:
||
```c++
int n, m; cin >> n >> m; // rooms, switches
sat st(m);
vector<int> status(n); // status of door (0 = locked ; 1 = unlocked)
vector<vector<int>> switches(n, vector<int>());

for (int i = 0; i < n; i++) cin >> status[i];

for (int i = 0; i < m; i++) {
    int cnt; cin >> cnt;
    for (int j = 0; j < cnt; j++) {
        int door; cin >> door;
        
        switches[door-1].push_back(i);
    }
}

for (int door = 0; door < n; door++) {
    if (status[door] == 0) { // locked, então eu abro ela com "exatamente" 1 switch (número ímpar de pressionadas em algum switch)
        st.add_xor(switches[door][0], switches[door][1]);
    } else { // unlocked, então eu pressiono um número par de vezes
        st.add_xnor(switches[door][0], switches[door][1]);
    }
}

auto [ans, _] = st.solve();

cout << (ans ? "YES" : "NO") << '\n';
```
||