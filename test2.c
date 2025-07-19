#include "pipex.h"

int main()
{
    int fd[2];

    pipe(fd);

    int id1 = fork();
    if (id1 == 0)
    {
        

        dup2(fd[1], 1);
         char *args[3];

        args[0] = "ls";
        args[1] = "-l";
        args[2] = NULL;

        execve("/bin/ls", args, NULL);
    }


    int id2 = fork();
    if (id2 == 0)
    {
        dup2(fd[0], 0);
        char str[500];
        int readfd = read(0, str, 500);
        str[readfd] = 0;
        printf("%s", str);
    }
    // char str[500];
    // int readfd = read(fd[0], str, 500);
    // str[readfd] = 0;
    // printf("%s", str);
}