#include "genericList.h"
#include "clients.h"

struct event
{
    struct Client *client;
    int type;
    int time;
};

struct eventHorizon
{
    struct List *events;
};
