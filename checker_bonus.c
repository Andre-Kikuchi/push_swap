/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesferr <alesferr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/26 11:59:37 by alesferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	read_line(char *buf)
{
	int		i;
	int		r;
	char	c;

	i = 0;
	while (1)
	{
		r = read(0, &c, 1);
		if (r < 0)
			return (-2);
		if (r == 0 && i == 0)
			return (-1);
		if (r == 0)
			return (-2);
		if (c == '\n')
		{
			buf[i] = '\n';
			buf[i + 1] = '\0';
			return (i + 1);
		}
		if (i >= 3)
			return (-2);
		buf[i++] = c;
	}
}

static int	op_of(const char *line)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		if (ft_streq(line, op_name(i)))
			return (i);
		i++;
	}
	return (-1);
}

static void	exec_all(t_ps *ps)
{
	char	buf[5];
	int		len;
	int		op;

	while (1)
	{
		len = read_line(buf);
		if (len == -1)
			return ;
		if (len == -2)
			error_exit(ps);
		op = op_of(buf);
		if (op < 0)
			error_exit(ps);
		do_op(ps, op);
	}
}

int	main(int argc, char **argv)
{
	t_ps	ps;

	init_ps(&ps);
	ps.quiet = 1;
	if (argc < 2)
		return (0);
	parse_numbers(&ps, argc - 1, argv + 1);
	exec_all(&ps);
	if (is_sorted(&ps.a) && ps.b.size == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	free_ps(&ps);
	return (0);
}
