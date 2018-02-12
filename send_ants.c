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

// void				no_path(void)
// {
// 	ft_printf("ERROR, no possible path\n");
// }
//
int					valid_link(char *link)
{
	char *link_ptr;

	link_ptr = link;
	if (*link == '-')
		return (0);
	while (*link != '-')
		link++;
	link++;
	if (*link == '\0')
		return (0);
	return (1);
}

int					handle_errors(t_swarm *swarm)
{
	t_room	*colony_ptr;

	colony_ptr = swarm->colony;
	if (swarm->colony == NULL)
		return (0);
	if (swarm->ants == 0)
		return (0);
	while (colony_ptr != NULL && colony_ptr->room_type != 1)
		colony_ptr = colony_ptr->next;
	if (colony_ptr == NULL)
		return (0);
	colony_ptr = swarm->colony;
	while (colony_ptr != NULL && colony_ptr->room_type != 0)
		colony_ptr = colony_ptr->next;
	if (colony_ptr == NULL)
		return (0);
	return (1);
}

int					path_length(char **rooms)
{
	int	room_number;

	room_number = 0;
	while (rooms[room_number] != '\0')
		room_number++;
	return (room_number);
}

void				lone_ant(char **path)
{
	int		room;

	room = path_length(path) - 2;
	while (room >= 0)
	{
		ft_printf("L%d-%s\n", 1, path[room]);
		room--;
	}
}

void				send_ants(t_swarm *swarm)
{
	int		sent_ants;
	int		done_ants;
	int		printed_ants;
	int		room_indx;
	int		path_len;

	sent_ants = 0;
	done_ants = 0;
	path_len = path_length(swarm->path);
	while (done_ants < swarm->ants)
	{
		printed_ants = done_ants;
		sent_ants = (sent_ants < swarm->ants) ? sent_ants + 1 : sent_ants;
		room_indx = (path_len - sent_ants > 0) ? (path_len - sent_ants) - 1 : 0;
		while (printed_ants < sent_ants && room_indx < path_len)
		{
			// if (room_indx != path_len - 1)
				ft_printf("L%d-%s ", printed_ants + 1, swarm->path[room_indx]);
			if (room_indx == 0)
				done_ants++;
			printed_ants++;
			room_indx++;
		}
		ft_printf("\n");
	}
}
