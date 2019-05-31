/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecbinsearch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 19:33:00 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/04/16 19:33:00 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec.h"

/*
** @param vec - sorted valid int vector that would be searched through
** @param val - value that will be looked for
** @return - index of the vector where value is stored or negative if value 
** haven't been found
**/

int ft_vecbinsearch_int(t_vector *vec, int val)
{
	int ret;
	int tmp;
	int mod;
	
	ret = vec->len / sizeof(int) / 2 - 1;
	mod = (vec->len / sizeof(int) - ret) / 2;
	while (ret && ret != vec->len)
	{
		tmp = ((int*)vec->data)[ret];
		if (val == tmp)
			break ;
		else if (val < tmp)
			ret -= mod ? mod : 1;
		else
			ret += mod ? mod : 1;
		mod /= 2;
	}
	if (ret == 0)
		ret = ((int*)vec->data)[ret] == val ? ret : -1;
	return (ret);
}
