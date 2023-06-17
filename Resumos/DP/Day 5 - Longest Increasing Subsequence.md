> _Finding and using the longest increasing subsequence of an array._

Como o nome diz, é basicamente a maior subsequência crescente de um array.

Por exemplo, pro array `7 3 5 3 6 2 9 8`, uma das LIS é `3 5 6 9`.

A solução naive é simples, fazendo uma DP em O(N^2):

```c++
// dp[i] = maior LIS que termina em i

vector<int> dp(n, 1); // todo elemento é uma LIS de tamanho 1
for (int i = 0; i < n; i++) {
	for (int j = 0; j < i; j++) {
		if (a[j] < a[i]){
			dp[i] = max(dp[i], dp[j] + 1); // máximo entre o que já tem lá e e pegar o elemento atual na LIS de j
		}
 	}
}

int size_of_lis = *max_element(dp);
```

LIS não é um conteúdo frequente, mas é provavelmente o tipo mais simples para se fazer uma "otimização de DP".

Veja que você só tem um estado na DP, mas a transição é O(N^2), teria como melhorar isso? **Pense em como deixar isso melhor**.

[CSES] Increasing Subsequence: https://cses.fi/problemset/task/1145

Dica 1: || Temos um for dentro de outro for, dá pra tirar esse for de dentro ||
Dica 2: || Complexidade fica O(N * logN) ||
Dica 3: || Você pode substituir esse for por uma segtree ou por busca binária/`lower_bound` (faça das duas formas :)) ||

Observação: || note que o array sempre fica ordenado, try to prove this for yourself. ||

## Reading
CSES, pg. 80, 7.2 Longest increasing subsequence: https://usaco.guide/CPH.pdf#page=80
CP Algorithms, Longest increasing subsequence: https://cp-algorithms.com/sequences/longest_increasing_subsequence.html

## Problemas
[CSES] Towers: https://cses.fi/problemset/task/1073
[Codeforces] Consecutive Subsequence: https://codeforces.com/contest/977/problem/F
[USACO Guide] LCS on Permutations: https://codeforces.com/gym/102951/problem/C

### Dicas
### Questão 17 - [CSES] Towers: https://cses.fi/problemset/task/1073

Dica 1: || a complexidade final do código é O(N * log N)||

Dica 2: || a sacada é que é sempre ótimo colocar o próximo cubo no topo da torre com o menor cubo atual (ou criar uma nova torre, se não for possível)||

Dica 3: || equivalente à longest non-decreasing subsequence||

Nota: || se não precisasse adicionar as torres na ordem do input, penso que daria pra resolver só ordenando com guloso ||

Solução: ||
```c++
multiset<int> towers;
    
for (int i = 0; i < n; i++) {
    auto it = towers.upper_bound(arr[i]);

    if (it == towers.end()) {
        towers.insert(arr[i]);
    } else {
        towers.insert(arr[i]);
        towers.erase(it);
    }
}

cout << towers.size() << '\n';
```
||

### Questão 18 - [Codeforces] Consecutive Subsequence: https://codeforces.com/contest/977/problem/F

Dica 1: || separe as coisas: encontrar o maior tamanho da sequência e encontrar a sequência em si||

Dica 2: || é uma LIS mas você não tenta pegar **algum** dos elementos menores que `arr[i]`, mas só o `arr[i]-1`||

Notas: || da pra fazer O(N logN) com bb/multiset/map ou em O(N) com hash/unordered_map ||

Solução: ||
```c++
dp[arr[i]] = max(dp[arr[i]], dp[arr[i]-1] + 1); // pegar o anterior, começar uma sequência com esse elemento
```
||

### Questão 19 - [USACO Guide] LCS on Permutations: https://codeforces.com/gym/102951/problem/C

Dica 1: || lembra do "coração" da LIS: adicionar coisas mantendo uma ordenação||

Dica 2: || a sacada é que da pra se aproveitar de que os elementos do array são distintos ||

Ideia: || se você salva a posição de cada `a[i]` , a LCS vai ser a LIS no array `position[b[i]]`. Experimenta fazer um caso pra provar disso. ||

Solução: ||
```c++
for (int i = 0; i < n; i++) {
    cin >> a[i];
}

for (int i = 0; i < n; i++) {
    cin >> b[i];
    
    pos[b[i]] = i;
}

vector<int> dp;

for (int i = 0; i < n; i++) {
    int it = lower_bound(dp.begin(), dp.end(), a[i], [&](int a, int b) { return pos[a] < pos[b]; }) - dp.begin();
    
    if (it == dp.size()) {
        dp.push_back(a[i]);
    } else {
        dp[it] = a[i];
    }
}

cout << dp.size() << '\n';
```
||

