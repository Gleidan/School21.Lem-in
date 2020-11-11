/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:52:30 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/11 10:37:54 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void init_room(t_room *room_lst, char **room)
{
	room_lst->name = ft_strdup(room[0]);
	room_lst->begin_link = NULL;
	room_lst->next = NULL;
	room_lst->prev = NULL;
	room_lst->same_hash = NULL;
	room_lst->room_copy = NULL;
	room_lst->queue = NULL;
	room_lst->link_count = 0;
	room_lst->in_queue = 0;
	room_lst->bellman_ford = 0;
}

/*
**	Record room on structure in (begin_room)
**	variable as is it presented in the map.
**	If we have (start) or (end) point,
**	we also write to the (start) of (end).
*/

static void	record_room(t_lem *lem, char **room, t_coord *point)
{
	t_room *room_lst;

	if (!lem->begin_room)
	{
		if (!(lem->begin_room = (t_room*)malloc(sizeof(t_room))))
			end_with_error(lem);
		room_lst = lem->begin_room;
	}
	else
	{
		room_lst = lem->begin_room;
		while (room_lst->next)
			room_lst = room_lst->next;
		if (!(room_lst->next = (t_room *)malloc(sizeof(t_room))))
			end_with_error(lem);
		room_lst = room_lst->next;
	}
	init_room(room_lst, room);
	lem->start = (point->start) ? room_lst : lem->start;
	lem->end = (point->end) ? room_lst : lem->end;
	point->start = 0;
	point->end = 0;
	
}

static int	check_repeats(t_room *begin_rooms, char **room)
{
	t_room *tmp;

	tmp = begin_rooms;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, room[0]))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	check_room(char **room)
{
	int i;
	int j;

	i = 0;
	if (!room[2] || room[3])
		return (0);
	while (room[i])
	{
		j = 0;
		while (i > 0 && room[i][j])
		{
			if (!ft_isdigit(room[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*
**	Split the line into 3 parts, because
**	room looks like this (name x y).
**	Checking the room for validity and repeats.
*/

int			save_room(t_lem *lem, char *line, t_coord *point)
{
	char **split_line;

	if (lem->rooms)
		end_with_error(lem);
	if (!(split_line = ft_strsplit(line, ' ')))
		return (0);
	if (!check_room(split_line) || check_repeats(lem->begin_room, split_line))
		end_with_error(lem);
	record_room(lem, split_line, point);
	lem->nb_rooms++;
	ft_clear_table(split_line);
	return (1);
}
