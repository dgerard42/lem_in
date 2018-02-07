#include "lem_in.h"

typedef struct		s_queue
{
	struct s_room	*origin;        //for tracking origin linking node
	struct s_room	*destination;   //for tracking destination linking node
    int             distance;          //for counting number of nodes between


	struct s_queue	*next;          //tracking within queue
	struct s_queue	*last;
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

t_queue     *init_queue(t_swarm *swarm) //here dont go down tunnels. go down colon ptr from swarm.
{
    t_queue     *temp;
    t_room      *tmp_room;

   tmp_room = swarm->colony;
    while (tmp_room != NULL)
    {
        if (tmp_room->room_type == 1)
            break ;
        tmp_room = tmp_room->next;
    }
    temp = new_queue(NULL , tmp_room, 0);
    temp->destination->visited = true;
    return (temp);
}

/*
**traverse linked list queue for comparing current room to
**rooms already checked in queue
*/

int     node_already_visited(t_queue *current, t_room *room)
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

void    add_to_queue(t_queue *current, t_room *rm)
{
    int     dist;
    t_queue *tmp;
    t_queue *last;

    dist = current->distance;
    rm->visited = true;
    last = current;
    while (last->next != NULL)
        last = last->next;
    tmp = new_queue(current->destination, rm, (dist + 1));
    last->next = tmp;
    tmp->last = last;
}

char        **assemble_path(t_queue *head, t_swarm *swarm)
{
    t_queue     *tmp;
    int         count;
    int         temp;
    char        **path;
    t_room      *previous;
    (void)swarm;

    tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    count = tmp->distance + 2;
    temp = 0;
    path = (char**)malloc(sizeof(char*) * count);
	path[count] = NULL;
    while (temp < count - 1)
    {
        path[temp] = ft_strdup(tmp->destination->name);
        if (tmp->destination->room_type == 1)
            break ;
        previous = tmp->origin;
        tmp = head;
        while (tmp->destination != previous)
            tmp = tmp->next;
        temp++;
    }
    return (path);
}

/*
**asses if the room has be visited before.
**if so, will calculate if current possible link has shorter steps
*/

int         current_link_shorter(t_queue *head, t_queue *current, t_room *room)
{
    t_queue *tmp;

    while (head && head->destination != room)
        head = head->next;
    if (!head)
        return (1);
    if ((head->destination == room) && (current->distance + 1  <  head->distance))
    {
        tmp = head;
        tmp->last->next = tmp->next;
        tmp->next->last = tmp->last;
        free(tmp);
        return (1);
    }
    return (0);
}

void       print_path(char **strings)
{
    int i;

    i = 0;
    ft_putchar('\n');
    while (strings[i] != NULL)
        ft_putendl(strings[i++]);
    ft_putchar('\n');
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

    head = init_queue(swarm);
    tmp_room = head->destination;
    current = head;
    while (current != NULL)
    {
        tmp_tunnel = tmp_room->tunnels;
        while (tmp_tunnel != NULL)
        {
            if (current_link_shorter(head, current, tmp_tunnel->to_room))//tmp_tunnel->to_room->visited == false)
                add_to_queue(current, tmp_tunnel->to_room);     //adding room to queue
            if (tmp_tunnel->to_room->room_type == 0)
            {
                swarm->path = assemble_path(head, swarm);
                // print_path(swarm->path);
                return ;
            }
            tmp_tunnel = tmp_tunnel->next;
        }
        current = current->next;
        tmp_room = current->destination;
    }
}
