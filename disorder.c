double	compute_disorder(int *stack, int size)
{
	int		i;
	int		j;
	double	mistakes;
	double	total_pairs;

	i = 0;
	mistakes = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (stack[i] > stack[j])
				mistakes++;
			j++;
		}
		i++;
	}
	total_pairs = (double)size * (size - 1) / 2;
	if (total_pairs == 0)
		return (0);
	return (mistakes / total_pairs);
}
