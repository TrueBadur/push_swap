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
	t_list *i;

	while (!check_sort(mngr->stk[0], ASC, 0) && mngr->stk[0]->lst_s > 3)
		ft_printf("pb\n", mngr->dbg *= cmd_push(mngr, "b"));
	if (!check_sort(mngr->stk[0], ASC, 0))
		ft_printf("sa\n", cmd_swap(mngr, "a"));
}

t_stk *stk_copy(t_stk *stk)
{
	t_stk *stk_c;
	t_list *tmp;

	if (!(stk_c = malloc(sizeof(t_stk))))
		return NULL;
	ft_memcpy(stk_c, stk, sizeof(t_stk));
	stk_c->lst = ft_lstcopy(stk->lst);
	tmp = stk_c->lst;
	while (tmp->next)
		tmp = tmp->next;
	stk_c->l_e = tmp;
	return (stk_c);
}

void stk_del(t_stk *stk)
{
	ft_lstdel(&stk->lst, NULL);
	free(stk);
}

t_vector *get_ops_seq(t_stk *stk_c, int num, t_mngr *mngr, t_vector *vec)
{
	int t;
	int i;
	int col_cn;

	col_cn = 1;
	if (num > stk_c->max || num < stk_c->min)
	{
		i = val_to_place_dir_exist(stk_c, stk_c->min, 0);
		while (i)
		{
			int l = (int)((char*)vec->data)[vec->len - sizeof(int) * col_cn];
			if (l == ((i < 0) ? RROT_B : ROT_B))
//			if (((int*)vec->data)[vec->len - sizeof(int) * col_cn] == (i < 0) ? RROT_B : ROT_B)
			{
				col_cn++;
				ft_vecremove(vec, vec->len - sizeof(int), sizeof(int));
				t = (i < 0) ? RROT_R : ROT_R;
			}
			else
				t = (i < 0) ? RROT_A : ROT_A;
			ft_vecpush(vec, &t, sizeof(int));
			i += i < 0 ? 1 : -1;
		}
		t = PSH_A;
		ft_vecpush(vec, &t, sizeof(int));
	}
	else
	{
		i = val_to_place_dir_nexis(stk_c, num);
		while (i)
		{
			if ((num < (int) stk_c->lst->data &&
				 num > (int) stk_c->l_e->data) ||
				(num > stk_c->max && (int) stk_c->lst->data == stk_c->min) ||
				(num < stk_c->min && (int) stk_c->l_e->data == stk_c->max)) //todo remove redundant ifs
			{
				t = PSH_A;
				ft_vecpush(vec, &t, sizeof(int));
				break;
			}
			else
			{
				int l = (int)((char*)vec->data)[vec->len - sizeof(int) * col_cn];
				if (l == (i > 0 ? ROT_B : RROT_B))
//			if (((int*)vec->data)[vec->len - sizeof(int) * col_cn] == (i < 0) ? RROT_B : ROT_B)
				{
					col_cn++;
					ft_vecremove(vec, vec->len - sizeof(int), sizeof(int));
					t = i > 0 ? ROT_R : RROT_R;
				}
				else
					t = i > 0 ? ROT_A : RROT_A;
				stk_c = i > 0 ? rot_f(stk_c, mngr) : rot_r(stk_c, mngr);
				ft_vecpush(vec, &t, sizeof(int));
			}
		}
		stk_del(stk_c);
	}
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
	//starting from first el in b stack then second then last, then third,
	// then prelast and so on. count how many moves it is needed to place this el
	// in place in a stack, get the shortest
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
		vec_t = get_ops_seq(stk_copy(mngr->stk[0]), tmp, mngr, vec_t);
		if (vec_t->len / sizeof(int) < count)
		{
			count = vec_t->len / sizeof(int);
			if (vec)
				ft_vecdel(&vec);
			vec = vec_t;
		}
//		else if (vec_t->len / sizeof(int) == count)
//		{
//			//run find_shortest (or some equivalent) on copy of the current mngr
//			// with evaluated seq to find out which one is more effective
//		}
		else
			ft_vecdel((void **)&vec_t);
	}
	//todo remove vec_t
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

void collapse_seq(t_vector *seq)
{
	int len;
	int i;
	int *iseq;

	len = seq->len / 4;
	i = 0;
	iseq = (int*)seq->data;
	ft_printf("Sequence is:\n");
	while (i < len)
	{
		ft_printf("--%d++ ", iseq[i]);
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
		collapse_seq(vec);
		eval_seq(vec, mngr);
		ft_vecdel((void**)&vec);
	}
}

void select_opt(t_mngr *mngr)
{
	split_stack_opt(mngr);
	insert_sort(mngr);

}

void gen_commands(t_mngr *mngr)
{
	//check for size to choose algo
//	bin_merge(mngr);
//	double_bouble(mngr);
	select_opt(mngr);
}