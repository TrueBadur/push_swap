/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <ehugh-be@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:52:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/06/06 23:01:12 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stk_del(t_stk *stk, t_mngr *mngr)
{
	t_list *lst;
	t_list	*tmp;

	if (!stk)
		return ;
	lst = stk->lst;
	while (lst)
	{
		tmp = lst->next;
		if (mngr->viz && lst->content_size > sizeof(int))
		{
			mlx_destroy_image(mngr->mlx->mlx, ((t_simg*)lst->data)->img->img_ptr);
			free(((t_simg*)lst->data)->img);
			free(lst->data);
			free(lst);
		}
		else
			ft_lstdelone(&lst, NULL);
		lst = tmp;
	}
	free(stk);
}

void	help(void)
{
	ft_printf("Usage:\n./pushswap [-(file|debug|vis|color|bubble)]"
"('number_to_be_sorted')|(numbers to be sorted)\n"
"every flag should be given separately\n"
"-file should be the last one just before file name\n");
}

/*
** @param stk - main t_stk which will be cleaned before exit or NULL
** @param err - number of error from e_errors enum
** Prints error message to stderror, clean up and exit the program
*/

#ifdef HIDDEN

void	pushswap_exit(t_mngr *mngr, int err)
{
	if (err != HELP_CALL)
		ft_fdprintf(STDERR_FILENO, "Error\n");
	else
		help();
	if (err == NO_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", NO_ARG_MSG);
	else if (err == STR_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", STR_ARG_MSG);
	else if (err == INT_OVERFLOW_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", INT_OVERFLOW_MSG);
	else if (err == DUPLICTATE_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", DUP_ARG_MSG);
	stk_del(mngr->stk[0]);
	stk_del(mngr->stk[1]);
	free(mngr->l_cmd);
	ft_avlfree(mngr->s_arr);
	ft_vecdel((void**)&mngr->vec);
	exit(err);
}

#else

void	pushswap_exit(t_mngr *mngr, int err)
{
	if (err != HELP_CALL && err != SUCCESS)
		ft_fdprintf(STDERR_FILENO, "Error\n");
	else if (err == HELP_CALL)
		help();
	if (err == NO_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", NO_ARG_MSG);
	else if (err == STR_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", STR_ARG_MSG);
	else if (err == INT_OVERFLOW_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", INT_OVERFLOW_MSG);
	else if (err == DUPLICTATE_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", DUP_ARG_MSG);
	stk_del(mngr->stk[0], mngr);
	stk_del(mngr->stk[1], mngr);
	if (mngr->viz)
	{
		mlx_destroy_window(mngr->mlx->mlx, mngr->mlx->win_ptr);
		free(mngr->mlx);
	}
	close(mngr->fd);
	free(mngr->l_cmd);
	ft_avlfree(mngr->s_arr);
	exit(err);
}

#endif
