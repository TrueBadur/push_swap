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

#ifdef HIDDEN

int	main(int ac, char **av)
{
	t_mngr	mngr;

	ft_bzero(&mngr, sizeof(mngr));
	if (ac == 1)
		checker_error(NULL, NO_ARG);
	else
		parse_args(ac, av, &mngr);
	if (mngr.bub)
		set_for_bub(&mngr);
	mngr.s_arr = ft_avlfree(mngr.s_arr);
	if (check_sort(mngr.stk[0], ASC, 1) && !mngr.stk[1]->lst)
		return (0);
	draw_stacks(&mngr);
	gen_commands(&mngr);
	if (mngr.dbg)
		ft_printf("Total operations = %d\n", mngr.n_cmd);
	return ((check_sort(mngr.stk[0], ASC, 1) && !mngr.stk[1]->lst) ? 0 :
			SORT_FAILED);
}

#else

int	main(int ac, char **av)
{
	t_mngr	mngr;

	ft_bzero(&mngr, sizeof(mngr));
	if (ac == 1)
		checker_error(NULL, NO_ARG);
	else
		parse_args(ac, av, &mngr);
	mngr.s_arr = ft_avlfree(mngr.s_arr);
	if (check_sort(mngr.stk[0], ASC, 1) && !mngr.stk[1]->lst)
		return (0);
	draw_stacks(&mngr, INIT);
	gen_commands(&mngr);
	if (mngr.dbg)
		ft_printf("Total operations = %d\n", mngr.n_cmd);
	return ((check_sort(mngr.stk[0], ASC, 1) && !mngr.stk[1]->lst) ? 0 :
	SORT_FAILED);
}

#endif
