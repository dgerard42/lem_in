/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learn_colony.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 21:18:33 by dgerard           #+#    #+#             */
/*   Updated: 2018/02/17 21:18:37 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**distance formula for finding the distance between 2 rooms
*/

int				find_distance(t_room *room_a, t_room *room_b)
{
	int	distance;

	distance = sqrt(pow(room_b->x_coord - room_a->x_coord, 2) +
		pow(room_b->y_coord - room_a->y_coord, 2));
	return (distance);
}

/*
**allocate for the new tunnel node
**traverse room linked list until you find the second room in the link
**save that room to the to_room pointer in thw new tunnel node
**traverse linked list again until you find the first room in the link
**find the distance between linked rooms, save to length in new tunnel node
**save the new tunnel node to the end of the tunnel linked list of starting r.
*/

int				learn_connection(t_swarm *swarm, char *room_a, char *room_b)
{
	t_tunnel	*new_tunnel;
	t_room		*colony_ptr;

	new_tunnel = tunnel_lstnew();
	colony_ptr = swarm->colony;
	while (colony_ptr != NULL && colony_ptr->next != NULL &&
			ft_strcmp(colony_ptr->name, room_a))
		colony_ptr = colony_ptr->next;
	new_tunnel->to_room = colony_ptr;
	colony_ptr = swarm->colony;
	while (colony_ptr != NULL && colony_ptr->next != NULL &&
			ft_strcmp(colony_ptr->name, room_b))
		colony_ptr = colony_ptr->next;
	if (colony_ptr != NULL)
	{
		new_tunnel->length = find_distance(colony_ptr, new_tunnel->to_room);
		new_tunnel->next = colony_ptr->tunnels;
		colony_ptr->tunnels = new_tunnel;
	}
	return (1);
}

/*
**allocate for a new node of the room list
**copy the name and the coordinates of the room from the output into the node
**add the pointer to the new node to the end of the list in the main struct
*/

int				save_name(t_swarm *swarm, t_room *new_room)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (swarm->sight[i] != ' ' && swarm->sight[i] != '\0'
		&& !(swarm->sight[i] == 'L' && i == 0))
		i++;
	if (swarm->sight[i] != ' ')
		return (0);
	new_room->name = ft_strnew(i);
	i = 0;
	while (swarm->sight[j] != ' ' && swarm->sight[j] != '\0')
		new_room->name[i++] = swarm->sight[j++];
	j++;
	return (j);
}

int				save_coords(t_room *new_room, char *look)
{
	new_room->x_coord = ft_atoi(look);
	while (*look != '\0' && ft_isdigit(*look))
		look++;
	if (*look != ' ')
		return (0);
	look++;
	if (!(ft_isdigit(*look)))
		return (0);
	new_room->y_coord = ft_atoi(look);
	while (*look != '\0' && ft_isdigit(*look))
		look++;
	if (*look != '\0')
		return (0);
	return (1);
}

int				memorize_rooms(t_swarm *swarm, int room_type)
{
	int		i;
	t_room	*new_room;
	char	*look;

	new_room = room_lstnew(room_type);
	look = swarm->sight;
	if (!(i = save_name(swarm, new_room)))
		return (0);
	look += i;
	if (!(ft_isdigit(*look)))
		return (0);
	if (!(save_coords(new_room, look)))
		return (0);
	new_room->next = swarm->colony;
	swarm->colony = new_room;
	return (1);
}
