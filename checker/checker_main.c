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

int	check_sort_simple(t_mngr *mngr)
{
	t_list *lst;

	if (mngr->stk[1]->lst)
		return (0);
	lst = mngr->stk[0]->lst;
	while (lst->next && (int)lst->data < (int)lst->next->data)
		lst = lst->next;
	if (lst->next)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_mngr	mngr;

	ft_bzero(&mngr, sizeof(mngr));
	mngr.fd = STDIN_FILENO;
	mngr.tp = 'c';
	if (ac == 1)
		pushswap_exit(NULL, NO_ARG);
	else
		parse_args(ac, av, &mngr);
	draw_stacks(&mngr, INIT);
	parse_commands(&mngr);
	if (mngr.dbg)
		ft_printf("Total operations = %d\n", mngr.n_cmd);
	if (check_sort_simple(&mngr))
		ft_printf("{Green}OK{eof}\n");
	else
		ft_printf("{Red}KO{eof}\n");
	pushswap_exit(&mngr, SUCCESS);
}
