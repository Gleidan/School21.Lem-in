/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:44:30 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/11 10:39:04 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void out_links(t_lem *lem, char *name)
{
	int			room_hash;
	t_room		*find_room;
	t_link		*ptr;

	room_hash = hash(lem->nb_rooms, name);
	find_room = lem->rooms[room_hash];
	while (ft_strcmp(name, find_room->name) != 0)
		find_room = find_room->same_hash;
	find_room->room_copy = copy_room(lem, find_room);
	ptr = find_room->begin_link;
	if (!(find_room->room_copy->begin_link = (t_link *)malloc(sizeof(t_link))))
		end_with_error(lem);
	find_room->room_copy->begin_link->name = ft_strdup(find_room->name);
	find_room->room_copy->begin_link->weight = 0;
	find_room->room_copy->begin_link->next = NULL;
	find_room->room_copy->begin_link->on = 1;
	while (ptr)
	{
		if (ptr->on && ptr->weight != -1)
		{
			copy_links(lem, find_room->room_copy->begin_link, ptr);
			ptr->on = 0;
		}
		ptr = ptr->next;
	}
}

static void inverse_edges(t_lem *lem, t_path *room_first, t_path *room_second)
{
	int room_hash;
	t_room *find_room;
	t_link *find_link;

	room_hash = hash(lem->nb_rooms, room_first->name);
	find_room = lem->rooms[room_hash];
	while (ft_strcmp(room_first->name, find_room->name) != 0)
		find_room = find_room->same_hash;
	find_link = find_room->begin_link;
	while (ft_strcmp(find_link->name, room_second->name) != 0)
		find_link = find_link->next;
	find_link->weight = -1;
	room_hash = hash(lem->nb_rooms, room_second->name);
	find_room = lem->rooms[room_hash];
	while (ft_strcmp(room_second->name, find_room->name) != 0)
		find_room = find_room->same_hash;
	find_link = find_room->begin_link;
	while (ft_strcmp(find_link->name, room_first->name) != 0)
		find_link = find_link->next;
	find_link->on = 0;
}

void	s_algorithm(t_lem *lem)
{
	t_way *way;
	t_path *path;

	way = lem->solutions->ways;
	while (way)
	{
		path = way->path;
		while (path->forward)
		{
			inverse_edges(lem, path, path->forward);
			path = path->forward;
		}
		way = way->next;
	}
	way = lem->solutions->ways;
	while (way)
	{
		path = way->path->forward;
		while (path->forward)
		{
			out_links(lem, path->name);
			path = path->forward;
		}
		way = way->next;
	}
}