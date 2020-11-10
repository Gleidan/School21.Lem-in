/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_with_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:39:10 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/10 16:48:30 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_way(t_way *tmp_way, t_path *tmp_path)
{
	t_path *p_ptr;

	p_ptr = tmp_path;
	while (tmp_path)
	{
		p_ptr = tmp_path->forward;
		free(tmp_path->name);
		free(tmp_path);
		tmp_path = p_ptr;
	}
	free(tmp_way);
}

void	end_with_error(t_lem *lem, int error, char **arr)
{
	if (lem)
	{
	//	if (lem->map)
	//		ft_strdel(&lem->map);
		if (lem->rooms)
			free(lem->rooms);
		free (lem);
	}
	if (arr)
		ft_clear_table(arr);
	if (error == 1)
		ft_putstr_fd("Allocated memmory error\n", 2);
	else if (error == 2)
		ft_putstr_fd("Invalid read file\n", 2);
	exit(0);
}