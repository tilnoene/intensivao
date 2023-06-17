> _A ordem que vc faz as coisas influencia_

## Problems
[CSES] Money Sums: [https://cses.fi/problemset/task/1745](https://cses.fi/problemset/task/1745 "https://cses.fi/problemset/task/1745")
[CSES] Coin Combinations II: [https://cses.fi/problemset/task/1636](https://cses.fi/problemset/task/1636 "https://cses.fi/problemset/task/1636")
[CSES] Book Shop: [https://cses.fi/problemset/task/1158](https://cses.fi/problemset/task/1158 "https://cses.fi/problemset/task/1158")
[AtCoder] LCS: [https://atcoder.jp/contests/dp/tasks/dp_f](https://atcoder.jp/contests/dp/tasks/dp_f "https://atcoder.jp/contests/dp/tasks/dp_f")

### Dicas
### Questão 12 - [CSES] Money Sums: https://cses.fi/problemset/task/1745

Dica 1: || a abordagem mais fácil é iterativa||

Dica 2: || note que o valor máximo que você pode construir é a soma de todas as moedas, no caso `1000 * 100 = 1e5`||

Dica 3: || você pode fazer com um estado só ou com dois||

Dica 4: || crie a DP para dizer se é possível ou não construir cada soma, depois percorra esse array e coloque na resposta se `dp[i] == true`||

Dica 5 (sacada): || como garantir que só usei um tipo de cada moeda? bom, basta percorrer primeiro os itens e depois o peso e tomar cuidado com a ordem que você altera os valores na DP para não contar a mesma moeda várias vezes. ||

Fórmula da DP: 
||
```c++
vector<int> dp(MAX_VAL, 0); // is_possible
dp[0] = 1;

for (auto coin : coins) {
    for (int i = MAX_VAL-1; i >= 0; i--) {
        if (i+coin < MAX_VAL) {
            dp[i+coin] |= dp[i];
        }
    }
}

vector<int> ans;

for (int i = 1; i < MAX_VAL; i++) {
    if (dp[i]) {
        ans.push_back(i);
    }
}

cout << ans.size() << '\n';
for (auto e : ans) {
    cout << e << ' ';
}
```
||
### Questão 13 - [CSES] Coin Combinations II: https://cses.fi/problemset/task/1636

Dica 1: || a abordagem mais fácil é iterativa||

Dica 2: || você pode fazer com um estado só||

Dica 3: || a ideia é similar a anterior||

Dica 4 (sacada): || como garantir que está "ordenado"? bom, basta percorrer primeiro os itens e depois o peso e tomar cuidado com a ordem que você altera os valores na DP para não contar a mesma moeda várias vezes. ||

Fórmula da DP: 
||
```c++
vector<ll> dp(x+1, 0);
dp[0] = 1;

for (int j = 0; j < n; j++) {
    for (int i = 0; i <= x; i++) {
        if (i-coin[j] >= 0) {
            dp[i] += dp[i-coin[j]];
            dp[i] %= MOD;
        }
    }
}

cout << dp[x] << '\n';
```
||
### Questão 14 - [CSES] Book Shop: https://cses.fi/problemset/task/1158

Dica 1: ||não tem muito o que pensar, é uma knapsack normal||

Observação: || não dá pra passar essa questão de forma recursiva :)||

Fórmula da DP: 
||
```c++
vector<vector<int>> dp(n+1, vector<int>(x+1, 0));
dp[0][0] = 0;

for (int i = 1; i <= n; i++) {
    for (int peso = 1; peso <= x; peso++) {
        if (peso - price[i] >= 0) { // pegar o item
            dp[i][peso] = max(dp[i-1][peso], dp[i-1][peso - price[i]] + pages[i]);
        } else { // n pegar o item
            dp[i][peso] = dp[i-1][peso];
        }
    }
}

cout << dp[n][x] << '\n';
```
||
### Questão 15 - [AtCoder] LCS: https://atcoder.jp/contests/dp/tasks/dp_f

Dica 1: ||é o mesmo código do LCS padrão, o desafio agora é recuperar a resposta||

Dica 2: ||primeiro encontre a LCS e depois se preocupe em encontrar qual a string em si||

Dica 3: ||crie uma matriz (com as mesmas dimensões da DP) que indica de qual posição você veio||

Dica 4: ||assim como a resposta está em `dp[n][m]`, você começa a recuperar a resposta a partir do índice `recuperar_path[n][m]`||

Dica 5: || para preencher essa tabela `recuperar_path`, ao invés de fazer as transições com `max()`, faça algo do gênero: `if(pega > npega) { dp[i][j] = pega; recuperar_path[i][j] = {i+1, j+1} }; `, etc... ||

Fórmula da DP: 
||
```c++
int dp[n+1][m+1];
pair<int, int> p[n+1][m+1];

memset(dp, 0, sizeof(dp));
memset(p, -1, sizeof(p));

// DP padrão
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        if (a[i-1] == b[j-1]) {
            dp[i][j] = dp[i-1][j-1] + 1;
            p[i][j] = {i-1, j-1}; // "vim de lá"
        } else {
            if (dp[i-1][j] > dp[i][j-1]) {
                dp[i][j] = dp[i-1][j];
                p[i][j] = {i-1, j}; // "vim de lá"
            } else {
                dp[i][j] = dp[i][j-1];
                p[i][j] = {i, j-1}; // "vim de lá"
            }
        }
    }
}

// recuperar resposta
string ans = "";
pair<int, int> curr = {n, m};

while (curr.first != 0 && curr.second != 0) {
    auto [i, j] = curr;

    // se são iguais, é pq o caractere tá na resposta
    if (a[i-1] == b[j-1]) {
        ans += a[i-1];
    }

    curr = p[i][j];
}

reverse(ans.begin(), ans.end());
```
||
