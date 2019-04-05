/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:54:11 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/02 18:54:11 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static t_stk * rot_f(t_stk *stk, t_mngr *mngr)
{
	t_list *tmp;

	if (!stk || !stk->lst || !stk->l_e)
		checker_error(mngr, WRONG_INSTR);
	if (stk->lst == stk->l_e)
		return (stk);
	tmp = stk->lst->next;
	stk->lst->next = stk->l_e->next;
	stk->l_e->next = stk->lst;
	stk->l_e = stk->l_e->next;
	stk->lst = tmp;
	return (stk);
}

static t_stk *rot_r(t_stk *stk, t_mngr *mngr)
{
	t_list *tmp;

	if (!stk || !stk->lst || !stk->l_e)
		checker_error(mngr, WRONG_INSTR);
	if (stk->lst == stk->l_e)
		return (stk);
	tmp = stk->l_e;
	stk->l_e = (ft_lstfind_n(stk->lst, stk->lst_size - 2));
	stk->l_e->next = NULL;
	tmp->next = stk->lst;
	stk->lst = tmp;
	return (stk);
}

char		cmd_rotate(t_mngr *mngr, char *str)
{
	char	r;

	r = *str == 'r' ? 1 : 0;
	str += r;
	if (*str == 'a' || *str == 'b' || *str == 's')
	{
		if (*str == 'a' || *str == 's')
			mngr->stk[0] = r ? rot_r(mngr->stk[0], mngr) :
					rot_f(mngr->stk[0], mngr);
		if (*str == 'b' || *str == 's')
			mngr->stk[1] = r ? rot_r(mngr->stk[1], mngr) :
					rot_f(mngr->stk[1], mngr);
	}
	else
		checker_error(mngr, NOT_EXIST_INSTR);
	if (*(str + 1))
		checker_error(mngr, NOT_EXIST_INSTR);
	return (ROT_A * !r + RROT_A * r + 2 * (*str == 's') + (*str == 'b'));
}
