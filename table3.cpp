#include <iostream>
#include <bitset>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const int n = 15;
const int k = 11;
const int r = 4;
const bitset<5> g = 0b10011;
const bitset<k> info = 0b01011010001;

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

bitset<n> encode(bitset<k> data) {
    bitset<n> shifted = bitset<n>(data.to_ullong()) << r;
    bitset<r> rem = divide(shifted);
    return shifted | bitset<n>(rem.to_ullong());
}

vector<bitset<n>> generate_errors(int weight) {
    vector<bitset<n>> errors;
    for (int mask = 1; mask < (1 << n); mask++) {
        bitset<n> err(mask);
        if (err.count() == weight) errors.push_back(err);
    }
    return errors;
}

long long comb(int n, int k) {
    if (k > n) return 0;
    long long res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return res;
}

int main() {
    bitset<n> codeword = encode(info);
    cout << "Закодированное слово: " << codeword << "\n\n";

    vector<long long> detected(16, 0);
    vector<long long> total(16, 0);

    for (int w = 1; w <= n; w++) {
        total[w] = comb(n, w);
        auto errors = generate_errors(w);
        for (auto &err : errors) {
            bitset<n> received = codeword ^ err;
            bitset<r> syndrome = divide(received);
            if (syndrome != 0) detected[w]++;
        }
    }

    cout << "Результирующая таблица (обнаруживающая способность):\n";
    cout << "i\tC(15,i)\tОбнаружено N0\tC0, %\n";
    cout << fixed << setprecision(2);
    for (int i = 1; i <= n; i++) {
        double c0 = (detected[i] * 100.0) / total[i];
        cout << i << "\t" << total[i] << "\t" << detected[i] 
             << "\t\t" << c0 << "%\n";
    }

    cout << "\nОбщее число возможных ошибок: " << (1 << n) - 1 << "\n";
    return 0;
}
