/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahideo-k <ahideo-k@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/27 18:10:38 by ahideo-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	op_swap(t_stack *s)        // static: só visível dentro deste arquivo
{
	int	tmp;                            // variável temporária pra troca

	if (s->size < 2)                     // se tem menos de 2 elementos...
		return ;                          // ...não há o que trocar, sai da função
	tmp = s->v[s->top];                  // guarda o valor do topo em tmp
	s->v[s->top] = s->v[(s->top + 1) % s->cap]; // topo recebe o valor do segundo elemento
	s->v[(s->top + 1) % s->cap] = tmp;   // segundo elemento recebe o valor guardado (tmp)
}

static void	op_push(t_stack *src, t_stack *dst) // src: origem; dst: destino
{
	int	x;                              // guarda o valor que será movido

	if (src->size == 0)                  // se a origem está vazia...
		return ;                          // ...não há nada pra empurrar, sai
	x = src->v[src->top];                // lê o valor do topo da origem
	src->top = (src->top + 1) % src->cap; // avança o topo da origem (removeu o elemento)
	src->size--;                          // diminui o tamanho da origem em 1
	dst->top = (dst->top + dst->cap - 1) % dst->cap; // recua o topo do destino (abre espaço)
	dst->v[dst->top] = x;                 // escreve o valor movido na nova posição de topo
	dst->size++;                          // aumenta o tamanho do destino em 1
}

static void	op_rot(t_stack *s)          // rotação "pra cima" (ra/rb)
{
	if (s->size < 2)                      // com 0 ou 1 elemento, rotação não muda nada
		return ;                           // sai sem fazer nada
	s->v[(s->top + s->size) % s->cap] = s->v[s->top]; // copia o valor do topo pro "final"
	s->top = (s->top + 1) % s->cap;        // avança o topo em 1 posição (com wraparound)
}

static void	op_rrot(t_stack *s)         // rotação reversa (rra/rrb)
{
	if (s->size < 2)                      // com 0 ou 1 elemento, nada a fazer
		return ;                           // sai
	s->top = (s->top + s->cap - 1) % s->cap; // recua o topo em 1 posição (com wraparound)
	s->v[s->top] = s->v[(s->top + s->size) % s->cap]; // copia o valor do "final" pro novo topo
}

void	do_op(t_ps *ps, t_op op)          // ps: struct mestre; op: qual operação executar
{
	if (op == SA || op == SS)             // se pediram sa OU ss (que inclui sa)...
		op_swap(&ps->a);                   // ...troca os 2 primeiros de 'a'
	if (op == SB || op == SS)             // se pediram sb OU ss...
		op_swap(&ps->b);                   // ...troca os 2 primeiros de 'b'
	if (op == PA)                          // se pediram pa (push de b pra a)...
		op_push(&ps->b, &ps->a);            // ...move do topo de b pro topo de a
	if (op == PB)                          // se pediram pb (push de a pra b)...
		op_push(&ps->a, &ps->b);            // ...move do topo de a pro topo de b
	if (op == RA || op == RR)              // se pediram ra OU rr (que inclui ra)...
		op_rot(&ps->a);                     // ...gira 'a' pra cima
	if (op == RB || op == RR)              // se pediram rb OU rr...
		op_rot(&ps->b);                     // ...gira 'b' pra cima
	if (op == RRA || op == RRR)            // se pediram rra OU rrr...
		op_rrot(&ps->a);                    // ...gira 'a' pra baixo (reverso)
	if (op == RRB || op == RRR)            // se pediram rrb OU rrr...
		op_rrot(&ps->b);                    // ...gira 'b' pra baixo (reverso)
	ps->count[op]++;                        // incrementa o contador dessa operação (--bench)
	if (!ps->quiet)                         // se NÃO está em modo silencioso...
		ft_putstr_fd(op_name(op), 1);        // ...imprime o nome da operação no stdout (fd 1)
}
