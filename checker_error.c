/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:52:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/01 17:52:59 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 *
 * @param stk - main t_stk which will be cleaned before exit or NULL
 * @param err - number of error from e_errors enum
 *
 * Prints error message to stderror, cleans up and exit the program
 */

void checker_error(t_mngr *mngr, int err)
{
	//TODO make cleanup
	ft_fdprintf(STDERR_FILENO, "Error\n");
	if (err == NO_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", NO_ARG_MSG);
	else if (err == STR_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", STR_ARG_MSG);
	else if (err == INT_OVERFLOW_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", INT_OVERFLOW_MSG);
	else if (err == DUPLICTATE_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", DUP_ARG_MSG);
//	if (stk)
//		cleanup(stk);
	exit(err);
}
