/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:34:43 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/12 10:54:56 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_lem(t_lem *lem)
{
	if (lem)
		if (lem->map)
			free_map(lem->map);
	if (lem->begin_room)
		free_room_list(&lem->begin_room);
	if (lem->rooms)
		free(lem->rooms);
	if (lem->solutions)
		free_solutions(lem->solutions);
	free(lem);
}

void	init_struct(t_lem *lem)
{
	lem->nb_ants = 0;
	lem->nb_rooms = 0;
	lem->map = NULL;
	lem->begin_room = NULL;
	lem->start = NULL;
	lem->end = NULL;
	lem->rooms = NULL;
	lem->solutions = NULL;
}

/*
**	Two main parts of program:
**	parsing - filling (lem) structure
**	and finding_paths, that running the algorithm
*/

int		main(void)
{
	t_lem	*lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		end_with_error(lem);
	init_struct(lem);
	if (!parsing(lem))
		end_with_error(lem);
	finding_paths(lem);
	free_lem(lem);
	return (0);
}
