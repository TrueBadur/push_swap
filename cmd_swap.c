/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:38:46 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/01 22:38:46 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stk	*swp_first(t_stk *stk, t_mngr *mngr)
{
	t_list	*tmp;

	if (!stk->lst || !stk->lst->next)
		checker_error(mngr, WRONG_INSTR);
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
	if (*str == 'a' || *str == 'b' || *str == 'r')
	{
		if (*str == 'a' || *str == 'r')
			mngr->stk[0] = swp_first(mngr->stk[0], mngr);
		if (*str == 'b' || *str == 'r')
			mngr->stk[1] = swp_first(mngr->stk[1], mngr);
	}
	else
		checker_error(mngr, NOT_EXIST_INSTR);
	if (*(str + 1))
		checker_error(mngr, NOT_EXIST_INSTR);
	mngr->dbg *= SWP_A + (*str == 'b') + 2 * (*str == 'r');
	if (mngr->dbg)
		draw_stacks(mngr);
	return (mngr->dbg);
}

void			swap(t_mngr *mngr, t_eops cmd)
{
	if (cmd == SWP_S)
		ft_printf("ss\n", cmd_swap(mngr, "r"));
	else
	{
		ft_printf(cmd == SWP_A ? "sa\n": "sb\n");
		cmd_swap(mngr, cmd == SWP_A ? "a" : "b");
	}
}