/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <ehugh-be@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:53:41 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/06/07 18:59:34 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#ifdef VIZUALIZER

static void		stk_del(t_stk *stk, t_mngr *mngr)
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

void		clean_all(t_mngr *mngr, int err)
{
	if (mngr->stk[0])
		stk_del(mngr->stk[0], mngr);
	if (mngr->stk[1])
		stk_del(mngr->stk[1], mngr);
	if (mngr->viz && mngr->mlx)
	{
		mlx_destroy_window(mngr->mlx->mlx, mngr->mlx->win_ptr);
		free(mngr->mlx);
	}
	close(mngr->fd);
	free(mngr->l_cmd);
	ft_avlfree(mngr->s_arr);
	exit(err);
}

#else

static void	stk_del(t_stk *stk, t_mngr *mngr)
{
	t_list *lst;
	t_list	*tmp;

	if (!stk)
		return ;
	lst = stk->lst;
	while (lst)
	{
		tmp = lst->next;
		ft_lstdelone(&lst, NULL);
		lst = tmp;
	}
	free(stk);
	mngr = mngr + 0;
}

void		clean_all(t_mngr *mngr, int err)
{
	if (mngr->stk[0])
		stk_del(mngr->stk[0], mngr);
	if (mngr->stk[1])
		stk_del(mngr->stk[1], mngr);
	close(mngr->fd);
	free(mngr->l_cmd);
	ft_avlfree(mngr->s_arr);
	exit(err);
}

#endif
