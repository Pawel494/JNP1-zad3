#include <vector>
#include <cassert>
#include "fibo.h"


//Funkcja zapisująca liczbę naturalną w systemie Fibonacciego.
std::vector<bool> convert(uint64_t n) {
    std::vector<bool> fibits;
    if (n == 0) {
        fibits.push_back(false);
        return fibits;
    }


    uint64_t a = 1;
    uint64_t b = 2;
    std::vector<int> fibNumbers;
    fibNumbers.push_back(a);

    while (b <= n) {
        fibNumbers.push_back(b);
        b = a + b;
        a = b - a;
    }

    size_t i = fibNumbers.size();
    fibits.resize(i);

    while (i > 1) {
        fibits[i - 1] = true;
        n -= fibNumbers[i - 1];

        while (i > 1 && fibNumbers[i - 1] > n) {
            i--;
            fibits[i - 1] = false;
        }
    }
    fibits[0] = (n != 0);
    return fibits;
}

//Funkcja przekształcająca liczbę do postaci unormowanej.
void Fibo::normalize() {
    size_t size = fibits.size();

    if (size == 1) {
        return;
    }

    if (fibits[size - 1] && fibits[size - 2]) {
        fibits.push_back(true);
        fibits[size - 1] = false;
        fibits[size - 2] = false;
    }

    for (size_t i = size - 2; i > 0; i--) {
        if (fibits[i] && fibits[i - 1]) {
            fibits[i + 1] = true;
            fibits[i] = false;
            fibits[i - 1] = false;
        }
    }

    for (size_t i = 0; i < size - 2; i++) {
        if (fibits[i] && fibits[i + 1]) {
            fibits[i + 2] = true;
            fibits[i] = false;
            fibits[i + 1] = false;
        }
    }
    if (fibits[size - 1] && fibits[size - 2]) {
        fibits.push_back(true);
        fibits[size - 1] = false;
        fibits[size - 2] = false;
    }
}

//Funkcja usuwająca zera wiodące.
void Fibo::deleteLeadingZeros() {
    size_t size = fibits.size();

    while (!fibits[size - 1] && size > 1) {
        fibits.pop_back();
        size--;
    }
}

// ============================== Konstruktory =================================


Fibo::Fibo() {
    fibits.push_back(false);
}

Fibo::Fibo(const std::string &str) {
    bool ok = true;
    for (char c: str) {
        if (c != '0' && c != '1') {
            ok = false;
        }
    }
    assert(ok);
    size_t size = str.size();

    for (size_t i = size; i > 0; i--) {
        fibits.push_back(str[i - 1] == '1');
    }

    normalize();
    deleteLeadingZeros();
}

Fibo::Fibo(const char *str){
    assert(str != nullptr);
    *this = Fibo((std::string) str);
}

Fibo::Fibo(const Fibo &f) {
    fibits = f.fibits;
}

Fibo::Fibo(uint64_t n) {
    fibits = convert(n);
    normalize();
}

Fibo::Fibo(uint32_t n) : Fibo((uint64_t) n) {}

Fibo::Fibo(uint16_t n) : Fibo((uint64_t) n) {}


Fibo::Fibo(int n) {
    assert(n >= 0);
    *this = Fibo((uint64_t) n);
}

// ============================== Operatory ====================================

/* Funkcja potrzebna do operatora +=. Przechodzi przez wektor i usuwa z
 * niego dwójki tak, żeby znowu przedstawiał liczbę w systemie Fibonacciego.
 * Zasada działania opiera się na 4-elementowym wagoniku który przechodzi
 * od lewej do prawej. Wymaga aby wektor na wejściu miał długość >= 4.
 * */
void Fibo::delete2(std::vector<int> &v) {
    size_t n = v.size();
    size_t a, b, c, d;
    a = n, b = n - 1, c = n - 2, d = n - 3;
    while (d > 0) {
        if (v[a-1] == 0 && v[b-1] == 3 && v[c-1] == 0) {
            v[a-1] = 1;
            v[b-1] = 1;
            v[c-1] = 0;
            v[d-1] += 1;
        } else if (v[a-1] == 0 && v[b-1] == 2 && v[c-1] == 0) {
            v[a-1] = 1;
            v[b-1] = 0;
            v[c-1] = 0;
            v[d-1] += 1;
        } else if (v[a-1] == 0 && v[b-1] == 2 && v[c-1] == 1) {
            v[a-1] = 1;
            v[b-1] = 1;
            v[c-1] = 0;
        } else if (v[a-1] == 0 && v[b-1] == 1 && v[c-1] == 2) {
            v[a-1] = 1;
            v[b-1] = 0;
            v[c-1] = 1;
        }
        a--;
        b--;
        c--;
        d--;
    }
    a = 3;
    b = 2;
    c = 1;
    d = 0;
    if(v[b] == 0 && v[c] == 2 && v[d] == 1) {
        v[b] = 1;
        v[c] = 1;
        v[d] = 0;
    }
    if(v[b] == 0 && v[c] == 1 && v[d] == 2) {
        v[b] = 1;
        v[c] = 0;
        v[d] = 1;
    }
    if (v[c] == 3) {
        v[b] = 1;
        v[c] = 1;
        v[d] = 1;
    }
    if (v[b] == 0 && v[c] == 2 && v[d] == 0) {
        v[b] = 1;
        v[c] = 0;
        v[d] = 1;
    }
    if (v[b] == 1 && v[c] == 2 && v[d] == 0) {
        v[a] = 1;
        v[b] = 0;
        v[c] = 1;
        v[d] = 0;
    }
    if (v[b] == 0 && v[c] == 1 && v[d] == 2) {
        v[b] = 1;
        v[c] = 0;
        v[d] = 1;
    }
    if (v[d] == 3) {
        v[c] = 1;
        v[d] = 1;
    }
    if (v[c] == 0 && v[d] == 2) {
        v[c] = 1;
        v[d] = 0;
    }
}

Fibo &Fibo::operator=(const Fibo &f) {
    if (this == &f) {
        return *this;
    }
    fibits = f.fibits;
    return *this;
}

/* Najpierw zwyczajnie dodaje liczby do siebie i wynik trzyma na wektorze
 * intów. Potem funkcja delete2 usuwa dwójki, a wektor z powrotem jest
 * przepisywany na fibits.
 * */
Fibo &Fibo::operator+=(const Fibo &f2) {
    size_t n = std::max(fibits.size(), f2.fibits.size());
    std::vector<int> v;

    for(size_t i = 0; i < n; i++) {
        if(i >= fibits.size())
            v.push_back(f2.fibits[i]);
        else if(i >= f2.fibits.size())
            v.push_back(fibits[i]);
        else
            v.push_back(fibits[i] + f2.fibits[i]);
    }

    v.push_back(0);
    while(v.size() < 4)
        v.push_back(0);

    delete2(v);

    while(v[v.size() - 1] == 0)
        v.pop_back();

    for(size_t i = 0; i < v.size(); i++) {
        if((i) < fibits.size())
            fibits[i] = v[i];
        else
            fibits.push_back(v[i]);
    }

    normalize();
    return *this;
}

const Fibo operator+(Fibo f1, const Fibo &f2) {
    return f1 += f2;
}

Fibo& Fibo::operator&=(const Fibo& that) {

    for(size_t i = fibits.size(); i > 0; i--) {
        if (i - 1 >= that.fibits.size()) {
            fibits[i-1] = 0;
        } else {
            fibits[i-1] = (fibits[i-1] & that.fibits[i-1]);
        }
    }

    bool tmp = false;

    for(auto && fibit : fibits) {
        if (fibit == 1)
            tmp = true;
    }

    if(tmp == 0) {
        int i = fibits.size();
        while (i > 1) {
            i--;
            fibits.pop_back();
        }
    } else {
        deleteLeadingZeros();
        normalize();
    }
    return *this;
}

Fibo& Fibo::operator|=(const Fibo& that) {
    size_t max = std::max(fibits.size(), that.fibits.size());
    size_t min = std::min(fibits.size(), that.fibits.size());

    for (size_t i = 0; i < min; i++) {
        fibits[i] = fibits[i] | that.fibits[i];
    }

    for (size_t i = 0; i < max; i++) {
        if (fibits.size() < i + 1) {
            fibits.push_back(that.fibits[i]);
        }
    }

    deleteLeadingZeros();
    normalize();
    return *this;
}

Fibo& Fibo::operator^=(const Fibo& that) {
    size_t max = std::max(fibits.size(), that.fibits.size());
    size_t min = std::min(fibits.size(), that.fibits.size());

    for (size_t i = 0; i < min; i++) {
        fibits[i] = fibits[i] ^ that.fibits[i];
    }

    for (size_t i = 0; i < max; i++) {
        if (fibits.size() < i + 1) {
            fibits.push_back(that.fibits[i]);
        }
    }
    deleteLeadingZeros();
    normalize();
    return *this;
}

Fibo& Fibo::operator<<=(const size_t  &n) {
    for(size_t i = 0; i < n; i++)
        fibits.push_back(false);
    for(size_t i = fibits.size() - 1; i >= n; i--) {
        fibits[i] = fibits[i - n];
    }
    for(int i = n - 1; i >= 0; i--)
        fibits[i] = false;

     return *this;
}

const bool Fibo::operator==(const Fibo &that) {
    return fibits == that.fibits;
}

bool Fibo::operator!=(const Fibo &that) {
    return fibits != that.fibits;
}

bool Fibo::operator<(const Fibo &that) {
    if(fibits.size() < that.fibits.size())
        return true;
    if(fibits.size() > that.fibits.size())
        return false;

    for(size_t i = fibits.size(); i > 0; i--) {
        if(fibits[i-1] < that.fibits[i-1])
            return true;
        if(fibits[i-1] > that.fibits[i-1])
            return false;
    }

    return false;
}

bool Fibo::operator<=(const Fibo &that) {
    return ((*this) < that || (*this) == that);
}

bool Fibo::operator>(const Fibo &that) {
    return !((*this) <= that);
}

bool Fibo::operator>=(const Fibo &that) {
    return ((*this) > that || (*this) == that);
}

const Fibo operator&(const Fibo &fib1, const Fibo &fib2) {
    return Fibo(fib1) &= fib2;
}

const Fibo operator|(const Fibo &fib1, const Fibo &fib2) {
    return Fibo(fib1) |= fib2;
}

const Fibo operator^(const Fibo &fib1, const Fibo &fib2) {
    return Fibo(fib1) ^= fib2;
}

const Fibo operator<<(const Fibo &fib1, const size_t  &n) {
    return Fibo(fib1) <<= n;
}

const bool operator==(const Fibo &fib1, const Fibo &fib2) {
    return Fibo(fib1) == fib2;
}

const bool operator<=(const Fibo &fib1, const Fibo &fib2) {
    return Fibo(fib1) <= fib2;
}

const bool operator>=(const Fibo &fib1, const Fibo &fib2) {
    return Fibo(fib1) >= fib2;
}

const bool operator!=(const Fibo &fib1, const Fibo &fib2) {
    return Fibo(fib1) != fib2;
}

const bool operator<(const Fibo &fib1, const Fibo &fib2) {
    return Fibo(fib1) < fib2;
}

const bool operator>(const Fibo &fib1, const Fibo &fib2) {
    return Fibo(fib1) > fib2;
}

std::ostream &operator<<(std::ostream &os, const Fibo &f ) {
    for(size_t i = f.fibits.size(); i > 0; i--)
        os << f.fibits[i-1];
    return os;
}

const size_t Fibo::length() {
    return fibits.size();
}

const Fibo Zero() {
    return Fibo("0");
}

const Fibo One() {
    return Fibo("1");
}