> _Finding the number of integers in a range that have a property._

## Reading
Codeforces Blog Digit DP: https://codeforces.com/blog/entry/53960
Dynamic Programming, pg. 30, 5. Digits: https://dp-book.com/Dynamic_Programming.pdf

Existem algumas abordagens comuns:
- vamos percorrer os dígitos ao invés dos números, então a ideia é não pensar em números mas em uma sequência de dígitos. Nós que damos sentido à essa sequência de dígitos.
- pode ser que os números do range não caibam em uma variável int ou long long, daí tem que ler como string
- para resolver para [l, r] geralmente vamos resolver para [0, r] e subtrair [0, l-1]. Note que são duas chamadas de DPs, e como geralmente a DP depende do upper_bound do intervalo, sua tabela precisa ser resetada.
- não importa qual o número em si, mas se ele satisfaz tal propriedade.
	- nos materiais eles explicam bem isso, imagina d1 d2 d3 di (...): Se você sabe que em algum ponto algum di é menor que o mesmo dígito no número original, você pode colocar qualquer dígito lá que via continuar mantendo a propriedade (de ser menor)
- quase sempre vai precisar desse estado do dígito atual e do estado booleano indicando se é menor que o número original ou não

Sugiro entender **bem** o problema enunciado e tentar fazer por você mesma.

"How many numbers **x** are there in the range **a** to **b**, where the digit **d** occurs exactly **k** times in **x**?"

### Problems
[SPOJ] PR003004 - Digit Sum: https://www.spoj.com/problems/PR003004/
[LightOJ] 1068 - Investigation: https://vjudge.net/problem/LightOJ-1068

### Dicas
### Questão 24 - [LightOJ] 1068 - Investigation: https://vjudge.net/problem/LightOJ-1068

Dica 1: || você precisa de 4 estados ||

Dica 1.1: || eles são: posição do dígito atual, soma dos dígitos, resto da divisão e `under` (o padrão) ||

Dica 2: || a soma dos dígitos é pequena (90 eh um upperbound), então pode salvar direto, mas o resto da divisão tem que ser calculado enquanto processa o número ||

Dica 3: || a transição ficaria: `dp(pos+1, , sum + d, (rem * 10 + d) % k, under)` ||

Dica 4: || a sacada pra não tomar TLE/MLE é que você não pode guardar um estado de tamanho k, e nem precisa. A maior soma possível é ~90, então qualquer número > 90 nunca vai ser divisível por k, então nem chamamos a recursão. Isso diminui o estado de 1e4 pra 1e2, o que passa nos 200 casos de teste :) ||