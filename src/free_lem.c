/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:22:35 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/12 11:00:02 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_way(t_way *tmp_way, t_path *tmp_path)
{
	t_path	*p_ptr;

	p_ptr = tmp_path;
	while (tmp_path)
	{
		p_ptr = tmp_path->f;
		free(tmp_path->name);
		free(tmp_path);
		tmp_path = p_ptr;
	}
	free(tmp_way);
}

void	free_solutions(t_sol *sol)
{
	t_sol	*sol_tmp;
	t_sol	*s_ptr;
	t_way	*way_tmp;
	t_way	*w_ptr;

	sol_tmp = sol;
	while (sol_tmp)
	{
		way_tmp = sol_tmp->ways;
		while (way_tmp)
		{
			w_ptr = way_tmp->next;
			free_way(way_tmp, way_tmp->path);
			way_tmp = w_ptr;
		}
		s_ptr = sol_tmp->next;
		free(sol_tmp);
		sol_tmp = s_ptr;
	}
}

void	free_links(t_link *links)
{
	t_link	*l_ptr;

	while (links)
	{
		l_ptr = links->next;
		free(links->name);
		free(links);
		links = l_ptr;
	}
}

void	free_room_list(t_room **rooms)
{
	t_room	*tmp;

	while (*rooms)
	{
		tmp = (*rooms)->next;
		free((*rooms)->name);
		if ((*rooms)->room_copy)
		{
			free_links((*rooms)->room_copy->begin_link);
			free((*rooms)->room_copy->name);
			free((*rooms)->room_copy);
		}
		free_links((*rooms)->begin_link);
		free((*rooms));
		(*rooms) = tmp;
	}
}

void	free_map(t_map *map)
{
	t_map	*tmp;

	while (map)
	{
		tmp = map->next;
		free(map->content);
		free(map);
		map = tmp;
	}
}
