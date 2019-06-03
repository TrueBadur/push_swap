/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:29:49 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/12 15:29:49 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
/*
** Compares first two elements in list
** @param lst - list in which to compare elements
** @return - 1, 0 or -1 if first element is greater, equal or less then second.
** If list is empty -5 is returned. If there is only one in list -6 is returned.
*/
t_edir	cmp_first_two(t_list *lst)
{
	if (!lst)
		return (EMPTY);
	if (!lst->next)
		return (ONE_EL);
	if ((int)lst->data < (int)lst->next->data)
		return (ASC);
	else if ((int)lst->data == (int)lst->next->data)
		return (EQ);
	else
		return (DESC);
}

/*
** Finds in which direction and for what amount to rotate stack to get val to
** bottom of the stack
** @param stk - stk in which list to find direction and number of rotates
** @param val - which value should get to bottom
** @return returns positive value if stack should be rotated to the top
** (aka "rr") and negative otherwise (aka "rrr") and 0 if val is in place
*/

int	val_to_place_dir_exist(t_stk *stk, int val, int place)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = stk->lst;
	while (lst->next && (int)lst->data != val && (lst = lst->next))
		i++;
	if ((FT_ABS(i - place)) > stk->lst_s / 2)
		i = -1 * FT_SIGN(i - place) * (stk->lst_s - FT_ABS(place - i));
	else
		i = i - place;
	return (i);
}

int val_to_place_dir_nexis(t_stk *stk, int val)
{
	int		i;
	t_list	*lst;

	lst = stk->lst;

	i = 0;
	while (lst->next)
	{
		if ((val < stk->min && (int)lst->data == stk->min) ||
			(val > stk->max && (int)lst->data == stk->min) ||
			((int)lst->data > val && (int)stk->l_e->data < val))
			break;
		else if ((int)lst->data < val && (int)lst->next->data > val)
		{
			i++;
			break ;
		}
		i++;
		lst = lst->next;
	}
	if (i > stk->lst_s / 2)
		i = -1 * (stk->lst_s - i);
	return (i);
}

/*
** @param stk - stk to check for sorted
** @param dir - direction in which to check for sorted (either ASC for ascended
** or DESC for descended
** @param final - if stack should be in the final state so that first el of the
** sequence should be at the first place
** @return 1 if list is sorted and 0 otherwise
**/

int check_sort(t_stk *stk, t_edir dir, int fin)
{
	t_list *lst;

	lst = stk->lst;
	if (!lst)
		return (0);
	while (lst->next)
		if (cmp_first_two(lst) != dir && lst->next)
		{
			if (fin)
				break;
			if ((dir == DESC && (int)lst->data == stk->min &&
				 (int)lst->next->data == stk->max) || (dir == ASC &&
													   (int)lst->data == stk->max && (int)lst->next->data == stk->min))
				lst = lst->next;
			else
				break ;
		}
		else
			lst = lst->next;
	if (lst->next)
		return (0);
	else if (fin || ((dir == ASC && (int)lst->data < (int)stk->lst->data) ||
					 (dir == DESC && (int)lst->data > (int)stk->lst->data)))
		return (1);
	return (0);
}
