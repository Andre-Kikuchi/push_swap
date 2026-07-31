/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesferr <alesferr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/26 11:59:29 by alesferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_pct(t_ps *ps)
{
	ft_putstr_fd("[bench] disorder:  ", 2);
	ft_putnbr_fd(ps->disorder / 100, 2);
	ft_putstr_fd(".", 2);
	ft_putnbr_fd((ps->disorder % 100) / 10, 2);
	ft_putnbr_fd(ps->disorder % 10, 2);
	ft_putstr_fd("%\n", 2);
}

static const char	*class_name(t_strat used)
{
	if (used == SIMPLE)
		return ("O(n^2)");
	if (used == MEDIUM)
		return ("O(n*sqrt(n))");
	return ("O(n log n)");
}

static const char	*strat_name(t_ps *ps)
{
	if (ps->strat == ADAPTIVE)
		return ("Adaptive");
	if (ps->used == SIMPLE)
		return ("Simple");
	if (ps->used == MEDIUM)
		return ("Medium");
	return ("Complex");
}

static void	put_ops_line(t_ps *ps, int from, int to)
{
	int	i;

	ft_putstr_fd("[bench]", 2);
	i = from;
	while (i < to)
	{
		ft_putstr_fd(" ", 2);
		write(2, op_name(i), ft_strlen(op_name(i)) - 1);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(ps->count[i], 2);
		i++;
	}
	ft_putstr_fd("\n", 2);
}

void	print_bench(t_ps *ps)
{
	long	total;
	int		i;

	total = 0;
	i = 0;
	while (i < 11)
		total += ps->count[i++];
	put_pct(ps);
	ft_putstr_fd("[bench] strategy:  ", 2);
	ft_putstr_fd(strat_name(ps), 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(class_name(ps->used), 2);
	ft_putstr_fd("\n[bench] total_ops: ", 2);
	ft_putnbr_fd(total, 2);
	ft_putstr_fd("\n", 2);
	put_ops_line(ps, 0, 5);
	put_ops_line(ps, 5, 11);
}
