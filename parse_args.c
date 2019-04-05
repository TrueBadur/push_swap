/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:22:11 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/01 19:22:11 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker/checker.h"
#include <limits.h>

static t_list *ins_to_stk(t_stk *stk, char *str, char mode, t_mngr *mngr)
{
	int		tmp;
	char	err;
	t_list	*lst;

	if ((err = ft_atoi_safe(str, &tmp)))
		checker_error(mngr, err < 0 ? INT_OVERFLOW_ARG : STR_ARG);
	lst = stk->lst;
	while (lst)
		if ((int) lst->content == tmp || (int)(lst = lst->next) * 0)
			checker_error(mngr, DUPLICTATE_ARG);
	stk->lst_size++;
	if (mode)
	{
		ft_lstaddlast(&stk->l_e, ft_lstnew(&tmp, sizeof(int)));
		stk->lst = (stk->lst_size == 1) ? stk->l_e : stk->lst;
		stk->l_e = (stk->lst_size > 1) ? stk->l_e->next : stk->l_e;
	}
	else
	{
		ft_lstadd(&stk->lst, ft_lstnew(&tmp, sizeof(int)));
		stk->l_e = (stk->lst_size == 1) ? stk->lst : stk->l_e;
	}
	return (stk->lst);
}

static void	parse_nums(t_mngr *mngr, int ac, char **av)
{
	mngr->stk[0]->lst = NULL;
	if (ac == 0)
	{
		while (*av)
			if (!(mngr->stk[0]->lst = ins_to_stk(mngr->stk[0], *(av++), 1, mngr)))
				checker_error(mngr, MEMORY_ALLOC_FAIL);
	}
	else
		while (ac-- > 1)
			if (!(mngr->stk[0]->lst = ins_to_stk(mngr->stk[0], av[ac], 0, mngr)))
				checker_error(mngr, MEMORY_ALLOC_FAIL);
}

void *parse_args(int ac, char **av, t_mngr *mngr)
{
	t_stk	*stk;

	if (!(stk = malloc(sizeof(t_stk))))
		checker_error(mngr, MEMORY_ALLOC_FAIL);
	ft_bzero(stk, sizeof(t_stk));
	if (!(mngr->stk[1] = malloc(sizeof(t_stk))))
		checker_error(mngr, INTERNAL_ERROR);
	ft_bzero(mngr->stk[1], sizeof(t_mngr));
	mngr->stk[0] = stk;
	if (ac == 2)
	{
		av = ft_strsplit(av[1], ' ');
		ac = 0;
		parse_nums(mngr, ac, av);
	}
	else
		parse_nums(mngr, ac, av);
}
