int main (int ac, char *av[]) {
    FILE *fd = fopen("/home/user/end/.pass", "r");
    char buffer[132]; 

    bzero(buffer, 33);

    if(fd == NULL || ac != 2)
        return 1;

    fread(buffer, 1, 66, fd);
    buffer[89] = '\0';

    buffer[atoi(av[1])] = '\0';

    fread(&buffer[66], 1, 65, fd);
    fclose(fd);

    if (!strcmp(buffer, av[1])) {
        execl("/bin/sh","sh" , NULL);
    }
    else {
        puts(&buffer[66]);
    }
    
    return 0;
}