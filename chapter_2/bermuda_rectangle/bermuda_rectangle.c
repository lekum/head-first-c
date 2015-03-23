#include <stdio.h>

void go_south_east(int *lat, int *lon)
{
    *lat = *lat - 1;
    *lon = *lon + 1;
}

int main()
{
    int latitude = 32;
    int longitude = -64;
    go_south_east(&latitude, &longitude);
    printf("The memory addresses are: [%p, %p]\n", &latitude, &longitude);
    printf("The size of an int is: %li\n", sizeof(latitude));
    printf("Avast! Now at: [%i, %i]\n", latitude, longitude);
    return 0;
}
