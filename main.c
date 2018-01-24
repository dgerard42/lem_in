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

void		learn_connections(t_swarm *swarm)
{

}

void		memorize_rooms(t_swarm *swarm, int room_type)
{
	t_room	*new_room;
	char	*look;

	new_room = (s_room*)malloc(sizeof(s_room));
	ft_bzero(new_room, sizeof(s_room));
	look = swarm->sight;
	while (look != ' ')
	{
		
	}
	swarm->colony = (swarm->colony == NULL) ? new_room : swarm->colony;
	ft_memdel((void**)&swarm->sight);
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
	find_paths(&swarm);	//sergios part
	send_ants(&swarm);	//also sergios part ?
	destroy_colony(&swarm);
}
