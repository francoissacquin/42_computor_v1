#include "input_char_check.cpp"
#include "polynomial_parser.cpp"
#include <string>
#include <iostream>

void		error_exit(int code)
{
	if (code == 1)
		std::cerr << "Wrong number of arguments, please use the executable as :\n>./computor \"[equation]\"\n";
	else if (code == 2)
		std::cerr << "Invalid character in equation!\nThis is the list of authorized characters: 0 1 2 3 4 5 6 7 8 9 + - * X ^\n";
	else if (code == 3)
		std::cerr << 
	exit(1);
}

int			main(int argc, char **argv)
{
	ft::string		raw_eq(argv[1]);
	t_poly_list		*left_parsed_terms;
	t_poly_list		*right_parsed_terms;


	if (argc != 2)
		error_exit(1);
	if (input_char_check(raw_eq))
		error_exit(2);
	// separer la string des 2 cotes du signe = et lancer les deux
	left_parsed_terms = parse_input_equation(, 1);
	right_parsed_terms = parse_input_equation(, -1);
	//verifier que chacun des deux cotes possede au moins un membre

	//ecraser les deux parsed_items dans une class de resolution de polynomiale
}
