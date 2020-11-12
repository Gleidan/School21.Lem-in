/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:17:40 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/11 20:39:17 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	The hash table is created in size (nb_rooms * 4).
**	Write down all rooms by their hash key position.
**	If we have collision - record in (same_hash) variable.
*/

static void		create_hash_table(t_lem *lem)
{
	int		hash_key;
	t_room	*tmp;
	t_room	*find_last_room;

	hash_key = -1;
	tmp = lem->begin_room;
	if (!(lem->rooms = (t_room**)malloc(sizeof(t_room*) * (lem->nb_rooms * 4))))
		end_with_error(lem);
	while (hash_key < lem->nb_rooms * 4 - 1)
		lem->rooms[++hash_key] = NULL;
	while (tmp)
	{
		hash_key = hash(lem->nb_rooms, tmp->name);
		if (!lem->rooms[hash_key])
			lem->rooms[hash_key] = tmp;
		else
		{
			find_last_room = lem->rooms[hash_key];
			while (find_last_room->same_hash)
				find_last_room = find_last_room->same_hash;
			find_last_room->same_hash = tmp;
		}
		tmp = tmp->next;
	}
}

static void		init_link(t_link *link, char *link_name)
{
	link->name = ft_strdup(link_name);
	link->weight = 1;
	link->on = 1;
	link->in_way = 0;
	link->next = NULL;
}

static int		create_new_link(t_lem *lem, t_room *find_room, char *room_link)
{
	t_link *link_list;

	if (!find_room->begin_link)
	{
		if (!(find_room->begin_link = (t_link*)malloc(sizeof(t_link))))
			end_with_error(lem);
		link_list = find_room->begin_link;
	}
	else
	{
		link_list = find_room->begin_link;
		while (link_list->next)
		{
			if (ft_strcmp(link_list->name, room_link) == 0)
				return (0);
			link_list = link_list->next;
		}
		if (ft_strcmp(link_list->name, room_link) == 0)
			return (0);
		if (!(link_list->next = (t_link*)malloc(sizeof(t_link))))
			end_with_error(lem);
		link_list = link_list->next;
	}
	init_link(link_list, room_link);
	return (1);
}

static int		add_link(t_lem *lem, char *room, char *room_link)
{
	int		hash_key;
	t_room	*find_room;

	hash_key = hash(lem->nb_rooms, room);
	find_room = lem->rooms[hash_key];
	if (!find_room)
		return (0);
	while (find_room && ft_strcmp(find_room->name, room))
		find_room = find_room->same_hash;
	if (!find_room || !(create_new_link(lem, find_room, room_link)))
		return (0);
	find_room->link_count++;
	return (1);
}

/*
**	Split line into 2 parts, because
**	link looks like this (room1-room2).
**	Creating hash_table in (rooms) variable.
*/

int				save_links(t_lem *lem, char *line)
{
	char	**split_line;

	if (!(split_line = ft_strsplit(line, '-')))
		end_with_error(lem);
	if (ft_strchr(split_line[0], ' ') || ft_strchr(split_line[1], ' ') ||
		!lem->begin_room)
		end_with_error(lem);
	if (!lem->rooms)
		create_hash_table(lem);
	if (!(add_link(lem, split_line[0], split_line[1])))
	{
		ft_clear_table(split_line);
		return (0);
	}
	if (!(add_link(lem, split_line[1], split_line[0])))
	{
		ft_clear_table(split_line);
		return (0);
	}
	ft_clear_table(split_line);
	return (1);
}
