
double	power_of_ten(int num)
{
	double	rst = 1.0;
	if (num >= 0)
	{
		for (int i = 0; i < num; i++)
		{
			rst *= 10.0;
		}
	}
	else
	{
		for (int i = 0; i < (0 - num); i++)
		{
			rst *= 0.1;
		}
	}
	return rst;
}

double	square_root(double a)
{
	double	cpy = a;
	double	rst = 0.0;
	int		max_digits = 8;
	int		i;
	double	j = 1.0;

	for (i = max_digits; i > 0; i--)
	{
		if (cpy - (( 2 * rst) + (j * power_of_ten(i))) * ( j * power_of_ten(i)) >= 0)
		{
			while (cpy - (( 2 * rst) + (j * power_of_ten(i))) * ( j * power_of_ten(i)) >= 0)
			{
				j++;
				if (j >= 10)
					break;
			}
			j--; // correct the extra value by minus one to j
			cpy -= (( 2 * rst) + (j * power_of_ten(i))) * ( j * power_of_ten(i));

			rst += j * power_of_ten(i);

			j = 1.0;
		}
	}

	for (i = 0; i >= 0 - max_digits; i--)
	{
		if (cpy - (( 2 * rst) + (j * power_of_ten(i))) * ( j * power_of_ten(i)) >= 0)
		{
			while (cpy - (( 2 * rst) + (j * power_of_ten(i))) * ( j * power_of_ten(i)) >= 0)
			{
				j++;
				if (j >= 10)
					break;
			}
			j--; // correct the extra value by minus one to j
			cpy -= (( 2 * rst) + (j * power_of_ten(i))) * ( j * power_of_ten(i));

			rst += j * power_of_ten(i);

			j = 1.0;
		}
	}

	return rst;
}