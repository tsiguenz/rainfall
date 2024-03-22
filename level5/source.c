#include <stdio.h>
#include <stdlib.h>

void o(void) { //0x080484a4
    system("/bin/sh");
    exit(1);
}

void n(void) {
    char buffer[520];

    fgets(buffer, 512, stdin);
    printf(buffer);
    exit(1); //0x08049838
}

int main(int ac, char *av[]) {
    n();
}
