#include <string>

int		input_char_check(std::string str)
{
	std::string	authorized_chars = "1234567890+-*X^= ";
	int			len = str.size();
	int			equal_count = 0;
	int			variable_count = 0;

	if (len < 3)
		return (5);
	for (int i = 0; i < len; i++)
	{
		if (authorized_chars.find(str[i]) == std::string::npos)
			return (2);
		if (str[i] == '=')
			equal_count++;
		if (str[i] == 'X')
			variable_count++;
	}
	if (equal_count != 1)
		return (3);
	if (variable_count == 0)
		return (9);
	return (0);
}

std::string		cut_spaces_on_edges(std::string str)
{
	int		start = 0;
	int		end = str.size() - 1;

	while (isspace(str[start]))
		start++;
	while (isspace(str[end]))
		end--;
	if (start > end)
		start = end;
	return (str.substr(start, end - start + 1));
}