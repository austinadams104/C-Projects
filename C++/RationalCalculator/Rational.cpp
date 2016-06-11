#include "Rational.h"

Rational::Rational(int n, int d)
{
	numerator = n;
	denominator = d;
	simplify(n, d);
}

Rational::Rational(Rational const& fraction)
{
	numerator = fraction.getNumerator();
	denominator = fraction.getDenominator();
	simplify(numerator, denominator);
}

int Rational::getNumerator()const{
	return numerator;
}
int Rational::getDenominator()const{
	return denominator;
}

Rational::operator float()
{
	return static_cast<float>(numerator/denominator);
}
Rational::operator double()
{
	return static_cast<double>(numerator/denominator);
}

int Rational::gcd(int x, int y)
{
	if (x%y == 0)
		return y;
	else
		return gcd(y, x%y);
	
}

void Rational::simplify(int num, int denom)
{
	numerator = num / gcd(num, denom);
	denominator = denom / gcd(num, denom);	
}

 Rational& Rational::operator+=(Rational const & fraction)
{
	int rightNum = fraction.getNumerator();
	int rightDenom = fraction.getDenominator();

	rightNum *= denominator;
	rightDenom *= denominator;

	numerator = numerator*fraction.getDenominator();
	denominator = denominator*fraction.getDenominator();
	
	numerator = numerator + rightNum;
	simplify(numerator, denominator);
	return *this;
	
}
Rational& Rational::operator-=(Rational const & fraction)
{
	int rightNum = fraction.getNumerator();
	int rightDenom = fraction.getDenominator();

	rightNum *= denominator;
	rightDenom *= denominator;

	numerator = numerator*fraction.getDenominator();
	denominator = denominator*fraction.getDenominator();

	numerator = numerator - rightNum;
	simplify(numerator, denominator);
	return *this;
}
Rational& Rational::operator*=(Rational const & fraction)
{
	numerator = numerator * fraction.getNumerator();
	denominator = denominator * fraction.getDenominator();
	simplify(numerator, denominator);
	return *this;
}
Rational& Rational:: operator/=(Rational const & fraction)
{
	numerator = numerator*fraction.getDenominator();
	denominator = denominator*fraction.getNumerator();
	simplify(numerator, denominator);
	return *this;
}
Rational& Rational:: operator=(Rational const& fraction)
{
	numerator = fraction.getNumerator();
	denominator = fraction.getDenominator();
	return *this;
}

bool operator==(Rational const &left, Rational const &right)
{
	if (left.getNumerator() == right.getNumerator() &&(right.getNumerator() == right.getNumerator()))
		return true;
	else
		return false;
}
bool operator!=(Rational const &left, Rational const &right)
{
	if (left == right)
		return false;
	else
		return true;
}
bool operator<(Rational const &left, Rational const &right)
{
	double lefty = static_cast<double>((left.getNumerator()) / static_cast<double>(left.getDenominator()));
	double righty = (static_cast<double>(right.getNumerator()) / static_cast<double>(right.getDenominator()));

	if (lefty < righty)
		return true;
	else
		return false;
}
bool operator>(Rational const &left, Rational const &right)
{
	if (left < right)
		return false;
	else
		return true;
}
bool operator<=(Rational const &left, Rational const &right)
{
	if (left == right)
		return true;
	else if (left < right)
		return true;
	else
		return false;
}
bool operator>=(Rational const &left, Rational const &right)
{
	if (left == right)
		return true;
	else if (left > right)
		return true;
	else
		return false;
}
Rational operator+(Rational const &left, Rational const &right)
{
	Rational leftSide(left);
	leftSide += right;
	return leftSide;
}
Rational operator-(Rational const &left, Rational const &right)
{
	Rational leftSide(left);
	leftSide -= right;
	return leftSide;
}
Rational operator*(Rational const &left, Rational const &right)
{
	Rational leftSide(left);
	leftSide *= right;
	return leftSide;
}
Rational operator/(Rational const &left, Rational const &right)
{
	Rational leftSide(left);
	leftSide /= right;
	return leftSide;
}
std::ostream & operator<<(std::ostream & stream, Rational const& fraction)
{
	stream << fraction.getNumerator() << "/" << fraction.getDenominator();
	return stream;
}
std::istream & operator>>(std::istream & stream, Rational & fraction)
{
	int n, d;
	stream >> n;
	char slash;
	stream >> slash;
	stream >> d;
	fraction = Rational{ n, d };
	return stream;
}