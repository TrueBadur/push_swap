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

#include "push_swap.h"

t_stk * rot_f(t_stk *stk, t_mngr *mngr)
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

t_stk *rot_r(t_stk *stk, t_mngr *mngr)
{
	t_list *tmp;

	if (!stk || !stk->lst || !stk->l_e)
		checker_error(mngr, WRONG_INSTR);
	if (stk->lst == stk->l_e)
		return (stk);
	tmp = stk->l_e;
	stk->l_e = (ft_lstfind_n(stk->lst, stk->lst_s - 2));
	stk->l_e->next = NULL;
	tmp->next = stk->lst;
	stk->lst = tmp;
	return (stk);
}

char cmd_rotate(t_mngr *mng, char *str, int dir)
{
	char	r;

	mng->n_cmd++;
	if (!dir)
	{
		r = *str == 'r' && *(str + 1) ? 1 : 0;
		str += r;
	}
	else
		r = 1;
	if (*str == 'a' || *str == 'b' || *str == 'r')
	{
		if (*str == 'a' || *str == 'r')
			mng->stk[0] = r ? rot_r(mng->stk[0], mng) : rot_f(mng->stk[0], mng);
		if (*str == 'b' || *str == 'r')
			mng->stk[1] = r ? rot_r(mng->stk[1], mng) : rot_f(mng->stk[1], mng);
	}
	else
		checker_error(mng, NOT_EXIST_INSTR);
	if (*(str + 1))
		checker_error(mng, NOT_EXIST_INSTR);
	mng->dbg *= ROT_A * !r + RROT_A * r + 2 * (*str == 'r') + (*str == 'b');
	if (mng->dbg)
		draw_stacks(mng);
	return (mng->dbg);
}
