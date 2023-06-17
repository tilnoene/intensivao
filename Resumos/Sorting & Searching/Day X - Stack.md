>_push, pop e top_

### Reading
CSAcademy, Stack Introduction: https://csacademy.com/lesson/stack_introduction/
- _esse post ficou **muito** bem feito, até simula o problema clássico de brackets matching_

LIFO: Last In First Out, ou seja, é uma pilha, uma pilha de cartas, onde você só adiciona cartas no topo e tira cartas do topo.

"Therefore, the closing symbols match the opening symbols in reverse order of their appearance.". Isso é uma dica de que podemos usar stack pra resolver.

Mas tem problemas que não necessariamente tem essa propriedade, um exemplo é esse:

[CSES] Nearest Smaller Values: https://cses.fi/problemset/task/1645

Você já deve ter feito, e também se pensar em alguma ideia agora, provavelmente vai envolver sets com busca binária e etc. Isso resolve o problema, mas é O(N log(N)), o que as vezes é muito apertado para uma transição em uma DP ou algo do tipo.

Consegue resolver usando stack?

Dica 1: || a stack vai salvar um par ordenado contendo o valor do elemento e sua posição no array original. ||

Dica 2: || sempre que passarmos por um elemento novo vamos inseri-lo na pilha. ||

Dica 3: || vamos manter os elementos da stack sempre em ordem crescente. ||

Solução:
||
```c++
stack<pair<int, int>> st;
    
for (int i = 0; i < n; i++) {
	// remove os elementos que são maiores ou iguais ao atual, pois eles nunca mais vão ser resposta pra elementos da direita (afinal o arr[i] é um candidato melhor do que todos eles)
	while (st.size() && st.top().first >= arr[i]) {
		st.pop();
	}

		if (st.empty()) { // se for vazia significa que não sobrou ninguém, então não existe ninguém menor que arr[i]
		ans[i] = 0;
	} else { // se existe, o que está no topo da pilha é o mais próximo
		ans[i] = st.top().second;
	}
	
	st.push({arr[i], i + 1});
}
```

Dá pra ver isso no sample da questão, onde quando processamos o terceiro elemento (1), podemos remover todos os outros dois à esquerda pois são maiores ou iguais que 1, então nunca mais vão ser respostas daqui pra frente.
||

Essa técnica se chama **monotonic stack**, pois os elementos na pilha sempre estão em ordem crescente.

### Reading
Handbook, pg. 89, 8.2 Nearest smaller elements: https://usaco.guide/CPH.pdf#page=89
- _explica a solução do problema Nearest smaller elements_
CS Academy, Stack Application: Soldiers Row: https://csacademy.com/lesson/stack_application_soldiers_row/
- _explica um problema parecido, com animação_

### Problems
[CSES] Nearest Smaller Values: https://cses.fi/problemset/task/1645

[CSES] Advertisement: https://cses.fi/problemset/task/1142/
