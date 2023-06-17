#include <bits/stdc++.h>

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;
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