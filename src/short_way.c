/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_way.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:53:39 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/11 10:39:40 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"

static void	mark_link(t_lem *lem, char *room_first, char *room_second)
{
	int hash_key;
	t_room *find_room;
	t_link *find_link;

	hash_key = hash(lem->nb_rooms, room_second);
	find_room = lem->rooms[hash_key];
	while (ft_strcmp(find_room->name, room_second) != 0)
		find_room = find_room->same_hash;
	if (ft_strcmp(room_first, room_second) == 0)
		find_room = find_room->room_copy;
	find_link = find_room->begin_link;
	while (ft_strcmp(find_link->name, room_first) != 0)
		find_link = find_link->next;
	find_link->in_way++;
}

static void new_path(t_lem *lem, t_way *current_way, t_path *tmp_path)
{
	t_room *find_room;
	t_path *back;

	while (ft_strcmp(tmp_path->name, lem->start->name) != 0)
	{
		if (!(tmp_path->forward = (t_path*)malloc(sizeof(t_path))))
			end_with_error(lem);
		tmp_path->forward->ant_name = 0;
		back = tmp_path;
		tmp_path = tmp_path->forward;
		tmp_path->backward = back;
		find_room = lem->rooms[hash(lem->nb_rooms, back->name)];
		while (ft_strcmp(back->name, find_room->name) != 0)
			find_room = find_room->same_hash;
		if (find_room->room_copy && check_copy(find_room, tmp_path->backward->backward->name))
			find_room = find_room->room_copy;
		if (ft_strcmp(find_room->prev->name, find_room->name) == 0)
			tmp_path->name = ft_strdup(find_room->prev->prev->name);
		else
			tmp_path->name = ft_strdup(find_room->prev->name);
		mark_link(lem, tmp_path->name, tmp_path->backward->name);
		tmp_path->forward = NULL;
		current_way->len++;
	}
	current_way->path->backward = tmp_path;
}

t_way *new_way(t_lem *lem)
{
	t_way *tmp_way;

	if (!(tmp_way = (t_way*)malloc(sizeof(t_way))) || !(tmp_way->path = (t_path*)malloc(sizeof(t_path))))
		end_with_error(lem);
	tmp_way->path->name = ft_strdup(lem->end->name);
	tmp_way->path->backward = NULL;
	tmp_way->path->forward = NULL;
	tmp_way->next = NULL;
	tmp_way->len = 0;
	tmp_way->ants = 0;
	tmp_way->on = 1;
	tmp_way->path->ant_name = 0;
	return (tmp_way);
}

static void	add_new_way(t_lem *lem, t_way *tmp_way)
{
	new_path(lem, tmp_way, tmp_way->path);
	clean_queue(lem);
	graph_recovery(lem, lem->solutions->next);
	find_crossover(lem, tmp_way);
	free_way(tmp_way, tmp_way->path);
	find_new_ways(lem, NULL);
	in_way_recovery(lem->end->begin_link);
}

void	short_way(t_lem *lem)
{
	t_way		*way;
	t_way		*tmp_way;
	t_sol		*new_sol;
	
	if (!lem->solutions)
	{
		if (!(lem->solutions = (t_sol*)malloc(sizeof(t_sol))))
			end_with_error(lem);
		init_sol(lem->solutions);
		way = new_way(lem);
		new_path(lem, way, way->path);
		lem->solutions->ways = way;
		lem->solutions->n_ways = 1;
		lem->solutions->index = 1;
	}
	else
	{
		if (!(new_sol = (t_sol*)malloc(sizeof(t_sol))))
			end_with_error(lem);
		init_sol(new_sol);
		new_sol->next = lem->solutions;
		lem->solutions = new_sol;
		lem->solutions->index = lem->solutions->next->index + 1;
		tmp_way = new_way(lem);
		add_new_way(lem, tmp_way);
	}
}
