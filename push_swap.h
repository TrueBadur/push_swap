/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <ehugh-be@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 05:30:53 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/06/07 02:09:37 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PUSH_SWAP_PUSH_SWAP_H
# define PUSH_SWAP_PUSH_SWAP_H
# define NO_ARG_MSG "You need to provide at least one numerical argument."
# define STR_ARG_MSG "Arguments must be only numerical."
# define INT_OVERFLOW_MSG "Arguments must fit into int."
# define DUP_ARG_MSG "Arguments can not duplicate"
# define WRITE (O_WRONLY | O_CREAT | O_TRUNC)
# define CHMOD (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
# define W_HEIGHT 1300
# define W_WIDTH 1300
# define X_PAD (W_WIDTH / 100)
# define COL_WIDTH ((W_WIDTH - X_PAD * 4) / 2)
# define Y_PAD (W_HEIGHT / 100)
# define SPEED_STEP 25000


# include <fcntl.h>
# include <limits.h>
# include <mlx.h>
#include <time.h>
# include "libft.h"



# ifdef HIDDEN
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
	char		bub;
	char 		viz;
	char		*l_cmd;
	unsigned	n_cmd;
	t_btavl		*s_arr;
	t_vector	*vec;
}				t_mngr;


typedef enum	e_swap_opts
{
	STD,
	A_ONL,
	B_ONL,
	BOTH_ONL,
	A_OR_BOTH,
	B_OR_BOTH
}				t_eswopt;

# else

typedef struct	s_mlx
{
	void *mlx;
	void *win_ptr;
	clock_t		interval;
	char		pause;
	clock_t		sleep;
}				t_mlx;

typedef struct	s_stacks
{
	t_list	*lst;
	t_list	*l_e;
	int		lst_s;
	int		min;
	int 	max;
}				t_stk;

typedef struct s_mngr
{
	t_stk		*stk[2];
	char		dbg;
	char 		viz;
	char 		tp;
	int			fd;
	char		*l_cmd;
	unsigned	n_cmd;
	t_btavl		*s_arr;
	t_mlx		*mlx;
}				t_mngr;

# endif

typedef enum 	e_ops
{
	INIT,
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

enum	e_keys
{
	SPEED_INCREASE = 2,
	SPEED_DECREASE = 0,
	STEP_FORWARD = 36,
	PAUSE = 49,
	QUIT = 53
};

typedef struct	s_img
{
	void		*img_ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_uint2		res;
	t_int2		pos;
}				t_img;

typedef struct	s_stk_img
{
	int		val;
	t_img	*img;
}				t_simg;

enum	e_errors
{
	SUCCESS,
	HELP_CALL,
	NO_ARG,
	STR_ARG,
	FILE_ERROR,
	INT_OVERFLOW_ARG,
	DUPLICTATE_ARG,
	NOT_EXIST_INSTR,
	WRONG_INSTR,
	INTERNAL_ERROR,
	MEMORY_ALLOC_FAIL,
	MLX_FAIL,
	SORT_FAILED,
	INTERUPTED
};

# ifdef HIDDEN

void safe_swap(t_mngr *mngr, t_eswopt mode, int piv);
void 		set_for_bub(t_mngr *mngr);
void		bin_merge(t_mngr *mngr);
void		double_bouble(t_mngr *mngr);
void		set_sort_both(t_mngr *mngr);
void	 	set_sort(t_stk *stk, t_edir dir, int val);
void		smart_swap(t_mngr *mngr);
void		safe_rotate(t_mngr *mngr, char c);
int			get_sort(t_mngr *mngr);
# endif
void  		split_stack_inssort(t_mngr *mngr);
t_vector 	*get_ops_seq(t_stk *stk_c, int num, t_vector *vec);
int 		get_stk_n(t_stk *stk, t_vector **vec, int i);
void 		find_shortest(t_mngr *mngr, t_vector **vec, int i);
void 		eval_seq(t_vector *vec, t_mngr *mngr);
void		parse_nums(t_mngr *mngr, int ac, char **a, int skip);

void		pushswap_exit(t_mngr *mngr, int err);
void		parse_args(int ac, char **av, t_mngr *mngr);
void		draw_stacks(t_mngr *mngr, t_eops cmd);
void		gen_commands(t_mngr *mngr);
void		swap(t_mngr *mngr, t_eops cmd);
char		cmd_swap(t_mngr *mngr, const char *str);
char 		cmd_rotate(t_mngr *mng, const char *str, int dir);
void		rotate(t_mngr *mngr, t_eops cmd);
char		cmd_push(t_mngr *mngr, const char *str);
void		push(t_mngr *mngr, t_eops cmd);
int			parse_command(t_mngr *mngr);
void		split_stack(t_mngr *mngr);
t_edir		cmp_first_two(t_list *lst);
int			val_to_place_dir_exist(t_stk *stk, int val, int place);
int			check_sort(t_stk *stk, t_edir dir, int fin);
t_stk		*rot_f(t_stk *stk, t_mngr *mngr);
t_stk		*rot_r(t_stk *stk, t_mngr *mngr);
int			val_to_place_dir_nexis(t_stk *stk, int val);
int			set_flags(char *arg, int *fd, char **av, t_mngr *mngr);
void 		start_viz(t_mngr *mngr);
void end_programm(t_mngr *mngr);
int		getcolpos(t_eops cmd);

#endif
