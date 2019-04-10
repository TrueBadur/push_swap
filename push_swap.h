/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 05:30:53 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/05 05:30:53 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PUSH_SWAP_PUSH_SWAP_H
# define PUSH_SWAP_PUSH_SWAP_H
# define NO_ARG_MSG "You need to provide at least one numerical argument."
# define STR_ARG_MSG "Arguments must be only numerical."
# define INT_OVERFLOW_MSG "Arguments must fit into int."
# define DUP_ARG_MSG "Arguments can not duplicate"


# include <fcntl.h>
# include "libft.h"

typedef struct	s_stacks
{
	t_list	*lst;
	t_list	*l_e;
	size_t	lst_size;
}				t_stk;

typedef struct s_mngr
{
	t_stk		*stk[2];
	char		col;
	char		dbg;
	char		*l_cmd;
	unsigned	n_cmd;
	t_btavl		*s_arr;
	int 		min;
	int 		max;
}				t_mngr;

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

void	checker_error(t_mngr *mngr, int err);
void	parse_args(int ac, char **av, t_mngr *mngr);
void	draw_stacks(t_mngr *mngr);
void	gen_commands(t_mngr *mngr);
char	cmd_swap(t_mngr *mngr, char *str);
char	cmd_rotate(t_mngr *mngr, char *str);
char	cmd_push(t_mngr *mngr, char *str);
void	parse_commands(t_mngr *mngr);
void	bin_merge(t_mngr *mngr);
void	split_stack(t_mngr *mngr);
void	double_bouble(t_mngr *mngr);

#endif //PUSH_SWAP_PUSH_SWAP_MAIN_H
