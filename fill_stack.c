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

#ifdef HIDDEN

int		set_flags(char *arg, int *fd, char **av, t_mngr *mngr)
{
	int ret;

	ret = 1;
	if (ft_strcmp(arg + 1, "help") == 0 || *(arg + 1) == 'h')
		pushswap_exit(mngr, HELP_CALL);
	else if (ft_strcmp(arg + 1, "file") == 0 || *(arg + 1) == 'f')
	{
		*fd = open(*(av + 1), O_RDONLY);
		ret++;
	}
	else if (ft_strcmp(arg + 1, "sfile") == 0 || *(arg + 1) == 's')
	{
		mngr->fd = open(*(av + 1), mngr->tp == 'c' ? O_RDONLY : WRITE, CHMOD);
		ret++;
	}
	else if (ft_strcmp(arg + 1, "debug") == 0 || *(arg + 1) == 'd')
		mngr->dbg = 1;
	else if (ft_strcmp(arg + 1, "result") == 0 || *(arg + 1) == 'r')
		mngr->dbg = -1;
	else if (ft_strcmp(arg + 1, "viz") == 0 || *(arg + 1) == 'v')
		mngr->viz = 1;
	else if (*(arg + 1) == 'b' || *(arg + 1) == 'm')
		mngr->bub = *(arg + 1) == 'b' ? 1 : 2;
	return (ret);
}

#else

int		set_flags(char *arg, int *fd, char **av, t_mngr *mngr)
{
	int ret;

	ret = 1;
	if (ft_strcmp(arg + 1, "help") == 0 || *(arg + 1) == 'h')
		pushswap_exit(mngr, HELP_CALL);
	else if (ft_strcmp(arg + 1, "file") == 0 || *(arg + 1) == 'f')
	{
		*fd = open(*(av + 1), O_RDONLY);
		ret++;
	}
	else if (ft_strcmp(arg + 1, "sfile") == 0 || *(arg + 1) == 's')
	{
		mngr->fd = open(*(av + 1), mngr->tp == 'c' ? O_RDONLY : WRITE, CHMOD);
		ret++;
	}
	else if (ft_strcmp(arg + 1, "debug") == 0 || *(arg + 1) == 'd')
		mngr->dbg = 1;
	else if (ft_strcmp(arg + 1, "result") == 0 || *(arg + 1) == 'r')
		mngr->dbg = -1;
	else if (ft_strcmp(arg + 1, "viz") == 0 || *(arg + 1) == 'v')
		mngr->viz = mngr->tp == 'c' ? 1 : 0;
	return (ret);
}

#endif

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
		pushswap_exit(mngr, err < 0 ? INT_OVERFLOW_ARG : STR_ARG);
	if ((t_btavl*)ft_avlsearch(mngr->s_arr, tmp, 0))
		pushswap_exit(mngr, DUPLICTATE_ARG);
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
				pushswap_exit(mngr, MEMORY_ALLOC_FAIL);
	}
	else
		while (ac-- > 1 + skip)
			if (!(mngr->stk[0]->lst = instostk(mngr->stk[0], a[ac], 0, mngr)))
				pushswap_exit(mngr, MEMORY_ALLOC_FAIL);
}
