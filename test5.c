#include "pipex.h"

typedef struct s_pipex
{
    char    *path;
    char    *cmd;
    char    *temp;
    char    *resultat;
    char    **pathd;
    char    **commande;
    char    **args;
    pid_t   pid1;
    pid_t   pid2;
    int     pipefd[2];
    int     inf;
    int     outf;
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
            return (NULL);
        //protection
        cmdd = ft_split((*argv)[nb], ' ');
        if (!cmdd)
            return (NULL);
        //protection

        if (execve(pathd, cmdd, NULL) == -1)
        {
            perror("execve");
            exit (1);
        }
}

int main(int argc, char **argv, char **env)
{
    t_pipex *pipex;
    // (void)env;
    // (void)argv;
    if (argc != 5)
        return (1);

    pipex = malloc(sizeof(t_pipex));
    if (!pipex)
        return (1);
    if (pipe(pipex->pipefd) == -1)
    {
        perror("pipe");
        exit (1);
    }
    pipex->pid1 = fork();
    if (pipex->pid1 == -1)
    {
        perror("fork_pid1");
        exit (1);
    }
    if (pipex->pid1 == 0)
    {
        pipex->inf = open(argv[1], O_RDONLY);
        if (pipex->inf == -1)
        {
            perror("infile");
            exit (1);
        }
        if (dup2(pipex->inf, 0) == -1)
        {
            perror("dup2_inf");
            exit (1);
        }
        if (dup2(pipex->pipefd[1], 1) == -1)
        {
            perror("dup2_pipefd[1]");
            exit (1);
        }
        close(pipex->pipefd[0]);
        close(pipex->pipefd[1]);
        close(pipex->inf);

        ft_execve(&argv, &env, 2, pipex);
    }
    else
    {
        close(pipex->pipefd[1]);
        pipex->pid2 = fork();
        if (pipex->pid2 == -1)
        {
            perror("fork_pid2");
            exit (1);
        }
        if (pipex->pid2 == 0)
        {
            pipex->outf = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (pipex->outf == -1)
            {
                perror("outfile");
                exit (1);
            }
            if (dup2(pipex->pipefd[0], 0) == -1)
            {
                perror("pipefd[0]");
                exit (1);
            }
            if (dup2(pipex->outf, 1) == -1)
            {
                perror("outf");
                exit (1);
            }
            close(pipex->pipefd[0]);
            close(pipex->outf);
            ft_execve(&argv, &env, 3, pipex);
        }
        else
        {
            close(pipex->pipefd[0]);
            wait(NULL);
            wait(NULL);
        }
        free(pipex);
    }
    return (0);
}