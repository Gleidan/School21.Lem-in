/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:34:43 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/10 17:15:01 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Two main parts of program:
**	parsing - filling (lem) structure
**	and finding_paths, that running the algorithm
**	
*/

int	main(void)
{
	t_lem *lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		end_with_error(lem, 1, NULL);
	ft_bzero(lem, sizeof(lem));
	if (!parsing(lem))
		end_with_error(lem, 1, NULL);
	finding_paths(lem);

//	ft_printf("%s\n", lem->map);
//	ft_printf("ants %d rooms %d\n", lem->nb_ants, lem->nb_rooms);
//	ft_printf("start %s end %s\n", lem->start->name, lem->end->name);
	
/*	
	t_room *temp_room;
	t_link *temp_link;
	
	temp_room = lem->begin_room;
	
	while (temp_room)
	{
		ft_printf("Name of room %s and hash_key %d\n", temp_room->name, hash(lem->nb_rooms, temp_room->name));
		temp_link = temp_room->begin_link;
		while (temp_link)
		{
			ft_printf("Name of link %s\n", temp_link->name);
			temp_link = temp_link->next;
		}
		if (temp_room->same_hash)
			ft_printf("same hash %s and hash_key %d\n", temp_room->same_hash->name, hash(lem->nb_rooms, temp_room->same_hash->name));
		if (temp_room->room_copy)
			ft_printf("room copy %s\n", temp_room->room_copy->name);
		temp_room = temp_room->next;
		ft_printf("\n");
	}

	t_room *temp_path;

	temp_path = lem->end;
	while (temp_path)
	{
		ft_printf("%s\n", temp_path->name);
		temp_path = temp_path->prev;
	}

	temp_path = lem->begin_room;
	while (temp_path)
	{
		if (temp_path->prev)
			ft_printf("%s: %s\n", temp_path->name, temp_path->prev->name);
		temp_path = temp_path->next;
	}

	t_sol *tmp_sol = lem->solutions;

	while (tmp_sol)
	{
		ft_printf("%d %d %d\n", tmp_sol->index, tmp_sol->n_ways, tmp_sol->steps);
		t_way *tmp_way = tmp_sol->ways;
		while (tmp_way)
		{
			t_path *tmp_path = tmp_way->path;
			while (tmp_path)
			{
				ft_printf("%s\n", tmp_path->backward->name);
				tmp_path = tmp_path->forward;
			}
			tmp_way = tmp_way->next;
		}
		tmp_sol = tmp_sol->next;
	}
	*/
	return (0);
}