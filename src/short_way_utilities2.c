/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_way_utilities2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:27:34 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/12 10:58:14 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			init_sol(t_sol *solutions)
{
	solutions->index = 0;
	solutions->n_ways = 0;
	solutions->steps = 0;
	solutions->next = NULL;
	solutions->ways = NULL;
}

static void		remove_crossed_links(t_lem *lem, t_room *find_room,
					t_link *find_link, t_path *tmp_path)
{
	int hash_key;

	find_link->on = 0;
	find_link->in_way = 0;
	hash_key = hash(lem->nb_rooms, tmp_path->f->name);
	find_room = lem->rooms[hash_key];
	while (ft_strcmp(tmp_path->f->name, find_room->name) != 0)
		find_room = find_room->same_hash;
	find_link = find_room->begin_link;
	while (ft_strcmp(find_link->name, tmp_path->name) != 0)
		find_link = find_link->next;
	find_link->on = 0;
	find_link->in_way = 0;
}

static int		check_reverse_link(t_lem *lem, char *room_name, char *link_name)
{
	int			hash_key;
	t_room		*find_room;
	t_link		*find_link;

	hash_key = hash(lem->nb_rooms, room_name);
	find_room = lem->rooms[hash_key];
	while (ft_strcmp(room_name, find_room->name) != 0)
		find_room = find_room->same_hash;
	find_link = find_room->begin_link;
	while (ft_strcmp(find_link->name, link_name) != 0)
		find_link = find_link->next;
	if (find_link->in_way >= 1)
		return (1);
	return (0);
}

int				find_crossover(t_lem *lem, t_way *way)
{
	int			rt;
	t_room		*find_room;
	t_link		*find_link;
	t_path		*tmp_path;

	rt = 0;
	tmp_path = way->path;
	while (tmp_path->f)
	{
		find_room = lem->rooms[hash(lem->nb_rooms, tmp_path->name)];
		while (ft_strcmp(tmp_path->name, find_room->name) != 0)
			find_room = find_room->same_hash;
		find_link = find_room->begin_link;
		while (ft_strcmp(find_link->name, tmp_path->f->name) != 0)
			find_link = find_link->next;
		if (find_link->in_way > 1 ||
			(find_link->in_way >= 1 && check_reverse_link(lem, find_link->name,
				find_room->name)))
		{
			rt = 1;
			remove_crossed_links(lem, find_room, find_link, tmp_path);
		}
		tmp_path = tmp_path->f;
	}
	return (rt);
}
