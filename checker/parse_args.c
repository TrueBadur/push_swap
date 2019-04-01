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

#include "checker.h"
#include <limits.h>

static void ins_to_stk(t_stk *stk, char *str, char mode)
{
	int		tmp;
	char	err;

	if ((err = ft_atoi_safe(str, &tmp)))
		checker_error(stk, err < 0 ? INT_OVERFLOW_ARG : STR_ARG);
	if (mode)
		ft_lstaddlast(&stk->a, ft_lstnew(&tmp, sizeof(int)));
	else
		ft_lstadd(&stk->a, ft_lstnew(&tmp, sizeof(int)));
}

static void	parse_nums(t_stk *stk, int ac, char **av)
{
	stk->a = NULL;
	stk->b = NULL;
	if (ac == 0)
		while (*av)
			ins_to_stk(stk, *(av++), 1);
	else
		while (ac-- > 1)
			ins_to_stk(stk, av[ac], 0);
}

t_stk		*parse_args(int ac, char **av)
{
	t_stk	*stk;

	stk = malloc(sizeof(t_stk));
	if (ac == 2)
	{
		av = ft_strsplit(av[1], ' ');
		ac = 0;
		parse_nums(stk, ac, av);
	}
	else
		parse_nums(stk, ac, av);
	stk->a_end = ft_lstfindlast(stk->a);
	return (stk);
}
