/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_bouble.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:01:50 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/08 22:01:50 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void dbd_split_stack(t_mngr *mngr)
{
	//upgraded split for double bouble
	//send here only those elements which are less then mid of array
	//simultaneously sort a stack
}

static void	bsort_both(t_mngr *mngr)
{
	int	tmp;
	int i;

	//while not sorted
	//sort down ascending
	tmp = mngr->stk[0]->lst_size - 1;
	i = mngr->stk[0]->lst_size - 1;
	while (i)
	{
		tmp = i;
		while (tmp)
		{
			if ((int) mngr->stk[0]->lst->next->content <
				(int) mngr->stk[0]->lst->content)
				((int) mngr->stk[1]->lst->next->content <
				 (int) mngr->stk[1]->lst->content) ?
				ft_printf("sr\n", mngr->dbg *= cmd_swap(mngr, "r")) : ft_printf("sa\n", mngr->dbg *= cmd_swap(mngr, "a"));
			else if ((int) mngr->stk[1]->lst->next->content <
					 (int) mngr->stk[1]->lst->content)
				ft_printf("sb\n", mngr->dbg *= cmd_swap(mngr, "b"));
			if (--tmp > 1)
				ft_printf("rr\n", mngr->dbg *= cmd_rotate(mngr, "r"));
			//	draw_stacks(mngr);
		}
		draw_stacks(mngr);
		ft_printf("rrr\n", mngr->dbg *= cmd_rotate(mngr, "rr"));
		draw_stacks(mngr);
		tmp = i;
		while (tmp)
		{
			if ((int) mngr->stk[0]->lst->next->content <
				(int) mngr->stk[0]->lst->content)
				((int) mngr->stk[1]->lst->next->content <
				 (int) mngr->stk[1]->lst->content) ?
				ft_printf("sr\n", mngr->dbg *= cmd_swap(mngr, "r")) : ft_printf(
						"sa\n", mngr->dbg *= cmd_swap(mngr, "a"));
			else if ((int) mngr->stk[1]->lst->next->content <
					 (int) mngr->stk[1]->lst->content)
				ft_printf("sb\n", mngr->dbg *= cmd_swap(mngr, "b"));
			if (--tmp > 1)
				ft_printf("rrr\n", mngr->dbg *= cmd_rotate(mngr, "rr"));
			draw_stacks(mngr);
		}
		i--;
		draw_stacks(mngr);
		ft_printf("rr\n", mngr->dbg *= cmd_rotate(mngr, "r"));
		draw_stacks(mngr);
	}
	//else rotate
	//sort up descending

}

void	double_bouble(t_mngr *mngr)
{
	split_stack(mngr);
	draw_stacks(mngr);
	//rotate till new mid element each stack
	bsort_both(mngr);
	//draw_stacks(mngr);
	//merge_two(mngr);
}

pb
pb
sb
pb
sr
pb
sr
ra
ra
sa
ra
ra
sa
pb
sa
pb
sr
pb
sr
sa
rr
sr
rr
rr
sr
rr
sr
rr
sr
ra
sa
rrr
sa
rrr
sb
rrr
sr
rrr
sa
rra
sa
rr
rr
sb
rr
sr
rrr
sa
rrr
rrr
pa
pa
pa
pa
pa
pa
pa


pb
pb
pb
rra
rra
sa
ra
sa
ra
sa
pb
sr
pb
ra
sa
ra
sa
sa
ra
sa
pb
sa
rb
pb
sr
pb
sa
rrr
sr
rrr
sb
rra
sa
rra
sa
rra
sa
ra
rb
rr
rr
sa
rra
sa
rra
sa
rra
rra
pa
pa
pa
pa
pa
pa
pa
pa