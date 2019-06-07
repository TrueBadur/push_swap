/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:52:47 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/06/07 20:03:34 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	fndmax(t_list *lst)
{
	int max;

	max = INT_MIN;
	while (lst)
	{
		max = (int)lst->data > max ? (int)lst->data : max;
		lst = lst->next;
	}
	return (max);
}

static int	fndmin(t_list *lst)
{
	int min;

	min = INT_MAX;
	while (lst)
	{
		min = (int)lst->data < min ? (int)lst->data : min;
		lst = lst->next;
	}
	return (min);
}

static void	pushfirst(t_stk *from, t_stk *to)
{
	t_list *tmp;

	if (!from->lst)
		return ;
	tmp = from->lst->next;
	from->lst->next = to->lst;
	to->lst = from->lst;
	from->lst = tmp;
	from->lst_s--;
	to->lst_s++;
	from->l_e = from->lst_s == 0 ? NULL : from->l_e;
	to->l_e = to->lst_s == 1 ? to->lst : to->l_e;
	to->min = to->min > (int)to->lst->data ? (int)to->lst->data : to->min;
	to->max = to->max < (int)to->lst->data ? (int)to->lst->data : to->max;
	from->max = from->max == (int)to->lst->data ? fndmax(from->lst) : from->max;
	from->min = from->min == (int)to->lst->data ? fndmin(from->lst) : from->min;
}

char		cmd_push(t_mngr *mngr, const char *str)
{
	mngr->n_cmd++;
	if (*str == 'a')
		pushfirst(mngr->stk[1], mngr->stk[0]);
	else if (*str == 'b')
		pushfirst(mngr->stk[0], mngr->stk[1]);
	else
		pushswap_exit(mngr, WRONG_INSTR);
	if (*(str + 1))
		pushswap_exit(mngr, WRONG_INSTR);
	if (mngr->dbg)
		draw_stacks(mngr, PSH_A + (*str == 'b'));
	return (mngr->dbg);
}

void		push(t_mngr *mngr, t_eops cmd)
{
	ft_fdprintf(mngr->fd, cmd == PSH_A ? "pa\n" : "pb\n");
	cmd_push(mngr, cmd == PSH_A ? "a" : "b");
}
