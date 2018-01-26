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
**
*/

int			find_distance(t_room *room_a, t_room *room_b)
{
	int	distance;

	distance = sqrt(pow(room_b->x_coord - room_a->x_coord, 2) +
		pow(room_b->y_coord - room_a->y_coord, 2));
	return (distance);
}

/*
**
*/

void		learn_connection(t_swarm *swarm)
{
	t_tunnel 	*new_tunnel;
	// char		*look;
	t_tunnel	colony_ptr;
	char		**linked_rooms;

	new_tunnel = tunnel_lstnew(void);
	// look = swarm->sight;
	colony_ptr = swarm->colony;
	linked_rooms = ft_strsplit(swarm->sight);
	while(ft_strcmp(colony_ptr->name, linked_rooms[1]))
		colony_ptr = colony_ptr->next;
	new_tunnel->to_room = colony_ptr;
	colony_ptr = swarm->colony;
	while(ft_strcmp(colony_ptr->name, linked_rooms[0]))
		colony_ptr = colony_ptr->next;
	colony_ptr->tunnels = new_tunnel;

}

/*
**allocate for a new node of the room list
**copy the name and the coordinates of the room from the output into the node
**add the pointer to the new node to the end of the list in the main struct
*/

void		memorize_rooms(t_swarm *swarm, int room_type)
{
	int		i;
	t_room	*new_room;
	char	*look;
	t_room	colony_ptr;

	i = 0;
	new_room = room_lstnew(void);
	look = swarm->sight;
	colony_ptr = swarm->colony;
	while (look[i] != ' ')
		i++;
	new_room->name = ft_strnew(i);
	i = 0;
	while (*look != ' ')
		new_room->name[i++] = *look++;
	look++;
	ft_atoi(look) = new_room->x_coord;
	while (ft_isdigit(*look))
		look++;
	look++;
	ft_atoi(look) = new_room->y_coord;
	if (list == NULL)
		new_room = colony_ptr;
	else
	{
		room_lstiter(colony_ptr);
		colony_ptr->next = new_room;
	}
}

int			main()
{
	t_swarm	swarm;
	char	done;
	char	room_type;

	ft_bzero(swarm, sizeof(s_swarm));
	done = 0;
	room_type = -1;
	while (get_next_line(STDIN_FILENO, &swarm.sight) > 0)
	{
		room_type = -1;
		if (done < 2)
		{
			if (ft_strstr(sight, "#")) //ft_strchr
			{
				room_type = (ft_strstr(swarm.sight, "##start")) ? 1 : room_type;
				room_type = (ft_strstr(swarm.sight, "##end")) ? 0 : room_type;
				ft_memdel((void**)&swarm.sight);
				get_next_line(STDIN_FILENO, &swarm.sight)
				if (room_type == 0|| room_type == 1)
					done += 1;
			}
			else
				room_type = 2;
			if (room_type != -1)
				memorize_rooms(&swarm, room_type);
		}
		else if (done >= 2)
		{
			if (ft_strstr(swarm.sight, "#")) //then skip line
			{
				ft_memdel((void**)&swarm.sight);
				get_next_line(STDIN_FILENO, &swarm.sight)
			}
			learn_connection(&swarm);
		}
		ft_memdel((void**)&swarm.sight);
	}
	find_paths(&swarm);	//sergios part
	send_ants(&swarm);	//also sergios part ?
	destroy_colony(&swarm);
}
