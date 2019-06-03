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
#include <limits.h>
# include "libft.h"

typedef struct	s_stacks
{
	t_list	*lst;
	t_list	*l_e;
	int		lst_s;
	int		sq_l;
	int 	sort;
	int		piv;
	int		min;
	int 	max;
}				t_stk;

typedef struct s_mngr
{
	t_stk		*stk[2];
	char		col;
	char		dbg;
	char		*l_cmd;
	unsigned	n_cmd;
	t_btavl		*s_arr;
	t_vector	*vec;
}				t_mngr;

typedef enum 	e_ops
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
}				t_eops;

typedef enum 	e_dir
{
	ASC = -1,
	DESC = 1,
	EQ,
	EMPTY,
	ONE_EL
}				t_edir;

typedef enum	e_swap_opts
{
	STD,
	A_ONL,
	B_ONL,
	BOTH_ONL,
	A_OR_BOTH,
	B_OR_BOTH
}				t_eswopt;

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
char cmd_rotate(t_mngr *mng, char *str, int dir);
char	cmd_push(t_mngr *mngr, const char *str);
void	parse_commands(t_mngr *mngr);
void	bin_merge(t_mngr *mngr);
void	split_stack(t_mngr *mngr);
void	double_bouble(t_mngr *mngr);
t_edir 	cmp_first_two(t_list *lst);
int		val_to_place_dir_exist(t_stk *stk, int val, int place);
int check_sort(t_stk *stk, t_edir dir, int fin);
void	set_sort_both(t_mngr *mngr);
void set_sort(t_stk *stk, t_edir dir, int val);
void smart_swap(t_mngr *mngr);
void	safe_rotate(t_mngr *mngr, char c);
int	get_sort(t_mngr *mngr);
void set_sort(t_stk *stk, t_edir dir, int val);
void safe_swap(t_mngr *mngr, t_eswopt mode, int piv);
t_stk * rot_f(t_stk *stk, t_mngr *mngr);
t_stk *rot_r(t_stk *stk, t_mngr *mngr);
int val_to_place_dir_nexis(t_stk *stk, int val);

#endif //PUSH_SWAP_PUSH_SWAP_MAIN_H