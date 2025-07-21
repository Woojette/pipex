#include "pipex.h"

typedef struct s_pipex
{
    char    *path;
    char    *cmd;
    char    *temp;
    char    *resultat;
    char    **pathd;
    char    **commande;
    char    *args[3];
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
        {
            break ;
        }
        i++;
    }
    pipex->commande = ft_split((*argv)[nb], ' ');
    pipex->pathd = ft_split((*env)[i], ':');
    free(pipex->pathd[0]);
    pipex->pathd[0] = ft_substr(pipex->pathd[0], 5, ft_strlen(pipex->pathd[0])-5); //malloc
    pipex->cmd = ft_strjoin("/", pipex->commande[0]);
    while (pipex->pathd[j])
    {
        pipex->temp = ft_strjoin(pipex->pathd[j], pipex->cmd);
        printf("%d %s\n", j, pipex->temp);
        if (access(pipex->temp, F_OK) == 0)
        {
            printf("final %s\n", pipex->temp); //execve 넣을 주소 (temp에 들어감)
            break ;
        }
        free(pipex->temp);
        j++;
    }
    // execve(pipex->temp, pipex->commande, NULL);
    ft_free_tab(pipex->commande);
    ft_free_tab(pipex->pathd);
    return (free(pipex->cmd), pipex->temp);
}

int main(int argc, char **argv, char **env)
{
    t_pipex *pipex;
    char    *pathd;

    if (argc != 5)
        return (1);
    pipex = malloc(sizeof(t_pipex));
    if (!pipex)
        return (1);
    pipe(pipex->pipefd);

    pipex->pid1 = fork();
    if (pipex->pid1 == 0)
    {
        pipex->inf = open(argv[1], O_RDONLY);
        if (pipex->inf == -1)
        {
            perror("infile");
            exit (1);
        }
        dup2(pipex->inf, 0);
        dup2(pipex->pipefd[1], 1);
        close(pipex->pipefd[0]);
        pathd = adresse(&argv, &env, 2, pipex);
        // free(pathd);
        // free(pipex);

        pipex->args[0] = "cat";
        pipex->args[1] = "-e";
        pipex->args[2] = NULL;
        close(pipex->inf);
        execve(pathd, pipex->args, NULL);
        perror("execve_cmd1");
        exit (1);
    }

    
    else
    {
        close(pipex->pipefd[1]);
        pipex->pid2 = fork();
        if (pipex->pid2 == 0)
        {
            pipex->outf = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (pipex->outf == -1)
            {
                perror("outfile");
                exit (1);
            }
            

            dup2(pipex->pipefd[0], 0);
            dup2(pipex->outf, 1);

            // close(pipex->pipefd[1]);
            pathd = adresse(&argv, &env, 3, pipex);
            pipex->args[0] = "wc";
            pipex->args[1] = "-l";
            pipex->args[2] = NULL;
            close(pipex->outf);
            execve(pathd, pipex->args, NULL);
            perror("execve_cmd2");
            exit (1);
        }
        else
        {
            wait(NULL);
            wait(NULL);
            close(pipex->pipefd[0]);
            close(pipex->pipefd[1]);
        }
        // free(pipex);
    }
    
    return (0);
}