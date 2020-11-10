/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_new_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:42:31 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/10 16:37:52 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	in_way_recovery(t_link *next_room)
{
	while (next_room)
	{
		if (next_room->in_way == -1)
			next_room->in_way = 1;
		next_room = next_room->next;
	}
}

static t_link *in_way_link_finder(t_room *room, int number)
{
	t_link *tmp_link;
	
	tmp_link = room->begin_link;
	while (tmp_link)
	{
		if (tmp_link->in_way == 1)
		{
			tmp_link->in_way = number;
			return (tmp_link);
		}
		tmp_link = tmp_link->next;
	}
	return (NULL);
}

static int make_paths(t_lem *lem, t_path **new_path, t_link **next_room)
{
	t_room *find_room;

	(*new_path)->forward = (t_path*)malloc(sizeof(t_path));
	(*new_path)->forward->backward = (*new_path);
	(*new_path) = (*new_path)->forward;
	(*new_path)->ant_name = 0;
	(*new_path)->name = ft_strdup((*next_room)->name);
	(*new_path)->forward = NULL;
	if (ft_strcmp((*next_room)->name, lem->start->name) == 0)
		return (0);
	find_room = lem->rooms[hash(lem->nb_rooms, (*new_path)->name)];
	while (ft_strcmp((*new_path)->name, find_room->name) != 0)
		find_room = find_room->same_hash;
	*next_room = in_way_link_finder(find_room, 1);
	return (1);
}

void	find_new_ways(t_lem *lem, t_link *next_room)
{
	t_way *way;
	t_path *new_path;

	while ((next_room = in_way_link_finder(lem->end, -1)))
	{
		lem->solutions->n_ways++;
		if (!lem->solutions->ways)
		{
			lem->solutions->ways = new_way(lem);
			way = lem->solutions->ways;
		}
		else
		{
			way->next = new_way(lem);
			way = way->next;
		}
		new_path = way->path;
		while (next_room)
		{
			way->len++;
			if (!make_paths(lem, &new_path, &next_room))
				break ;
		}
		way->path->backward = new_path;
	}
}