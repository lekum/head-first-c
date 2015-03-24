#include <stdio.h>

void fortune_cookie(char msg[])
{
    printf("Message reads: %s\n", msg);
    printf("Message is in position %p\n", msg);
    printf("Message occupies %li bytes\n", sizeof(msg));
}

int main(int argc, char **argv)
{
    char quote[] = "Cookies make you fat";
    fortune_cookie(quote);
    return 0;
}

