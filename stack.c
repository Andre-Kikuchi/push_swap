/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahideo-k <ahideo-k@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/27 18:10:02 by ahideo-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"          // traz todos os tipos e protótipos definidos acima

void	init_ps(t_ps *ps)        // recebe ponteiro pra struct mestre a inicializar
{
	int	i;                      // variável de controle do loop, declarada no topo

	ps->a.v = NULL;              // buffer de 'a' começa nulo (nada alocado ainda)
	ps->b.v = NULL;              // buffer de 'b' começa nulo também
	ps->bench = 0;               // flag de benchmark desligada por padrão
	ps->quiet = 0;                // flag de silêncio desligada (vai imprimir operações)
	ps->strat = ADAPTIVE;         // estratégia padrão exigida pela subject
	ps->used = ADAPTIVE;          // estratégia "usada" também começa como adaptativa
	ps->disorder = 0;             // desordem começa em 0, será calculada depois
	i = 0;                        // inicia o contador do loop em 0
	while (i < 11)                // repete enquanto i for menor que 11 (11 operações)
		ps->count[i++] = 0;        // zera count[i], DEPOIS incrementa i (pós-fixado)
}

void	st_init(t_ps *ps, t_stack *s, int cap) // ps: pra poder chamar error_exit;
                                                 // s: qual stack inicializar; cap: tamanho
{
	s->v = malloc(sizeof(int) * cap); // aloca cap inteiros contíguos na memória
	if (!s->v)                        // se malloc falhou (retornou NULL)...
		error_exit(ps);                // ...aborta o programa com mensagem de erro
	s->cap = cap;                      // guarda a capacidade alocada na struct
	s->top = 0;                        // topo lógico começa na posição física 0
	s->size = 0;                       // nenhum elemento ocupado ainda
}

int	st_get(t_stack *s, int i)         // s: a stack; i: deslocamento a partir do topo
{
	return (s->v[(s->top + i) % s->cap]); // soma top+i, aplica módulo cap, acessa o array
}

int	is_sorted(t_stack *s)              // s: a stack a verificar
{
	int	i;                              // índice de percurso

	i = 1;                              // começa em 1 pra poder comparar com i-1
	while (i < s->size)                 // repete enquanto ainda há pares a comparar
	{
		if (st_get(s, i - 1) > st_get(s, i)) // se o elemento anterior é maior que o atual...
			return (0);                        // ...achou uma inversão: não está ordenado
		i++;                                  // avança pro próximo par
	}
	return (1);                          // percorreu tudo sem inversão: está ordenado
}

void	free_ps(t_ps *ps)                // ps: struct cujas stacks serão liberadas
{
	free(ps->a.v);                      // libera o buffer de 'a' (free(NULL) é seguro)
	free(ps->b.v);                      // libera o buffer de 'b'
	ps->a.v = NULL;                      // zera o ponteiro por segurança (evita use-after-free)
	ps->b.v = NULL;                      // idem para 'b'
}