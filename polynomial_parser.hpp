#ifndef POLYNOMIAL_PARSER
#define POLYNOMIAL_PARSER

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

#endif