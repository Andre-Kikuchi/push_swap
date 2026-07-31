/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahideo-k <ahideo-k@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:44:49 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/27 18:11:14 by ahideo-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(t_ps *ps)             // ps: struct a limpar antes de sair
{
	free_ps(ps);                          // libera a memória das stacks
	ft_putstr_fd("Error\n", 2);            // escreve "Error\n" no stderr (fd 2)
	exit(1);                               // encerra o programa com código de erro 1
}

static int	apply_flag(t_ps *ps, const char *s) // ps: struct; s: a flag lida, ex "--bench"
{
	if (ft_streq(s, "--bench"))           // compara s com "--bench"
		ps->bench = 1;                      // se igual, liga a flag de benchmark
	else if (ft_streq(s, "--simple"))     // senão, compara com "--simple"
		ps->strat = SIMPLE;                 // se igual, força estratégia simples
	else if (ft_streq(s, "--medium"))     // senão, compara com "--medium"
		ps->strat = MEDIUM;                 // se igual, força estratégia medium
	else if (ft_streq(s, "--complex"))    // senão, compara com "--complex"
		ps->strat = COMPLEX;                // se igual, força estratégia complex
	else if (ft_streq(s, "--adaptive"))   // senão, compara com "--adaptive"
		ps->strat = ADAPTIVE;               // se igual, força estratégia adaptativa
	else                                   // se não bateu com nenhuma flag conhecida...
		return (0);                         // ...devolve 0 (falha)
	return (1);                            // se chegou aqui, alguma flag foi aplicada: sucesso
}

int	parse_flags(t_ps *ps, int argc, char **argv) // argc: total de argumentos; argv: os textos
{
	int	i;                                 // índice de percurso pelos argumentos

	i = 1;                                  // começa em 1 (argv[0] é o nome do programa)
	while (i < argc && argv[i][0] == '-' && argv[i][1] == '-')
	// continua enquanto: ainda há argumentos E o atual começa com "--"
	{
		if (apply_flag(ps, argv[i]) == 0)       // tenta aplicar a flag; se apply_flag falhou...
			error_exit(ps);                   // ...aborta com erro (flag desconhecida)
		i++;                                  // avança pro próximo argumento
	}
	return (i);                             // devolve o índice de onde os números começam
}
