/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:16:17 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/12 10:59:47 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_path(int ant_name, char *path_name, int n)
{
	if (n)
		write(1, " ", 1);
	ft_printf("L%d-%s", ant_name, path_name);
}

static void		print_ways(t_lem *lem, int n)
{
	t_way	*way;
	t_path	*path;

	way = lem->solutions->ways;
	while (way)
	{
		path = way->path;
		while (path->ant_name <= 0 && path->f != way->path->b)
			path = path->f;
		while (path->ant_name > 0)
		{
			print_path(path->ant_name, path->name, n++);
			path = path->f;
		}
		way = way->next;
	}
	write(1, "\n", 1);
}

static int		not_finished(t_way *ways)
{
	t_way	*tmp;
	int		rt;

	rt = 1;
	tmp = ways;
	while (tmp)
	{
		if (tmp->path->f->ant_name == -1 ||
			(tmp->path->f == tmp->path->b && tmp->ants <= 0))
			rt = 0;
		else
			return (1);
		tmp = tmp->next;
	}
	return (rt);
}

void			run_ants(t_lem *lem, t_way *w, int i)
{
	t_path *pwalk;

	while (not_finished(lem->solutions->ways))
	{
		w = lem->solutions->ways;
		while (w)
		{
			pwalk = w->path;
			while (pwalk != w->path->b)
			{
				if (pwalk->f == w->path->b && w->ants > 0)
				{
					pwalk->ant_name = ++i;
					w->ants--;
				}
				else if (pwalk->f == w->path->b && w->ants <= 0)
					pwalk->ant_name = -1;
				else
					pwalk->ant_name = pwalk->f->ant_name;
				pwalk = pwalk->f;
			}
			w = w->next;
		}
		print_ways(lem, 0);
	}
}
