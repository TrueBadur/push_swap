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
# include <fcntl.h>

typedef struct	s_stacks
{
	t_list	*lst;
	t_list	*l_e;
	size_t	lst_size;
}				t_stk;

typedef struct s_mngr
{
	t_stk	*stk[2];
	char	col;
	char 	dbg;
	char	*l_cmd;
	unsigned n_cmd;
	int 		fd;
}				t_mngr;

enum	e_errors
{
	NO_ARG = 1,
	STR_ARG,
	INT_OVERFLOW_ARG,
	DUPLICTATE_ARG,
	NOT_EXIST_INSTR,
	WRONG_INSTR,
	INTERNAL_ERROR,
	MEMORY_ALLOC_FAIL,
};

enum 	e_ops
{
	SWP_A = 2,
	SWP_B,
	SWP_S,
	PSH_A = 12,
	PSH_B,
	ROT_A = 22,
	ROT_B,
	ROT_R,
	RROT_A = 32,
	RROT_B,
	RROT_R
};

void checker_error(t_mngr *mngr, int err);
void *parse_args(int ac, char **av, t_mngr *mngr);
void	parse_commands(t_mngr *mngr);
char	cmd_swap(t_mngr *mngr, char *str);
char	cmd_rotate(t_mngr *mngr, char *str);
char	cmd_push(t_mngr *mngr, char *str);
void	draw_stacks(t_mngr *mngr);


#endif //PUSH_SWAP_CHECKER_H
