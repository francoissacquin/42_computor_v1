#include "polynomial_parser.hpp"

t_poly_list *		parse_input_equation(char *str, int eq_side)
{
	t_poly_list			*start = NULL;
	t_poly_list			*temp = NULL;
	t_parsing			info;

	info.curr_pos = &(str[0]);
	info.eq_side = eq_side;

	while (pos != str.end())
	{
		if (temp == NULL)
		{
			temp = accept_new_term(&info);
			start = temp;
		}
		else
		{
			temp->next = accept_new_term(&info);
			temp = temp->next;
		}
	}
	return (start);
}

t_poly_list *		accept_new_term(t_parsing *info)
{
	t_poly_list *	new_term;
	int				coef;
	int				expo;

	coef = accept_new_coefficient(info);
	expo = accept_new_exponent(info);
	new_term = create_new_link(coef, expo);

	return (new_term);
}

t_poly_list *		create_new_link(int coef, int exponent)
{
	t_poly_list *	new_link;

	if (!(new_link = malloc(sizeof(t_poly_list))))
		error_list(3);
	new_link->c = coef;
	new_link->e = expo;
	new_link->next = NULL;

	return (new_link);
}

int			accept_new_coefficient(t_parsing *info)
{
	int		coef;
	int		sign;

	sign = accept_sign(info);
	c = accept_number(info);

	return (c * sign);
}

int			accept_new_exponent(t_parsing *info)
{
	int		expo = 0; // default exponent is 0

	skip_spaces(info);

	if (*(info->curr_pos) == 'X')
	{
		e = 1;
		info->curr_pos++;
		if (*(info->curr_pos) == '^')
		{
			info->curr_pos++;
			e = accept_number(info);
		}
	}
	return (e);
}

int			accept_sign(t_parsing *info)
{
	int		sign;

	sign = info->eq_side; 
	// default value is 1 for left side of equation and -1 for right side

	skip_spaces(info);

	if (*(info->curr_pos) == '-')
	{
		sign *= -1;
		info->curr_pos++;
	}
	else if (*(info->curr_pos) == '+')
		info->curr_pos++;
	
	return (sign);
}

int			accept_number(t_parsing *info)
{
	int		num;
	char *	end;

	num = strtol(info->curr_pos, &end, 10);
	if (info->curr_pos == end)
		num = 1;

	info->curr_pos = end;

	return num;
}

void		skip_spaces(t_parsing *info)
{
	while (isspace(*(info->curr_pos)))
		info->curr_pos++;
}