#include "pipex.h"

int main(int argc, char **argv, char **env)
{
    t_pipex *pipex;

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
        ft_fork(&argv, 1, pipex);
        // pipex->inf = open(argv[1], O_RDONLY); //
        // if (pipex->inf == -1)
        // {
        //     perror("infile");
        //     exit (1);
        // }
        // if (dup2(pipex->inf, 0) == -1)
        // {
        //     perror("dup2_inf");
        //     exit (1);
        // }
        // if (dup2(pipex->pipefd[1], 1) == -1)
        // {
        //     perror("dup2_pipefd[1]");
        //     exit (1);
        // }
        // close(pipex->pipefd[0]);
        // close(pipex->pipefd[1]);
        // close(pipex->inf); //

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
            ft_fork(&argv, 4, pipex);
            // pipex->outf = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644); //
            // if (pipex->outf == -1)
            // {
            //     perror("outfile");
            //     exit (1);
            // }
            // if (dup2(pipex->pipefd[0], 0) == -1)
            // {
            //     perror("pipefd[0]");
            //     exit (1);
            // }
            // if (dup2(pipex->outf, 1) == -1)
            // {
            //     perror("outf");
            //     exit (1);
            // }
            // close(pipex->pipefd[0]);
            // close(pipex->outf); //
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