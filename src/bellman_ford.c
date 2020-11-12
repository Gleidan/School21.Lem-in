/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:46:54 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/11 13:58:55 by Gimad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Add the room to the queue and save the link
**	to the current node in the variable (prev).
**	For example: we have start <- n <- n <- end.
*/

static void		add_to_queue(t_lem *lem, t_room *next_for_q,
					t_room *current_room, t_link *room_links)
{
	int		hash_key;
	t_room	*find_room;

	hash_key = hash(lem->nb_rooms, room_links->name);
	find_room = lem->rooms[hash_key];
	while (ft_strcmp(room_links->name, find_room->name) != 0)
		find_room = find_room->same_hash;
	if (room_links->weight == -1 &&
		ft_strcmp(room_links->name, lem->start->name) != 0 &&
			ft_strcmp(room_links->name, lem->end->name) != 0)
		find_room = find_room->room_copy;
	if (find_room->in_queue == 0 && room_links->on)
	{
		next_for_q->queue = find_room;
		find_room->prev = current_room;
		if (!current_room->prev)
			find_room->bellman_ford = room_links->weight;
		else
			find_room->bellman_ford = find_room->prev->bellman_ford +
					room_links->weight;
		next_for_q = next_for_q->queue;
		next_for_q->in_queue = 1;
	}
}

/*
**	Add to the queue all rooms
**	that are associated with the current
*/

static void		next_room_for_queue(t_lem *lem, t_room *current_room)
{
	t_room *next_for_q;
	t_link *cur_room_links;

	next_for_q = current_room;
	while (next_for_q->queue)
		next_for_q = next_for_q->queue;
	cur_room_links = current_room->begin_link;
	while (cur_room_links)
	{
		add_to_queue(lem, next_for_q, current_room, cur_room_links);
		if (next_for_q->queue)
			next_for_q = next_for_q->queue;
		cur_room_links = cur_room_links->next;
	}
}

/*
**	If all rooms be in queue - loop is break.
*/

static int		check_queue_status(t_room *begin)
{
	while (begin)
	{
		if (begin->in_queue == 0)
			return (0);
		begin = begin->next;
	}
	return (1);
}

/*
**	We fill the queue and walk through it until
**	end is reached.
*/

int				bf_algorithm(t_lem *lem)
{
	t_room *queue_tmp;

	queue_tmp = lem->start;
	queue_tmp->in_queue = 1;
	while (!check_queue_status(lem->begin_room))
	{
		next_room_for_queue(lem, queue_tmp);
		queue_tmp->in_queue = -1;
		if (!queue_tmp->queue && lem->end->in_queue == 0)
			return (0);
		else if (!queue_tmp->queue && lem->end->in_queue != 0)
			return (1);
		queue_tmp = queue_tmp->queue;
	}
	return (1);
}
