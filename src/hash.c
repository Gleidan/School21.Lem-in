/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:25:32 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/11 14:01:38 by Gimad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Create unique hash key.
**	For example: name - "lem"
**	key - 30;
*/

int		hash(int size, char *name)
{
	int i;
	int key;

	i = 0;
	key = 0;
	while (name[i])
	{
		key += name[i];
		i++;
	}
	key = key % (size * 4);
	return (key);
}
