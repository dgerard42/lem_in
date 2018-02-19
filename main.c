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
**declare new base struct on the stack and zero it out
**read through the input to stdin using gnl & freeing as you go
**check every line read to see if it is a room or a connection
**send lines to their appropriate functions with room types
**skip lines with comments or commands
*/

int				valid_link(t_swarm *swarm)
{
	int		error;
	char	*link_ptr;
	char	**linked_rooms;

	error = 1;
	link_ptr = swarm->sight;
	if (*link_ptr == '-')
		return (0);
	while (*link_ptr != '-')
		link_ptr++;
	link_ptr++;
	if (*link_ptr == '\0')
		return (0);
	linked_rooms = ft_strsplit(swarm->sight, '-');
	if (ft_strchr(linked_rooms[0], ' ') || ft_strchr(linked_rooms[1], ' '))
		return (0);
	error = learn_connection(swarm, linked_rooms[0], linked_rooms[1]);
	if (error != 0)
		error = learn_connection(swarm, linked_rooms[1], linked_rooms[0]);
	ft_2dfreearray((void**)linked_rooms, 2);
	if (error == 0)
		return (0);
	return (1);
}

int				learn_room_type(t_swarm *swarm)
{
	int room_type;

	room_type = (ft_strstr(swarm->sight, "##start")) ? 1 : 2;
	room_type = (ft_strstr(swarm->sight, "##end")) ? 0 : room_type;
	ft_memdel((void**)&swarm->sight);
	if (get_next_line(swarm->fd, &swarm->sight) > 0)
		ft_printf("%s\n", swarm->sight);
	return (room_type);
}

int				scan_colony(t_swarm *swarm)
{
	int		room_type;

	room_type = 2;
	ft_printf("%s\n", swarm->sight);
	if (ft_strchr(swarm->sight, '#') && !(ft_strstr(swarm->sight, "##start"))
		&& !(ft_strstr(swarm->sight, "##end")))
	{
		ft_memdel((void**)&swarm->sight);
		if (get_next_line(swarm->fd, &swarm->sight) > 0)
			ft_printf("%s\n", swarm->sight);
	}
	if (swarm->sight != NULL && (ft_strstr(swarm->sight, "##start")
		|| (ft_strstr(swarm->sight, "##end"))))
		room_type = learn_room_type(swarm);
	if (swarm->sight != NULL && !(ft_strchr(swarm->sight, '#'))
		&& !(ft_strchr(swarm->sight, '-')))
		if (!(memorize_rooms(swarm, room_type)))
			return (0);
	if (swarm->sight != NULL && ft_strchr(swarm->sight, '-') &&
		!(valid_link(swarm)))
		return (0);
	return (1);
}

void			check_ants(t_swarm *swarm)
{
	ft_bzero((void *)swarm, sizeof(struct s_swarm));
	swarm->fd = open("our_maps/map_1.map", O_RDONLY);
	if (get_next_line(swarm->fd, &swarm->sight) > 0)
	{
		swarm->ants = ft_atoi(swarm->sight);
		ft_printf("%s\n", swarm->sight);
		ft_memdel((void**)&swarm->sight);
	}
}

int				main(void)
{
	t_swarm	swarm;
	int		error;

	error = 1;
	check_ants(&swarm);
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
	// check_paths(swarm.path);
	// check_inputs(&swarm);
	destroy_colony(&swarm);
}
