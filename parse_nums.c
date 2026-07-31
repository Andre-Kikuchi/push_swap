/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nums.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesferr <alesferr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/26 12:00:06 by alesferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static long	parse_token(t_ps *ps, const char *s, int *i)
{
	long	sign;
	long	n;
	int		digits;

	sign = 1;
	n = 0;
	digits = 0;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		n = n * 10 + (s[*i] - '0');
		if (n * sign > 2147483647 || n * sign < -2147483648)
			error_exit(ps);
		digits++;
		(*i)++;
	}
	if (digits == 0 || (s[*i] != '\0' && s[*i] != ' '))
		error_exit(ps);
	return (n * sign);
}

static int	count_tokens(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != ' ')
			i++;
	}
	return (count);
}

static void	fill_from(t_ps *ps, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i])
		{
			ps->a.v[ps->a.size] = (int)parse_token(ps, s, &i);
			ps->a.size++;
		}
	}
}

static void	check_dups(t_ps *ps)
{
	int	i;
	int	j;

	i = 0;
	while (i < ps->a.size)
	{
		j = i + 1;
		while (j < ps->a.size)
		{
			if (ps->a.v[i] == ps->a.v[j])
				error_exit(ps);
			j++;
		}
		i++;
	}
}

void	parse_numbers(t_ps *ps, int n, char **av)
{
	int	i;
	int	count;
	int	total;

	total = 0;
	i = 0;
	while (i < n)
	{
		count = count_tokens(av[i]);
		if (count == 0)
			error_exit(ps);
		total += count;
		i++;
	}
	st_init(ps, &ps->a, total);
	st_init(ps, &ps->b, total);
	i = 0;
	while (i < n)
	{
		fill_from(ps, av[i]);
		i++;
	}
	check_dups(ps);
}
