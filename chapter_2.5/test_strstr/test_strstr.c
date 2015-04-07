#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char *pos;
    char s0[][80] = {"dysfunctional", "troll"};
    char s1[] = "fun";
    if (pos = strstr(s0[0], s1))
    {
        printf("The string \"%s\" has been found inside \"%s\"\n", s1, s0[0]);
        return 0;
    }
    return -1;
}
