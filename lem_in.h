/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 20:11:57 by dgerard           #+#    #+#             */
/*   Updated: 2018/03/10 18:39:37 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <math.h>
# include <stdbool.h>

/*
**room type = 1 = start, 0 = end, 2 = middle
**tunnels =head of the linked list of tunnels which are connected to the room
**next = pointers to next malloced room
*/

typedef	struct		s_room
{
	char			*name;
	int				room_type;
	int				x_coord;
	int				y_coord;
	bool			visited;
	struct s_tunnel	*tunnels;
	struct s_room	*next;
}					t_room;

typedef	struct		s_tunnel
{
	struct s_room	*to_room;
	int				length;
	struct s_tunnel	*next;
}					t_tunnel;

/*
**rooms = how many instances of the room struct have been allocated, RM@END
**colony = pointer to the head element
**path = 1st lvl = room names in path, 2nd lvl = room names
**fd = REMOVE @END
*/

typedef	struct		s_swarm
{
	int				ants;
	int				rooms;
	struct s_room	*colony;
	char			*sight;
	char			**path;
	int				fd;
}					t_swarm;

/*
**origin tracks previous linknode.
**destination is next linknode
**distance is counting by number of links
**next and last are linking for BFS algorithm.
*/

typedef struct		s_queue
{
	struct s_room	*origin;
	struct s_room	*destination;
	int				distance;
	struct s_queue	*next;
	struct s_queue	*last;
}					t_queue;

t_room				*room_lstnew(int room_type);
t_tunnel			*tunnel_lstnew(void);
void				destroy_colony(t_swarm *swarm);
void				bfs(t_swarm *swarm);
void				send_ants(t_swarm *swarm);
int					handle_errors(t_swarm *swarm);
int					valid_link(t_swarm *swarm);
void				no_path(void);
void				free_list(t_queue *head);
t_queue				*new_queue(t_room *start, t_room *end, int dist);
t_queue				*init_queue(t_swarm *swarm);
void				add_to_queue(t_queue *current, t_room *rm);
void				lone_ant(char **path);
int					memorize_rooms(t_swarm *swarm, int room_type);
int					learn_connection(t_swarm *swarm, char *rooma, char *roomb);

/*
**test functions below. remove in the final version
*/

void				check_inputs(t_swarm *swarm);
void				open_testfiles(t_swarm *swarm, char *path);
void				check_paths(char **swarms);

#endif
