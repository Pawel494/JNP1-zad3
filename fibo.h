/*
 * Interfejs klasy Fibo reprezentującej liczby zapisane w systemie
 * Fibonacciego.
 *
 * Autorzy: Paweł Majewski i Anna Kalisz
 *
 * "System Fibonacciego (https://pl.wikipedia.org/wiki/System_Fibonacciego) to
 * binarny, pozycyjny system liczbowy, w którym poszczególnym pozycjom
 * odpowiadają kolejne liczby Fibonacciego. W zapisie liczby nie używa się
 * pierwszych dwóch liczb z ciągu Fibonacciego. Zaczynającemu się od 1 ciągowi
 * cyfr 0 i 1 (tylko takich się używa) an…a3a2 odpowiada liczba
 * an*F(n) + … + a3*F(3) + a2*F(2).
 * Wyjątkiem jest liczba 0, którą zapisujemy jako 0."
 */
#ifndef FIBONACCI_FIBO_H
#define FIBONACCI_FIBO_H

#include <string>
#include <vector>
#include <ostream>

class Fibo {

    friend std::ostream &operator<<(std::ostream &, const Fibo&);

public:
    //konstruktory
    explicit Fibo(const std::string &str);
    explicit Fibo(const char *str);
    Fibo(void);
    Fibo(const Fibo &f);
    Fibo(uint64_t n);
    Fibo(uint32_t n);
    Fibo(uint16_t n);
    Fibo(int n);
    Fibo(char) = delete;
    explicit Fibo(bool) = delete;

    //operatory
    Fibo  &operator=(const Fibo &f);
    Fibo &operator+=(const Fibo &f);
    Fibo &operator&=(const Fibo &that);
    Fibo &operator|=(const Fibo &that);
    Fibo &operator^=(const Fibo &that);
    Fibo &operator<<=(const size_t &n);
    const bool operator==(const Fibo &that);
    bool operator<(const Fibo &that);
    bool operator<=(const Fibo &that);
    bool operator!=(const Fibo &that);
    bool operator>(const Fibo &that);
    bool operator>=(const Fibo &that);

    //metody
    const size_t length();

private:

    std::vector<bool> fibits;

    void normalize();

    void deleteLeadingZeros();

    void delete2(std::vector<int> &v);

};

const Fibo operator+(Fibo f1, const Fibo &f2);
const Fibo operator&(const Fibo &fib1, const Fibo &fib2);
const Fibo operator|(const Fibo &fib1, const Fibo &fib2);
const Fibo operator^(const Fibo &fib1, const Fibo &fib2);
const Fibo operator<<(const Fibo &fib1, const size_t &n);
const bool operator==(const Fibo &fib1, const Fibo &fib2);
const bool operator<=(const Fibo &fib1, const Fibo &fib2);
const bool operator>=(const Fibo &fib1, const Fibo &fib2);
const bool operator!=(const Fibo &fib1, const Fibo &fib2);
const bool operator<(const Fibo &fib1, const Fibo &fib2);
const bool operator>(const Fibo &fib1, const Fibo &fib2);


const Fibo Zero();
const Fibo One();

#endif //FIBONACCI_FIBO_H
