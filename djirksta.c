
#include "lem_in.h"

typedef struct		s_queue
{
	struct s_room	*origin;
	struct s_room	*destination;
	int				distance;
	
	struct t_queue	*next;
	struct t_queue	*last;
}					t_queue;


t_queue		*new_queue(void)
{
	t_queue *temp;

	temp = (t_queue*)malloc(sizeof(t_queue));
	ft_bzero(temp, sizeof(temp));
	return (temp);
}

t_queue		*init_q(t_swarm *env)
{
	t_queue	*temp;
	t_room	*find_start;
	
	temp = new_queue(void);
	find_start = env->colony;
	while (find_start->room_type != 1)
		find_start = find_start->next;
	temp->end = find_start;
	return (temp);
}

t_queue		*make_new_queue(t_queue *current, t_room *room, int	distance)
{
	t_queue	*temp;

	temp = new_queue();
	temp->start = current->end;
	temp->end = room;
	temp->distance = current->distance + distance;
	return (temp);
}

/*
**below inserts item into the queue
**by assesing the distance or until end of list
*/

void		insert_queue(t_queue *item, t_queue *start)
{
	t_queue *temp;

	temp = start;
	while (temp->next != NULL && temp->distance < item->distance)
		temp = temp->next;
	if (temp->next != NULL)
	{
		start = start->next;
		item->next = start;
		start->last = item;
	}
	temp->next = item;
	item->last = temp;
}

/*
**Below: runs thru all the possible links for a given room
**will also check at end of tunnel for if its been visited
**if not, will mark visited and add to queue
*/

t_queue		*add_tunnels(t_queue *current, t_queue *end)
{
	t_tunnel	*tunnel;
	t_room		*room;
	t_queue		*temp;

	tunnel = current->end->tunnels;
	while (tunnel)
	{
		if (tunnel->to_room->visited == false)
		{
			tunnel->to_room->visited = true;
			temp = make_new_queue(current, tunnel->to_room, tunnel->length); //current start, to_room second
			insert_queue(temp, current);	//inserts new queue into list from current point and on
		}
		tunnel = tunnel->next;
	}
	return (room);
}

t_swarm		*dijkstra(t_swarm *env)
{
	t_queue	*start;
	t_queue	*current;		//represent the current room
	t_queue	*end;
	int		count;
	
	start = init_q(env);
	current = start;
	while (current)
	{
		end = add_tunnels(current, end);	//disects t_room *tunnels and tacs them to queue
		current = current->next;
	}
	//construct path from end room to start
}