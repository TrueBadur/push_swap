/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:45:37 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/01 16:45:37 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int check_sort(t_mngr *mngr)
{
	t_list *lst;

	if (mngr->stk[1]->lst)
		return (0);
	lst = mngr->stk[0]->lst;
	while (lst->next && (int)lst->content < (int)lst->next->content)
		lst = lst->next;
	if (lst->next)
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	t_mngr	mngr;

	if (ac == 1)
		checker_error(NULL, NO_ARG);
	else
		parse_args(ac, av, &mngr);
	if (check_sort(&mngr))
		return (0);
	mngr.dbg = 1;
	mngr.col = 1;
	mngr.n_cmd = 0;
	draw_stacks(&mngr);
	gen_commands(&mngr);
	ft_printf("Total operations = %d\n", mngr.n_cmd);
	return (0);
}

