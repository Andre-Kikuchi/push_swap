/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahideo-k <ahideo-k@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/08/04 13:23:08 by ahideo-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_chunks(t_ps *ps, int chunk);
static int	max_pos(t_stack *b);

void	sort_medium(t_ps *ps)
{
	int	chunk;

	if (is_sorted(&ps->a) == 1)
		return ;
	chunk = ft_isqrt(3 * ps->a.size / 2) + 2;
	push_chunks(ps, chunk);
	while (ps->b.size > 0)
	{
		rot_to_top(ps, &ps->b, max_pos(&ps->b), 1);
		do_op(ps, PA);
	}
}

static void	push_chunks(t_ps *ps, int chunk)
{
	int	lim;

	while (ps->a.size > 0)
	{
		lim = ps->b.size;
		if (st_get(&ps->a, 0) < lim + chunk / 2)
		{
			do_op(ps, PB);
			do_op(ps, RB);
		}
		else if (st_get(&ps->a, 0) < lim + chunk)
			do_op(ps, PB);
		else
			do_op(ps, RA);
	}
}

static int	max_pos(t_stack *b)
{
	int	i;
	int	pos;

	pos = 0;
	i = 1;
	while (i < b->size)
	{
		if (st_get(b, i) > st_get(b, pos))
			pos = i;
		i++;
	}
	return (pos);
}
