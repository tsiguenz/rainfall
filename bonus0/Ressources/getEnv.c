#include <stdlib.h>
#include <stdio.h>

int main(int ac, char *av[])
{
    printf("Address of our var is %p\n", getenv(av[1]));

    return 0;
}
