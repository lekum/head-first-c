#include <stdio.h>
#include <string.h>

int main()
{
    char error_number[10];
    while(1)
    {
        puts("\nPlease, enter a error number:");
        if (fgets(error_number, sizeof(error_number), stdin) != NULL)
        {
            printf("It means %s\n", strerror(atoi(error_number)));
        }
        else
        {
            break;
        }
    }
    return 0;
}

