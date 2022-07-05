#include "polynomial_parser.hpp"
#include "computor.h"
#include <string>

Polynomial_parser::Polynomial_parser(std::string str, int eq_side): raw_eq(str), curr_pos(0), eq_side(eq_side)
{
	// nothing to see here
}

Polynomial_parser::~Polynomial_parser() {}

void		Polynomial_parser::skip_spaces()
{
	while (isspace(this->raw_eq[this->curr_pos]))
		this->curr_pos++;
}

int			Polynomial_parser::accept_number()
{
	int		num;
	char *	end;

	num = strtol(this->curr_pos, &end, 10);
	// definitivement faire mon propre atoi je pense
	if (this->curr_pos == end)
		num = 1;
	this->curr_pos = end;

	return num;
}

int			Polynomial_parser::accept_sign()
{
	int		sign;

	sign = this->eq_side; 
	// default value is 1 for left side of equation and -1 for right side

	skip_spaces();

	if (this->raw_eq[this->curr_pos] == '-')
	{
		sign *= -1;
		this->curr_pos++;
	}
	else if (this->raw_eq[this->curr_pos] == '+')
		this->curr_pos++;
	
	return (sign);
}

int			Polynomial_parser::accept_new_exponent()
{
	int		expo = 0; // default exponent is 0

	skip_spaces();

	if (this->raw_eq[this->curr_pos] == 'X')
	{
		expo = 1;
		this->curr_pos++;
		if (this->raw_eq[this->curr_pos] == '^')
		{
			this->curr_pos++;
			expo = accept_number();
		}
	}
	else if (this->raw_eq[this->curr_pos] == '*')
	{
		skip_spaces();
		if (this->raw_eq[this->curr_pos] == 'X')
		{
			expo = 1;
			this->curr_pos++;
			if (this->raw_eq[this->curr_pos] == '^')
			{
				this->curr_pos++;
				expo = accept_number();
			}
		}
	}
	return (expo);
}

int			Polynomial_parser::accept_new_coefficient()
{
	int		coef;
	int		sign;

	sign = accept_sign();
	coef = accept_number();

	return (coef * sign);
}

t_poly_list *		Polynomial_parser::create_new_link(int coef, int expo)
{
	t_poly_list *	new_link;

	if (!(new_link = (t_poly_list *)malloc(sizeof(t_poly_list))))
		error_exit(3);
	new_link->c = coef;
	new_link->e = expo;
	new_link->next = NULL;

	return (new_link);
}

t_poly_list *		Polynomial_parser::accept_new_term()
{
	t_poly_list *	new_term;
	int				coef;
	int				expo;

	coef = accept_new_coefficient();
	expo = accept_new_exponent();
	new_term = create_new_link(coef, expo);

	return (new_term);
}

t_poly_list *		Polynomial_parser::parse_input_equation()
{
	t_poly_list			*start = NULL;
	t_poly_list			*temp = NULL;
	t_parsing			info;

	while (this->raw_eq[this->curr_pos])
	{
		if (temp == NULL)
		{
			temp = accept_new_term();
			start = temp;
		}
		else
		{
			temp->next = accept_new_term();
			temp = temp->next;
		}
	}
	return (start);
}
