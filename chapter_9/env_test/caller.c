#include <unistd.h>

int main()
{
    char *my_env[] = {"JUICE=peach and apple", NULL};
    execle("diner_info.out", "diner_info.out", "4", NULL, my_env);
}
