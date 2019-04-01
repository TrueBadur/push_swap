/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:57:16 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/01 16:57:16 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PUSH_SWAP_CHECKER_H
# define PUSH_SWAP_CHECKER_H
# define NO_ARG_MSG "You must provide set of nonduplicate ints as arguments"
# define STR_ARG_MSG "Nonnumeric characters not allowed in arguments"
# define INT_OVERFLOW_MSG "One or more of the arguments doesn't fit in int"

# include "libft.h"

typedef struct	s_stacks
{
	t_list	*a;
	t_list	*b;
	t_list	*a_end;
	t_list	*b_end;
}				t_stk;

enum	e_errors
{
	NO_ARG = 1,
	STR_ARG,
	INT_OVERFLOW_ARG,
	DUPLICTATE_ARG,
	NOT_EXIST_INSTR,
	WRONG_INSTR,
};

void checker_error(t_stk *stk, int err);
t_stk	*parse_args(int ac, char **av);
void	parse_commands(t_stk *stk);

#endif //PUSH_SWAP_CHECKER_H
