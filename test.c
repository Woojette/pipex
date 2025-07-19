#include "pipex.h"

typedef struct s_pipex
{
    char    *path;
    char    *cmd;
    char    *temp;
    char    *resultat;
    char    **pathd;
    char **commande;
}t_pipex;

void    ft_free_tab(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

char *adresse(char ***argv, char ***env, int nb, t_pipex *pipex)
{
    int     i;
    int     j;

   (void)argv;
   (void)nb;
    // char    *path;
    // char    *cmd;
    // char    *temp;
    // char    *resultat;
    // char    **pathd;

    i = 0;
    j = 0;
    pipex->path = "PATH=";
    while ((*env)[i])
    {
        if (ft_strncmp((*env)[i], pipex->path, 5) == 0)
        {
            break ;
        }
        i++;
    }
    // printf("%s\n", (*env)[i]);
   
    pipex->commande = ft_split((*argv)[nb], ' ');
    pipex->pathd = ft_split((*env)[i], ':');
    // free((*env)[i]);
    // printf("%s\n", pipex->pathd[0]);
    free(pipex->pathd[0]);
    pipex->pathd[0] = ft_substr(pipex->pathd[0], 5, ft_strlen(pipex->pathd[0])-5); //malloc
    // printf("%s\n", pipex->pathd[0]);
    pipex->cmd = ft_strjoin("/", pipex->commande[0]);
    while (pipex->pathd[j])
    {
        pipex->temp = ft_strjoin(pipex->pathd[j], pipex->cmd);
        // free(pipex->cmd);
        printf("%d %s\n", j, pipex->temp);
        if (access(pipex->temp, F_OK) == 0)
        {
            printf("final %s\n", pipex->temp);
            break ;
        }
        free(pipex->temp);
        j++;
    }
    execve(pipex->temp, pipex->commande, NULL);
    ft_free_tab(pipex->commande);
    ft_free_tab(pipex->pathd);
    return (free(pipex->cmd), pipex->temp);
    // return (pipex->resultat = pipex->temp,/* free(pipex->temp), pipex->temp = NULL, */pipex->resultat);
    // return("test");
}


int main(int argc, char **argv, char **env)
{
    t_pipex *pipex;
    // int     i;
    // int     j;
    char    *pathd;
    // char    *path;
    // char    *cmd1;
    // char    *temp;
    // char    **pathd;

    // i = 0;
    // j = 0;
    // path = "PATH=";
    if (argc != 5)
        return (1);
    pipex = malloc(sizeof(t_pipex));
    if (!pipex)
        return (1);
    pathd = adresse(&argv, &env, 2, pipex);
    printf("fonction %s\n", pathd);

   
    free(pathd);
    free(pipex);
    // int n = 0;
    // while(commande[n])
    // {
    //     printf("%d %s\n", n ,commande[n]);
    //     n++;
    // }
    // printf("%d %s\n", n ,commande[n]);
    // execve(temp, commande, NULL);


    // j = 0;
    // while (pathd[j])
    // {
    //     if (access(adresse[j], F_OK))
    //         break ;
    // }
    // cmd = ft_strjoin("/", argv[3]);
    // adresse = ft_strjoin(pathd[i], cmd);


    // char *args[3];

    // args[0] = "ls";
    // args[1] = "-l";
    // args[2] = NULL;

    // execve("ls", args, NULL);

    // char *path = "/home/wooyang/bin/ls";
    // if (access(path, F_OK) == 0)
    // {
    //     printf("ca marche");
    // }
    // else 
    // {
    //     printf("ca marhe pas");
    // }

    // return ("bin/ls");
    // int i = 0;
    // while (env[i])
    // {
    //     printf("%s\n", env[i]);
    //     i++;
    // }
}