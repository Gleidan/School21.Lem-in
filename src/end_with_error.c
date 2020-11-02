/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_with_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:39:10 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/02 19:30:23 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	end_with_error(t_lem *lem, int error, char **arr)
{
	if (lem)
	{
		if (lem->map)
			ft_strdel(&lem->map);
		if (lem->rooms)
			free(lem->rooms);
		free (lem);
	}
	if (arr)
		ft_clear_table(arr);
	if (error == 1)
		ft_putstr_fd("Allocated memmory error\n", 2);
	else if (error == 1)
		ft_putstr_fd("Invalid read file\n", 2);
	exit(0);
}