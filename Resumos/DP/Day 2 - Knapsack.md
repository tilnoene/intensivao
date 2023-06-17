**Day 2 - Knapsack**
Tentar fazer a questão antes de ler:

[AtCoder] Knapsack 1: https://atcoder.jp/contests/dp/tasks/dp_d

> Problems that can be modeled as filling a limited-size container with items.

Geralmente envolvem preencher um recipiente limitado com um conjunto de itens onde queremos contar ou otimizar alguma quantidade associada aos itens.

Algumas variações:
- **Knapsack 0/1 (clássico):** Você tem itens com um peso e um valor e quer escolher um conjunto de itens que maximiza o valor total contanto que o peso total caiba no recipiente.
- Encontrar todos os pesos totais possíveis que podemos obter de qualquer subconjunto de itens de modo que o peso total caiba no recipiente. Exemplo: "De quantas formas consigo somar tanto?"
- Contar quantas sequências de itens preencherão o recipiente completamente (o peso total é exatamente a capacidade do container) (a ordem pode ou não importar).

Geralmente o estado da DP vai ser a capacidade do recipiente e as transições envolvem tentar adicionar um item ao recipiente.

## Problems
[CSES] Dice Combinations: https://cses.fi/problemset/task/1633
[CSES] Minimizing Coins: https://cses.fi/problemset/task/1634
[CSES] Coin Combinations I: https://cses.fi/problemset/task/1635

## Dicas
### Questão 5 - [CSES] Dice Combinations: https://cses.fi/problemset/task/1633

Dica 1: || a abordagem mais fácil é iterativa||

Dica 2: || a complexidade final do código é O(N * 6). Isso significa que pra cada número, você pode atualizar seu valor 6 vezes. ||

Dica 3: || Você precisa só de um estado. Então esse é um caso interessante onde a complexidade de tempo não é a mesma do número de estados.||

Dica 4: || `dp[i]` = a resposta até i = número de formas de construir soma i||

Dica 5: || a transição é, pra cada número, atualizar sua resposta olhando os 6 valores anteriores||

Fórmula da DP: ||
```c++
dp(i) = dp(i-1) + dp(i-2) + dp(i-3) + dp(i-4) + dp(i-5) + dp(i-6)
```
||
### Questão 6 - [CSES] Minimizing Coins: https://cses.fi/problemset/task/1634/

Dica 1: || a abordagem mais fácil é iterativa||

Dica 2: || a complexidade final do código é O(X * N). Isso significa que pra cada número, você pode atualizar seu valor N vezes. ||

Dica 3: || Você precisa só de um estado. Então esse é um caso interessante onde a complexidade de tempo não é a mesma do número de estados.||

Dica 4: || `dp[i]` = a resposta até i = menor número de moedas pra formar o número i||

Dica 5: || a transição é, pra cada número, atualizar sua resposta olhando os N valores anteriores||

Fórmula da DP: ||
```c++
dp(i) = min(dp(i-j)) for j in moedas
```
||
