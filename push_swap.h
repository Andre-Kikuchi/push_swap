/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahideo-k <ahideo-k@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/08/04 16:49:22 by ahideo-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

typedef enum e_op
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
}	t_op;

typedef enum e_strat
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
}	t_strat;

typedef struct s_stack
{
	int	*v;
	int	cap;
	int	top;
	int	size;
}	t_stack;

typedef struct s_ps
{
	t_stack	a;
	t_stack	b;
	int		bench;
	int		quiet;
	t_strat	strat;
	t_strat	used;
	int		disorder;
	long	count[11];
}	t_ps;

/* stack.c */
void		init_ps(t_ps *ps);
void		st_init(t_ps *ps, t_stack *s, int cap);
int			st_get(t_stack *s, int i);
int			is_sorted(t_stack *s);
void		free_ps(t_ps *ps);

/* ops.c */
void		do_op(t_ps *ps, t_op op);

/* parse.c */
int			parse_flags(t_ps *ps, int argc, char **argv);
void		error_exit(t_ps *ps);

/* parse_nums.c */
void		parse_numbers(t_ps *ps, int n, char **av);

/* disorder.c */
int			disorder_bp(t_stack *a);

/*ranks.c*/
void		to_ranks(t_ps *ps);

/* sort_simple.c, sort_medium.c, sort_complex.c, sort_small.c */
void		sort_simple(t_ps *ps);
void		sort_medium(t_ps *ps);
void		sort_complex(t_ps *ps);
void		sort_small(t_ps *ps);

/* bench.c */
void		print_bench(t_ps *ps);

/* utils.c */
size_t		ft_strlen(const char *s);
int			ft_streq(const char *a, const char *b);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putnbr_fd(long n, int fd);
int			ft_isqrt(int n);

/* utils2.c */
const char	*op_name(int op);
int			min_pos(t_stack *a);
void		rot_to_top(t_ps *ps, t_stack *s, int pos, int is_b);

#endif
