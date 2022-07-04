#ifndef POLYNOMIAL_PARSER
#define POLYNOMIAL_PARSER

typedef struct s_poly_list
{
	int		c; //coefficient
	int		e; //exponent
	s_poly_list		*next;
}	t_poly_list;

#endif