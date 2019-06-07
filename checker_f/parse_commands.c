/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:09:28 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/06/07 20:05:52 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_eops	str_to_op(const char *str)
{
	int ret;

	ret = 0;
	if (*(str) == 'p')
		return (*(str + 1) == 'a' ? PSH_A : PSH_B);
	else if (*(str) == 's')
		ret += SWP_A;
	else if (*(str) == 'r')
		if (*(str + 2) && *(str + 1) == 'r')
			ret += RROT_A;
		else
			ret += ROT_A;
	else
		return (0);
	str += *(str + 2) && *(str + 1) == 'r' ? 2 : 1;
	if (*str == 'r' || *str == 's')
		ret += 2;
	else
		ret += *str == 'a' ? 0 : 1;
	return (ret);
}

int		parse_command(t_mngr *mngr)
{
	int cmd;

	if (!get_next_line(mngr->fd, &mngr->l_cmd))
		return (0);
	if (!mngr->l_cmd)
		return (-1);
	if (*mngr->l_cmd == 's')
		cmd_swap(mngr, mngr->l_cmd + 1);
	else if (*mngr->l_cmd == 'p')
		cmd_push(mngr, mngr->l_cmd + 1);
	else if (*mngr->l_cmd == 'r')
		cmd_rotate(mngr, mngr->l_cmd + 1, 0);
	else if (*mngr->l_cmd == '\0')
		return (0);
	else
		pushswap_exit(mngr, WRONG_INSTR);
	cmd = str_to_op(mngr->l_cmd);
	if (mngr->dbg)
		draw_stacks(mngr, cmd);
	free(mngr->l_cmd);
	mngr->l_cmd = NULL;
	return (cmd);
}
