/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:27:22 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/10 17:25:02 by jconcent         ###   ########.fr       */
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
	int				on;
	int				in_way;
	struct s_link	*next;
}				t_link;

typedef struct	s_room
{
	char			*name;
	int				link_count;
	int				in_queue;
	int				bellman_ford;
	t_link			*begin_link;
	struct s_room	*same_hash;
	struct s_room	*room_copy;
	struct s_room	*queue;
	struct s_room	*next;
	struct s_room	*prev;
}				t_room;

typedef struct s_path
{
	char *name;
	int ant_name;
	struct s_path *forward;
	struct s_path *backward;
}	t_path;

typedef struct s_way
{
	int len;
	int ants;
	int on;
	struct s_way *next;
	t_path *path;
}	t_way;

typedef struct s_sol
{
	int index;
	int n_ways;
	int steps;
	t_way *ways;
	struct s_sol *next;
}	t_sol;

typedef struct s_map
{
	char *content;
	struct s_map *next;
} t_map;

typedef struct	s_lem
{
	int		nb_ants;
	int		nb_rooms;
	t_map	*map;
	t_room	*begin_room;
	t_room	*start;
	t_room	*end;
	t_room	**rooms;
	t_sol	*solutions;
}				t_lem;

void			end_with_error(t_lem *lem, int error, char **arr);
int				save_room(t_lem *lem, char *line, t_coord *point);
int				save_links(t_lem *lem, char *line);
int				hash(int size, char *name);
int				parsing(t_lem *lem);
int		bf_algorithm(t_lem *lem);
int		finding_paths(t_lem *lem);
int		check_copy(t_room *current_room, char *link_name);
void	short_way(t_lem *lem);
void	clean_queue(t_lem *lem);
void	graph_recovery(t_lem *lem, t_sol *prev_sol);
int	find_crossover(t_lem *lem, t_way *way);
void	free_way(t_way *tmp_way, t_path *tmp_path);
t_way *new_way(t_lem *lem);
void	find_new_ways(t_lem *lem, t_link *next_room);
void	in_way_recovery(t_link *next_room);
void	s_algorithm(t_lem *lem);
t_room		*copy_room(t_lem *lem, t_room *original);
t_link		*copy_links(t_lem *lem, t_link *copy_link, t_link *original_link);
void	init_sol(t_sol *solutions);
void	print_map(t_lem *lem);
void	run_ants(t_lem *lem, t_way *w, int i);

#endif