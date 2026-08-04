/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahideo-k <ahideo-k@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/08/04 13:00:10 by ahideo-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
