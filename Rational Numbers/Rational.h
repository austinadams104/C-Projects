#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational {
public:
	Rational(int n = 0, int d = 1); 
	Rational(Rational const&); 
	operator float(); 
	operator double(); 
	Rational& operator+=(Rational const &); 
	Rational& operator-=(Rational const &); 
	Rational& operator*=(Rational const &); 
	Rational& operator/=(Rational const &); 
	Rational& operator=(Rational const&);
	int getNumerator()const; 
	int getDenominator()const;
	int gcd(int, int);
	void simplify(int, int);
private:
	int numerator; 
	int denominator;
};

bool operator<(Rational const &, Rational const &); 
bool operator==(Rational const &, Rational const &); 
bool operator!=(Rational const &, Rational const &); 
bool operator>(Rational const &, Rational const &); 
bool operator<=(Rational const &, Rational const &);
bool operator>=(Rational const &, Rational const &);
Rational operator+(Rational const &, Rational const &); 
Rational operator-(Rational const &, Rational const &); 
Rational operator*(Rational const &, Rational const &); 
Rational operator/(Rational const &, Rational const &);
std::ostream & operator<<(std::ostream &, Rational const&); 
std::istream & operator>>(std::istream &, Rational &);

#endif