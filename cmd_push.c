/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:52:47 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/02 18:52:47 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	pushfirst(t_stk *from, t_stk *to, t_mngr *mngr)
{
	t_list *tmp;

	if (!from->lst)
		checker_error(mngr, WRONG_INSTR);
	tmp = from->lst->next;
	from->lst->next = to->lst;
	to->lst = from->lst;
	from->lst = tmp;
	from->lst_size--;
	to->lst_size++;
	from->l_e = from->lst_size == 0 ? NULL : from->l_e;
	to->l_e = to->lst_size == 1 ? to->lst : to->l_e;
}

char		cmd_push(t_mngr *mngr, char *str)
{
	mngr->n_cmd++;
	if (*str == 'a')
		pushfirst(mngr->stk[1], mngr->stk[0], mngr);
	else if (*str == 'b')
		pushfirst(mngr->stk[0], mngr->stk[1], mngr);
	else
		checker_error(mngr, NOT_EXIST_INSTR);
	if (*(str + 1))
		checker_error(mngr, NOT_EXIST_INSTR);
	return (PSH_A + (*str == 'b'));
}