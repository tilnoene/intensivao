**Day 3 - Paths on Grids**

Tenta fazer a questão:

[CSES] Grid Paths: [https://cses.fi/problemset/task/1638](https://cses.fi/problemset/task/1638 "https://cses.fi/problemset/task/1638")

São os problemas que envolvem uma matriz 2D de quadrados, e temos que analisar caminhos.

**Caminho (path):** é uma sequência de movimentos restritos a uma direção no eixo x e outra no eixo y, pois se você pudesse ir tanto pra esquerda quanto pra direita, o problema ficaria muito complicado.

Geralmente começam em canto e terminam em outro canto, e podem pedir a quantidade de caminhos que satisfazem alguma propriedade ou encontrar o min/max de alguma coisa dentre todos os caminhos.

Normalmente você divide em subproblemas, que são subretângulos da matriz.

## Problems
[LeetCode] LCS: [https://leetcode.com/problems/longest-common-subsequence/](https://leetcode.com/problems/longest-common-subsequence/ "https://leetcode.com/problems/longest-common-subsequence/")
[USACO] Cow Checklist: [http://www.usaco.org/index.php?page=viewproblem2&cpid=670](http://www.usaco.org/index.php?page=viewproblem2&cpid=670 "http://www.usaco.org/index.php?page=viewproblem2&cpid=670")
[USACO] Radio Contact: [http://www.usaco.org/index.php?page=viewproblem2&cpid=598#](http://www.usaco.org/index.php?page=viewproblem2&cpid=598# "http://www.usaco.org/index.php?page=viewproblem2&cpid=598#")

### Dicas
### Questão 8 - [CSES] Grid Paths: https://cses.fi/problemset/task/1638

Dica 1: || a abordagem mais fácil é iterativa||

Dica 2: || a complexidade final do código é O(N^2)||

Dica 3: || Você precisa de dois estados||

Dica 4: || `dp[i][j]` = número de formas de chegar em `i, j`||

Dica 5: || note que você só pode se mover para a direita e para a esquerda, então a transição é somar "de quantas formas eu vim daqui?"||

Fórmula da DP: ||
```c++
dp[0][0] = (grid[0][0] != '*') // caso base

dp(i, j) = dp(i-1, j) + dp(i, j-1) // transição

dp[n-1][n-1] // resposta
```
||
### Questão 9 - [LeetCode] LCS: https://leetcode.com/problems/longest-common-subsequence/

Dica 1: || a abordagem mais fácil é recursiva||

Dica 2: || a complexidade final do código é O(N^2)||

Dica 3: || você precisa de dois estados||

Dica 4: || `dp[i][j]` = tamanho da maior subsequência até a letra `i` da primeira string e a letra `j` da segunda string||

Dica 5: || experimente visualizar o problema como na imagem ||

Dica 6: || bom, existem dois casos: quando as letras `a[i]` e `b[i]` são iguais e diferentes, vou chamar de "pega" ou "não pega".||

Dica 7: || se você opta por não pegar, então você vai para o `max(dp(i+1, j), dp(i, j+1)`||

Dica 8: || se você opta por pegar, então você vai para `dp(i+1, j+1)` (note que você só pode pegar se as letras `i` e `j` forem iguais). Uma forma de ver o porquê de ir pra diagonal é para você não processar a mesma letra da primeira string duas vezes, assim você estaria considerando que ela se repetiu quando não é verdade. Experimente fazer o exemplo `ac` e `bala`||
### Questão 10 - [USACO] Cow Checklist: http://www.usaco.org/index.php?page=viewproblem2&cpid=670

Dica 1: || a abordagem mais fácil é recursiva||

Dica 2: || a complexidade final do código é O(N^2)||

Dica 3: || você precisa de três estados||

Dica 4: || note que você precisa começar da vaca Holstein 1 e terminar na vaca Holstein H. Cuidado com indexação em 0, eu usei em 1.||

Dica 5: || `dp[i][j][quem]` = peguei todas as vacas Holstein até i e todas as vacas Guernsey até j, onde se `quem = 0`, estou na vaca Holstein i, caso contrário estou na vaca Guernsey j||

Dica 6: || você pode ir pra qualquer uma das próximas duas vacas||

Fórmula da DP: 
||
```c++
if (i == n && j == m) {
  if (vez == 0) return 0; // terminei na vaca Holstein
  else return INF; // terminei na vaca Guernsey
}

curr = (vez ? g[j] : h[i]); // vaca atual

dp(i, j, vez) = max(dp(i+1, j, 0) + dist(curr, h[i+1]), dp(i, j+1, 1) + dist(curr, g[i+1])) // transição

dp[1][0][0] // resposta (começando da vaca Holstein 1...)
cout << dp(1, 0, 0) << '\n';
```
||

### Questão 11 - [USACO] Radio Contact: http://www.usaco.org/index.php?page=viewproblem2&cpid=598#

Dica 1: || a abordagem mais fácil é recursiva||

Dica 2: || a complexidade final do código é O(N^2)||

Dica 3: || você precisa de dois estados||

Dica 4 (sacada): || note que, dado os pontos iniciais do fazendeiro e da vaca e suas respectivas sequências de movimentos, você pode pré-calcular todos os pontos que eles vão passar, uma vez que um ponto do fazendeiro não depende de um ponto da vaca e vice-versa. Daí a transição fica O(1), e a questão fica bem parecia com a anterior, só que mais simples.||

Dica 5: || existem 3 transições: só o fazendeiro mover, só a vaca mover ou os dois se moverem ao mesmo tempo||

Dica 6: || `dp[i][j]` = o fazendo está na posição i e a vaca está na posição j||

Fórmula da DP: 
||
```c++
if (i == n && j == m) {
  return 0; // passei por todas as coordenadas
}

dp(i, j) = max({
  dp(i+1, j) + dist(f[i+1], v[j]), // só o fazendeiro se move
  dp(i, j+1) + dist(f[i], v[j+1]), // só a vaca se move
  dp(i+1, j+1) + dist(f[i+1, v[j+1]) // os dois se movem ao mesmo tempo
})

cout << dp(0, 0) << '\n';
```
||
