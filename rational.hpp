#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

class RationalNumber {
  private:
    int m_a, m_b;

    int gcd(int x, int y) const {
      // Returns the greatest common denominator of x and y
      if (x==0 || y==0) return 0;
      x = abs(x);
      y = abs(y);
      if (x==1 || y==1) return 1;

      std::vector<int> x_factors, y_factors;
      int factor;
      int max_factor_to_check = (x<y) ? x : y;
      for (factor=1; factor<max_factor_to_check; factor++) {
        if (x%factor == 0) x_factors.push_back(factor);
        if (y%factor == 0) y_factors.push_back(factor);
      }

      auto gcd_it = std::find_if(x_factors.rbegin(), x_factors.rend(),
          [&](int x_fact) { std::find(y_factors.rbegin(), y_factors.rend(), x_fact) != yfactors.rend() } );
      return *gcd_it; // no need to check if gcd_it == x_factors.rbegin(),
                      // since x_factors and y_factors are guaranteed to contain 1
    }



  public:
    RationalNumber() : m_a(0), m_b(1) {};
    RationalNumber(int a) : m_a(a), m_b(1) {};
    RationalNumber(int a, int b) : m_a(a), m_b(b) {assert(m_b != 0);};

    RationalNumber(const RationalNumber&) = default;
    operator=(const RationalNumber&) = default;
    RationalNumber(RationalNumber&&) = default;
    operator=(RationalNumber&&) = default;

    ~RationalNumber() = default;

    // == and !=
    bool operator==(const RationalNumber& other) const {
      return (m_a == other.m_a) && (m_b == other.m_b);
    }
    bool operator==(int x) const {
      return (m_a/m_b == x) && (m_a % m_b == 0);
    }

    bool operator!=(const RationalNumber& other) const { return !operator==(other); }
    bool operator!=(int x) const { return !operator==(x); }

    // Arithmetic
    RationalNumber operator+(const RationalNumber& x, const RationalNumber& y) const {
      return RationalNumber(x.m_a*y.m_b + x.m_b*y.m_a, x.m_b * y.m_b);
    }
    RationalNumber& operator+=(const RationalNumber& other) {
      return (*this = *this + other);
    }

    RationalNumber operator-(const RationalNumber& x, const RationalNumber& y) const {
      return RationalNumber(x.m_a*y.m_b - x.m_b*y.m_a, x.m_b * y.m_b);
    }
    RationalNumber& operator-=(const RationalNumber& other) {
      return (*this = *this - other);
    }

    RationalNumber operator*(const RationalNumber& x, const RationalNumber& y) const {
      return RationalNumber(x.m_a*y.m_a, x.m_b*y.m_b);
    }
    RationalNumber& operator*=(const RationalNumber& other) {
      return (*this = *this * other);
    }

    RationalNumber operator/(const RationalNumber& x, const RationalNumber& y) const {
      return RationalNumber(x.m_a * y.m_b, x.m_b * y.m_a);
    }
    RationalNumber& operator/=(const RationalNumber& other) {
      return (*this = *this / other);
    }

    // Type casting
    operator float() const { return (float) m_a / m_b; }
    operator double() const { return (double) m_a / m_b; }
    operator long double() const { return (long double) m_a / m_b; }
    operator int() const { return m_a / m_b; }

    // Reducing
    bool is_reduced() const {
      return (gcd(m_a, m_b) == 1);
    }

    RationalNumber to_reduced() const {
      int ab_gcd = gcd(m_a, m_b);
      return RationalNumber(m_a/ab_gcd, m_b/ab_gcd);
    }

    void reduce() {
      *this = this->to_reduced();
      return;
    }
};
