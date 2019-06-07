/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:38:46 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/06/07 20:05:23 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stk	*swp_first(t_stk *stk)
{
	t_list	*tmp;

	if (!stk->lst || !stk->lst->next)
		return (stk);
	tmp = stk->lst->next;
	stk->lst->next = stk->lst->next->next;
	tmp->next = stk->lst;
	stk->lst = tmp;
	if (stk->lst_s == 2)
		stk->l_e = stk->lst->next;
	return (stk);
}

char			cmd_swap(t_mngr *mngr, const char *str)
{
	mngr->n_cmd++;
	if (*str == 'a' || *str == 'b' || *str == 's')
	{
		if (*str == 'a' || *str == 's')
			mngr->stk[0] = swp_first(mngr->stk[0]);
		if (*str == 'b' || *str == 's')
			mngr->stk[1] = swp_first(mngr->stk[1]);
	}
	else
		pushswap_exit(mngr, WRONG_INSTR);
	if (*(str + 1))
		pushswap_exit(mngr, WRONG_INSTR);
	if (mngr->dbg)
		draw_stacks(mngr, SWP_A + (*str == 'b') + 2 * (*str == 's'));
	return (mngr->dbg);
}

void			swap(t_mngr *mngr, t_eops cmd)
{
	if (cmd == SWP_S)
		ft_fdprintf(mngr->fd, "ss\n", cmd_swap(mngr, "s"));
	else
	{
		ft_fdprintf(mngr->fd, cmd == SWP_A ? "sa\n" : "sb\n");
		cmd_swap(mngr, cmd == SWP_A ? "a" : "b");
	}
}
