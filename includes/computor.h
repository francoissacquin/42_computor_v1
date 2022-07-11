#ifndef COMPUTOR_H
#define COMPUTOR_H

#include "../polynomial_parsing/polynomial_parser.hpp"
#include "../polynomial_solver/polynomial_solver.hpp"
#include <string>
#include <iostream>

void			error_exit(int code, t_poly_list * eq);
int				input_char_check(std::string str);
std::string		cut_spaces_on_edges(std::string str);
void			skip_spaces();
t_poly_list *	parse_input_equation(char *str, int eq_side);

#endif