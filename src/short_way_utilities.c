/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_way_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:31:38 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/10 15:29:24 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void delete_copy(t_room *room)
{
	t_link *del_link;
	t_link *helper;
	t_link *tmp_link;

	if (room->room_copy)
	{
		del_link = room->room_copy->begin_link;
		while (del_link)
		{
			helper = del_link->next;
			free(del_link->name);
			free(del_link);
			del_link = helper;
		}
		free(room->room_copy->name);
		free(room->room_copy);
		room->room_copy = NULL;
	}
	tmp_link = room->begin_link;
	while (tmp_link)
	{
		tmp_link->weight = 1;
		tmp_link->on = 1;
		tmp_link = tmp_link->next;
	}
}

void	graph_recovery(t_lem *lem, t_sol *prev_sol)
{
	int		hash_key;
	t_way	*tmp_way;
	t_path	*tmp_path;
	t_room	*find_room;

	tmp_way = prev_sol->ways;
	while (tmp_way)
	{
		tmp_path = tmp_way->path;
		while (tmp_path)
		{
			hash_key = hash(lem->nb_rooms, tmp_path->name);
			find_room = lem->rooms[hash_key];
			while (ft_strcmp(tmp_path->name, find_room->name) != 0)
				find_room = find_room->same_hash;
			delete_copy(find_room);
			tmp_path = tmp_path->forward;
		}
		tmp_way = tmp_way->next;
	}
}

void	clean_queue(t_lem *lem)
{
	t_room *tmp;
	t_room *next;

	tmp = lem->start;
	while (tmp)
	{
		next = tmp->queue;
		tmp->prev = NULL;
		tmp->queue = NULL;
		tmp->in_queue = 0;
		tmp->bellman_ford = 0;
		tmp = next;
	}
}

int		check_copy(t_room *current_room, char *link_name)
{
	t_link *tmp_link;

	tmp_link = current_room->begin_link;
	while (tmp_link)
	{
		if (ft_strcmp(link_name, tmp_link->name) == 0)
			break ;
		tmp_link = tmp_link->next;
	}
	if (tmp_link->on == 0)
		return (1);
	else
		return (0);
}