#include <string.h>
#include <stdio.h>
#define MAX_LEN 80

void print_reverse(char *s)
{
    size_t len = strlen(s);
    char *t = s + len - 1;
    while ( t >= s)
    {
        printf("%c", *t);
        t = t - 1;
    }
    puts("");
}

int main(int argc, char **argv)
{
    char entered_string[MAX_LEN];
    puts("Enter a string: ");
    fgets(entered_string, sizeof(entered_string), stdin);
    printf("\n");
    print_reverse(entered_string);
    return 0;
}
