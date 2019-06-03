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

void  split_stack_opt(t_mngr *mngr)
{
	while (!check_sort(mngr->stk[0], ASC, 0) && mngr->stk[0]->lst_s > 3)
		ft_printf("pb\n", mngr->dbg *= cmd_push(mngr, "b"));
	if (!check_sort(mngr->stk[0], ASC, 0))
		ft_printf("sa\n", cmd_swap(mngr, "a"));
}

t_vector *get_ops_seq(t_stk *stk_c, int num, t_vector *vec)
{
	int t;
	int i;
	int col_cn;

	col_cn = 1;
	i = val_to_place_dir_nexis(stk_c, num);
	while (i)
	{
//		collapse_seq(vec);
		int l = col_cn * sizeof(int) > vec->len ? 0 : (int)((char*)vec->data)[vec->len - sizeof(int) * col_cn];
		if (l == ((i < 0) ? RROT_B : ROT_B))
//			if (((int*)vec->data)[vec->len - sizeof(int) * col_cn] == (i < 0) ? RROT_B : ROT_B)
		{
			ft_vecremove(vec, vec->len - sizeof(int) * col_cn, sizeof(int));
			col_cn++;
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
 * sets sequence of commands in vector vec to get ith element (0 is top most element, 1 is the second
 * from top, 2 - first from bottom and then alternate top and bottom) of stack
 * and returns value of this element
 */

int get_stk_n(t_stk *stk, t_vector **vec, int i)
{
	int t;
	int n;
	t_list *lst;

	if (i == 0)
		return ((int)stk->lst->data);
	else
	{
		if (i % 2 == 1)
		{
			i = i / 2 + 1;
			lst = stk->lst;
			while (i-- && lst->next)
			{
				lst = lst->next;
				t = ROT_B;
				ft_vecpush(*vec, &t, sizeof(t));
			}
		}
		else
		{
			n = stk->lst_s - (i / 2);
			lst = stk->lst;
			while (n-- && lst->next)
				lst = lst->next;
			i = i / 2;
			while (i--)
			{
				t = RROT_B;
				ft_vecpush(*vec, &t, sizeof(t));
			}
		}
	}
	return ((int)lst->data);
}

t_vector *find_shortest(t_mngr *mngr)
{
	t_vector *vec;
	t_vector *vec_t;
	unsigned count;
	int i;
	int tmp;

	count = INT_MAX;
	i = 0;
	vec = NULL;
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
			if (vec)
				ft_vecdel(&vec);
			vec = vec_t;
		}
		else
			ft_vecdel((void **)&vec_t);
	}
	ft_vecdel((void **)&vec_t);
	return vec;
}

void eval_seq(t_vector *vec, t_mngr *mngr)
{
	int *tmp;
	unsigned i;

	tmp = (int*)vec->data;
	i = 0;
	while (i < vec->len / sizeof(int))
	{
		if (tmp[i] < PSH_A)
		{
			if (tmp[i] == SWP_S)
				cmd_swap(mngr, "r");
			else
				cmd_swap(mngr, tmp[i] == SWP_A ? "a" : "b");
		}
		else if (tmp[i] < ROT_A)
			cmd_push(mngr, tmp[i] == PSH_A ? "a" : "b");
		else if (tmp[i] < RROT_A)
		{
			if (tmp[i] == ROT_R)
				cmd_rotate(mngr, "r", 0);
			else
				cmd_rotate(mngr, tmp[i] == ROT_A ? "a" : "b", 0);
		}
		else
		{
			if (tmp[i] == RROT_R)
				cmd_rotate(mngr, "rr", 0);
			else
				cmd_rotate(mngr, tmp[i] == RROT_A ? "ra" : "rb", 0);
		}
		i++;
	}
}

void insert_sort(t_mngr *mngr)
{
	t_vector *vec;

	while(mngr->stk[1]->lst_s)
	{
		vec = find_shortest(mngr);
		// check if seq may be simplified
		eval_seq(vec, mngr);
		ft_vecdel((void**)&vec);
	}
	int i = val_to_place_dir_exist(mngr->stk[0], mngr->stk[0]->min, 0);
	while (i)
	{
		safe_rotate(mngr, 'r');
		safe_rotate(mngr, '\0');
		i += i < 0 ? 1 : -1;
	}
}

void gen_commands(t_mngr *mngr)
{
	split_stack_opt(mngr);
	insert_sort(mngr);
//	double_bouble(mngr);
}