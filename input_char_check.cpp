#include <string.h>

bool	input_char_check(ft::string str)
{
	ft::string	authorized_chars = "1234567890+-*X^";
	int			len = str.size();

	for (int i = 0; i < len; i++)
	{
		if (authorized_chars.find(str[i]) == ft::string::npos)
			return true;
	}
	return false;
}