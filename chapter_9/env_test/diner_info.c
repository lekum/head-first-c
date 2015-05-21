#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Diners: %s\n", argv[1]);
    printf("Juice: %s\n", getenv("JUICE"));
}

