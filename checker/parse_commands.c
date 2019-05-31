/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:09:28 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/01 22:09:28 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


void	parse_commands(t_mngr *mngr)
{
	while (get_next_line(STDIN_FILENO, &mngr->l_cmd))
	{
		if (!mngr->l_cmd)
			continue ;
		if (*mngr->l_cmd == 's')
			mngr->dbg *= cmd_swap(mngr, mngr->l_cmd + 1);
		else if (*mngr->l_cmd == 'p')
			mngr->dbg *= cmd_push(mngr, mngr->l_cmd + 1);
		else if (*mngr->l_cmd == 'r')
			mngr->dbg *= cmd_rotate(mngr, mngr->l_cmd + 1, 0);
		else if (*mngr->l_cmd == '\0')
			return ;
		else
			checker_error(mngr, NOT_EXIST_INSTR);
		if (mngr->dbg)
			draw_stacks(mngr);
	}
}
