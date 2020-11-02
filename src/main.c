/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:34:43 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/02 19:30:25 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Initialized general structure
*/

static void init_struct(t_lem *lem)
{
	lem->nb_ants = 0;
	lem->nb_rooms = 0;
	lem->map = NULL;
	lem->begin_room = NULL;
	lem->rooms = NULL;
	lem->start = NULL;
}

int	main(void)
{
	t_lem *lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		end_with_error(lem, 1, NULL);
	init_struct(lem);
	if (!parsing(lem))
		end_with_error(lem, 1, NULL);
	ft_printf("%s\n", lem->map);
	ft_printf("ants %d rooms %d\n", lem->nb_ants, lem->nb_rooms);
	ft_printf("start %s end %s\n", lem->start->name, lem->end->name);
	return (0);
}