#include "computor.h"
#include <string>

void		error_exit(int code)
{
	if (code == 1)
		std::cerr << "Wrong number of arguments, please use the executable as :\n>./computor \"[equation]\"\n";
	else if (code == 2)
		std::cerr << "Invalid character in equation!\nThis is the list of authorized characters: 0 1 2 3 4 5 6 7 8 9 + - * X ^\n";
	else if (code == 3)
		std::cerr << "Equation not valid\nThe equation should have one and only equal sign\n";
	else if (code == 4)
		std::cerr << "Equation not valid\nThe equation should have one and only equal sign\n";
	exit(1);
}

t_poly_list *		equation_slicing(std::string str)
{
	Polynomial_parser		right_side(str.substr(0, str.find("=")), 1);
	Polynomial_parser		left_side(str.substr(str.find("=") + 1), -1);
	t_poly_list *	left_parsed_terms;
	t_poly_list *	right_parsed_terms;
	t_poly_list *	temp;

	left_parsed_terms = left_side.parse_input_equation();
	right_parsed_terms = right_side.parse_input_equation();
	if (left_parsed_terms == NULL || right_parsed_terms == NULL)
		return NULL;
	temp = left_parsed_terms;
	while (temp && temp->next)
		temp = temp->next;
	temp->next = right_parsed_terms;
	return (left_parsed_terms);
}

void		print_linked_list(t_poly_list * list)
{
	while (list)
	{
		std::cout << "coeff: " << list->c << " | expo: " << list->e << std::endl;
		list = list->next;
	}
}

int			main(int argc, char **argv)
{
	int				err;
	t_poly_list		*temp;


	if (argc != 2)
		error_exit(1);
	std::string		raw_eq(argv[1]);
	if ((err = input_char_check(raw_eq)) != 0)
		error_exit(err);
	temp = equation_slicing(raw_eq);
	if (temp == NULL)
		error_exit(4);
	print_linked_list(temp);
}
