/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 20:11:57 by dgerard           #+#    #+#             */
/*   Updated: 2018/01/20 20:11:58 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <math.h>
# include <stdbool.h>

typedef	struct		s_room
{
	char		*name;
	char		room_type; // 1 = start, 0 = end, 2 = middle
	int			x_coord;
	int			y_coord;
	bool		visited;
	int			connections; //number of tunnels there are, so you know how far
	s_tunnel	*tunnels; //the head of the linked list of tunnels which are connected to the room
	s_room		*next;    //pointers to next malloced room
	// int		**tunnel_len; //for each correspoindingly indexed connected room, distance of that tunnel
	//^^^ nvm, just figure out this shit by using the coords and distance formula
}					t_room;

typedef	struct		s_tunnel
{
	s_room		*to_room;
	int			length;
	s_tunnel	*next;
}					t_tunnel;

typedef	struct		s_swarm
{
	int		ants;
	int		rooms; //how many instances of the room struct have been allocated
	s_room	*colony; //pointer to the head element
	char	*sight;
	char	**path; //1st lvl = room names in path, 2nd lvl = room names
}					t_swarm;

void		room_lstiter(t_room *room);
void		tunnel_lstiter(t_tunnel *tunnel);
t_room		*room_lstnew(void);
t_tunnel	*tunnel_lstnew(void);

#endif
