/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 05:30:53 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/05 05:30:53 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		split_stack_inssort(t_mngr *mngr)
{
	while (!check_sort(mngr->stk[0], ASC, 0) && mngr->stk[0]->lst_s > 3)
		push(mngr, PSH_B);
	if (!check_sort(mngr->stk[0], ASC, 0))
		swap(mngr, SWP_A);
}

t_vector	*get_ops_seq(t_stk *stk_c, int num, t_vector *vec)
{
	int t;
	int i;
	int col_cn;
	int l;

	col_cn = 1;
	i = val_to_place_dir_nexis(stk_c, num);
	while (i)
	{
		l = col_cn * sizeof(int) > vec->len ? 0 : 
				(int)((char*)vec->data)[vec->len - sizeof(int) * col_cn];
		if (l == ((i < 0) ? RROT_B : ROT_B))
		{
			ft_vecremove(vec, vec->len - sizeof(int) * col_cn++, sizeof(int));
			t = (i < 0) ? RROT_R : ROT_R;
		}
		else
			t = (i < 0) ? RROT_A : ROT_A;
		ft_vecpush(vec, &t, sizeof(int));
		i += i < 0 ? 1 : -1;
	}
	t = PSH_A;
	ft_vecpush(vec, &t, sizeof(int));
	return (vec);
}

/*
 * sets sequence of commands in vector vec to get ith element (0 is top most
 * element, 1 is the second from top,
 * 2 - first from bottom and then alternate top and bottom) of stack
 * and returns value of this element
 */

int			get_stk_n(t_stk *stk, t_vector **vec, int i)
{
	int		n;
	t_list	*lst;

	if (i == 0)
		return ((int)stk->lst->data);
	lst = stk->lst;
	if (i % 2 == 1)
	{
		i = i / 2 + 1;
		while (i-- && lst->next && (lst = lst->next))
			ft_vecpush_small(*vec, ROT_B, sizeof(int));
	}
	else
	{
		n = stk->lst_s - (i / 2);
		while (n-- && lst->next)
			lst = lst->next;
		i = i / 2;
		while (i--)
			ft_vecpush_small(*vec, RROT_B, sizeof(int));
	}
	return ((int)lst->data);
}

void	 find_shortest(t_mngr *mngr, t_vector **vec, int i)
{
	t_vector *vec_t;
	unsigned count;
	int tmp;

	count = INT_MAX;
	while (1)
	{
		vec_t = ft_vecinit(sizeof(int));
		tmp = get_stk_n(mngr->stk[1], &vec_t, i++);
		if (vec_t->len / sizeof(int) >= count)
			break ;
		vec_t = get_ops_seq(mngr->stk[0], tmp, vec_t);
		if (vec_t->len / sizeof(int) < count)
		{
			count = vec_t->len / sizeof(int);
			if (*vec)
				ft_vecdel((void**)vec);
			*vec = vec_t;
		}
		else
			ft_vecdel((void **)&vec_t);
	}
	ft_vecdel((void **)&vec_t);
}

void eval_seq(t_vector *vec, t_mngr *mngr)
{
	int			*tmp;
	unsigned	i;

	tmp = (int*)vec->data;
	i = 0;
	while (i < vec->len / sizeof(int))
	{
		if (tmp[i] < PSH_A)
			swap(mngr, tmp[i]);
		else if (tmp[i] < ROT_A)
			push(mngr, tmp[i]);
		else
			rotate(mngr, tmp[i]);
		i++;
	}
}
