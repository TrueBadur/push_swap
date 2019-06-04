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

#include "push_swap.h"
#include <limits.h>

static t_list *instostk(t_stk *stk, char *str, char mode, t_mngr *mngr)
{
	int		tmp;
	char	err;

	if ((err = ft_atoi_safe(str, &tmp)))
		checker_error(mngr, err < 0 ? INT_OVERFLOW_ARG : STR_ARG);
	if ((t_btavl*)ft_avlsearch(mngr->s_arr, tmp, 0))
		checker_error(mngr, DUPLICTATE_ARG);
	stk->lst_s++;
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
	t_btavl *t = ft_avlnew(0, mode ? (int)stk->l_e->data :
	(int)stk->lst->data, 0);
	mngr->s_arr = ft_avlins(mngr->s_arr, t);
	return (stk->lst);
}

static void	parse_nums(t_mngr *mngr, int ac, char **a)
{
	mngr->stk[0]->lst = NULL;
	if (ac == 0)
	{
		while (*a)
			if (!(mngr->stk[0]->lst = instostk(mngr->stk[0], *(a++), 1, mngr)))
				checker_error(mngr, MEMORY_ALLOC_FAIL);
	}
	else
		while (ac-- > 1)
			if (!(mngr->stk[0]->lst = instostk(mngr->stk[0], a[ac], 0, mngr)))
				checker_error(mngr, MEMORY_ALLOC_FAIL);
}

void init_stacks(t_mngr *mngr)
{
	if (!(mngr->stk[0] = malloc(sizeof(t_stk))))
		checker_error(mngr, MEMORY_ALLOC_FAIL);
	ft_bzero(mngr->stk[0], sizeof(t_stk));
	if (!(mngr->stk[1] = malloc(sizeof(t_stk))))
		checker_error(mngr, MEMORY_ALLOC_FAIL);
	ft_bzero(mngr->stk[1], sizeof(t_stk));
}

int set_flags(int ac, char **av, t_mngr *mngr)
{
	char *arg;
	int i;
	int fd;

	i = 0;
	fd = -1;
	while (++i < ac)
	{
		arg = av[i];
		if (*arg == '-')
		{
			if (ft_strcmp(arg + 1, "help") || *(arg + 1) == 'h')
				checker_error(mngr, HELP_CALL);
			if (ft_strcmp(arg + 1, "file") || *(arg + 1) == 'f')
				fd = open(av[1], O_RDONLY);
			if (ft_strcmp(arg + 1, "debug") || *(arg + 1) == 'd')
				mngr->dbg = 1;
			if (ft_strcmp(arg + 1, "vis") || *(arg + 1) == 'v')
				mngr->viz = 1;
			if (ft_strcmp(arg + 1, "bubble") || *(arg + 1) == 'b')
				mngr->bub = 1;
		}
	}
	return (fd);
}

void parse_args(int ac, char **av, t_mngr *mngr)
{
	int 	fd;
	char	*str;

	init_stacks(mngr);
	fd = 0;
	if (av[1][0] == '-')
		fd = set_flags(ac, av, mngr);
	if (ac == 2)
	{
		if (fd > 0 )
		{
			get_next_line(fd, &str);
			close(fd);
		}
		else
			str = av[1];
		str = (char*)ft_strsplit(str, ' ');
		ac = 0;
		parse_nums(mngr, ac, (char**)str);
	}
	else
		parse_nums(mngr, ac, av);
}
