#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#define DEFAULT_PORT 30000
#define ANSWER_LEN 80

int listener_d;

void error(char *msg)
{
    fprintf(stderr, "%s: %s", msg, strerror(errno));
    exit(1);
}

int read_in(int socket, char *buf, int len)
{
    char *s = buf;
    int slen = len;
    int c = recv(socket, s, slen, 0);
    slen -= c;
    // The telnet string received ends in \r\n
    while ((c > 0) && (s[c - 1] != '\n'))
    {
        // Take on account the part of the buffer written
        s += c;
        c = recv(socket, s, slen, 0);
        slen -= c;
    }
    if (c < 0)
        return  c; // There is an error
    else if (c == 0)
        buf[0] = '\0'; // Send back an empty string
    else
        s[c - 2] = '\0'; // Replace the '\r' character with a '\0'
    return len - slen; // Return the bytes read
}

int open_listener_socket()
{
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
        error("Unable to create a socket");
    return s;
}

void bind_to_port(int socket, int port)
{
    // Create a structure to store the service port and the IP (localhost)
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t) htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse,
                   sizeof(int)) == -1)
        error("Unable to set the reuse option on the socket");

    // Bind it to localhost:port
    int c = bind(socket, (struct sockaddr *) &name, sizeof(name));
    if (c == -1)
        error("Unable to bind the socket");
}

int say(int socket, char *s)
{
    int result = send(socket, s, strlen(s), 0);
    if (result == -1)
        fprintf(stderr, "%s: %s\n",
                "Error talking to client", strerror(errno));
    return result;
}

void handle_shutdown(int sig)
{
    if (listener_d)
        close(listener_d);
    fprintf(stderr, "Bye!\n");
    exit(0);
}

void disconnect_client(int socket, char *msg)
{
    say(socket, msg);
    close(socket);
}

int catch_signal(int sig, void (*handler)(int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

void service_client(int socket)
{
    char *questions[] = {
                        "Knock! Knock!\r\n",
                        "Oscar\r\n",
                       };
    char *valid_answers[] = {
                             "Who's there?",
                             "Oscar who?",
                            };
    char *final_sentence = "Oscar silly question, you get a silly answer\r\n";
    char answer[ANSWER_LEN];
    char silence[] = "Next time say something\r\n";
    char wrong_answer[] = "Wrong answer\r\n";
    int i;
    for (i = 0; i < 2; i++)
    {
        say(socket, questions[i]);
        if (read_in(socket, answer, ANSWER_LEN) < 3)
        {
            disconnect_client(socket, silence);
            return;
        }
        else if (strncasecmp(answer, valid_answers[i], ANSWER_LEN) != 0)
        {
            disconnect_client(socket, wrong_answer);
            return;
        }
    }
    disconnect_client(socket, final_sentence);
}

int main(int argc, char *argv[])
{
    if (catch_signal(SIGINT, handle_shutdown) == -1)
    {
        fprintf(stderr, "Can't map the handler");
        exit(2);
    }
    int service_port = DEFAULT_PORT;
    if (argc > 1)
    {
        service_port = atoi(argv[1]);
    }


    // Create the socket and bind it to the port
    listener_d = open_listener_socket();
    bind_to_port(listener_d, service_port);

    // Listen up to 10 connections
    int c = listen(listener_d, 10);
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

        service_client(connect_d);
    }

    return 0;
}
