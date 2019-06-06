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

static void		print_cmd_name(t_eops cmd, int n_cmd)
{
	static const char	*cmds[] = {"sa", "sb", "ss", "pa", "pb", "ra", "rb",
									"rr", "rra", "rrb", "rrr", "init"};
	int					i;

	if (cmd == INIT)
		i = 11;
	else if (cmd < PSH_A && cmd >= SWP_A)
		if (cmd == SWP_S)
			i = 2;
		else
			i = cmd == SWP_A ? 0 : 1;
	else if (cmd < ROT_A)
		i = cmd == PSH_A ? 3 : 4;
	else if (cmd < RROT_A)
		if (cmd == ROT_R)
			i = 7;
		else
			i = cmd == ROT_A ? 5 : 6;
	else if (cmd == RROT_R)
		i = 10;
	else
		i = cmd == RROT_A ? 8 : 9;
	ft_printf("Exec %s (%d):\n", cmds[i], n_cmd);
}

int		getcolpos(t_eops cmd)
{
	int ret;

	if (cmd == INIT)
		ret = 1;
	else if (cmd < PSH_A && cmd >= SWP_A)
		if (cmd == SWP_S)
			ret = 2 * 3 * 11 * 13;
		else
			ret = cmd == SWP_A ? 2 * 11 : 3 * 13;
	else if (cmd < ROT_A)
		ret = cmd == PSH_A ? 2 : 3;
	else if (cmd < RROT_A)
		if (cmd == ROT_R)
			ret = 2 * 5 * 3 * 7;
		else
			ret = cmd == ROT_A ? 2 * 5 : 3 * 7;
	else if (cmd == RROT_R)
		ret = 2 * 5 * 3 * 7;
	else
		ret = cmd == RROT_A ? 2 * 5 : 3 * 7;
	return (ret);
}

void			print_first(t_list **a, t_list **b, int colpos)
{
	int i;

	i = 0;
	while ((*a || *b) && i++ < 2)
	{
		if ((colpos % 2 == 0 && i == 1) || (colpos % 11 == 0 && i == 2))
			ft_printf("{Red}");
		if (*a)
			ft_printf("%-12d{eof}   ", (int)(*a)->data);
		else
			ft_printf("%15c", ' ');
		if ((colpos % 3 == 0 && i == 1) || (colpos % 13 == 0 && i == 2))
			ft_printf("{Red}");
		if (*b)
			ft_printf("%-12d{eof}", (int)(*b)->data);
		ft_printf("\n");
		*a = *a ? (*a)->next : *a;
		*b = *b ? (*b)->next : *b;
	}
}

static void		print_else(t_list *a, t_list *b, int colpos)
{
	while (a || b)
	{
		if (a && !a->next && colpos % 5 == 0)
			ft_printf("{Red}");
		if (a)
			ft_printf("%-12d{eof}   ", (int)a->data);
		else
			ft_printf("%15c", ' ');
		if (b && !b->next && colpos % 7 == 0)
			ft_printf("{Red}");
		if (b)
			ft_printf("%-12d{eof}\n", (int)b->data);
		else
			ft_printf("\n");
		a = a ? (a)->next : a;
		b = b ? (b)->next : b;
	}
}

void			draw_stacks(t_mngr *mngr, t_eops cmd)
{
	t_list	*a;
	t_list	*b;
	int		colpos;

	if (mngr->dbg != 1)
		return ;
	a = mngr->stk[0]->lst;
	colpos = getcolpos(cmd);
	ft_printf("------------------------------------------------------------\n");
	b = mngr->stk[1]->lst;
	print_cmd_name(cmd, mngr->n_cmd);
	print_first(&a, &b, colpos);
	print_else(a, b, colpos);
	ft_printf("{Green}____________   {Red}____________{eof}\n");
	ft_printf("      {Green}A              {Red}B     {eof}\n");
}
