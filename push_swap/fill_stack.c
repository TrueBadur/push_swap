/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:22:11 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/01 19:22:11 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

static void		set_min_max(t_stk *stk, int val)
{
	stk->min = val < stk->min ? val : stk->min;
	stk->max = val > stk->max ? val : stk->max;
}

static t_list	*instostk(t_stk *stk, char *str, char mode, t_mngr *mngr)
{
	int		tmp;
	char	err;
	t_btavl	*t;

	if ((err = ft_atoi_safe(str, &tmp)))
		checker_error(mngr, err < 0 ? INT_OVERFLOW_ARG : STR_ARG);
	if ((t_btavl*)ft_avlsearch(mngr->s_arr, tmp, 0))
		checker_error(mngr, DUPLICTATE_ARG);
	stk->lst_s++;
	set_min_max(stk, tmp);
	if (mode)
	{
		ft_lstaddlast(&stk->l_e, ft_lstnew(&tmp, sizeof(int)));
		stk->lst = (stk->lst_s == 1) ? stk->l_e : stk->lst;
		stk->l_e = (stk->lst_s > 1) ? stk->l_e->next : stk->l_e;
	}
	else
	{
		ft_lstadd(&stk->lst, ft_lstnew(&tmp, sizeof(int)));
		stk->l_e = (stk->lst_s == 1) ? stk->lst : stk->l_e;
	}
	t = ft_avlnew(0, mode ? (int)stk->l_e->data :
	(int)stk->lst->data, 0);
	mngr->s_arr = ft_avlins(mngr->s_arr, t);
	return (stk->lst);
}

void			parse_nums(t_mngr *mngr, int ac, char **a, int skip)
{
	mngr->stk[0]->lst = NULL;
	if (ac == 0)
	{
		while (*a)
			if (!(mngr->stk[0]->lst = instostk(mngr->stk[0], *(a++), 1, mngr)))
				checker_error(mngr, MEMORY_ALLOC_FAIL);
	}
	else
		while (ac-- > 1 + skip)
			if (!(mngr->stk[0]->lst = instostk(mngr->stk[0], a[ac], 0, mngr)))
				checker_error(mngr, MEMORY_ALLOC_FAIL);
}
