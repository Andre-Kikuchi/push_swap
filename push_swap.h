/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahideo-k <ahideo-k@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/27 18:07:43 by ahideo-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H          // se PUSH_SWAP_H ainda não foi definido...
# define PUSH_SWAP_H         // ...define agora, pra evitar inclusão dupla

# include <unistd.h>         // traz read(), write() (usados o tempo todo)
# include <stdlib.h>         // traz malloc(), free(), exit()

typedef enum e_op             // começa a definição de um tipo enumerado
{
	SA,                        // SA = 0 (valor automático, primeiro da lista)
	SB,                        // SB = 1
	SS,                        // SS = 2
	PA,                        // PA = 3
	PB,                        // PB = 4
	RA,                        // RA = 5
	RB,                        // RB = 6
	RR,                        // RR = 7
	RRA,                       // RRA = 8
	RRB,                       // RRB = 9
	RRR                        // RRR = 10
}	t_op;                      // apelido do tipo: t_op (prefixo t_ = typedef)

typedef enum e_strat           // outro enum, pra estratégias de ordenação
{
	SIMPLE,                    // SIMPLE = 0
	MEDIUM,                    // MEDIUM = 1
	COMPLEX,                   // COMPLEX = 2
	ADAPTIVE                   // ADAPTIVE = 3
}	t_strat;

typedef struct s_stack         // começa a definição de uma struct
{
	int	*v;                    // ponteiro pro buffer de inteiros na memória
	int	cap;                   // capacidade total do buffer (fixa)
	int	top;                   // índice físico de onde está o "topo" agora
	int	size;                  // quantos elementos estão ocupados agora
}	t_stack;                    // apelido: t_stack (prefixo s_ na struct)

typedef struct s_ps             // a struct "mestre" do programa
{
	t_stack	a;                  // a stack principal (guarda os números)
	t_stack	b;                  // a stack auxiliar
	int		bench;              // 1 se a flag --bench foi passada
	int		quiet;              // 1 = não imprime operações (usado no checker)
	t_strat	strat;              // estratégia pedida pelo usuário (ou ADAPTIVE)
	t_strat	used;               // estratégia que realmente rodou
	int		disorder;           // desordem calculada (0 a 10000)
	long	count[11];           // contador de uso de cada uma das 11 operações
}	t_ps;

/* stack.c */                   // comentário organizacional: agrupa protótipos
void		init_ps(t_ps *ps);          // assinatura de init_ps
void		st_init(t_ps *ps, t_stack *s, int cap); // assinatura de st_init
int			st_get(t_stack *s, int i);  // assinatura de st_get
int			is_sorted(t_stack *s);      // assinatura de is_sorted
void		free_ps(t_ps *ps);          // assinatura de free_ps

/* ops.c */
void		do_op(t_ps *ps, t_op op);   // assinatura de do_op

/* parse.c */
int			parse_flags(t_ps *ps, int argc, char **argv); // assinatura
void		error_exit(t_ps *ps);       // assinatura de error_exit

/* parse_nums.c */
void		parse_numbers(t_ps *ps, int n, char **av); // assinatura

/* disorder.c */
void		to_ranks(t_ps *ps);          // assinatura de to_ranks
int			disorder_bp(t_stack *a);     // assinatura de disorder_bp

/* sort_simple.c, sort_medium.c, sort_complex.c, sort_small.c */
void		sort_simple(t_ps *ps);       // assinatura
void		sort_medium(t_ps *ps);       // assinatura
void		sort_complex(t_ps *ps);      // assinatura
void		sort_small(t_ps *ps);        // assinatura

/* bench.c */
void		print_bench(t_ps *ps);       // assinatura

/* utils.c */
size_t		ft_strlen(const char *s);         // assinatura
int			ft_streq(const char *a, const char *b); // assinatura
void		ft_putstr_fd(const char *s, int fd);    // assinatura
void		ft_putnbr_fd(long n, int fd);           // assinatura
int			ft_isqrt(int n);                        // assinatura

/* utils2.c */
const char	*op_name(int op);                       // assinatura
int			min_pos(t_stack *a);                     // assinatura
void		rot_to_top(t_ps *ps, t_stack *s, int pos, int is_b); // assinatura

#endif                          // fecha o #ifndef do início do arquivo
