#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define DEFAULT_PORT 30000

void error(char *msg)
{
    fprintf(stderr, "%s: %s", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[])
{
    int service_port = DEFAULT_PORT;
    if (argc > 1)
    {
        service_port = atoi(argv[1]);
    }

    char *advice[] = {
                      "Take smaller bites\n",
                      "Go for the tight jeans\n",
                      "One word: inappropriate\n",
                      "You might want to rethink that haircut\n"
                     };

    // Create the socket
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    if (listener_d == -1)
        error("Unable to create a socket");

    // Create a structure to store the service port and the IP (localhost)
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t) htons(service_port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind it to localhost:service_port
    int c = bind(listener_d, (struct sockaddr *) &name, sizeof(name));
    if (c == -1)
    {
        char err_msg[80];
        sprintf(err_msg, "Unable to bind the socket to localhost:%i",
                service_port);
        error(err_msg);
    }

    // Listen up to 10 connections
    c = listen(listener_d, 10);
    if (c == -1)
        error("Unable to listen for connections");
    puts("Waiting for connection");

    while (1)
    {
        // Accept connection
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr,
                                &address_size);
        if (connect_d == -1)
            error("Unable to open secondary socket");

        char *msg = advice[rand() % 4];
        c = send(connect_d, msg, strlen(msg), 0);
        if (c == -1)
            error("Unable to send the message");
        close(connect_d);
    }

    return 0;
}
