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

int		val_to_place_dir_exist(t_stk *stk, int val, int place)
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

int		val_to_place_dir_nexis(t_stk *stk, int val)
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
			break ;
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
*/

int		check_sort(t_stk *stk, t_edir dir, int fin)
{
	t_list *lst;

	lst = stk->lst;
	if (!lst)
		return (0);
	while (lst->next)
		if (cmp_first_two(lst) != dir && lst->next)
			if (fin)
				break ;
			else if ((dir == DESC && (int)lst->data == stk->min &&
			(int)lst->next->data == stk->max) || (dir == ASC &&
			(int)lst->data == stk->max && (int)lst->next->data == stk->min))
				lst = lst->next;
			else
				break ;
		else
			lst = lst->next;
	if (lst->next)
		return (0);
	else if (fin || (dir == ASC && ((int)lst->data < (int)stk->lst->data ||
			(int)lst->data == stk->max)) || (dir == DESC && ((int)lst->data >
			(int)stk->lst->data || (int)lst->data == stk->min)))
		return (1);
	return (0);
}
