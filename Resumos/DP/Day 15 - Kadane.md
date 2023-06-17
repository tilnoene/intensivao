**Day 15 - Kadane**

>_Tem gente que diz que é guloso e não DP_

Questões envolvendo DP de Kadane geralmente vão pedir a maior soma possível para um subarray com alguma restrição.

subarray = contíguo
subsequence = não contíguo

(faz a maximum subarray sum iterativa e recursiva)

### Problems
[LeetCode] Maximum Subarray: https://leetcode.com/problems/maximum-subarray/
[CSES] Maximum Subarray Sum: https://cses.fi/problemset/task/1643
[Codeforces] Beautiful Array: https://codeforces.com/contest/1155/problem/D

### Dicas
## [LeetCode] Maximum Subarray: https://leetcode.com/problems/maximum-subarray/

Dica 1: || só precisa de um estado ||

Dica 2: || a complexidade é O(N) ||

Dica 3: || a resposta não necessariamente é `dp[n]` ||

Dica 4: || a transição é o máximo entre começar uma nova dp daqui ou somar o elemento atual na anterior ||

Solução:
||
```c++
dp[i] = max(arr[i] + dp[i-1], arr[i]); // iterativa

dp(i) = max(arr[i] dp(i+1), arr[i]); // recursiva 1; if (i == n-1) return arr[n-1];
dp(i) = max(dp(i-1) + arr[i], arr[i]); // recursiva 2; if (i == 0) return arr[0];
```
||
## [Codeforces] Beautiful Array: https://codeforces.com/contest/1155/problem/D

Dica 1: || eh bem parecida com aquela D do atcoder ||

Dica 2: || na transição você precisa saber se está multiplicando ou não, e então escolher começar a multiplicar, continuar multiplicando ou parar de multiplicar ||

Solução:
||
Uma das soluções usei 3 estados `dp[pos][ini][fim]`, indicando se o intervalo já começou e/ou já terminou. Nessa eu dois estados interpretando os números:
0 - não comecei a multiplicar
1 - estou multiplicando
2 - já finalizei a multiplicação

```c++
ll dp(int pos, int status) {
    if (pos >= n) return 0;

    ll& mem = tb[pos][status];
    if (mem != -1) return mem;
    mem = 0;

    if (status == 0) { // não comecei a multiplicar
        mem = max({
            arr[pos], // pegar só o elemento
            arr[pos] + dp(pos+1, 0), // não começa a multiplicar
            arr[pos] * x + dp(pos+1, 1) // começa a multiplicar
        });
    } else if (status == 1) { // estou multiplicando
        mem = max({
            arr[pos] * x, // pegar só o elemento
            arr[pos] * x + dp(pos+1, 1), // continuo multiplicando
            arr[pos] + dp(pos+1, 2) // parei de multiplicar
        });
    } else { // já finalizei a multiplicacao (kadane padrão)
        mem = max({
            0LL,
            arr[pos], // pegar só o elemento
            arr[pos] + dp(pos+1, 2) // ele + próxima sequência
        });
    }

    return mem;
}

dp(0, 0); // começa sem multiplicar
dp(0, 1); // começa multiplicando

// como é kadane, a resposta não necessariamente está em dp[n]

ll ans = 0;
    
for (int i = 0; i < n; i++) {
	for (int j = 0; j < 3; j++) {
		ans = max(ans, tb[i][j]);
	}
}

cout << ans << '\n';
```
||
