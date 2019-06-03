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



int main(int ac, char **av)
{
	t_mngr	mngr;

	ft_bzero(&mngr, sizeof(mngr));
	if (ac == 1)
		checker_error(NULL, NO_ARG);
	else
		parse_args(ac, av, &mngr); //TODO parse - arguments
	mngr.vec = ft_vecinit(mngr.stk[0]->lst_s);
	ft_avltovec(mngr.s_arr, mngr.vec);
	mngr.s_arr = ft_avlfree(mngr.s_arr);
	if (check_sort(mngr.stk[0], ASC, 1) && !mngr.stk[1]->lst)
		return (0);
	set_sort(mngr.stk[0], ASC, mngr.stk[0]->max);
	mngr.stk[0]->piv = ((int*)(mngr.vec->data))[(mngr.stk[0]->lst_s - 1) / 2];
	mngr.stk[0]->max = ((int*)(mngr.vec->data))[mngr.stk[0]->lst_s - 1];
	mngr.stk[0]->min = ((int*)(mngr.vec->data))[0];
	mngr.dbg = 1;
	mngr.col = 1;
	mngr.n_cmd = 0;
	draw_stacks(&mngr);
	gen_commands(&mngr);
	ft_printf("Total operations = %d\n", mngr.n_cmd);
	return (check_sort(mngr.stk[0], ASC, 1) && !mngr.stk[1]->lst);
}

