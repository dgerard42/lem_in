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

# include "lem_in.h"

/*
**distance formula for finding the distance between 2 rooms
*/

int			find_distance(t_room *room_a, t_room *room_b)
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
**save the new tunnel node to the end of the tunnel linked list of room it starts in
*/

void			learn_connection(t_swarm *swarm)
{
	t_tunnel 	*new_tunnel;
	t_room		*colony_ptr;
	char		**linked_rooms;

	new_tunnel = tunnel_lstnew();
	colony_ptr = swarm->colony;
	linked_rooms = ft_strsplit(swarm->sight, '-');
	while(ft_strcmp(colony_ptr->name, linked_rooms[1]))
		colony_ptr = colony_ptr->next;
	new_tunnel->to_room = colony_ptr;
	colony_ptr = swarm->colony;
	while(ft_strcmp(colony_ptr->name, linked_rooms[0]))
		colony_ptr = colony_ptr->next;
	new_tunnel->length = find_distance(colony_ptr, new_tunnel->to_room);
	new_tunnel->next = colony_ptr->tunnels;
	colony_ptr->tunnels = new_tunnel;
	ft_2dfreearray((void**)linked_rooms, 2);
}

/*
**allocate for a new node of the room list
**copy the name and the coordinates of the room from the output into the node
**add the pointer to the new node to the end of the list in the main struct
*/

void			memorize_rooms(t_swarm *swarm, int room_type)
{
	int		i;
	t_room	*new_room;
	char	*look;

	i = 0;
	new_room = room_lstnew(room_type);
	look = swarm->sight;
	while (look[i] != ' ')
		i++;
	new_room->name = ft_strnew(i);
	i = 0;
	while (*look != ' ')
		new_room->name[i++] = *look++;
	look++;
	new_room->x_coord = ft_atoi(look);
	while (ft_isdigit(*look))
		look++;
	look++;
	new_room->y_coord = ft_atoi(look);
	new_room->next = swarm->colony;
	swarm->colony = new_room;
}

/*
**declare new base struct on the stack and zero it out
**read through the input to stdin using gnl & freeing as you go
**check every line read to see if it is a room or a connection
**send lines to their appropriate functions with room types
**skip lines with comments or commands
*/

void			scan_colony(t_swarm *swarm)
{
	int	room_type;

	room_type =	2;
	if (ft_strchr(swarm->sight, '#'))
	{
		room_type = (ft_strstr(swarm->sight, "##start")) ? 1 : 2;
		room_type = (ft_strstr(swarm->sight, "##end")) ? 0 : 2;
		ft_memdel((void**)&swarm->sight);
		get_next_line(swarm->fd, &swarm->sight);
	}
	if (!(ft_strchr(swarm->sight, '#')) && !(ft_strchr(swarm->sight, '-')))
		memorize_rooms(swarm, room_type);
	if (ft_strchr(swarm->sight, '-'))
		learn_connection(swarm);
}

int				main(void)
{
	t_swarm	swarm;

	ft_bzero((void *)&swarm, sizeof(struct s_swarm));
	open_testfiles(&swarm); //RM @END
	while (get_next_line(swarm.fd, &swarm.sight) > 0)
	{
		scan_colony(&swarm);
 		ft_memdel((void**)&swarm.sight);
	}
	ft_printf("\n\t\tsergio's part start here \n");
	bfs(&swarm);	//sergios part
	// send_ants(&swarm);	//also sergios part ?
	//check_inputs(&swarm);
	destroy_colony(&swarm);
}
