int language = 0;

void greetuser(char *var)
{
    char buffer[72];

    if (language == 1)
        strcpy(buffer, "Hyvää päivää ");
    else if (language == 2)
        strcpy(buffer, "Goedemiddag! ");
    else if (language == 0)
        strcpy(buffer, "Hello ");

    strcat(buffer, var);
    puts(buffer);
}

int main(int ac, char *av[])
{

    if (ac != 3)
        return 1;

    char *langVar;
    char buffer[76];

    bzero(buffer, 19);
    strncpy(buffer, av[1], 40);
    strncpy(buffer + 40, av[2], 32);

    langVar = getenv("LANG");

    if (langVar != NULL)
    {
        if (memcmp(langVar, "fi", 2) == 0)
            language = 1;
        else if (memcmp(langVar, "nl", 2) == 0)
            language = 2;
    }

    char var[19];
    strncpy(var, buffer, 19);
    greetuser(var);
}