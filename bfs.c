#include "lem_in.h"

typedef struct		s_queue
{
	struct s_room	*origin;        //for tracking origin linking node
	struct s_room	*destination;   //for tracking destination linking node
    int             distance;          //for counting number of nodes between


	struct t_queue	*next;          //tracking within queue
	struct t_queue	*last;
}					t_queue;

/*
**t_queue      *new_queue(t_room *start, t_room *end)
**makes new item for queue
**start room and end room
*/

t_queue      *new_queue(t_room *start, t_room *end, int dist)
{
    t_queue  *temp;

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

t_queue     *init_queue(t_swarm *swarm)
{
    t_queue     *temp;
    t_room      *tmp_room;

   tmp_room = swarm->colony;
    while (tmp_room->room_type != 1)
        tmp_room = tmp_room->next;
    temp = new_queue(tmp_room, NULL, 0);
    return (temp);
}

/*
**traverse linked list queue for comparing current room to 
**rooms already checked in queue
*/

int     node_already_visited(t_queue *current, t_room *room)
{
    while (current)
    {
        if (current->destination == room && current->destination->visited == true)
            return (1);
        current->next;
    }
    return (0);
}

/*
**this function adds to end of queue 
** the current path
*/

void    add_to_queue(t_queue *head, t_queue *current, t_room *rm)
{
    int    dist;
    t_queue *tmp;

    dist = current->distance;
    rm->visited = true;
    while (current->next != NULL)
        current = current->next;
    tmp = new_queue(current->destination, rm, (dist + 1));
    current->next = tmp;
    tmp->last = current;
}

void        assemble_path(t_queue *head, t_swarm *swarm)
{
    t_queue     *tmp;
    int         i;
    int         count;
    t_queue     *last;

    tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    count = tmp->distance + 2;
    swarm->path = (char**)malloc(sizeof(char*) * count);
    swarm->path[--count] = NULL;
    while (count >= 0)
    {
        swarm->path[count--] = ft_strnew(tmp->destination->name);
        last = tmp->origin;
        while (tmp->destination != last)
            tmp = tmp->last;
    }
}


// last took off here
//find a way to back check with previous queued items
//if current assesment is a shorter path place new item in proper place of queue

void		bfs(t_swarm *swarm)
{
    t_queue     *head;
    t_queue     *current;
    t_tunnel    *tmp_tunnel;
    t_room      *tmp_room;
    t_queue     *tmp_q;

    tmp_room = swarm->colony;
    head = init_queue(swarm);
    current = head;
    while (tmp_room != NULL)     //while all nodes not visited //change this to if current node is == end node.
    {
        while (tmp_tunnel != NULL)
        {
            tmp_tunnel = tmp_room->tunnels;
            if (node_already_visted(head, tmp_tunnel->to_room))           //if already visited continue
                continue ;
            else
                add_to_queue(current, tmp_tunnel->to_room);     //adding room to queue
            if (tmp_tunnel->to_room->room_type == 0)
            {
                assemble_path(head, swarm);
                return ;
            }
        }
        tmp_room = tmp_room->next;
    }
}
