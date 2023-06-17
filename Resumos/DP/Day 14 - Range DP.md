**Day 14 - Range DP**

> _Solving a DP problem on every contiguous subarray of the original array._
> _**Finalmente!**_

DP on ranges é uma técnica usada pra resolver problemas na forma: "qual é o mínimo/máximo de alguma métrica que conseguimos em um array A?" com as sequintes propriedades:

- Guloso parece viável mas dá respostas erradas.
- Dada as respostas para cada subarray [l, x] e [y, r], conseguimos calcular a resposta para o subarray [l, r] em tempo `O(r - l)`.
- Subarrays disjuntos podem ser "combinados" independentemente.
- O tamanho do array geralmente não é maior que 500.

Essa técnica se baseia na suposição de que podemos "combinar" dois subarrays `[l, x-1]` e `[x, r]` para obter um **candidato** para melhor resposta de `[l, r]`, então testamos a melhor resposta tentando combinar todas as possibilidades para x (dentro do intervalo `[l, r]`). Note que pra isso funcionar precisamos percorrer os subarrays em ordem crescente de comprimento, pois usamos subarrays menores para calcular um subarray maior.

Como existem O(N^2) subarrays e processar cada um leva O(N) de tempo, geralmente as soluções vão rodar em O(N^3). Então geralmente você tem uma tabela `n x n` indicando a melhor resposta do range `[l][r]` e tenta melhorar a resposta de cada subarray testando juntar outros dois que "estão dentro".

Se não sair do lugar na primeira, experimenta ir lendo as dicas.

### Problems
[USACO] Modern Art 3: http://usaco.org/index.php?page=viewproblem2&cpid=1114
[Codeforces] Clear the String: https://codeforces.com/contest/1132/problem/F
[Codeforces] Vasya and Binary String: https://codeforces.com/contest/1107/problem/E

#### Por que `[l+1, x-1] + [x, r]` e não `[l+1, x] + [x+1, r]`?
Pois quando fazemos `if (s[l] == s[x])`, estamos tentando juntar o `s[l]` com o `s[x]` em um movimento só, então pra isso precisamos apagar o meio (`[l+1, x-1]`) da melhor forma e daí "propagar" pro resto `[x, r]`, e o `x` está incluso pois pode ser ótimo continuar realizando operação nesse caractere `s[x]`. Isso fica mais claro na questão _Vasya and Binary String_.

![[Pasted image 20230529131645.png]]

### Dicas
## [USACO] Modern Art 3: http://usaco.org/index.php?page=viewproblem2&cpid=1114

Dica 1: || você precisa de dois estados, onde `dp[i][j]` = menor número de pinceladas para formar o intervalo `[i, j]`. ||

Dica 2: || pense que no estado `[left, right]` você está calculando a melhor resposta tentando "melhorar" o intervalo `[left, right]`, onde começa com `painting[left]`. Como eu melhoro isso? Bom, basta eu achar algum `x` tal que `painting[left] = painting[x]`, pois seria como se vc assumisse que anteriormente você fez uma pincelada no range `[left, x]` e depois fez outras ali no meio. ||

Dica 3: || o caso base é eu ter um intervalo de tamanho 1, daí eu preciso gastar uma pincelada para esse intervalo necessariamente. ||

Dica 4: || a transição seria:
```c++
mem = 1 + dp(left+1, right); // caso base = eu uso uma pincelada só pro left e arrumo o [left+1, right]

for (int i = left+1; i <= right; i++) {
    if (painting[left] == painting[i]) { 
	    // se forem iguais, posso montar o intervalo [left, right] juntando [left, i-1] e [i, right], então pego o mínimo
	    
        mem = min(mem, dp(left+1, i-1) + dp(i, right));
    }
}
```
||

Solução:
||
```c++
int n, painting[MAX], tb[MAX][MAX];

int dp(int left, int right) {
    if (left > right) return 0;
    
    int& mem = tb[left][right];
    if (mem != -1) return mem;
    
    mem = 1 + dp(left+1, right);
    
    for (int i = left+1; i <= right; i++) {
        if (painting[left] == painting[i]) {
            mem = min(mem, dp(left+1, i-1) + dp(i, right));
        }
    }
    
    return mem;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for (int i = 0; i < n; i++) cin >> painting[i];
    
    memset(tb, -1, sizeof(tb));
    
    cout << dp(0, n-1) << '\n';
    
    return 0;
}
```
||
## [Codeforces] Vasya and Binary String: https://codeforces.com/contest/1107/problem/E

Dica 1: || você precisa de três estados, `[l][r]` e mais algum ||

Dica 2: || a complexidade final do código é O(n^4) ||

Dica 3: || `dp[l][r][cnt]` = melhor resposta no range `[l, r]` tendo pego `cnt` caracteres `s[l]` consecutivos ||

Dica 4: || a transição fica: como pra esquerda estamos tentando remover o intervalo, então o número de consecutivos volta pro caso base que é 1, mas pra direita, como demos match em `s[left]` e `s[i]`, aumentamos ele em 1. ||

Dica 4 (código): || `max(mem, dp(left+1, i-1, 1) + dp(i, right, consecutive_digits+1))` ||

Dica 5: || o caso base agora, ao invés de somar 1, somaremos o tamanho do intervalo de consecutivos que chegou lá ||

Solução:
||
```c++
ll n, points[MAX], tb[MAX][MAX][MAX];
string s;

ll dp(int left, int right, int consecutive_digits) {
    if (left > right) return 0;
    
    ll& mem = tb[left][right][consecutive_digits];
    if (mem != -1) return mem;
    
    mem = points[consecutive_digits] + dp(left+1, right, 1);
    for (int i = left+1; i <= right; i++) {
        if (s[left] == s[i]) {
            mem = max(mem, dp(left+1, i-1, 1) + dp(i, right, consecutive_digits+1));
        }
    }
    
    return mem;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> s;
    for (int i = 1; i <= n; i++) cin >> points[i];
    
    memset(tb, -1, sizeof(tb));
    
    cout << dp(0, n-1, 1) << '\n';

    return 0;
}
```
||