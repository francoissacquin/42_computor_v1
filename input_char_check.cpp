#include <string>

int		input_char_check(std::string str)
{
	std::string	authorized_chars = "1234567890+-*X^=";
	int			len = str.size();
	int			equal_count = 0;

	for (int i = 0; i < len; i++)
	{
		if (authorized_chars.find(str[i]) == std::string::npos)
			return (2);
		if (str[i] == '=')
			equal_count++;
	}
	if (equal_count != 1)
		return (3);
	return (0);
}