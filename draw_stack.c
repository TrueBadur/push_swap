/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 00:13:55 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/03 00:13:55 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


void	printlist(t_list *lst)
{
	ft_printf("{Green}%-12d{eof}\n", (int)lst->data);
}

void	draw_stacks(t_mngr *mngr)
{
	t_list	*a;
	t_list	*b;
	unsigned 	i;

	//TODO wrap long lists
	if (!mngr->dbg)
		return ;
	a = mngr->stk[0]->lst;
	ft_printf("--------------------------------------------------------\n");
	if (mngr->dbg == 1)
	{
		ft_printf("Init a and b:\n");
		ft_lstiter(a, printlist);
	}
	else
	{
		b = mngr->stk[1]->lst;
		ft_printf("Exec %s (%d):\n", mngr->l_cmd, mngr->n_cmd);
		ft_strdel(&mngr->l_cmd);
		i = 0;
		while (a || b)
		{
			if ((mngr->dbg - SWP_A) % 10 == 0 || (mngr->dbg - SWP_S) % 10 == 0)
				if (i == 0 || (i == 1 && mngr->dbg < 10) || (i == mngr->stk[0]->lst_s - 1 && mngr->dbg > 20))
					ft_printf("{Red}");
			if (a)
				ft_printf("%-12d{eof}   ", (int) a->data);
			else
				ft_printf("%15c", ' ');
			if ((mngr->dbg - SWP_B) % 10 == 0 || (mngr->dbg - SWP_S) % 10 == 0)
				if (i == 0 || (i == 1 && mngr->dbg < 10) || (i == mngr->stk[1]->lst_s - 1 && mngr->dbg > 20))
					ft_printf("{Red}");
			if (b)
				ft_printf("%-12d{eof}\n", (int) b->data);
			else
				ft_printf("\n");
			i++;
			a = a ? a->next : a;
			b = b ? b->next : b;
		}
	}
	ft_printf("{Green}____________   {Red}____________{eof}\n");
	ft_printf("      {Green}A              {Red}B     {eof}\n");
	mngr->dbg = 2;
}