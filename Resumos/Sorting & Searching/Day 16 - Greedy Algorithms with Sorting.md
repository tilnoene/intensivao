**Day 16 - Greedy Algorithms with Sorting**

>_troll_

Tenta fazer essa questão antes de prosseguir:

[USACO Guide] Studying Algorithms: https://codeforces.com/gym/102951/problem/B https://codeforces.com/gym/102951/problem/B

### Problems
[USACO Guide] Studying Algorithms: https://codeforces.com/gym/102951/problem/B
[CSES] Movie Festival: https://cses.fi/problemset/task/1629
[CSES] Tasks and Deadlines: https://cses.fi/problemset/task/1630
[CSES] Movie Festival II: https://cses.fi/problemset/task/1632

### Dicas
### [CSES] Tasks and Deadlines: https://cses.fi/problemset/task/1630
Dica: || é sempre ótimo você tentar minimizar o `finishing_time`, já que todos os outros valores são fixos (tenta escrever no papel a fórmula pra algum caso de teste), e você faz isso sempre escolhendo as tasks com menor duração. Note também que, se a duração é a mesma, a ordem não importa. ||


### [CSES] Movie Festival II: https://cses.fi/problemset/task/1632

Dica 1: || é parecido com a ideia de LIS, da questão Towers. ||

Dica 2: || ordenamos os filmes pelo que termina primeiro. ||

Dica 3: || salvamos quando termina o último filme de cada membro em um multiset, e então vamos inserindo sempre no primeiro que é possível (se existir). ||

Solução:
```c++
int n, k; cin >> n >> k;
vector<pair<int, int>> arr(n); // { ending, starting }

for (int i = 0; i < n; i++) {
    cin >> arr[i].second >> arr[i].first;
}

sort(arr.begin(), arr.end());

int movies = 0;
multiset<int> members; // quando termina cada filme de cada membro

for (int i = 0; i < n; i++) {
    auto it = members.lower_bound(-arr[i].second);

    if (it != members.end()) {
        members.erase(it);
        members.insert(-arr[i].first);
        movies++;
    } else if (members.size() < k) {
        members.insert(-arr[i].first);
        movies++;
    }
}

cout << movies << '\n';
```