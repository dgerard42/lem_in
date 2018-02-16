/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 22:42:07 by dgerard           #+#    #+#             */
/*   Updated: 2018/01/24 09:21:35 by sbalcort         ###   ########.fr       */
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

int 			learn_connection(t_swarm *swarm, char *room_a, char *room_b)
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

int				memorize_rooms(t_swarm *swarm, int room_type)
{
	int		i;
	t_room	*new_room;
	char	*look;

	i = 0;
	new_room = room_lstnew(room_type);
	look = swarm->sight;
	while (look[i] != ' ' && look[i] != '\0' && look[i] != 'L')
		i++;
	if (look[i] != ' ')
		return (0);
	new_room->name = ft_strnew(i);
	i = 0;
	while (*look != ' ' && *look != '\0')
		new_room->name[i++] = *look++;
	look++;
	if (!(ft_isdigit(*look)))
		return (0);
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
	if (look[i] != '\0')
		return (0);
	new_room->next = swarm->colony;
	swarm->colony = new_room;
	return (1);
}

/*
**declare new base struct on the stack and zero it out
**read through the input to stdin using gnl & freeing as you go
**check every line read to see if it is a room or a connection
**send lines to their appropriate functions with room types
**skip lines with comments or commands
*/

int			scan_colony(t_swarm *swarm)
{
	int		room_type;
	char	**linked_rooms;
	int		error;

	error = 1;
	room_type = 2;
	ft_printf("%s\n", swarm->sight);
	if (ft_strchr(swarm->sight, '#') && !(ft_strstr(swarm->sight, "##start")) && !(ft_strstr(swarm->sight, "##end")))
	{
		ft_memdel((void**)&swarm->sight);
		if (get_next_line(swarm->fd, &swarm->sight) > 0)
			ft_printf("%s\n", swarm->sight);
	}
	if (swarm->sight != NULL && (ft_strstr(swarm->sight, "##start") || (ft_strstr(swarm->sight, "##end"))))
	{
		room_type = (ft_strstr(swarm->sight, "##start")) ? 1 : 2;
		room_type = (ft_strstr(swarm->sight, "##end")) ? 0 : room_type;
		ft_memdel((void**)&swarm->sight);
		if (get_next_line(swarm->fd, &swarm->sight) > 0)
			ft_printf("%s\n", swarm->sight);
	}
	if (swarm->sight != NULL && !(ft_strchr(swarm->sight, '#')) && !(ft_strchr(swarm->sight, '-')))
		if (!(memorize_rooms(swarm, room_type)))
			return (0);
	if (swarm->sight != NULL && ft_strchr(swarm->sight, '-') && valid_link(swarm->sight))
	{
		linked_rooms = ft_strsplit(swarm->sight, '-');
		if (ft_strchr(linked_rooms[0], ' ') || ft_strchr(linked_rooms[1], ' '))
			return (0);
		error = learn_connection(swarm, linked_rooms[0], linked_rooms[1]);
		if (error != 0)
			error = learn_connection(swarm, linked_rooms[1], linked_rooms[0]);
		ft_2dfreearray((void**)linked_rooms, 2);
		if (error == 0)
			return (0);
	}
	return (1);
}

int				main(void)
{
	t_swarm	swarm;
	int		error;

	error = 1;
	ft_bzero((void *)&swarm, sizeof(struct s_swarm));
	swarm.fd = open("maps/space_room", O_RDONLY);
	if (get_next_line(swarm.fd, &swarm.sight) > 0)
	{
		swarm.ants = ft_atoi(swarm.sight);
		ft_printf("%s\n", swarm.sight);
		ft_memdel((void**)&swarm.sight);
	}
	while (get_next_line(swarm.fd, &swarm.sight) > 0 && error == 1)
	{
		error = scan_colony(&swarm);
		ft_memdel((void**)&swarm.sight);
	}
	if (!(handle_errors(&swarm)) || error == 0)
	{
		destroy_colony(&swarm);
		ft_printf("ERROR\n");
		return (0);
	}
	bfs(&swarm);
	ft_printf("\n");
	if (swarm.path)
		((swarm.ants == 1) ? lone_ant(swarm.path) : send_ants(&swarm));
	else
		ft_printf("ERROR, no possible path\n");
	check_paths(swarm.path);
	destroy_colony(&swarm);
}
