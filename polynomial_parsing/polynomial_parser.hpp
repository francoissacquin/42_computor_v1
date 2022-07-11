#ifndef POLYNOMIAL_PARSER
#define POLYNOMIAL_PARSER

#include <string>

typedef struct s_poly_list
{
	int		c; //coefficient
	int		e; //exponent
	s_poly_list		*next;
}	t_poly_list;

typedef struct	s_parsing
{
	char *	curr_pos;
	int		eq_side;
}	t_parsing;


class Polynomial_parser
{
private:
	std::string			raw_eq;
	int					curr_pos;
	int					eq_side;
	int					error_level;

public:
	Polynomial_parser(std::string str, int eq_side);
	~Polynomial_parser();

	t_poly_list *		parse_input_equation();
	t_poly_list *		accept_new_term();
	t_poly_list *		create_new_link(int coef, int expo);
	int					accept_new_coefficient();
	int					accept_new_exponent();
	int					accept_sign();
	int					accept_number();
	void				skip_spaces();
};

#endif