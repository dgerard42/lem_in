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

void		room_lstiter(t_room *room)
{
	while (room != NULL)
		room = room->next;
}

void		tunnel_lstiter(t_tunnel *tunnel)
{
	while (tunnel != NULL)
		tunnel = tunnel->next;
}

t_room		*room_lstnew(void)
{
	t_room *new_room;

	new_room = (s_room*)malloc(sizeof(s_room));
	ft_bzero(new_room, sizeof(s_room));
	return (new_room);
}

t_tunnel	*tunnel_lstnew(void)
{
	t_room *new_tunnel;

	new_tunnel = (s_tunnel*)malloc(sizeof(s_tunnel));
	ft_bzero(new_tunnel, sizeof(s_tunnel));
	return (new_tunnel);
}
