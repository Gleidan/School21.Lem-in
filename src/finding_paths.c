/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:45:23 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/11 14:00:50 by Gimad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		extend_ants(t_lem *lem, t_sol *sol, int max_len)
{
	int		n;
	int		s;
	t_way	*tmp;

	s = max_len - 1;
	n = lem->nb_ants;
	tmp = sol->ways;
	while (tmp && n > 0 && sol->n_ways != 1)
	{
		if (tmp->on)
		{
			tmp->ants = (n < max_len - tmp->len) ? n : max_len - tmp->len;
			n -= tmp->ants;
		}
		tmp = tmp->next;
	}
	s += (n % sol->n_ways == 0) ? n / sol->n_ways : n / sol->n_ways + 1;
	tmp = sol->ways;
	while (n-- > 0)
	{
		++tmp->ants;
		tmp = (tmp->next) ? tmp->next : sol->ways;
	}
	sol->steps = s;
}

static void		count_steps(t_lem *lem, t_sol *sol)
{
	int		max_len;
	int		valid_space;
	t_way	*tmp;

	valid_space = 0;
	tmp = sol->ways;
	max_len = tmp->len;
	if (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->len > max_len)
			max_len = tmp->len;
		tmp = tmp->next;
	}
	tmp = sol->ways;
	while (tmp)
	{
		valid_space += max_len - tmp->len;
		tmp = tmp->next;
	}
	extend_ants(lem, sol, max_len);
}

/*
**	The found paths are suitable
**	as long as the number of steps
**	of the found path is less than
**	the previous one.
*/

static int		compare_solutions(t_lem *lem)
{
	t_sol *s_tmp;
	t_way *w_tmp;
	t_way *w_ptr;

	if (!lem->solutions || !lem->solutions->next)
		return (1);
	else if (lem->solutions->steps < lem->solutions->next->steps)
		return (1);
	else
	{
		s_tmp = lem->solutions;
		w_tmp = s_tmp->ways;
		while (w_tmp)
		{
			w_ptr = w_tmp->next;
			free_way(w_tmp, w_tmp->path);
			w_tmp = w_ptr;
		}
		lem->solutions = lem->solutions->next;
		free(s_tmp);
		return (0);
	}
}

/*
**	While we can create optimized paths
**	we get the path thanks to the bs_algo,
**	then we get shortest way and exclude
**	intersections
*/

int				finding_paths(t_lem *lem)
{
	while (compare_solutions(lem))
	{
		if (lem->solutions)
			s_algorithm(lem);
		if (!(bf_algorithm(lem)))
			break ;
		short_way(lem);
		if (!lem->solutions->next)
			clean_queue(lem);
		count_steps(lem, lem->solutions);
	}
	if (!lem->solutions)
		end_with_error(lem);
	print_map(lem);
	run_ants(lem, lem->solutions->ways, 0);
	return (0);
}
