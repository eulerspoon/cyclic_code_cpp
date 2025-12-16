#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>

using namespace std;

const int n = 15;

long long comb(int n, int k) {
    if (k > n) return 0;
    long long res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return res;
}

int main() {
    cout << "Таблица ошибок, сортированных по кратности:\n";
    cout << "Кратность (i) | Число ошибок C(15,i)\n";
    cout << "-------------------------------------\n";
    long long total = 0;
    for (int i = 1; i <= n; i++) {
        long long c = comb(n, i);
        total += c;
        cout << i << "\t\t" << c << "\n";
    }
    cout << "-------------------------------------\n";
    cout << "Всего ошибок: " << total << " (2^15 - 1 = " << (1 << 15) - 1 << ")\n";
    return 0;
}
