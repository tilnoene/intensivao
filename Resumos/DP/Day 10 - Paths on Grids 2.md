**Day 10 - Paths on Grids 2**

### Reading
Handbook, pg. 81, 7.3 Paths in a grid: https://usaco.guide/CPH.pdf#page=81
Programiz - Longest Common Subsequence: https://www.programiz.com/dsa/longest-common-subsequence

(recursiva e iterativa)

### Problems
[CSES] Edit Distance: https://cses.fi/problemset/task/1639
[CSES] Array Description: https://cses.fi/problemset/task/1746

*tenta recuperar resposta do Edit Distance, que nem tu queria kk*

### Dicas
### Questão 32 - [CSES] Array Description: https://cses.fi/problemset/task/1746

Dica 1: || note que m, x[i] = 100 ||

Dica 2: || vc precisa de dois estados: posição e número anterior ||

Dica 3: || a transição é basicamente você tentar colocar um número se for 0, e se não for pega `dp(i+1, arr[i])` ||

Possíveis erros e casos de borda:

|| TLE: vc não precisa percorrer de 1 até m, mas sim de prev-1 até prev+1.||

|| Tome cuidado para prev+1 não extrapolar m e prev-1 não ficar menor que 1.  ||

|| Antes de começar, ele pode ter dado um array inválido, exemplo: `2 8 3` ||

|| O array pode começar com 0, daí você pode começar com "qualquer" valor ||

|| Imagine o seguinte caso: `2 0 4`. A resposta é 1, o único número possível é 3. Quando você testar colocar `(1, 2, 3)` onde tem o 0, 1 e 2 são inválidos pois `4-2 > 1` e `4-1 > 1`. ||

(falta ler handbook)
(falta ler programiz)
(falta recuperar resposta edit distance)
(falta iterativa array description)
(falta iterativa edit distance)

