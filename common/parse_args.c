/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <ehugh-be@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:22:11 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/06/07 17:19:59 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

void	init_stacks(t_mngr *mngr)
{
	if (!(mngr->stk[0] = malloc(sizeof(t_stk))))
		pushswap_exit(mngr, MEMORY_ALLOC_FAIL);
	ft_bzero(mngr->stk[0], sizeof(t_stk));
	if (!(mngr->stk[1] = malloc(sizeof(t_stk))))
		pushswap_exit(mngr, MEMORY_ALLOC_FAIL);
	ft_bzero(mngr->stk[1], sizeof(t_stk));
	mngr->stk[0]->min = INT_MAX;
	mngr->stk[0]->max = INT_MIN;
	mngr->stk[1]->min = INT_MAX;
	mngr->stk[1]->max = INT_MIN;
}

int		read_flags(int ac, char **av, t_mngr *mngr, int *fd)
{
	char	*arg;
	int		i;

	i = 1;
	while (i < ac)
	{
		arg = av[i];
		if (*arg == '-')
			i += set_flags(arg, fd, av + i, mngr);
		else
			return (--i);
	}
	return (i);
}

static void two_arg_handle(t_mngr *mngr, char **av, int fd, int skip)
{
	char	*str;
	char 	**arr;
	int i;

	if (fd > 0)
	{
		get_next_line(fd, &str);
		close(fd);
	}
	else
		str = av[1 + skip];
	arr = ft_strsplit(str, ' ');
	parse_nums(mngr, 0, arr, 0);
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	if (fd > 0)
		free(str);
}

void	parse_args(int ac, char **av, t_mngr *mngr)
{
	int		fd;
	int		skip;

	init_stacks(mngr);
	fd = -2;
	skip = 0;
	if (av[1][0] == '-')
		skip = read_flags(ac, av, mngr, &fd);
	if (mngr->fd == -1 || fd == -1)
		pushswap_exit(mngr, fd == -1 ? FILE_ERROR_N : FILE_ERROR_C);
	if (ac - skip == 2 || ac - skip == 0)
		two_arg_handle(mngr, av, fd, skip);
	else if (fd == -2 && (mngr->fd < 2 && mngr->fd > -1))
		parse_nums(mngr, ac, av, skip);
	else
		pushswap_exit(mngr, WRONG_ARG);
}
