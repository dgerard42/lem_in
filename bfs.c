/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:12:41 by sbalcort          #+#    #+#             */
/*   Updated: 2018/02/09 11:12:44 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue		*get_last_ptr(t_queue *head)
{
	while (head->next != NULL)
		head = head->next;
	return (head);
}

char		**assemble_path(t_queue *head)
{
	t_queue	*tmp;
	int		count;
	int		temp;
	char	**path;
	t_room	*previous;

	tmp = get_last_ptr(head);
	count = tmp->distance + 2;
	temp = 0;
	path = (char**)malloc(sizeof(char*) * count);
	while (temp < count - 1)
	{
		path[temp] = ft_strdup(tmp->destination->name);
		temp = ((tmp->destination->room_type == 1) ? (temp + 1) : temp);
		if (tmp->destination->room_type == 1)
			break ;
		previous = tmp->origin;
		tmp = head;
		while (tmp->destination != previous)
			tmp = tmp->next;
		temp++;
	}
	path[temp] = NULL;
	return (path);
}

/*
**asses if the room has be visited before.
**if so, will calculate if current possible link has shorter steps
*/

int			current_link_shorter(t_queue *head, t_queue *current, t_room *room)
{
	t_queue	*tmp;

	while (head && head->destination != room)
		head = head->next;
	if (!head)
		return (1);
	if ((head->destination == room) &&
	((current->distance + 1) < head->distance))
	{
		tmp = head;
		tmp->last->next = tmp->next;
		tmp->next->last = tmp->last;
		free(tmp);
		return (1);
	}
	return (0);
}

void		print_path(char **strings)
{
	int	i;

	i = 0;
	ft_putchar('\n');
	while (strings[i] != NULL)
		ft_putendl(strings[i++]);
	ft_putchar('\n');
}

/*
**last took off here
**find a way to back check with previous queued items
**if current assesment is a shorter path place new item in proper place of queue
*/

void		bfs(t_swarm *swarm)
{
	t_queue		*head;
	t_queue		*current;
	t_tunnel	*tmp_tunnel;

	head = init_queue(swarm);
	current = head;
	while (current)
	{
		tmp_tunnel = current->destination->tunnels;
		while (tmp_tunnel)
		{
			if (current_link_shorter(head, current, tmp_tunnel->to_room))
				add_to_queue(current, tmp_tunnel->to_room);
			if (tmp_tunnel->to_room->room_type == 0)
			{
				swarm->path = assemble_path(head);
				free_list(head);
				return ;
			}
			tmp_tunnel = tmp_tunnel->next;
		}
		current = (current->next ? current->next : NULL);
	}
	free_list(head);
}
