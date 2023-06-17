**Day 11 - General 3**

### Problems
[USACO] Teamwork: http://www.usaco.org/index.php?page=viewproblem2&cpid=863
[USACO] Why Did the Cow Cross the Road II: http://www.usaco.org/index.php?page=viewproblem2&cpid=718

Essa é uma questão legal para ver alguns casos onde a abordagem recursiva é mais chata de se trabalhar.

[USACO] Snakes: http://www.usaco.org/index.php?page=viewproblem2&cpid=945

### Dicas
## Questão 33 - [USACO] Teamwork: http://www.usaco.org/index.php?page=viewproblem2&cpid=863

Dica 1: || fazer recursiva é meio complicado por conta da transição pois você precisaria saber o máximo de/e quem está no grupo, etc... ||

Dica 2: || só precisa de um estado ||

Dica 3: || `dp[i]` = maximum skill for cows up to i ||

Dica 4: || a complexidade do código é O(N * K) ||

Dica 5: || transição: pra cada `i` você percorre `k` caras anteriores tentando melhorar sua resposta (assumindo que os k caras estão no seu grupo atual terminando em i) ||

Solução:
||
```c++
vector<int> dp(n+1, 0); // dp[i] = maximum skill for cows up to i

for (int cow = 0; cow < n; cow++) {
    int most_skilled = skill[cow];

    for (int j = cow; j >= max(0, cow-k+1); j--) {
        most_skilled = max(most_skilled, skill[j]);
        
        if (j == 0) {
            dp[cow] = max(dp[cow], (cow-j+1) * most_skilled);
        } else {
            dp[cow] = max(dp[cow], dp[j-1] + (cow-j+1) * most_skilled);
        }
    }
}

cout << dp[n-1] << '\n';
```
||

## Questão 34 - [USACO] Why Did the Cow Cross the Road II: http://www.usaco.org/index.php?page=viewproblem2&cpid=718

Dica 1: || eh um classico pega/npega ||

Dica 2: || precisa de dois estados, a faca atual e o field atual ||

Dica 3: || a transição é que vc pode escolher entre: ||

3.1: || não dar match na vaca atual, ou seja, ir para a próxima vaca mantendo o field ||

3.2: || não dar match no field atual, ou seja, ir para o próximo field mantendo a vaca ||

3.3: || dar match na vaca atual com o field atual (somente se `| vaca - field | <= 4`) ||

Solução:
||
```c++
int dp(int cow, int field) {
    if (cow >= n or field >= n) return 0;

    int& mem = tb[cow][field];
    if (mem != -1) return mem;

    mem = max(dp(cow+1, field), dp(cow, field+1));

    if (abs(cows[cow] - fields[field]) <= 4) {
        mem = max(mem, dp(cow+1, field+1) + 1);
    }

    return mem;
}
```
||
## Questão 35 - [USACO] Snakes: http://www.usaco.org/index.php?page=viewproblem2&cpid=945

Dica 1: || N <= 400, dá pra fazer O(N^3) ||

Dica 2: || separa o problema e calcula o wasted space só no final. Diggo, a DP vai salvar a soma das nets e no final vc imprime `dp() - sum(groups)`. Agora o problema é minimizar a soma dos tamanhos das nets.  ||

Dica 3: || você precisa de dois estados||

Dica 4: || iterativa faz mais sentido ||

Dica 5: || `dp[i][j]` = minimum sum of all net sikes for the first i snakes after j resizings ||

Dica 6: || é semelhante a Teamwork, pra cada grupo i após k resizings, você tenta melhorar a resposta, percorrendo c de i-1 até 0 trocando para uma net que consiga capturar todos os grupos.||

Dica 7: || uma net do tamanho do maior grupo garante que vc consegue capturar todos os grupos ||

Dica 7.1: || tenta melhorar a resposta do meu grupo terminando em "group" começando em algum outro grupo após "c" trocando para uma net do tamanho que consiga capturar todos os grupos  (uma net do tamanho do maior grupo garante isso). ||

Solução: || 
```c++
int space_used = 0;

for (int i = 1; i <= n; i++) {
    cin >> snakes[i];
    space_used += snakes[i];
}

vector<vector<int>> dp(n + 1, vector<int>(k+1, 0)); // dp[i][j] = minimum sum of all net sikes for the first i snakes after j resizings
int largest_group = 0;

for (int group = 1; group <= n; group++) {
    largest_group = max(largest_group, snakes[group]);

    dp[group][0] = largest_group * group; // caso base: com zero resizings, ela vai pegar todo o intervalo com uma net do tamanho do maior greupo

    for (int resizing = 1; resizing <= k; resizing++) {
        dp[group][resizing] = INT32_MAX;
        int net_size = snakes[group];

        /*
            tenta melhorar a resposta do meu grupo terminando em "group" começando em algum outro
            grupo após "c" trocando para uma net do tamanho que consiga capturar todos os grupos
            (uma net do tamanho do maior grupo garante isso).
        */

        for (int c = group-1; c >= 0; c--) {
            dp[group][resizing] = min(dp[group][resizing], dp[c][resizing-1] + net_size * (group - c));

            net_size = max(net_size, snakes[c]);
        }
    }
}

cout << dp[n][k] - space_used << '\n';
```
||
