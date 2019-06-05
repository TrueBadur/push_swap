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
		pushswap_exit(mngr, WRONG_INSTR);
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
		pushswap_exit(mngr, WRONG_INSTR);
	if (stk->lst == stk->l_e)
		return (stk);
	tmp = stk->l_e;
	stk->l_e = (ft_lstfind_n(stk->lst, stk->lst_s - 2));
	stk->l_e->next = NULL;
	tmp->next = stk->lst;
	stk->lst = tmp;
	return (stk);
}

char cmd_rotate(t_mngr *mng, const char *str, int dir)
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
		pushswap_exit(mng, NOT_EXIST_INSTR);
	if (*(str + 1))
		pushswap_exit(mng, NOT_EXIST_INSTR);
	if (mng->dbg)
		draw_stacks(mng, ROT_A * !r + RROT_A * r + 2 * (*str == 'r') +
		(*str == 'b'));
	return (mng->dbg);
}

void	rotate(t_mngr *mngr, t_eops cmd)
{
	if (cmd < RROT_A)
	{
		if (cmd == ROT_R)
			ft_fdprintf(mngr->fd, "rr\n", cmd_rotate(mngr, "r", 0));
		else
		{
			ft_fdprintf(mngr->fd, cmd == ROT_A ? "ra\n" : "rb\n");
			cmd_rotate(mngr, cmd == ROT_A ? "a" : "b", 0);
		}
	}
	else
	{
		if (cmd == RROT_R)
			ft_fdprintf(mngr->fd, "rrr\n", cmd_rotate(mngr, "rr", 0));
		else
		{
			ft_fdprintf(mngr->fd, cmd == RROT_A ? "rra\n" : "rrb\n");
			cmd_rotate(mngr, cmd == RROT_A ? "ra" : "rb", 0);
		}
	}
}