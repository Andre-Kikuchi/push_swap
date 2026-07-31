/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesferr <alesferr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/26 12:01:19 by alesferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

const char	*op_name(int op)
{
	static const char	*names[11] = {"sa\n", "sb\n", "ss\n", "pa\n",
		"pb\n", "ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};

	return (names[op]);
}

int	min_pos(t_stack *a)
{
	int	i;
	int	pos;

	pos = 0;
	i = 1;
	while (i < a->size)
	{
		if (st_get(a, i) < st_get(a, pos))
			pos = i;
		i++;
	}
	return (pos);
}

void	rot_to_top(t_ps *ps, t_stack *s, int pos, int is_b)
{
	t_op	up;
	t_op	down;

	up = RA;
	down = RRA;
	if (is_b)
	{
		up = RB;
		down = RRB;
	}
	if (pos <= s->size / 2)
	{
		while (pos-- > 0)
			do_op(ps, up);
	}
	else
	{
		pos = s->size - pos;
		while (pos-- > 0)
			do_op(ps, down);
	}
}
