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

void	split_stack(t_mngr *mngr)
{
	size_t tl;

	tl = mngr->stk[0]->lst_size / 2;
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

	i = mngr->stk[1]->lst_size / 2;
	while(i--)
	{
		la = mngr->stk[0]->lst;
		lb = mngr->stk[1]->lst;
		//TODO handle odd number of items in b and a stacks
		if ((int)la->content > (int)la->next->content)
		{
			if ((int)lb->content > (int)lb->next->content)
				ft_printf("sr\n", mngr->dbg *= cmd_swap(mngr, "r"), mngr->n_cmd++);
			else
				ft_printf("sa\n", mngr->dbg *= cmd_swap(mngr, "a"), mngr->n_cmd++);
		}
		else if ((int)lb->content > (int)lb->next->content)
			if (i != 0 || mngr->stk[1]->lst_size == mngr->stk[0]->lst_size)
				ft_printf("sb\n", mngr->dbg *= cmd_swap(mngr, "b"), mngr->n_cmd++);
		if (mngr->dbg > 1)
			draw_stacks(mngr);
		if (i > 0)
			ft_printf("rr\nrr\n", cmd_rotate(mngr, "r"),
					mngr->dbg *= cmd_rotate(mngr, "r"), mngr->n_cmd += 2);
		if (mngr->dbg > 1)
			draw_stacks(mngr);
	}
}

static void	merge_pairs(t_mngr *mngr, int sc)
{
	t_list *la;
	t_list	*lb;
	int		i;
	int 	j;
	int 	k;
	int		l;

	if (!mngr->stk[1]->lst_size)
		return ;
	i = mngr->stk[0]->lst_size / sc; //TODO handle odd number of items and different number of items in stacks
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
				if (la && (((int) la->content < (int)lb->content && l)|| !k))
					ft_printf("pb\n", mngr->dbg *= cmd_push(mngr, "b"), l--, mngr->n_cmd++);
				ft_printf("rb\n", mngr->dbg *= cmd_rotate(mngr, "b"), mngr->n_cmd);
				k -= k && (int)la->content >= (int)lb->content ? 1 : 0;
			}
			else
			{
				if (lb && (((int) lb->content < (int)la->content && l) || !k))
					ft_printf("pa\n", mngr->dbg *= cmd_push(mngr, "a"), l--, mngr->n_cmd++);
				ft_printf("ra\n", mngr->dbg *= cmd_rotate(mngr, "a"), mngr->n_cmd++);
				k -= lb && k && (int)lb->content >= (int)la->content ? 1 : 0;
			}
			//draw_stacks(mngr);
		}
	}
	merge_pairs(mngr, sc * 2);
}

void bin_merge(t_mngr *mngr)
{
	split_stack(mngr);
	//draw_stacks(mngr);
	sort_pairs(mngr);
	merge_pairs(mngr, 2);
}
