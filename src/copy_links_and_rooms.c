/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_links_and_rooms.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:57:40 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/11 13:59:20 by Gimad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link		*copy_links(t_lem *lem, t_link *copy_link,
							t_link *original_link)
{
	t_link	*tmp;

	tmp = copy_link;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = (t_link *)malloc(sizeof(t_link))))
		end_with_error(lem);
	tmp = tmp->next;
	tmp->name = ft_strdup(original_link->name);
	tmp->weight = original_link->weight;
	tmp->on = 1;
	tmp->next = NULL;
	return (tmp);
}

t_room		*copy_room(t_lem *lem, t_room *original)
{
	t_room	*copy;

	if (!(copy = (t_room*)malloc(sizeof(t_room))))
		end_with_error(lem);
	copy->name = ft_strdup(original->name);
	copy->next = NULL;
	copy->begin_link = NULL;
	copy->same_hash = NULL;
	copy->room_copy = NULL;
	copy->link_count = original->link_count;
	copy->prev = NULL;
	copy->queue = NULL;
	copy->in_queue = 0;
	copy->bellman_ford = 0;
	return (copy);
}
