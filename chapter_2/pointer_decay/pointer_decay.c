#include <stdio.h>

int getsize(char *str);

int main(int argc, char **argv)
{
    char letters[] = {'a', 'b', 'c'};
    int size = getsize(letters);
    printf("The size of the array is %li\n", sizeof(letters));
    printf("The size of the array is %i\nj", size);
}

int getsize(char *str)
{
    return sizeof(str);
}
