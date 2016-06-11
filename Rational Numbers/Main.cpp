#include "Rational.h"

int main()
{
	std::cout << "Welcome to the Rational operator Comparator\n";
	std::cout << "Enter a fraction: (numerator/denominator)\n";
	Rational a;
	Rational b;
	std::cin >> a;
	Rational temp_a = a;
	
	std::cout << "Enter a second fraction: \n";
	std::cin >> b;
	
	std::cout << std::endl << a << " + " << b << " = " << a + b << std::endl;
	std::cout << a << " - " << b << " = " << a - b << std::endl;
	std::cout << a << " * " << b << " = " << a * b << std::endl;
	std::cout << a << " / " << b << " = " << a / b << std::endl << std::endl;

	if (a<b)
	std::cout << a << " is less than "<< b << std::endl;
	else
		std::cout << a << " is not less than " << b << std::endl;

	if (a>b)
		std::cout << a << " is greater than " << b << std::endl;
	else
		std::cout << a << " is not greater than " << b << std::endl;

	if (a<=b)
		std::cout << a << " is less than or equal to " << b << std::endl;
	else
		std::cout << a << " is not less than or equal to " << b << std::endl;

	if (a>=b)
		std::cout << a << " is greater than or equal to " << b << std::endl;
	else
		std::cout << a << " is not greater than or equal to " << b << std::endl;

	if (a==b)
		std::cout << a << " is equal to " << b << std::endl;
	else
		std::cout << a << " is not equal to " << b << std::endl;

	if (a != b)
		std::cout << a << " is not equal to " << b << std::endl << std::endl;
	else
		std::cout << a << " is equal to " << b << std::endl << std::endl;


	a += b;
	std::cout << a << " += " << b << " = " << a << std::endl;
	a = temp_a;
	a -= b;
	std::cout << a << " -= " << b << " = " << a << std::endl;
	a = temp_a;
	a *= b;
	std::cout << a << " *= " << b << " = " << a << std::endl;
	a = temp_a;
	a /= b;
	std::cout << a << " /= " << b << " = " << a << std::endl;





	char dummy;
	std::cin >> dummy;
}