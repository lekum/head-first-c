#include <stdio.h>
#define MAXLINE 15

char line[MAXLINE];
int number;

int main(int argc, char **argv)
{
    printf("Please, enter one string\n");
    fgets(line, sizeof(line), stdin);
    puts(line);

    printf("Please, enter one integer\n");
    scanf("%i", &number);
    printf("The number is %i\n", number);
}
