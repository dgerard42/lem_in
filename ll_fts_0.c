/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_fts_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:11:47 by dgerard           #+#    #+#             */
/*   Updated: 2018/01/25 17:11:58 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lem_in.h"

t_room		*room_lstnew(int room_type)
{
	t_room *new_room;

	new_room = (t_room*)malloc(sizeof(struct s_room));
	ft_bzero(new_room, sizeof(struct s_room));
	new_room->room_type = room_type;
	return (new_room);
}

t_tunnel	*tunnel_lstnew(void)
{
	t_tunnel *new_tunnel;

	new_tunnel = (t_tunnel*)malloc(sizeof(struct s_tunnel));
	ft_bzero(new_tunnel, sizeof(struct s_tunnel));
	return (new_tunnel);
}

void		destroy_colony(t_swarm *swarm)
{
	t_room		*colony_ptr;
	t_room		*next_room;
	t_tunnel	*next_tunnel;

	colony_ptr = swarm->colony;
	while (colony_ptr != NULL)
	{
		next_room = colony_ptr->next;
		while (colony_ptr->tunnels != NULL)
		{
			next_tunnel = (colony_ptr->tunnels)->next;
			free(colony_ptr->tunnels);
			colony_ptr->tunnels = next_tunnel;
		}
		free(colony_ptr);
		colony_ptr = next_room;
	}
}
