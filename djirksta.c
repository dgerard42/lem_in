
#include "lem_in.h"

typedef struct      s_djirk;
{
    struct t_room   *room;
    char            *name;
    char            *from;
    float           distance;
    
}                   t_djirk;


t_swarm      *djirksta(t_swarm *env)
{
    t_djirk  *q;
    t_djirk  *current;
    
    while ()
    {


    }




}


int       djirksta(t_swarm *env)
{
    start/init Q
    current place in Q

    while (current place pointer is at end of Q)
    {
        if (node has been visited)
            calculate distance and find out if new calculation is shorter than current existing.
            replace if new distance is shorter
        else  // node has not been visted
            add node & insert in Q
        traverse down q;
    }
    at end assemble the linked lists in order
    return (1);
}