//
// Created by Ebrose Hugh beesbury on 2019-06-05.
//

#include "push_swap.h"
#ifdef HIDDEN
int	get_sort(t_mngr *mngr)
{
	int sa;
	int sb;
	int saf;
	int sbf;

	sa = mngr->stk[0]->sq_l == mngr->stk[0]->lst_s && mngr->stk[0]->lst_s != 0;
	sb = mngr->stk[1]->sq_l == mngr->stk[1]->lst_s && mngr->stk[1]->lst_s != 0;
	saf = check_sort(mngr->stk[0], ASC, 1);
	sbf = check_sort(mngr->stk[1], DESC, 1);
	sa = (sa + saf) ? (sa + saf) * 2 : 1;
	sa *= (sb + sbf) ? (sb + sbf) * 3 : 1;
	return (sa);
}
void set_sort(t_stk *stk, t_edir dir, int val)
{
	if (stk->lst_s == stk->sq_l)
		stk->sort = val_to_place_dir_exist(stk, val, stk->lst_s - 1);
	else if ((check_sort(stk, dir, 0)))
	{
		stk->sort = val_to_place_dir_exist(stk, val, stk->lst_s - 1);
		stk->sq_l = stk->lst_s;
	}
}
void	set_sort_both(t_mngr *mngr)
{
	if (mngr->stk[0]->lst)
		set_sort(mngr->stk[0], ASC, mngr->stk[0]->max);
	if (mngr->stk[1]->lst)
		set_sort(mngr->stk[1], DESC, mngr->stk[1]->min);
}
void	safe_rotate(t_mngr *mngr, char c)
{
	int		b0;
	int		b1;
	char st[2];
	int 	t;

	st[0] = c == 'r' ? 'r' : '\0';
	st[1] = '\0';
	b0 = -1;
	b1 = mngr->stk[1]->lst_s ? -1 : 0;
	set_sort_both(mngr);
	t = get_sort(mngr);
	if (t && t % 2 == 0)
		b0 = c == 'r' ? mngr->stk[0]->sort < 0 : mngr->stk[0]->sort > 0;
	if (t && t % 3 == 0)
		b1 = c == 'r' ? mngr->stk[1]->sort < 0 : mngr->stk[1]->sort > 0;
	if (b0)
		b1 ? ft_printf("r%sr\n", st, cmd_rotate(mngr, "r", c)) :
		ft_printf("r%sa\n", st, cmd_rotate(mngr, "a", c));
	else if (b1)
		ft_printf("r%sb\n", st, cmd_rotate(mngr, "b", c));
}

t_edir pivot_compare(t_stk *stk)
{
	t_list *lst;
	t_edir ret;

	lst = stk->lst;
	if (!lst || !lst->next)
		return (lst ? ONE_EL : EMPTY);
	if (((int)lst->data < stk->piv && (int)lst->next->data > stk->piv) ||
		((int)lst->data > stk->piv && (int) lst->next->data < stk->piv))
		ret = -cmp_first_two(lst);
	else
		ret = cmp_first_two(lst);
	if (ret < 0 && ret != ASC)
		return (-ret);
	return (ret);
}

void safe_swap(t_mngr *mngr, t_eswopt mode, int piv)
{
	int t;
	int b0;
	int b1;

	// if both elements by the same side of pivot do this else make up something))
	set_sort_both(mngr);
	t = get_sort(mngr);
	b0 = 0;
	b1 = 0;
	if (t && t % 2 != 0 && mode != B_ONL)
		b0 = piv ? pivot_compare(mngr->stk[0]) == DESC : cmp_first_two(mngr->stk[0]->lst) == DESC;
	if (t && t % 3 != 0 && mode != A_ONL)
		b1 = piv ? pivot_compare(mngr->stk[1]) == ASC : cmp_first_two(mngr->stk[1]->lst) == ASC;
	if (mode >= BOTH_ONL && b0 != b1)
	{
		if (mode == A_OR_BOTH)
			b1 = 0;
		else if (mode == B_OR_BOTH)
			b0 = 0;
		else
			return ;
	}
	if (b0)
		b1 ? ft_printf("sr\n", cmd_swap(mngr, "r")) :
		ft_printf("sa\n", cmd_swap(mngr, "a"));
	else if (b1)
		ft_printf("sb\n", cmd_swap(mngr, "b"));
}

void smart_swap(t_mngr *mngr)
{
	if (cmp_first_two(mngr->stk[0]->lst) == DESC)
		(cmp_first_two(mngr->stk[1]->lst) == ASC) ?
		ft_printf("sr\n", mngr->dbg *= cmd_swap(mngr, "r")) :
		ft_printf("sa\n", mngr->dbg *= cmd_swap(mngr, "a"));
	else if (cmp_first_two(mngr->stk[1]->lst) == ASC)
		ft_printf("sb\n", mngr->dbg *= cmd_swap(mngr, "b"));
}
#endif