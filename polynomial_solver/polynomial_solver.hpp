#ifndef POLYNOMIAL_SOLVER
#define POLYNOMIAL_SOLVER

#include "../includes/computor.h"
#include <map>

class Polynomial_solver
{
private:
	std::map<int, int>		poly_factors;
	long long				discriminant;
	int						degree;

public:
	Polynomial_solver(t_poly_list *parsed_eq);
	~Polynomial_solver();

	int		get_degree();

	void	calc_discriminant();
	void	print_reduced_form();
	void	print_polynomial_degree();
	void	find_solutions();
	void	resolve_degree_0();
};

#endif