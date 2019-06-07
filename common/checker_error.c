/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:52:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/06/07 20:11:22 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	help(void)
{
	ft_printf("Usage:\n./pushswap [-(file|debug|vis|color|bubble)]"
"('number_to_be_sorted')|(numbers to be sorted)\n"
"every flag should be given separately\n"
"-file should be the last one just before file name\n");
}

/*
** @param stk - main t_stk which will be cleaned before exit or NULL
** @param err - number of error from e_errors enum
** Prints error message to stderror, clean up and exit the program
*/

#ifdef HIDDEN

void	pushswap_exit(t_mngr *mngr, int err)
{
	if (err != HELP_CALL && err != SUCCESS)
		ft_fdprintf(STDERR_FILENO, "Error\n");
	else if (err == HELP_CALL)
		help();
	if (err == NO_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", NO_ARG_MSG);
	else if (err == WRONG_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", STR_ARG_MSG);
	else if (err == INT_OVERFLOW_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", INT_OVERFLOW_MSG);
	else if (err == DUPLICTATE_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", DUP_ARG_MSG);
	else if (err == FILE_ERROR_C || err == FILE_ERROR_N)
		ft_fdprintf(STDERR_FILENO, "%s\n", err == FILE_ERROR_C ?
		FILE_ERROR_C_MSG : FILE_ERROR_N_MSG);
	ft_vecdel((void**)&mngr->vec);
	clean_all(mngr, err);
	exit(err);
}

#else

void	pushswap_exit(t_mngr *mngr, int err)
{
	if (err != HELP_CALL && err != SUCCESS)
		ft_fdprintf(STDERR_FILENO, "Error\n");
	else if (err == HELP_CALL)
		help();
	if (err == NO_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", NO_ARG_MSG);
	else if (err == WRONG_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", STR_ARG_MSG);
	else if (err == INT_OVERFLOW_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", INT_OVERFLOW_MSG);
	else if (err == DUPLICTATE_ARG)
		ft_fdprintf(STDERR_FILENO, "%s\n", DUP_ARG_MSG);
	else if (err == FILE_ERROR_C || err == FILE_ERROR_N)
		ft_fdprintf(STDERR_FILENO, "%s\n", err == FILE_ERROR_C ?
		FILE_ERROR_C_MSG : FILE_ERROR_N_MSG);
	clean_all(mngr, err);
}

#endif
