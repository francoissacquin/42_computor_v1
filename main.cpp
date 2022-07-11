#include "includes/computor.h"
#include <string>

void		free_poly_list(t_poly_list * temp)
{
	t_poly_list	*del;
	if (temp == NULL)
		return ;
	if (temp && temp->next == NULL)
		free(temp);
	else
	{
		while (temp)
		{
			del = temp;
			temp = temp->next;
			free(del);
		}
	}
}

void		error_exit(int code, t_poly_list *temp)
{
	if (code == 1)
		std::cerr << "Wrong number of arguments, please use the executable as :\n>./computor \"[equation]\"\n";
	else if (code == 2)
		std::cerr << "Invalid character in equation!\nThis is the list of authorized characters: 0 1 2 3 4 5 6 7 8 9 + - * X ^\n";
	else if (code == 3)
		std::cerr << "Equation not valid\nThe equation should have one and only equal sign\n";
	else if (code == 4)
		std::cerr << "Equation not valid\nOne side of the equation is not parsable\n";
	else if (code == 5)
		std::cerr << "Equation not valid\nNot enough elements\n";
	else if (code == 6)
		std::cerr << "Equation not valid\nNumber cannot be contained in an int\n";
	else if (code == 7)
		std::cout << "The polynomial degree is strictly greater than 2. I can't solve it\n";
	else if (code == 8)
		std::cerr << "Malloc Failed\nABORTING PROGRAM\n";
	else if (code == 9)
		std::cerr << "Equation has no variable, it is either true or false but cannot resolved in terms of X\n";
	free_poly_list(temp);
	exit(1);
}

t_poly_list *		equation_slicing(std::string str)
{
	std::string				raw_left_side = str.substr(0, str.find("="));
	std::string				raw_right_side = str.substr(str.find("=") + 1);
	Polynomial_parser		left_side(cut_spaces_on_edges(raw_left_side), 1);
	Polynomial_parser		right_side(cut_spaces_on_edges(raw_right_side), -1);
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

int			equation_solver(t_poly_list * eq)
{
	Polynomial_solver		resolver(eq);

	resolver.print_reduced_form();
	resolver.print_polynomial_degree();
	if (resolver.get_degree() > 2)
		return (7);
	else if (resolver.get_degree() == 0)
	{
		resolver.resolve_degree_0();
		return (0);
	}
	resolver.calc_discriminant();
	return (0);
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
		error_exit(1, NULL);
	std::string		raw_eq(argv[1]);
	if ((err = input_char_check(raw_eq)) != 0)
		error_exit(err, NULL);
	temp = equation_slicing(raw_eq);
	if (temp == NULL)
		error_exit(4, temp);
	print_linked_list(temp);
	if ((err = equation_solver(temp)) > 0)
		error_exit(err, temp);

	free_poly_list(temp);
	return (0);
}
