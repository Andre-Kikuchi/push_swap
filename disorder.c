/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesferr <alesferr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/26 11:59:44 by alesferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	to_ranks(t_ps *ps)
{
	int	*r;
	int	i;
	int	j;

	r = malloc(sizeof(int) * ps->a.size);
	if (!r)
		error_exit(ps);
	i = -1;
	while (++i < ps->a.size)
	{
		r[i] = 0;
		j = -1;
		while (++j < ps->a.size)
			if (ps->a.v[j] < ps->a.v[i])
				r[i]++;
	}
	i = -1;
	while (++i < ps->a.size)
		ps->a.v[i] = r[i];
	free(r);
}

int	disorder_bp(t_stack *a)
{
	long	mistakes;
	long	pairs;
	int		i;
	int		j;

	pairs = (long)a->size * (a->size - 1) / 2;
	if (pairs == 0)
		return (0);
	mistakes = 0;
	i = -1;
	while (++i < a->size)
	{
		j = i;
		while (++j < a->size)
			if (a->v[i] > a->v[j])
				mistakes++;
	}
	return ((int)((mistakes * 10000 + pairs / 2) / pairs));
}
