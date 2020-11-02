/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:27:22 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/02 19:31:28 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
#define LEM_IN_H

#include "libft.h"
#include "errno.h"
#include "stdio.h"

typedef struct	s_coord
{
	int start;
	int end;
}				t_coord;

typedef struct	s_link
{
	char			*name;
	int				weight;
	struct s_link	*next;
}				t_link;

typedef struct	s_room
{
	char			*name;
	int				link_count;
	t_link			*begin_link;
	struct s_room	*same_hash;
	struct s_room	*room_copy;
	struct s_room	*next;
	struct s_room	*prev;
}				t_room;

typedef struct	s_lem
{
	int		nb_ants;
	int		nb_rooms;
	char	*map;
	t_room *begin_room;
	t_room	*start;
	t_room	*end;
	t_room	**rooms;
}				t_lem;

void			end_with_error(t_lem *lem, int error, char **arr);
int				save_room(t_lem *lem, char *line, t_coord *point);
int				save_links(t_lem *lem, char *line);
int				hash(int size, char *name);
int				parsing(t_lem *lem);

#endif