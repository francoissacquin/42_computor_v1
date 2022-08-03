#include "polynomial_solver.hpp"
#include "square_root.cpp"

Polynomial_solver::Polynomial_solver(t_poly_list *parsed_eq)
{
	while (parsed_eq)
	{
		if (this->poly_factors.count(parsed_eq->e) == 0)
		{
			this->poly_factors.insert(std::pair<int, int>(parsed_eq->e, parsed_eq->c));
		}
		else
		{
			std::map<int, int>::iterator	itr = this->poly_factors.find(parsed_eq->e);
			itr->second = itr->second + parsed_eq->c;
		}
		parsed_eq = parsed_eq->next;
	}
	if (this->poly_factors.count(0) == 0)
		this->poly_factors.insert(std::pair<int, int>(0, 0));
	if (this->poly_factors.count(1) == 0)
		this->poly_factors.insert(std::pair<int, int>(1, 0));
	if (this->poly_factors.count(2) == 0)
		this->poly_factors.insert(std::pair<int, int>(2, 0));
}

Polynomial_solver::~Polynomial_solver()
{
	this->poly_factors.clear();
}

int			Polynomial_solver::get_degree()
{
	return (this->degree);
}

void		Polynomial_solver::calc_discriminant()
{
	int		a = this->poly_factors.find(2)->second;
	int		b = this->poly_factors.find(1)->second;
	int		c = this->poly_factors.find(0)->second;

	this->discriminant = b * b - 4 * a * c;
	std::cout << "For polynomial equation: a * X^2 + b * X + c = 0\n";
	std::cout << "Disriminant = b^2 - 4 * a * c = " << b << "^2 - ( 4 * " << a << " * " << c << " )\n";
	std::cout << "Discriminant value: " << this->discriminant << "\n";
}

void		Polynomial_solver::print_reduced_form()
{
	std::map<int, int>::iterator	itr = this->poly_factors.begin();
	int										printed = 0;

	std::cout << "Reduced form: ";
	while (itr != this->poly_factors.end())
	{
		if (itr->second < 0)
		{
			if (printed != 0)
				std::cout << " - ";
			else
				std::cout << "-";
			if (std::abs(itr->second) != 1 || itr->first == 0)
			{
				std::cout << std::abs(itr->second);
				if (itr->first == 1)
					std::cout << " * X";
				else if (itr->first > 1)
					std::cout << " * X^" << itr->first;
			}
			else
			{
				if (itr->first == 1)
					std::cout << "X";
				else if (itr->first > 1)
					std::cout << "X^" << itr->first;
			}
			printed++;
		}
		else if (itr->second > 0)
		{
			if (printed != 0)
				std::cout << " + ";
			if (std::abs(itr->second) != 1 || itr->first == 0)
			{
				std::cout << std::abs(itr->second);
				if (itr->first == 1)
					std::cout << " * X";
				else if (itr->first > 1)
					std::cout << " * X^" << itr->first;
			}
			else
			{
				if (itr->first == 1)
					std::cout << "X";
				else if (itr->first > 1)
					std::cout << "X^" << itr->first;
			}
			printed++;
		}
		itr++;
	}
	if (printed == 0)
		std::cout << "0";
	std::cout << " = 0\n";
}

void		Polynomial_solver::print_polynomial_degree()
{
	std::map<int, int>::reverse_iterator	itr = this->poly_factors.rbegin();

	this->degree = 0;
	while (itr != this->poly_factors.rend())
	{
		if (itr->first > this->degree && itr->second != 0)
			this->degree = itr->first;
		itr++;
	}
	std::cout << "Polynomial degree: " << this->degree << "\n";
}

void		Polynomial_solver::resolve_degree_0()
{
	int		value = this->poly_factors.find(0)->second;

	if (value == 0)
		std::cout << "The equation accepts an infinity of solutions\n";
	else
		std::cout << "The equation has no possible solution\n";
}

void		Polynomial_solver::resolve_degree_1()
{
	long		a = this->poly_factors.find(0)->second * -1;
	long		b = this->poly_factors.find(1)->second;

	if (a % b != 0)
	{
		reduce_fraction(a, b);
		std::cout << "The solution is: " << (double)a / (double)b << std::endl;
	}
	else
		std::cout << "The solution is: " << a / b << std::endl;
}

void		Polynomial_solver::reduce_fraction(long a, long b)
{
	// We are using an euclidian division here to find the GCD
	long		temp_a;
	long		temp_b;
	if (std::abs(a) > std::abs(b))
	{
		temp_a = std::abs(a);
		temp_b = std::abs(b);
	}
	else
	{
		temp_a = std::abs(b);
		temp_b = std::abs(a);
	}
	long		dividend = a / b;
	long		remainder = a % b;

	while (remainder != 0)
	{
		temp_a = b;
		temp_b = remainder;
		dividend = temp_a / temp_b;
		remainder = temp_a % temp_b;
	}
	std::cout << "Irreducible Fraction form for solution is: " << a / temp_b << " / " << b / temp_b << std::endl;
}

std::string		Polynomial_solver::center_int_for_print(int a, unsigned long len)
{
	std::string		content = std::to_string(a);
	int				padding;
	if (content.size() < len)
		padding = len - content.size();
	else
		padding = 0;
	std::string		res(padding / 2 + padding % 2, ' ');

	res.insert(res.size(), content);
	res.insert(res.size(), padding / 2, ' ');

	return res;
}

std::string		Polynomial_solver::center_double_for_print(double a, unsigned long len)
{
	std::string		content = std::to_string(a);
	int				padding;
	if (content.size() < len)
		padding = len - content.size();
	else
		padding = 0;
	std::string		res(padding / 2 + padding % 2, ' ');

	res.insert(res.size(), content);
	res.insert(res.size(), padding / 2, ' ');

	return res;
}

void		Polynomial_solver::find_solutions()
{
	if (this->discriminant < 0)
	{
		std::cout << "Discriminant is negative, the equation has no real solutions but two complex solutions:" << std::endl;
		std::cout << "FORMULAS:" << std::endl;
		std::cout << "            ___                          ___" << std::endl;
		std::cout << " - b + i * √ Δ                - b - i * √ Δ " << std::endl;
		std::cout << "________________     AND     ________________" << std::endl;
		std::cout << "                                             " << std::endl;
		std::cout << "      2 * a                         2 * a    " << std::endl << std::endl;

		std::cout << "SOLUTIONS:" << std::endl;
		std::cout << "                  ___________                                            ___________" << std::endl;
		std::cout << this->center_int_for_print( -1 * this->poly_factors.find(1)->second, 10) << " + i * √" << this->center_int_for_print(this->discriminant, 10) << "                          " << this->center_int_for_print( -1 * this->poly_factors.find(1)->second, 10) << " -  i * √" << this->center_int_for_print(this->discriminant, 10) << std::endl;
		std::cout << "____________________________            AND          ____________________________" << std::endl;
		std::cout << std::endl;
		std::cout << this->center_int_for_print( 2 * this->poly_factors.find(2)->second, 23) << "                           " << this->center_int_for_print( 2 * this->poly_factors.find(2)->second, 23) << std::endl;
		std::cout << std::endl;
	}
	else if (this->discriminant == 0)
	{
		std::cout << "Discriminant is equal to zero, the equation has one solution:" << std::endl;
		std::cout << std::endl;
		std::cout << "             - b                       " << this->center_int_for_print( -1 * this->poly_factors.find(1)->second, 10) << std::endl;
		std::cout << "FORMULA:  __________        SOLUTION:  __________  =  "<< (-1 * this->poly_factors.find(1)->second) / (2 * this->poly_factors.find(0)->second) << std::endl;
		std::cout << std::endl;
		std::cout << "            2 * a                      " << this->center_int_for_print( 2 * this->poly_factors.find(0)->second, 10) << std::endl;
	}
	else
	{
		std::cout << "Discriminant is positive, the equation has two real solutions:" << std::endl;
		std::cout << "FORMULAS:" << std::endl;
		std::cout << "        ___                      ___" << std::endl;
		std::cout << " - b + √ Δ                - b - √ Δ " << std::endl;
		std::cout << "____________     AND     ____________" << std::endl;
		std::cout << "                                             " << std::endl;
		std::cout << "   2 * a                     2 * a    " << std::endl << std::endl;

		double		temp = (double)(-1 * (double)this->poly_factors.find(1)->second + (double)square_root((double)this->discriminant)) / (double)(2 * (double)this->poly_factors.find(2)->second);
		double		temp_2 = (double)(-1 * (double)this->poly_factors.find(1)->second - (double)square_root((double)this->discriminant)) / (double)(2 * (double)this->poly_factors.find(2)->second);

		std::cout << "SOLUTIONS:" << std::endl;
		std::cout << "              ___________                                         ___________" << std::endl;
		std::cout << this->center_int_for_print( -1 * this->poly_factors.find(1)->second, 10) << " + √" << this->center_int_for_print(this->discriminant, 10) << "                            " << this->center_int_for_print( -1 * this->poly_factors.find(1)->second, 10) << " - √" << this->center_int_for_print(this->discriminant, 10) << std::endl;
		std::cout << "_________________________ = " << this->center_double_for_print(temp, 10) << "    AND     _________________________ = " << this->center_double_for_print(temp_2, 10) << std::endl;
		std::cout << std::endl;
		std::cout << this->center_int_for_print( 2 * this->poly_factors.find(2)->second, 23) << "                           " << this->center_int_for_print( 2 * this->poly_factors.find(2)->second, 23) << std::endl;
		std::cout << std::endl;
	}
}


int		num_of_digits(char *str)
{
	int		res = 0;
	for(int i = 0; str[i];i++)
	{
		if (str[i] > 47 && str[i] < 58)
			res++;
	}
	return (res);
}