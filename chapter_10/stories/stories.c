#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

void open_url(char *url)
{
    char command[255];
    sprintf(command, "x-www-browser '%s'", url);
    system(command);
}

int main(int argc, char *argv[])
{
    char *phrase = argv[1];
    char *vars[] = {"RSS_FEED=http://feeds.feedburner.com/planetarduino?format=xml", NULL};
    int fd[2];
    if (pipe(fd) == -1)
        error("Can't create the pipe");

    pid_t pid = fork();
    if (pid == -1)
        error("Can't fork process");
    if (!pid)
    {
        close(fd[0]); // Close the "read" end of the pipe
        if (dup2(fd[1], 1) == -1)
            error("Can't redirect Standard Output");
        if (execle("/usr/bin/python", "/usr/bin/python", "./rssgossip.py", "-u", phrase, NULL, vars) == -1)
            error("Can't run script");
    }
    close(fd[1]); // Close the "write" end of the pipe
    if (dup2(fd[0], 0) == -1)
        error("Can't redirect Standard Input");
    char line[255];
    while (fgets(line, 255, stdin))
    {
        if (line[0] == '\t') // If the line starts with a tab
            open_url(line + 1);
    }
    return 0;
}
