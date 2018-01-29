/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 14:46:35 by dgerard           #+#    #+#             */
/*   Updated: 2018/01/27 14:46:38 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lem_in.h"
# include <fcntl.h>

void			check_inputs(t_swarm *swarm)
{
	t_room *colony_ptr;

	colony_ptr = swarm->colony;
	while (colony_ptr != NULL)
	{
		ft_printf("ROOM NAME: %s\n", colony_ptr->name);
		while (colony_ptr->tunnels != NULL)
		{
			ft_printf("TUNNEL FROM %s to %s\n", colony_ptr->name, ((colony_ptr->tunnels)->to_room)->name);
			colony_ptr->tunnels = (colony_ptr->tunnels)->next;
		}
		colony_ptr = colony_ptr->next;
	}
}

void				open_testfiles(t_swarm *swarm)
{
	swarm->fd = open("maps/map_0.map", O_RDONLY);
}
