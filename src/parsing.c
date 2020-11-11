/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:27:32 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/11 10:46:29 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void save_map(t_lem *lem, char *line)
{
	t_map *tmp_map;
	t_map *add_line;
	
	if (!lem->map)
	{
		if (!(tmp_map = (t_map*)malloc(sizeof(t_map))))
			end_with_error(lem);
		tmp_map->content = ft_strdup(line);
		tmp_map->next = NULL;
		lem->map = tmp_map;
	}
	else
	{
		tmp_map = lem->map;
		while (tmp_map->next)
			tmp_map = tmp_map->next;
		if (!(add_line = (t_map*)malloc(sizeof(t_map))))
			end_with_error(lem);
		add_line->content = ft_strdup(line);
		add_line->next = NULL;
		tmp_map->next = add_line;
	}
}

/*
**	If comment have "##start" or "##end" we make
**	point for {save_room} function to save the pointer
**	on room in start variables or end in general structure
*/

static int save_point(t_lem *lem, char *line, t_coord *point)
{
	if (point->start == 1 || point->end == 1)
		return (0);
	if (ft_strcmp("##start", line) == 0)
	{
		if (lem->start)
			return (0);
		point->start = 1;
	}
	if (ft_strcmp("##end", line) == 0)
	{
		if (lem->end)
			return (0);
		point->end = 1;
	}
	return (1);
}

static int check_ants(t_lem *lem, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) || (i == 0 && line[i] == 48) || !ft_isint(line))
			return (0);
		++i;
	}
	lem->nb_ants = ft_atoi(line);
	if (!lem->nb_ants)
		end_with_error(lem);
	return (1);
}

/*
**	At the first entry into the function
**	we write down the number of ants. 
**	Then we check for the presence of comment,
**	room or link signs in the line.
*/

static void parsing_map(t_lem *lem, char *line, t_coord *point)
{
	int rt;

	rt = 1;
	if (!lem->map)
		rt = check_ants(lem, line);
	else if (ft_strstr(line, "#"))
		rt = save_point(lem, line, point);
	else if (!ft_strstr(line, "-") && !ft_strstr(line, "##"))
		rt = save_room(lem, line, point);
	else
		rt = save_links(lem, line);
	save_map(lem, line);
	if (!rt)
		end_with_error(lem);
}

/*
**	Read map with GNL and fill general structure
*/

int	parsing(t_lem *lem)
{
	int		gnl;
	char	*line;
	t_coord	point;

	point.start = 0;
	point.end = 0;
	while ((gnl = get_next_line(0, &line)) > 0)
	{
		parsing_map(lem, line, &point);
		ft_strdel(&line);
	}
	if (gnl < 0)
		end_with_error(lem);
	free(line);
	if (!lem->begin_room || !lem->start || !lem->end || !lem->start->begin_link || !lem->end->begin_link)
		end_with_error(lem);
	free(line);
	return (1);
}
