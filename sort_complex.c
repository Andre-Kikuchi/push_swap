/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesferr <alesferr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/26 12:00:26 by alesferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	bits_needed(int n)
{
	int	bits;

	bits = 0;
	while ((n - 1) >> bits)
		bits++;
	return (bits);
}

void	sort_complex(t_ps *ps)
{
	int	bit;
	int	i;
	int	n;

	bit = 0;
	while (bit < bits_needed(ps->a.size))
	{
		if (is_sorted(&ps->a))
			break ;
		n = ps->a.size;
		i = 0;
		while (i++ < n)
		{
			if (((st_get(&ps->a, 0) >> bit) & 1) == 0)
				do_op(ps, PB);
			else
				do_op(ps, RA);
		}
		while (ps->b.size > 0)
			do_op(ps, PA);
		bit++;
	}
}
