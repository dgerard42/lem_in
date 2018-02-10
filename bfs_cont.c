/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_cont.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 18:01:23 by sbalcort          #+#    #+#             */
/*   Updated: 2018/02/09 18:01:26 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_list(t_queue *head)
{
	t_queue *temp;

	while (head)
	{
		temp = head;
		ft_bzero(temp, sizeof(temp));
		free(temp);
		head = head->next;
	}
}

/*
**t_queue      *new_queue(t_room *start, t_room *end)
**makes new item for queue
**start room and end room
*/

t_queue		*new_queue(t_room *start, t_room *end, int dist)
{
	t_queue	*temp;

	temp = (t_queue*)malloc(sizeof(t_queue));
	ft_bzero(temp, sizeof(t_queue));
	temp->distance = dist;
	temp->origin = start;
	temp->destination = end;
	return (temp);
}

/*
**t_queue     *init_queue(t_swarm *swarm)
**finds the starting room in linked list for initial queue
*/

t_queue		*init_queue(t_swarm *swarm)
{
	t_queue	*temp;
	t_room	*tmp_room;

	tmp_room = swarm->colony;
	while (tmp_room != NULL)
	{
		if (tmp_room->room_type == 1)
			break ;
		tmp_room = tmp_room->next;
	}
	temp = new_queue(NULL, tmp_room, 0);
	temp->destination->visited = true;
	return (temp);
}

/*
**traverse linked list queue for comparing current room to
**rooms already checked in queue
*/

int			node_already_visited(t_queue *current, t_room *room)
{
	while (current != NULL)
	{
		if (current->destination != NULL && room->visited == true)
			return (1);
		current = current->next;
	}
	return (0);
}

/*
**this function adds to end of queue
** the current path
*/

void		add_to_queue(t_queue *current, t_room *rm)
{
	int		dist;
	t_queue	*tmp;
	t_queue	*last;

	dist = current->distance;
	rm->visited = true;
	last = current;
	while (last->next != NULL)
		last = last->next;
	tmp = new_queue(current->destination, rm, (dist + 1));
	last->next = tmp;
	tmp->last = last;
}
