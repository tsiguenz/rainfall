void o(void) {
    system("/bin/sh");
    exit(1);
}

void v(void) {
    char buffer[520];

    fgets(buffer, 512, stdin);
    printf(buffer);
    exit(1);
}

int main(int ac, char *av[]) {
    n();
}