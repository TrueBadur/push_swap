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



void init_stacks(t_mngr *mngr)
{
	if (!(mngr->stk[0] = malloc(sizeof(t_stk))))
		checker_error(mngr, MEMORY_ALLOC_FAIL);
	ft_bzero(mngr->stk[0], sizeof(t_stk));
	if (!(mngr->stk[1] = malloc(sizeof(t_stk))))
		checker_error(mngr, MEMORY_ALLOC_FAIL);
	ft_bzero(mngr->stk[1], sizeof(t_stk));
	mngr->stk[0]->min = INT_MAX;
	mngr->stk[0]->max = INT_MIN;
	mngr->stk[1]->min = INT_MAX;
	mngr->stk[1]->max = INT_MIN;
}

int set_flags(int ac, char **av, t_mngr *mngr, int *fd)
{
	char *arg;
	int i;

	i = 0;
	while (++i < ac)
	{
		arg = av[i];
		if (*arg == '-')
		{
			if (ft_strcmp(arg + 1, "help") == 0 || *(arg + 1) == 'h')
				checker_error(mngr, HELP_CALL);
			else if (ft_strcmp(arg + 1, "file") == 0 || *(arg + 1) == 'f')
				*fd = open(av[i + 1], O_RDONLY);
			else if (ft_strcmp(arg + 1, "debug") == 0 || *(arg + 1) == 'd')
				mngr->dbg = 1;
			else if (ft_strcmp(arg + 1, "vis") == 0 || *(arg + 1) == 'v')
				mngr->viz = 1;
			else if (ft_strcmp(arg + 1, "bubble") == 0 || *(arg + 1) == 'b')
				mngr->bub = 1;
		}
		else
			return (--i);
	}
	return (--i);
}

void parse_args(int ac, char **av, t_mngr *mngr)
{
	int 	fd;
	int		skip;
	char	*str;

	init_stacks(mngr);
	fd = -1;
	skip = 0;
	if (av[1][0] == '-')
		skip = set_flags(ac, av, mngr, &fd);
	if (ac - skip == 2)
	{
		if (fd > 0 )
		{
			get_next_line(fd, &str);
			close(fd);
		}
		else
			str = av[1 + skip];
		str = (char*)ft_strsplit(str, ' ');
		ac = 0;
		parse_nums(mngr, ac, (char**)str, 0);
	}
	else
		parse_nums(mngr, ac, av, skip);
}
