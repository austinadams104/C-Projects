#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include <string>
#include <sstream>
#include "Rational.h"

template<typename C, typename F>
void apply(std::string op, C& container, F function)
{
	if (container.size() < 2) throw std::runtime_error("Sorry, you need at least two numbers for it to work.\n");
	auto second = container.back();
	container.pop_back();

	auto first = container.back();
	container.pop_back();

	auto result = function(first, second);
	std::cout << first << " " << op << " " << second << " = " << result << std::endl;
	container.push_back(result);
}

int main()
{
	std::vector<Rational> stack;
	std::cout << "Welcome to the Polish Calculator! Let me teach you how this works...\n\n";
	std::cout << "First, you need to enter two numbers (Can be a rational number like 3/4)\n.";
	std::cout << "Then you hit what operand you want to use (ex. +, -, * ,/)\n";
	std::cout << "If you want to start over, hit 'c' for clear.\n";
	std::cout << "When your done and want to exit, hit 'e'.\n";
	while (true)
	{
		try{
			std::string input;
			std::getline(std::cin, input);
			if (input[0] == 'e') return EXIT_SUCCESS;
			if (input[0] == 'c')
			{
				stack.clear();
			}
			else if (input[0] == '+')
			{
				apply(" + ", stack, [](Rational a, Rational b){return a + b; });
			}
			else if (input[0] == '-')
			{
				apply(" - ", stack, [](Rational a, Rational b){return a - b; });
			}
			else if (input[0] == '*')
			{
				apply(" * ", stack, [](Rational a, Rational b){return a * b; });
			} 
			else if (input[0] == '/')
			{
				apply(" / ", stack, [](Rational a, Rational b){return a / b; });
			}
			else
			{
				Rational value;
				std::istringstream ss(input);
				ss >> value;
				stack.push_back(value);
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what();
			stack.clear();
		}
		catch (...)
		{
			std::cout << "Unexpected exception" << std::endl;
			stack.clear();
		}

	}
}

