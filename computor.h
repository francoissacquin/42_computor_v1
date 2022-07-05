#ifndef COMPUTOR_H
#define COMPUTOR_H

void		error_exit(int code);
int		input_char_check(std::string str);
void		skip_spaces(t_parsing *info);
t_poly_list *		parse_input_equation(char *str, int eq_side);

#endif