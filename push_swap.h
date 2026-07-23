/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahideo-k <ahideo-k@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:47:48 by ahideo-k          #+#    #+#             */
/*   Updated: 2026/07/23 16:20:30 by ahideo-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*representa um elemento da pilha.*/
typedef struct s_node
{
	int				value;		// o número que o usuário digitou
	int				index;		// índice de cada número - facilita os algoritmos que passam a trabalhar com os índices ao invés dos valores originais
	struct s_node	*next;		// ponteiro para o próximo nó
	struct s_node	*prev;		// ponteiro para o nó anterior
}	t_node;

/*representa uma pilha inteira, fornecendo acesso rápido ao topo, à base e ao tamanho*/
typedef struct s_stack
{
	t_node	*begin;				// aponta para o primeiro elemento da pilha
	t_node	*end;              // aponta pra o último elemento da pilha
	int		size;				// quantidade de elementos 
}	t_stack;

/*representa o estado completo do programa, reunindo as duas pilhas e as configurações da execução.*/
typedef struct s_data
{
	t_stack	a;					// representa a stack a
	t_stack	b;					// representa a stack b
	int		bench;				// funciona como uma chave liga/desliga (flag). "O usuário pediu o modo benchmark?" Se sim: bench = 1; se não: bench = 0;
	t_strategy	strategy;			// qual algoritmo que será usado
	double	disorder;			// representa o quão desordenada está a entrada 93,66
}	t_data;

typedef enum e_strategy
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
}	t_strategy;