> _Agora vai!_

## Reading
Geek for geeks (explica como faz a Digit Sum): https://www.geeksforgeeks.org/digit-dp-introduction/

### Problems
[USACO] Odometer: http://www.usaco.org/index.php?page=viewproblem2&cpid=435

### Dicas
### Questão 36 - [USACO] Odometer: http://www.usaco.org/index.php?page=viewproblem2&cpid=435

Dica 1: || A primeira parte é visualizar que você tem que resolver o problema separadamente para cada um dos dígitos, ou seja, chamar a dp 10 vezes (iterando `target_digit` de 0 até 9) para saber quantos números tem mais da metade de ocorrências desse `target_digit`.  ||

Dica 2: || A DP precisa de 4 estados: `pos` (posição do dígito atual), `counter` (pra saber quantos dígitos são iguais a `target_digit`), `under` indicando se o número é estritamente menor que o atual ou não e `started`, indicando se o número tem algum dígito além de leading zeros. ||

Dica 3: || Bom, nesse ponto você já deve ter notado que, quando o número tem uma quantidade par de dígitos, o código conta alguns casos a mais. Mais especificamente, conta os casos duas vezes (exemplo: `2211` e `1122`). ||

Dica 4: ||
A alteração que eu sugiro fazer pra remover essas duplicatas é a seguinte:

Além do `target_digit`, teremos um `target_digit2`, e então depois de rodar a resposta faremos um for chamando a dp novamente mas dessa vez subtraindo as duplicatas.

```c++
ans = 0;
for (int digit = 1; digit <= 9; digit++) {
	ans += dp(digit, -1); // target_number, target_number2
}

for (int i = 0; i <= 9; i++) {
	for (int j = i+1; j <= 9; j++) {
		ans -= dp(i, j); // target_number, target_number2
	}
}
```

- se `target_digit2` for -1, significa que estou contando todos os casos, inclusive os com duplicatas.

Quando `target_digit2` não for -1, queremos achar quantos casos são do tipo (1122, 2211, 1212, 1221, ...), pois eles foram contados tanto no `dp(1, -1)` quanto no `dp(2, -1)`, não concorda?

Então pra isso alteramos algumas coisas (**quando target_digit2 != -1**):
- Estou querendo adicionar o dígito `d` no número atual. Se `d != target_digit` e `d != target_digit2`, eu não chamo a recursão.
- No caso base, ao invés de `>=`, usaremos `==`, ou seja, contando os que tem exatamente metade no número de ocorrências. Como só estamos processando números que contém somente os dígitos `{target_digit, target_digit2}`, não precisamos nos preocupar com o resto.
	- É difícil saber o tamanho do número por conta dos leading zeros, talvez até dê pra fazer algo como um estado com o número de dígitos "de verdade" do número atual, mas existe uma sacada interessante:
		- Começamos com 0 ocorrências do dígito `target_digit` no counter.
		- Ao percorrer os dígitos para colocar o adicionar o dígito `d` no número atual, se o número já tiver "começado" `(started || d != 0)`, fazemos a seguinte verificação:
			- Se `target_digit == d`, `counter += 1`
			- Senão, `counter -= 1`
		- No fim, se `counter` for `>= 0` no caso base (ou seja, percorreu todos os dígitos do número), significa que pelo menos metade é o dígito, né? Afinal, começou com 0.
		- Mas com isso também sabemos que, se `counter == 0`, o `target_digit` apareceu exatamente metade das vezes (os contadores foram se "anulando").
		- Também sabemos que, se `counter == 0` e `target_digit2 != -1`, o `target_digit2` também apareceu metade das vezes (afinal ignoramos os outros dígitos na recursão).
		- Porém dessa forma não dá pra armazenar num array como estado pois `counter` pode ser negativo, então é só somar um `offset` nas comparações **e** chamar a dp com esse `offset` ao invés de 0 (afinal, meio que "substituimos o zero por esse offset, ou seja, o meu valor `offset` significaria o meu valor `0`"). Esse `offset` tem que ser pelo menos o tamanho do número (pois o pior caso é subtrair 1 para todos os dígitos do número).
||

Solução:
||
```c++
using ll = long long;

const int MAX_SZ = 20;

ll tb[MAX_SZ][MAX_SZ * 2][2][2];

void reset() { memset(tb, -1, sizeof(tb)); }

/*
    Calcula o número de sequência onde pelo menos metade dos digitos são iguals a target_digit.
    Se target_digit2 não for -1, então calcula o número de sequências onde os dígitos são metade target_digit e a outra metade target_diti2 (para resolver o problema de contar de mais).
    @param pos é a posição do dígito atual
    @param counter é o número de ocorrências do dígito target_digit1
    @param under indica se a sequência atual é estritamente menor que number (upperbound)
    @param started indica se a sequência tem algum dígito além de zeros à esquerda
*/

ll dp(string& number, int target_digit, int target_digit2, int pos, int counter, bool under, bool started) {
    int number_sz = number.size();

    if (pos >= number_sz) {
        if (!started) return 0; // a sequência contém apenas zeros (100 <= X <= Y <= 10^18)

        if (target_digit2 == -1) {
            return (counter >= MAX_SZ); // pelo menos metade dos digitos são iguals a target_digit
        } else {
            return (counter == MAX_SZ); // exatamente metade dos digitos são iguals a target_digit (logo, a outra metade é igual a target_digit2)
        }
    }

    ll& mem = tb[pos][counter][under][started];
    if (mem != -1) return mem;
    mem = 0;

    int limit = 9;
    if (!under) limit = number[pos] - '0';

    for (int d = 0; d <= limit; d++) {
        bool is_under = (under || d < limit);
        bool is_started = (started || d != 0);

        // se queremos contar quantas sequências tem exatamente metade target_digit e target_digit2, os outros dígitos não importam
        if (is_started && target_digit2 != -1 && (target_digit != d && target_digit2 != d)) continue;
        
        int new_counter = counter;
        if (is_started) {
            if (target_digit == d) new_counter++;
            else new_counter--;
        }
        mem += dp(number, target_digit, target_digit2, pos + 1, new_counter, is_under, is_started);
    }

    return mem;
}

ll count_interesting_to(ll ubound) {
    string number = to_string(ubound);
    
    ll ans = 0;
    for (int digit = 0; digit <= 9; digit++) {
        reset();
        ans += dp(number, digit, -1, 0, MAX_SZ, false, false);
    }

    // se os dígitos são exatamente metade i e metade j, eles vão ser contados duas vezes, então removemos as duplicatas
    ll duplicates = 0;

    for (int i = 0; i <= 9; i++) {
        for (int j = i+1; j <= 9; j++) {
            reset();
            duplicates += dp(number, i, j, 0, MAX_SZ, false, false);
        }
    }

    return ans - duplicates;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("odometer.in", "r", stdin);
    freopen("odometer.out", "w", stdout);
    
    ll x, y; cin >> x >> y;

    cout << count_interesting_to(y) - count_interesting_to(x - 1) << '\n';

    return 0;
}
```
||
