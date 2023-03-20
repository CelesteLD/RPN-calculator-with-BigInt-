/**
 * @file bigint.h
 * @author Celeste Luis Díaz (alu0101321660@ull.edu.es)
 * @brief Clase BigInt<Base> diseñada para la primera práctica de 
 * Algoritmos y Estructuras de Datos Avanazadas 2022-2023
 * 
 *         ** Incompleta. Problemas con la Base Hexadecimal
 * 
 * @version 0.1
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

template <size_t Base> class BigInt;
template <size_t Base> std::ostream& operator<<(std::ostream&, const BigInt<Base>&);
template <size_t Base> bool operator==(const BigInt<Base>&, const BigInt<Base>&);
template <size_t Base> bool operator>(const BigInt<Base>&, const BigInt<Base>&);
template <size_t Base> bool operator<(const BigInt<Base>&, const BigInt<Base>&);
template <size_t Base> BigInt<Base> operator+(const BigInt<Base>&, const BigInt<Base>&);

template <size_t Base = 10>
class BigInt {

    private:
        std::vector<char> digits_;
        int sign_ = 1;
    
    public:

        // Constructors
        BigInt() = default;
        BigInt(long nr = 0);
        BigInt(std::string&);
        BigInt(const char*);
        BigInt(const BigInt<Base>&);

        // Asignation Operator
        BigInt<Base>& operator=(const BigInt<Base>&);

        // Flow Operators
        friend std::ostream& operator<< <>(std::ostream&, const BigInt<Base>&);

        // Accessors
        int sign() const;
        char operator[](int) const;

        // Comparators
        friend bool operator== <>(const BigInt<Base>&, const BigInt<Base>&);
        bool operator!=(const BigInt<Base>&) const;
        friend bool operator> <>(const BigInt<Base>&, const BigInt<Base>&);
        bool operator>=(const BigInt<Base> &) const;
        friend bool operator< <>(const BigInt<Base>&, const BigInt<Base>&);
        bool operator<=(const BigInt<Base>&) const;

        // Increment and Decrements
        BigInt<Base>& operator++(); // Pre-incremento
        BigInt<Base> operator++(int); // Post-incremento
        BigInt<Base>& operator--(); // Pre-decremento
        BigInt<Base> operator--(int); // Post-decremento
        

        // Arithmetic Operators
        friend BigInt<Base> operator+ <>(const BigInt<Base>&, const BigInt<Base>&);
        BigInt<Base> operator-(const BigInt<Base> &) const;
        BigInt<Base> operator-() const;
        BigInt<Base> operator*(const BigInt<Base>&) const;

        // XX
        std::string toString() const;
};

template <size_t Base>
BigInt<Base>::BigInt(long nr) {
    //std::cout << "Contructor long long : " << nr << std::endl;
    if (nr < 0) {
        //std::cout << "El número es negativo" << std::endl;
        sign_ = -1;
        nr = -nr;
    }
    do {
        digits_.push_back(nr % Base + '0');
        nr /= Base;
    } while (nr > 0);
    std::reverse(digits_.begin(), digits_.end());
}

template <size_t Base>
BigInt<Base>::BigInt(std::string& str) {
    //std::cout << "Constructor string : " << str << std::endl;
    if (str[0] == '-') {
        //std::cout << "El número es negativo" << std::endl;
        sign_ = -1;
        str.erase(0, 1);
    }
    for (int i = 0; i < str.size(); ++i) {
        digits_.push_back(str[i] - 0);
    }
}

template <size_t Base>
BigInt<Base>::BigInt(const char* str) {
    //std::cout << "Constructor char* : " << str << std::endl;
    if (str[0] == '-') {
        //std::cout << "El número es negativo" << std::endl;
        sign_ = -1;
        str++;
    }
    for (int i = 0; i < strlen(str); ++i) {
        digits_.push_back(str[i] - 0);
    }
}

template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& a) {
    //std::cout << "Constructor copia" << std::endl;
    sign_ = a.sign_;
    digits_ = a.digits_;
    if (sign_ == -1) {
        //std::cout << "El número es negativo" << std::endl;
    }
}

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& a) {
    //std::cout << "Asignación" << std::endl;
    sign_ = a.sign_;
    digits_ = a.digits_;
    return *this;
}

template <size_t Base>
std::ostream& operator<<(std::ostream& os, const BigInt<Base>& a) {
    if (a.sign_ == -1) {
        os << '-';
    }
    for (int i = 0; i < a.digits_.size(); ++i) {
        os << a.digits_[i];
    }
    return os;
}

template <size_t Base>
int BigInt<Base>::sign() const {
    return sign_;
}

template <size_t Base>
char BigInt<Base>::operator[](int i) const {
    return digits_[i];
}

template <size_t Base>
bool operator==(const BigInt<Base>& a, const BigInt<Base>& b) {
    if (a.sign_ != b.sign_) {
        return false;
    }
    if (a.digits_.size() != b.digits_.size()) {
        return false;
    }
    for (int i = 0; i < a.digits_.size(); ++i) {
        if (a.digits_[i] != b.digits_[i]) {
            return false;
        }
    }
    return true;
}

template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& a) const {
    return !(*this == a);
}

template <size_t Base>
bool operator>(const BigInt<Base>& a, const BigInt<Base>& b) {
    if (a.sign_ != b.sign_) {
        return a.sign_ > b.sign_;
    }
    if (a.digits_.size() != b.digits_.size()) {
        return a.sign_ * (a.digits_.size() > b.digits_.size());
    }
    for (int i = 0; i < a.digits_.size(); ++i) {
        if (a.digits_[i] != b.digits_[i]) {
            return a.sign_ * (a.digits_[i] > b.digits_[i]);
        }
    }
    return false;
}

template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base>& a) const {
    return (*this > a) || (*this == a);
}

template <size_t Base>
bool operator<(const BigInt<Base>& a, const BigInt<Base>& b) {
    return !(a >= b);
}

template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base>& a) const {
    return !(*this > a);
}

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator++() {
    BigInt<Base> one(1);
    *this = *this + one;
    return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {
    BigInt<Base> aux(*this);
    ++(*this);
    return aux;
}

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator--() {
    BigInt<Base> one(1);
    *this = *this - one;
    return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {
    BigInt<Base> aux(*this);
    --(*this);
    return aux;
}

template <size_t Base>
BigInt<Base> operator+(const BigInt<Base>& a, const BigInt<Base>& b) {
    if (a.sign() == b.sign()) {
        // Sumar los números empezando por el final
        int i = a.digits_.size() - 1;
        int j = b.digits_.size() - 1;
        int carry = 0;
        std::string result = "";

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) {
                sum += a[i] - '0';
                --i;
            }
            if (j >= 0) {
                sum += b[j] - '0';
                --j;
            }
            carry = sum / Base;
            sum %= Base;
            result += sum + '0';
        }
        std::reverse(result.begin(), result.end());

        BigInt<Base> res(result);
        res.sign_ = a.sign_;

        return res;
    } else if (a.sign() == -1) {
        return b - (-a);
    } else {
        return a - (-b);
    }


}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base>& a) const {
    // Restar los números empezando por el final
    if (a.sign() == -1) {
        return *this + (-a);
    } else if (sign() == -1) {
        return -((-*this) + a);
    } else if (*this < a) {
        return -(a - *this);
    }

    int i = digits_.size() - 1;
    int j = a.digits_.size() - 1;
    int carry = 0;
    std::string result = "";

    while (i >= 0 || j >= 0 || carry) {
        if (digits_[i] < a[j]) {
            int sum = digits_[i] - '0' + Base - carry;
            if (j >= 0) {
                sum -= a[j] - '0';
                --j;
            }
            carry = 1;
            result += sum + '0';
        } else {
            int sum = digits_[i] - '0' - carry;
            if (j >= 0) {
                sum -= a[j] - '0';
                --j;
            }
            carry = 0;
            result += sum + '0';
        }
        --i;
    }
    std::reverse(result.begin(), result.end());

    if (result[0] == '0') {
        result.erase(0, 1);
    }
    
    BigInt<Base> res(result);

    return res;

}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-() const {

    if (Base == 2) {
        // Cambiar cada 1 por un 0 y viceversa
        std::string result = "";
        for (int i = 0; i < digits_.size(); ++i) {
            if (digits_[i] == '0') {
                result += '1';
            } else {
                result += '0';
            }
        }
        BigInt<Base> res(result);
        return res;
    }
    
    BigInt<Base> res(*this);
    if (res.sign_ == 1) {
        res.sign_ = -1;
        //std::cout << "El número es negativo" << std::endl;
    } else {
        res.sign_ = 1;
        //std::cout << "El número es positivo" << std::endl;
    }

    return res;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base>& a) const {
    BigInt<Base> Zero("");

    BigInt<Base> One("1");

    //Sumar *this hasta que a == Zero

    BigInt<Base> aux("0");
    BigInt<Base> aAux("0");
    // Si el signo de A es negativo : PAsar a positivo y operar : Cambiar el signo del resultado
    if (a.sign() == -1) {
        aux = -(*this);
        aAux = -a;
    } else {
        aux = *this;
        aAux = a;
    }
    BigInt<Base> res("0");


    while (aAux >= One) {
        res = res + aux;
        aAux = --aAux;
    }

    if (a.sign() == -1) {
        res.sign_ = -1;
    }

    return res;   
}

template <size_t Base>
std::string BigInt<Base>::toString() const {
    std::string result = "";
    if(sign_ == -1) {
        result += '-';
    }
    for (int i = 0; i < digits_.size(); ++i) {
        result += digits_[i];
    }
    return result;
}