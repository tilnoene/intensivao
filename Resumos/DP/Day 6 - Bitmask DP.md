> _DP problems that require iterating over subsets._

Um **caminho hamiltoniano** passa por todos os vértices de um grafo e uma só vez por cada. Bom, tenta fazer essa questão antes de prosseguir:

[CSES] Hamiltonian Flights: https://cses.fi/problemset/task/1690

Dica 1: || Note que N <= 20 ||
Dica 2: || Você precisa de dois estados ||
Dica 3: || Você precisa saber quais nós você já visitou ||

Um problema clássico de caminhos hamiltonianos é o **caixeiro viajante**, em que um caixeiro deseja visitar um conjunto de N cidades (vértices), passando por cada cidade exatamente uma vez e retornando à cidade de origem, fazendo o caminho de menor tamanho possível.

> Em 2009 conseguiu-se uma resolução para este problema utilizando-se de bactérias[1] na implementação do algoritmo, que historicamente costuma ter um custo de tempo de computação exponencial.

## Reading
CSES Handbook, pg. 187, 19.2 Hamiltonian Paths: https://usaco.guide/CPH.pdf#page=187
CSES Handbook, pg. 112, 10.5 DP on bits: https://usaco.guide/CPH.pdf#page=112
A Primer on Bitmask DP: https://nwatx.me/post/dpbitmasks
Dynamic Programming, pg. 37, 6. Bitmasking: https://dp-book.com/Dynamic_Programming.pdf

## Problems
[AtCoder] Matching: https://atcoder.jp/contests/dp/tasks/dp_o?lang=en
[AtCoder] Pac-Takahashi: [https://atcoder.jp/contests/abc301/tasks/abc301_e](https://atcoder.jp/contests/abc301/tasks/abc301_e "https://atcoder.jp/contests/abc301/tasks/abc301_e")

### Dicas
### Questão 22 - [AtCoder] Pac-Takahashi: https://atcoder.jp/contests/abc301/tasks/abc301_e

Dica 1: || como só tem 18 doces, um nó source e um nó goal, você consegue aproveitar coisas disso||

Dica 2: || você pode salvar uma bitmask de estado indicando por quais você já passou ||

Dica 3: || você pode pré-computar as distâncias de todos esses 20 nós para todos os outros 20 nós ||

Dica 4: || você pode fazer 20 BFS pra ter isso ||

Dica 5: || na DP eu guardei o a mask e último que foi visitado, com isso eu consigo transitar (pra onde ir) testando ir para todos (se couber no tempo) ||

Dica 6: || mas como eu sei que cabe no tempo? bom, a dp[][] vai armazenar um par que é {número_de_doces, menor_tempo} ||
