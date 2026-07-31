/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahideo-k <ahideo-k@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/27 17:23:19 by ahideo-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	run_strategy(t_ps *ps)
{
	ps->used = ps->strat;
	if (ps->strat == ADAPTIVE)
	{
		if (ps->disorder < 2000)
			ps->used = SIMPLE;
		else if (ps->disorder < 5000)
			ps->used = MEDIUM;
		else
			ps->used = COMPLEX;
		if (ps->a.size <= 5)
		{
			ps->used = SIMPLE;
			sort_small(ps);
			return ;
		}
	}
	if (ps->used == SIMPLE)
		sort_simple(ps);
	else if (ps->used == MEDIUM)
		sort_medium(ps);
	else
		sort_complex(ps);
}

int	main(int argc, char **argv)
{
	t_ps	ps;
	int		i;

	/*1. INICIALIZA
	 Zera a struct mestre: ponteiros de a/b em NULL, flags desligadas,
	 estratégia padrão ADAPTIVE, contador de operações zerado.*/
	init_ps(&ps);

	/*2. SEPARA FLAGS DE NÚMEROS
	 Percorre argv procurando "--simple", "--medium", "--bench", etc.
	 Ajusta ps.strat/ps.bench conforme encontra. Devolve o índice `i`
	 de onde os números de verdade começam (o que sobrou depois das flags).*/
	i = parse_flags(&ps, argc, argv);

	/* Caso de borda: se não sobrou nenhum argumento numérico,
	 o programa não deve imprimir nada — só devolve o prompt.*/
	if (i >= argc)
		return (0);

	/* 3. PROCESSA OS NÚMEROS
	 Conta quantos números existem (inclusive dentro de argumentos com
	 espaço, tipo "4 67 3"), aloca as stacks a e b com essa capacidade
	 (nasce aqui o array circular), converte cada token de string pra
	 int com validação de overflow, e rejeita duplicatas.*/
	parse_numbers(&ps, argc - i, argv + i);

	/* 4. CALCULA DESORDEM
	 Mede o quão longe a stack a está de estar ordenada (a métrica
	 "disorder" exigida pela subject), ANTES de qualquer operação.*/
	ps.disorder = disorder_bp(&ps.a);

	/* 5. CONVERTE PRA RANKS
	 Provavelmente transforma os valores brutos (que podem ser
	 negativos, com buracos, etc.) em posições relativas 0..n-1,
	 facilitando os algoritmos medium/complex de trabalharem com
	 índices em vez de valores absolutos.*/
	to_ranks(&ps);

	/* 6. ESCOLHE ESTRATÉGIA E ORDENA
	 Decide, com base em ps.strat (flag forçada) ou em ps.disorder
	 (modo adaptativo), qual dos quatro algoritmos rodar, e executa.
	 É aqui que as operações (sa, pa, ra, ...) são de fato geradas
	 e impressas na saída padrão.*/
	run_strategy(&ps);

	/* Etapa extra, condicional: só roda se a flag --bench foi passada.
	 Imprime no stderr o disorder, a estratégia usada e a contagem
	 de cada operação.*/
	if (ps.bench)
		print_bench(&ps);

	/* 7. LIBERA MEMÓRIA
	 Dá free no buffer das duas stacks (a.v e b.v), evitando leak.*/
	free_ps(&ps);
	return (0);
}
