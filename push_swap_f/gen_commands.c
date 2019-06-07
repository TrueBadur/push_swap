/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 05:48:48 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/05 05:48:48 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	insert_sort(t_mngr *mngr)
{
	t_vector	*vec;
	int			i;

	vec = NULL;
	while (mngr->stk[1]->lst_s)
	{
		find_shortest(mngr, &vec, 0);
		eval_seq(vec, mngr);
		ft_vecdel((void**)&vec);
	}
	i = val_to_place_dir_exist(mngr->stk[0], mngr->stk[0]->min, 0);
	while (i)
	{
		rotate(mngr, i > 0 ? ROT_A : RROT_A);
		i += i < 0 ? 1 : -1;
	}
}

#ifdef HIDDEN

void	gen_commands(t_mngr *mngr)
{
	if (mngr->bub == 0)
	{
		split_stack_inssort(mngr);
		insert_sort(mngr);
	}
	else if (mngr->bub == 1)
		double_bouble(mngr);
	else
		bin_merge(mngr);
}

#else

void	gen_commands(t_mngr *mngr)
{
	split_stack_inssort(mngr);
	insert_sort(mngr);
}

#endif
