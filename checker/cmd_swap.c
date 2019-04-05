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

#include "checker.h"

static t_stk	*swp_first(t_stk *stk, t_mngr *mngr)
{
	t_list	*tmp;

	if (!stk->lst || !stk->lst->next)
		checker_error(mngr, WRONG_INSTR);
	tmp = stk->lst->next;
	stk->lst->next = stk->lst->next->next;
	tmp->next = stk->lst;
	stk->lst = tmp;
	if (stk->lst_size == 2)
		stk->l_e = stk->lst->next;
	return (stk);
}



char		cmd_swap(t_mngr *mngr, char *str)
{
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
	return (SWP_A + (*str == 'b') + 2 * (*str == 'r'));
}
