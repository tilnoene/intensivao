#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
using ll = long long;

const int MAX_SZ = 20;

ll tb[MAX_SZ][MAX_SZ][2][2][MAX_SZ][MAX_SZ];

void reset() { memset(tb, -1, sizeof(tb)); }

/*
    Calcula o número de sequência onde pelo menos metade dos digitos são iguals a target_digit.
    Se target_digit2 não for -1, então calcula o número de sequências onde os dígitos são metade target_digit e a outra metade target_diti2 (para resolver o problema de contar de mais).
    @param pos é a posição do dígito atual
    @param counter é o número de ocorrências do dígito target_digit1
    @param under indica se a sequência atual é estritamente menor que number (upperbound)
    @param started indica se a sequência tem algum dígito além de zeros à esquerda
*/

ll dp(string& number, int target_digit, int target_digit2, int pos, int counter, bool under, bool started, int sz, int counter2) {
    if (pos >= (int)number.size()) {
        if (target_digit2 == -1) {
            return (counter >= (sz+1)/2); // pelo menos metade dos digitos são iguals a target_digit
        } else {
            return (counter == counter2); // exatamente metade dos digitos são iguals a target_digit (logo, a outra metade é igual a target_digit2)
        }
    }

    ll& mem = tb[pos][counter][under][started][sz][counter2];
    if (mem != -1) return mem;
    mem = 0;

    int limit = 9;
    if (!under) limit = number[pos] - '0';

    for (int d = 0; d <= limit; d++) {
        bool is_under = (under || d < limit);
        bool is_started = (started || d != 0);

        // se queremos contar quantas sequências tem exatamente metade target_digit e target_digit2, os outros dígitos não importam
        if (is_started && target_digit2 != -1 && (target_digit != d && target_digit2 != d)) continue;

        mem += dp(number, target_digit, target_digit2, pos + 1, counter + (is_started && d == target_digit), is_under, is_started, sz + is_started, counter2 + (is_started && d == target_digit2));
    }

    return mem;
}

ll count_interesting_to(ll ubound) {
    string number = to_string(ubound);
    
    ll ans = 0;
    for (int digit = 0; digit <= 9; digit++) {
        reset();
        ans += dp(number, digit, -1, 0, 0, false, false, 0, 0);
    }

    // se a quantidade de dígitos é exatamente metade i e metade j, eles vão ser contados duas vezes, então removemos as duplicatas
    ll duplicates = 0;

    for (int i = 0; i <= 9; i++) {
        for (int j = i+1; j <= 9; j++) {
            reset();
            duplicates += dp(number, i, j, 0, 0, false, false, 0, 0);
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