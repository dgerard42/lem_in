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

t_queue      *new_queue(t_room *start, t_room *end)
{
    t_queue  *temp;

    temp = (t_queue*)malloc(sizeof(t_queue));
    ft_bzero(temp, sizeof(t_queue));
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
    temp = new_queue(tmp_room, NULL);
    return (temp);
}

void        *insert_queue()
{
}



/*
**counts all items in the queue
**if less than room count, returns 1
*/

int         all_nodes_not_visited(t_room *rooms)
{
    while (rooms != NULL)
    {
        if (rooms->visited == true)
            return (1);
        rooms = rooms->next;
    }
    return (0);
}

/*
**
**
*/

void		bfs(t_swarm *swarm)
{
    t_queue     *head;
    t_queue     *current;
    t_tunnel    *tmp_tunnel;
    t_room      *tmp_room;

    tmp_room = swarm->colony;
    head = init_queue(swarm);
    temp = new_queue(NULL, NULL); 
    while (all_nodes_not_visited(swarm->rooms))
    {
        tmp_tunnel = tmp_room->tunnels;
        while (tmp_tunnel != NULL)
        {
            if (node_already_visted(tmp))   //already visited continue
                compare the other visit && if current is shorter, replace it.
            else    //add to queue
                add item to end of queue with count + 1
        }
        tmp_room = tmp_room->next;
    }
}
