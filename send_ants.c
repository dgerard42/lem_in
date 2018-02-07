/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 13:16:43 by dgerard           #+#    #+#             */
/*   Updated: 2018/02/02 13:16:58 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				handle_errors(t_swarm *swarm)
{
	t_room	*colony_ptr;

	colony_ptr = swarm->colony;
	if (swarm->colony == NULL)
		return (0);
	if (swarm->ants == 0)
		return (0);
	while (colony_ptr != NULL && colony_ptr->room_type != 1)
		colony_ptr = colony_ptr->next;
	if (colony_ptr->room_type != 1)
		return(0);
	colony_ptr = swarm->colony;
	while (colony_ptr != NULL && colony_ptr->room_type != 0)
		colony_ptr = colony_ptr->next;
	if (colony_ptr->room_type != 0)
		return(0);
	return (1);
}

int					path_length(char **rooms)
{
	int	room_number;

	room_number = 0;
	while (rooms[room_number] != '\0')
		room_number++;
	ft_printf("PATH LENGTH: %d\n", room_number);
	return(room_number);
}

void				send_ants(t_swarm *swarm)
{
	int		sent_ants;
	int		done_ants;
	int		printed_ants;
	int		room_index;
	int		path_len;

	sent_ants = 0;
	done_ants = 0;
	path_len = path_length(swarm->path);
	while (done_ants < swarm->ants)
	{
		printed_ants = done_ants;
		sent_ants = (sent_ants < swarm->ants) ? sent_ants + 1 : sent_ants;
		room_index = (path_len - sent_ants > 0) ? (path_len - sent_ants) - 1 : 0;
		while (printed_ants < sent_ants && room_index < path_len)
		{
			if (room_index != path_len - 1)
				ft_printf("L%d-%s ", printed_ants + 1, swarm->path[room_index]);
			if (room_index == 0)
				done_ants++;
			printed_ants++;
			room_index++;
		}
		ft_printf("\n");
	}
}
