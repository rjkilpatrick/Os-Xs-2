#include <stdio.h>
#include "enet/enet.h"

int main(int argc, char **argv)
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    ENetEvent event;
    ENetAddress address;
    ENetHost *server;

    address.host = ENET_HOST_ANY;
    address.port = 7777;

    server = enet_host_create(&address, 2, 1, 0, 0);

    if (server == NULL)
    {
        printf("An error occurred while trying to create an ENet server host.");
        exit(EXIT_FAILURE);
    }

    // gameloop
    while (1)
    {
        ENetEvent event;
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(server, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                printf("A new client connected from %x:%u.\n",
                       event.peer->address.host,
                       event.peer->address.port);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                printf("A packet of length %zu containing %s was received from %s on channel %u.\n",
                       event.packet->dataLength,
                       event.packet->data,
                       event.peer->data,
                       event.channelID);
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%s disconnected.\n", event.peer->data);
                /* Reset the peer's client information. */
                event.peer->data = NULL;
                break;
            default:
                break;
            }
        }
    }

    enet_host_destroy(server);

    return 0;
}
