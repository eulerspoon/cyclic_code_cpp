#include <iostream>
#include <bitset>

using namespace std;

const int n = 15;
const int r = 4;
const bitset<5> g = 0b10011; // g(x) = x^4 + x + 1

bitset<r> divide(bitset<n> dividend) {
    bitset<n> remainder = dividend;
    for (int i = n - 1; i >= r - 1; i--) {
        if (remainder[i]) {
            for (int j = 0; j <= r; j++) {
                remainder[i - j] = remainder[i - j] ^ g[r - j];
            }
        }
    }
    bitset<r> res;
    for (int i = 0; i < r; i++) res[i] = remainder[i];
    return res;
}

int main() {
    cout << "Таблица синдромов ошибок кратности 1:\n";
    cout << "Бит ошибки | Вектор ошибки  | Синдром (4 бита)\n";
    cout << "--------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        bitset<n> err(1 << i); // ошибка в i-м бите
        bitset<r> syndrome = divide(err);
        cout << i + 1 << "\t\t" << err << "\t" << syndrome << "\n";
    }
    return 0;
}
