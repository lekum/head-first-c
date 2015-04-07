#include <stdio.h>
#include <string.h>
#define MAX_LEN 80

void find_track(char search_for[], char track_list[][MAX_LEN])
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (strstr(track_list[i], search_for))
        {
            printf("Track %i: '%s'\n", i, track_list[i]);
        }
    }
}

int main(int argc, char **argv)
{

    char tracks[][MAX_LEN] = {"I left my heart in Harvard Med School",
                             "Newark, Newark - a wonderful town",
                             "Dancing with a Dork",
                             "From here to maternity",
                             "The girl from Iwo Jima",
                            };
    char search_for[MAX_LEN];
    printf("Search for: ");
    fgets(search_for, sizeof(search_for), stdin);
    find_track(search_for, tracks);
    return 0;
}
