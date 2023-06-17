Bom, estive pensando em como ajudar você também com a parte de recursão (além da DP), então vamos tentar o seguinte (pelo menos nesse início): fazer as questões recursivas **e** iterativas. Vai ser um desafio pra nós dois kk.

Vamos começar com 3 questões, leia e entenda todas. 

Tenta anotar suas ideias ou approachs que seguiu durante seu raciocínio, daí posso tentar dizer quais fazem sentido e quais não fazem (e o porquê).

Todo dia as 21h vamos fazer upsolving e discutir sobre as questões em call, mas qualquer dúvida pode mandar no tópico da questão equivalente que posso ajudar (cria um tópico pra questão se não houver pra ficar mais organizado).

Por enquanto planejo usar questões da USACO, CSES, CF (& Gym) e AtCoder.

Vou colocar as questões em ordem de dificuldade, recomendo ler as dicas depois de tentar pensar um pouco (20~30 minutos).

Se já tiver feito alguma questão, não olha a solução e tenta fazer do zero.

**Day 1 - General (introduction)**
A ideia da DP é testar todas as **situações** possíveis, como um brute, mas onde você reutiliza valores de situações já calculadas anteriormente e transita entre os estados de forma inteligente.

As coisas primordiais são **definir os estados** e **qual a transição**. Geralmente o tamanho da entrada vai delimitar algum dos dois (ou os dois).

**Estado:** "O que define minha resposta na situação atual?" Ou seja, preciso de atributos que, só com eles, eu consiga identificar uma situação e diferenciá-la de todas as outras.

**Transição:** "Partindo do meu estado, pra quais outros estados eu posso ir?" ou "Nesse estado que estou, de onde posso ter vindo?".

Também precisamos definir um **caso base**, um valor que vai influenciar a resposta de todos os outros.

Algumas questões vão ser mais fáceis de pensar com abordagens recursivas e outras iterativas, por isso é bom entender ambas. Uma intuição pra ver essas duas abordagens de DP é como uma BFS ou uma DFS: você pode fazer uma DFS iterativa? Pode. Você pode fazer uma BFS recursiva? Pode, com uma stack. Mas é mais complicado de pensar assim.

## Problems
[CF] Mortal Kombat Tower: [https://codeforces.com/problemset/problem/1418/C](https://codeforces.com/problemset/problem/1418/C "https://codeforces.com/problemset/problem/1418/C")
[USACO] Hoof, Paper, Scissors: [http://www.usaco.org/index.php?page=viewproblem2&cpid=694](http://www.usaco.org/index.php?page=viewproblem2&cpid=694 "http://www.usaco.org/index.php?page=viewproblem2&cpid=694")
[USACO] Time is Mooney: [http://www.usaco.org/index.php?page=viewproblem2&cpid=993](http://www.usaco.org/index.php?page=viewproblem2&cpid=993 "http://www.usaco.org/index.php?page=viewproblem2&cpid=993")
## Dicas
### Questão 1 - [CF] Mortal Kombat Tower: https://codeforces.com/problemset/problem/1418/C

Dica 1: || a abordagem mais fácil é recursiva||

Dica 2: || pega ou não pega (troca ou não troca)||

Dica 3: || você precisa de três estados||

Dica 4: || os estados são: monstro atual (n), de quem é a vez (2), quantos eu já matei (2)||

Dica 5: || `dp[i][vez][quantos]` = melhor resposta até `i`, na vez do jogador `x`, matando `quantos` monstros (melhor resposta = mínimos de skip points usados)||

Dica 6: || a transição é trocar de jogador ou continuar com o jogador atual (se for possível)||

Fórmula da DP: ||
```c++
dp(i, jogador, quantidade) = min(
  dp(i+1, !jogador, 0), // trocar de jogador
  dp(i+1, jogador, quantidade+1) // manter o jogador, se quantidade < 1 (só posso pegar dois seguidos, estados 0 e 1)
) + (jogador == 1 && arr[i] == 1);
```
||
### Questão 2 - [USACO] Hoof, Paper, Scissors: http://www.usaco.org/index.php?page=viewproblem2&cpid=694

Dica 1: || a abordagem mais fácil é recursiva||

Dica 2: || pega ou não pega (troca ou não troca)||

Dica 3: || você precisa de três estados||

Dica 4: || os estados são: jogada atual (n), meu gesto atual (3), quantas trocas eu já fiz (21)||

Dica 5: || `dp[i][gesto][trocas]` = melhor resposta até a jogada `i`, usando o gesto `gesto` e tendo realizado `trocas` trocas até ali (melhor resposta = maior número de vitórias) ||

Dica 6: || a transição é pegar o máximo entre continuar com o meu gesto ou trocar para algum dos outros dois gestos (se ainda for possível)||

Fórmula da DP: ||
```c++
dp(i, gesto, trocas) = max(
  dp(i+1, gesto, trocas), // manter o gesto atual
  dp(i+1, outro_gesto1, trocas+1), // trocar o gesto, se trocas < k
  dp(i+1, outro_gesto2, trocas+1), // trocar o gesto, se trocas < k
) + (jogador == 1 && arr[i] == 1);
```

Note que, pela dica 5, podemos ver que a resposta pode começar utilizando qualquer um dos gestos, então vamos chamar:
```c++
ans = max({dp(0, 0, 0), dp(0, 1, 0), dp(0, 2, 0)});
```
||
### Questão 3 - [USACO] Time is Mooney: http://www.usaco.org/index.php?page=viewproblem2&cpid=993

Dica 1: || a abordagem mais fácil é iterativa||

Dica 2: || você precisa de dois estados||

Dica 3: || a complexidade final é O(N^2) (note que N <= 1000)||

Dica 4: || a observação mais importante é que os dias nunca podem ultrapassar 1000, pois no pior caso com `c=1` temos 1000t - t^2, ou seja, você pode usar os dias como estado||

Dica 5: || os estados são: nó atual, dia atual ||

Dica 6: || a transição é sempre para os nós adjacentes do nó atual e sempre com dia + 1||
