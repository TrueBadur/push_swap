/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_merge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 05:51:58 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/05 05:51:58 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#ifdef HIDDEN

void	simple_split_stack(t_mngr *mngr)
{
	size_t tl;

	tl = mngr->stk[0]->lst_s / 2;
	while (tl--)
	{
		ft_printf("pb\n");
		mngr->dbg *= cmd_push(mngr, "b");
	}
}

static void	sort_pairs(t_mngr *mngr)
{
	int	i;
	t_list *la;
	t_list	*lb;

	i = mngr->stk[1]->lst_s / 2;
	while(i--)
	{
		la = mngr->stk[0]->lst;
		lb = mngr->stk[1]->lst;
		//TODO handle odd number of items in b and a stacks
		if ((int)la->data > (int)la->next->data)
		{
			if ((int)lb->data > (int)lb->next->data)
				ft_printf("sr\n", mngr->dbg *= cmd_swap(mngr, "r"));
			else
				ft_printf("sa\n", mngr->dbg *= cmd_swap(mngr, "a"));
		}
		else if ((int)lb->data > (int)lb->next->data)
			if (i != 0 || mngr->stk[1]->lst_s == mngr->stk[0]->lst_s)
				ft_printf("sb\n", mngr->dbg *= cmd_swap(mngr, "b"));
		if (mngr->dbg > 1)
			draw_stacks(mngr);
		if (i > 0)
			ft_printf("rr\nrr\n", cmd_rotate(mngr, "r", 0),
					  mngr->dbg *= cmd_rotate(mngr, "r", 0));
		if (mngr->dbg > 1)
			draw_stacks(mngr);
	}
}

static void	merge_pairs(t_mngr *mngr, int sc)
{
	t_list	*la;
	t_list	*lb;
	int		i;
	int 	j;
	int 	k;
	int		l;

	if (!mngr->stk[1]->lst_s)
		return ;
	i = mngr->stk[0]->lst_s / sc; //TODO handle odd number of items and different number of items in stacks
	while (i--)
	{
		j = sc * 2;
		k = sc;
		l = sc;
		while (j-- > 0)
		{
			ft_printf("", la = mngr->stk[0]->lst, lb = mngr->stk[1]->lst);
			if (i % 2 != 0)
			{
				if (la && (((int) la->data < (int)lb->data && l)|| !k))
					ft_printf("pb\n", mngr->dbg *= cmd_push(mngr, "b"), l--);
				ft_printf("rb\n", mngr->dbg *= cmd_rotate(mngr, "b", 0));
				k -= k && (int)la->data >= (int)lb->data ? 1 : 0;
			}
			else
			{
				if (lb && (((int) lb->data < (int)la->data && l) || !k))
					ft_printf("pa\n", mngr->dbg *= cmd_push(mngr, "a"), l--);
				ft_printf("ra\n", mngr->dbg *= cmd_rotate(mngr, "a", 0));
				k -= lb && k && (int)lb->data >= (int)la->data ? 1 : 0;
			}
			//draw_stacks(mngr);
		}
	}
	merge_pairs(mngr, sc * 2);
}

void simp_split_stack(t_mngr *mngr)
{
	while (mngr->stk[0]->lst_s != mngr->stk[1]->lst_s)
		ft_printf("pb\n", cmd_push(mngr, "b"));
}

void bin_merge(t_mngr *mngr)
{
	simple_split_stack(mngr);
	//draw_stacks(mngr);
	sort_pairs(mngr);
	merge_pairs(mngr, 2);
}
#endif