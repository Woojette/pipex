#include "pipex.h"

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

    i = 0;
    j = 0;
    pipex->path = "PATH=";
    while ((*env)[i])
    {
        if (ft_strncmp((*env)[i], pipex->path, 5) == 0)
            break ;
        i++;
    }
    pipex->commande = ft_split((*argv)[nb], ' ');
    if (!pipex->commande)
        return (NULL);
    //protection fait
    pipex->pathd = ft_split((*env)[i] + 5, ':');
    if (!pipex->pathd)
        return (NULL);
    //protection fait
    pipex->cmd = ft_strjoin("/", pipex->commande[0]);
    if (!pipex->cmd)
        return (NULL);
    //protection fait
    while (pipex->pathd[j])
    {
        pipex->temp = ft_strjoin(pipex->pathd[j], pipex->cmd);
        if (!pipex->temp)
            return (NULL);
        //protection fait
        // printf("%d %s\n", j, pipex->temp);
        if (access(pipex->temp, F_OK) == 0)
        {
            // printf("final %s\n", pipex->temp); //execve 넣을 주소 (temp에 들어감)
            break ;
        }
        free(pipex->temp);
        j++;
    }
    ft_free_tab(pipex->commande);
    ft_free_tab(pipex->pathd);
    return (free(pipex->cmd), pipex->temp);
}

void ft_execve(char ***argv, char ***env, int nb, t_pipex *pipex)
{
        char    *pathd;
        char    **cmdd;

        pathd = adresse(argv, env, nb, pipex);
        if (!pipex->pathd)
        {
            perror ("path_adresse");
            exit (1);
        }
        //protection fait
        cmdd = ft_split((*argv)[nb], ' ');
        if (!cmdd)
        {
            perror("argv");
            exit (1);
        }
        //protection fait
        if (execve(pathd, cmdd, NULL) == -1)
        {
            perror("execve");
            exit (1);
        }
}