/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:34:18 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/11 00:34:18 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"



static void	set_min_to_bot(t_stk *stk, t_mngr *mngr)
{
	char dir;

	stk->min = ((int*)mngr->vec->data)[((stk->lst_s - 1) / 2) + 1];
	dir = val_to_place_dir_exist(stk, stk->min, stk->lst_s - 1);
	mngr->stk[1]->min = INT_MAX;
	mngr->stk[1]->max = INT_MIN;
	while ((int)stk->l_e->data != stk->min)
	{
		safe_swap(mngr, BOTH_ONL, 0);
		if ((int)stk->lst->data <= stk->piv)
		{
			ft_printf("pb\n", mngr->dbg *= cmd_push(mngr, "b"));
			mngr->stk[1]->max = mngr->stk[1]->max > (int)mngr->stk[1]->lst->data
					? mngr->stk[1]->max : (int)mngr->stk[1]->lst->data;
			mngr->stk[1]->min = mngr->stk[1]->min < (int)mngr->stk[1]->lst->data
					? mngr->stk[1]->min : (int)mngr->stk[1]->lst->data;
		}
		else if (dir > 0)
			safe_rotate(mngr, 0);
		else if (dir < 0)
			safe_rotate(mngr, 'r');
	}
}

static void	push_max_to_place(t_stk *stk, t_mngr *mngr)
{
	t_stk	*stk1;

	stk1 = mngr->stk[1];
	while ((long)(stk->lst_s - stk1->lst_s) >= 1)
	{
		safe_swap(mngr, A_OR_BOTH, 0);
		if ((int)stk->lst->data <= stk->piv)
		{
			ft_printf("pb\n", mngr->dbg *= cmd_push(mngr, "b"));
			mngr->stk[1]->max = mngr->stk[1]->max > (int)mngr->stk[1]->lst->data
								? mngr->stk[1]->max : (int)mngr->stk[1]->lst->data;
			mngr->stk[1]->min = mngr->stk[1]->min < (int)mngr->stk[1]->lst->data
								? mngr->stk[1]->min : (int)mngr->stk[1]->lst->data;
		}
		else
			safe_rotate(mngr, 0);
	}
}

void		split_stack(t_mngr *mngr)
{
	t_stk	*stk;

	stk = mngr->stk[0];
	mngr->stk[1]->min = stk->min;
	mngr->stk[1]->max = stk->piv;
	set_min_to_bot(mngr->stk[0], mngr);
	push_max_to_place(stk, mngr);
}