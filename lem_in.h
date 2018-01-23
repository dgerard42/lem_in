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

typedef	struct		s_room
{
	char	*name;
	char	room_type; // 1 = start, 0 = end, 2 = middle
	int		x_coord;
	int		y_coord;
	bool	visited;
	int		connections; //number of tunnels there are, so you know how far
	s_room	**tunnels;    //pointers to other room structs
	// int		**tunnel_len; //for each correspoindingly indexed connected room, distance of that tunnel
}					t_room;

typedef	struct		s_swarm
{
	int		ants;
	int		rooms; //how many instances of the room struct have been allocated
	s_room	*colony; //pointer to the head element
	char	*sight;
	char	**paths; //first lvl = paths, 2nd lvl = room names in path, 3rd lvl = room names
}					t_swarm;

#endif
