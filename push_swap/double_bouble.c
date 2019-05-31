/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_bouble.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:01:50 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/08 22:01:50 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void 	find_seq_stack(t_mngr *mngr, t_stk *stk, int dir)
{
	t_list *lst;
	int 	size;
	int		i;
	int		f;
	int 	j;

	lst = stk->lst;
	if (!lst || !lst->next)
		return ;
	size = 1;
	f = 0;
	j = 0;
	i = ft_vecbinsearch_int(mngr->vec, (int)lst->data);
	while(f != stk->lst_s + 1 && stk->lst_s != stk->sq_l)
	{
		int t = f == 1 ? (int)stk->lst->data : (int)lst->next->data;
		int t2 = ((int*)mngr->vec->data)[i + dir];
		if (t == ((int*)mngr->vec->data)[i + dir] && size++)
		{
			if (dir > 0)
				i = i == mngr->vec->len / 4 - 2 ? ft_vecbinsearch_int(mngr->vec, stk->min) - 1 : i + 1;
			else
				i = i == 1 ? ft_vecbinsearch_int(mngr->vec, stk->max) + 1 : i - 1;
			stk->piv = size > stk->sq_l ? t : stk->piv;
		}
		else if (!f && (size = 1))
			i = ft_vecbinsearch_int(mngr->vec, (int)lst->next->data);
		else
			break ;
		stk->sq_l = size > stk->sq_l ? size : stk->sq_l;
		lst = f == 1 ? stk->lst : lst->next;
		f += lst->next && !f ? 0 : 1;
	}
}

void find_both_seq(t_mngr *mngr)
{
	mngr->stk[0]->sq_l = 0;
	find_seq_stack(mngr, mngr->stk[0], 1);
	mngr->stk[1]->sq_l = 0;
	find_seq_stack(mngr, mngr->stk[1], -1);

}

void sort_one_dir(t_mngr *mngr, char c, int tmp)
{
	while (tmp)
	{
		safe_swap(mngr, STD, 1);
		if (tmp-- > 0)
			safe_rotate(mngr, c);
		safe_swap(mngr, STD, 1);
	}
	return (find_both_seq(mngr)); //TODO check why sets double value in case of sort
}

void sync_stacks(t_mngr *mngr, int place, int mode)
{
	int d1max;
	int	d2max;

	if (mngr->stk[0]->lst_s != mngr->stk[1]->lst_s || get_sort(mngr) % 6 == 0)
		return ;
	if (mode == 1)
	{
		d1max = val_to_place_dir_exist(mngr->stk[0], mngr->stk[0]->max, place);
		d2max = val_to_place_dir_exist(mngr->stk[1], mngr->stk[1]->min, place);
	}
	else if (mode == 2)
	{
		d1max = val_to_place_dir_exist(mngr->stk[0], mngr->stk[0]->piv, place);
		d2max = val_to_place_dir_exist(mngr->stk[1], mngr->stk[1]->piv, place);
	}
	// TODO if d1 or d2 == half of stack size should be checked for signs
	while (d1max || d2max)
	{
		if (d1max)
			d1max > 0 ? cmd_rotate(mngr, "a", 0) : cmd_rotate(mngr, "ra", 0);
		if (d2max)
			d2max > 0 ? cmd_rotate(mngr, "b", 0) : cmd_rotate(mngr, "rb", 0);
		if (d1max > 0 && d2max > 0)
			ft_printf("rr\n", d1max--, d2max--);
		else if (d1max < 0 && d2max < 0)
			ft_printf("rrr\n", d1max++, d2max++);
		else
		{
			if (d1max)
				d1max > 0 ? ft_printf("ra\n", d1max--) : ft_printf("rra\n", d1max++);
			if (d2max)
				d2max > 0 ? ft_printf("rb\n", d2max--) : ft_printf("rrb\n", d2max++);
		}
		draw_stacks(mngr);
	}
}

void push_val_to_place(t_mngr *mngr, int val, int place, char c)
{
	int dir0;
	int dir1;
	int i;

	dir0 = val_to_place_dir_exist(mngr->stk[0], val, place);
	dir1 = val_to_place_dir_exist(mngr->stk[1], val, place);
	while (dir0 || dir1)
	{
		if (dir0 > 0)
			safe_rotate(mngr, c);
	}
}

static void	bsort_both(t_mngr *mngr)
{
	int i;
	int t;
	int j;

	t = 1;
	j = 0;
	// TODO maybe it is sufficient to check stacks for right set values around stack "end"
	while (i && t && t % 6 != 0)
	{
		i = mngr->stk[0]->lst_s - FT_MIN2(mngr->stk[0]->sq_l, mngr->stk[1]->sq_l) - 2;
		if (!i && get_sort(mngr) % 6 != 0)
			i = 1;
		sort_one_dir(mngr, '\0', i);
		set_sort_both(mngr);
		// set start of seq to second place
		sync_stacks(mngr, 1 + FT_MIN2(mngr->stk[0]->sq_l, mngr->stk[1]->sq_l), 2);
		if (get_sort(mngr) % 6 == 0)
			break;
		i = mngr->stk[0]->lst_s - FT_MIN2(mngr->stk[0]->sq_l, mngr->stk[1]->sq_l) - 2;
		if (!i && get_sort(mngr) % 6 != 0)
			i = 1;
		sort_one_dir(mngr, 'r', i);
		set_sort_both(mngr);
		// rotate both piv to bot
		sync_stacks(mngr, mngr->stk[0]->lst_s - 1, 2);

		t = get_sort(mngr);
		ft_printf("End of cycle %d\n", mngr->n_cmd);
	}
}

/*int	check_seq(t_vector *vec, t_list **lst, t_stk *stk, int min)
{
	int index;
	int j;

	index = vec_bin_search(vec, val);
	j = 1;
	while (1)
	{
		if ((int)(*lst)->data != ((int*)vec->data)[index + 1])
			break ;
	}
	if (j > min)

	return ()
}

int	get_max_sort_seq(t_stk *stk, enum e_dir dir, t_mngr *mngr)
{
	t_list *tmp1;
	int		ret;
	int		cur;

	tmp1 = stk->lst;
	ret = 1;
	while (tmp1->next)
	{
		if (cmp_first_two(tmp1) == dir)
			cur = check_seq(mngr->vec, &tmp1, stk, ret);
		else
			tmp1 = tmp1->next;
		ret = cur > ret ? cur : ret;
	}
}

void	sync_stacks_pro(t_mngr *mngr)
{
	char dir0;
	char dir1;

	get_max_sort_seq(mngr->stk[0], ASC);
	get_max_sort_seq(mngr->stk[1], DESC);
	dir0 = finddirection(mngr->stk[0], mngr->stk[0]->piv);
	dir1 = val_to_place_dir_exist(mngr->stk[1], mngr->stk[1]->piv);
}*/



void	double_bouble(t_mngr *mngr)
{

	ft_printf("%d %d %d\n", mngr->stk[0]->min, mngr->stk[0]->max, mngr->stk[0]->piv);
	split_stack(mngr);
	ft_printf("End of split %d\n", mngr->n_cmd);
	//find_both_seq(mngr);
	mngr->stk[0]->sq_l = 1;
	mngr->stk[0]->piv = mngr->stk[0]->max;
	mngr->stk[1]->sq_l = 1;
	mngr->stk[1]->piv = mngr->stk[1]->min;
	sync_stacks(mngr, mngr->stk[0]->lst_s - 1, 1);
	ft_printf("End of sync %d\n", mngr->n_cmd);
	bsort_both(mngr);
	ft_printf("End of sort %d\n", mngr->n_cmd);
	while (get_sort(mngr) % 24 != 0)
	{
		safe_rotate(mngr, 'r');
		safe_rotate(mngr, '\0');
	}
	ft_printf("End of rotate %d\n", mngr->n_cmd);
	while (mngr->stk[1]->lst_s != 0)
		ft_printf("pa\n", cmd_push(mngr, "a"));

	//merge_two(mngr);
}

/* -781 -585 -440 196 -495 -284 443 -18 889 -840 -422 -734 134 -54 391 175
pb
pb
sb
pb
sr
pb
sr
ra
ra
sa
ra
ra
sa
pb
sa
pb
sr
pb
sr
sa
rr
sr
rr
rr
sr
rr
sr
rr
sr
ra
sa
rrr
sa
rrr
sb
rrr
sr
rrr
sa
rra
sa
rr
rr
sb
rr
sr
rrr
sa
rrr
rrr
pa
pa
pa
pa
pa
pa
pa


pb
pb
pb
rra
rra
sa
ra
sa
ra
sa
pb
sr
pb
ra
sa
ra
sa
sa
ra
sa
pb
sa
rb
pb
sr
pb
sa
rrr
sr
rrr
sb
rra
sa
rra
sa
rra
sa
ra
rb
rr
rr
sa
rra
sa
rra
sa
rra
rra
pa
pa
pa
pa
pa
pa
pa
pa
 */