/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 22:42:07 by dgerard           #+#    #+#             */
/*   Updated: 2018/01/19 22:42:08 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lem_in.h"

void		learn_connections(t_swarm *swarm)
{

}

void		memorize_rooms(t_swarm *swarm, int room_type)
{
	t_room	*new_room;
	char	*look;

	new_room = (s_node*)malloc(sizeof(s_node));
	ft_bzero(new_room, sizeof(s_node));
	look = swarm.sight;
	while (look != '')
}

int			main()
{
	t_swarm	swarm;
	char	done;
	char	room_type;

	done = 0;
	room_type = -1;
	while (get_next_line(STDIN_FILENO, &swarm.sight) > 0)
	{
		room_type = -1;
		if (done < 2)
		{
			if (ft_strstr(sight, "#"))
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
			learn_connections(&swarm);
		}
		ft_memdel((void**)&swarm.sight);
	}
	find_paths(&swarm);
	send_ants(&swarm);
	destroy_colony(&swarm);
}
