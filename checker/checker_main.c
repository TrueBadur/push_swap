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

#include "libft.h"
#include "checker.h"

t_list	*printlist(t_list *lst)
{
	ft_printf("%d\n", *((int*)lst->content));
	return (lst);
}

int main(int ac, char **av)
{
	t_stk	*stk;

	if (ac == 1)
		checker_error(NULL, NO_ARG);
	else
		stk = parse_args(ac, av);
	ft_lstmap(stk->a, printlist);
	parse_commands(stk);
//	if (check_sort(stk))
//		ft_printf("OK\n");
//	else
//		ft_printf("KO\n");
	return (0);
}

