#include <string.h>
#include <stdio.h>

int length(char *s)
{
    return strlen(s);
}

int main()
{
    int (*fptr)(char *);
    fptr = length;
    char *greeting = "Hello!";
    printf("Lenght of %s: %i\n", greeting, fptr(greeting));
    return 0;
}
