**Day 17 - Prefix Sum**

Tente seu melhor resolvendo esse problema antes de continuar:

[USACO] Subsequences Summing to Sevens: http://www.usaco.org/index.php?page=viewproblem2&cpid=595

>_a assim você descobre que não sabe prefix sum_

Geralmente usamos a prefix sum para fazer queries de soma num range [l, r], mas isso também significa que a prefix sum tem informação sobre **todos** os subarrays do array original. Com isso conseguimos calcular uma série de coisas que vão ser exploradas nos problemas a seguir.

### Problems
[USACO] Subsequences Summing to Sevens: http://www.usaco.org/index.php?page=viewproblem2&cpid=595
[USACO] Hoof, Paper, Scissors: http://www.usaco.org/index.php?page=viewproblem2&cpid=691
[CSES] Subarray Sums II: https://cses.fi/problemset/task/1661
[CSES] Subarray Divisibility: https://cses.fi/problemset/task/1662
[SPOJ] MAXSUMSQ - Maximum Sum Sequences: https://www.spoj.com/problems/MAXSUMSQ/

### Dicas
## [USACO] Subsequences Summing to Sevens: http://www.usaco.org/index.php?page=viewproblem2&cpid=595

Dica 1: || não vamos salvar a prefix sum inteira, apenas o resto da divisão por 7 (`ps += arr[i]) %= 7`) ||

Dica 2: ||  se `ps[r]` é congruente a `ps[l]` módulo 7, então a subtração/soma deles também vai ser ||

Dica 3: || dada a afirmação acima, é sempre ótimo eu subtrair a primeira e a última aparição de x na prefix sum, onde `x` são todos os restos possíveis (`[0, 6]`). ||

Dica 4: || tem um caso de borda que é `ps[i] = 0`, aí o candidato pra resposta é o próprio `i` ||

Solução:
||
```c++
vector<int> pos(8, -1); // a primeira vez em que i apareceu, onde -1 = nunca apareceu

int n; cin >> n;
ll ps = 0;
int ans = 0;

for (int i = 0; i < n; i++) {
    int x; cin >> x;
    ps = (ps + x) % 7; // prefix sum até i

    if (ps == 0) ans = max(ans, i+1); // corner case: se já for 0 posso só pegar [0, i], então o tamanho do intervalo é i+1

    if (pos[ps] == -1) { // se ainda não apareceu, a ultima aparição é o próprio i
        pos[ps] = i;
    } else { // se apareceu, pega a posição do intervalo mais a esquerda que tem soma mod o que eu quero
        ans = max(ans, i - pos[ps]);
    }
}
```
||

## [USACO] Hoof, Paper, Scissors: http://www.usaco.org/index.php?page=viewproblem2&cpid=691

Dica 1: || essa tem mais cara de prefix sum né, a ideia é, pra cada i, vc testar pegar algum dos 3 pra esquerda e algum dos 3 pra direita e pegar o máximo de cada, respectivamente ||

Solução:
||
```c++
for (int i = 1; i <= n; i++) {
    int left = 0, right = 0;
    for (int j = 0; j < 3; j++) {
        left = max(left, ps[i][win(j)]);
        right = max(right, ps[n][win(j)] - ps[i][win(j)]);
    }

    ans = max(ans, left + right);
}
```
||
## [CSES] Subarray Sums II: https://cses.fi/problemset/task/1661
|| essa é uma questão bem bacana pq parece super difícil e não é. ||

Dica 1: || é parecida com a ideia da Subsequences Summing to Sevens. ||

Dica 2: || é um problema de contagem; não vamos conseguir iterar por todas as possibilidades, afinal o pior caso é O(n^2) ~ 10^10 subarrays com soma x. ||

Dica 3:
||
Vamos manter a prefix sum e, para cada índice i, contaremos o número de prefixos (que já passaram) com soma igual à `prefix_sum[i] - x`. Isso significa que, para cada um desses prefixos, podemos remover eles da nossa _soma atual_ para construir um subarray com soma x.
||

Solução:
||
```c++
map<ll, ll> cnt; // quantas vezes a prefix sum apareceu
cnt[0] = 1;

ll n, x; cin >> n >> x;
ll ps = 0, ans = 0;

for (int i = 0; i < n; i++) {
    int v; cin >> v;
    ps += v;
    
    ans += cnt[ps - x];
    // se existe um subarray com prefix sum igual a prefix_sum-x,
    // podemos excluir ele do noso subarray atual e conseguir a soma desejada que é x
	// então como podemos fazer isso pra cada um dos subarrays com essa propriedade, somamos a quantidade de vezes que eles já apareceram na resposta
    
    cnt[ps]++; // minha prefix sum atual apareceu mais uma vez
}

cout << ans << '\n';
```
||
## [CSES] Subarray Divisibility: https://cses.fi/problemset/task/1662

Dica 1: || Iremos manter a prefix sum mod n. ||

Dica 2: || Cuidado com valores negativos, nessa questão a prefix sum **sempre** deve ser >= 0 (por conta da divisibilidade e etc). ||

Dica 3: || Se um subarray tem, por exemplo, soma 3 (mod n), então para ele ficar com soma 0 (mod n) basta removermos algum prefixo também som soma 3 (mod n). ||

Dica 4: || Primeiro calcule quantas vezes cada valor aparece na prefix sum e depois calcule a resposta com base nisso. ||

Dica 5: || Dado que o a soma 3 (mod n) apareceu `x` vezes no prefixo, de quantas formas eu consigo montar um subarray com soma 0 (mod n)? ||

Dica 5.1: || Vamos pegar todos os pares possíveis, ou seja, um indicando o início e outro o final desse subarray. ||

Dica 5.2: || `(x * (x - 1)) / 2` ||

Dica 6: || Precisamos definir um caso base, ou seja, inicialmente quantos prefixos tem soma 0? ||

Dica 6.1: || Um array vazio tem soma 0, afinal não tem nenhum elemento. ||

Solução:
||
```c++
map<ll, ll> cnt; // quantas a cada prefix sum apareceu
cnt[0] = 1;

ll n; cin >> n;
ll ps = 0, ans = 0;

for (int i = 0; i < n; i++) {
    int v; cin >> v;
    ps = ((ps + v) % n + n) % n; // ps sempre >= 0
    
    cnt[ps]++;
}

for (auto [_, x] : cnt) { // tem que ser iguais pq subtraindo o mod fica 0
    ans += (x * (x - 1)) / 2;
}

cout << ans << '\n';
```
||
## [SPOJ] MAXSUMSQ - Maximum Sum Sequences: https://www.spoj.com/problems/MAXSUMSQ/

Solução: || Primeiro calcula kadane dps faz o mesmo processo da Subarray Sums II ||