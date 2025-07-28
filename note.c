#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;

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
		ft_fork(argv, 1, pipex);
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
		if (pipex->pid2 == 0) // *** enfant
		{
			ft_fork(argv, 4, pipex);
			ft_execve(&argv, &env, 3, pipex);
		}
		else // *** parent
		{ // *** dans le parent, on peut recuperer la valeur de retour du processus de l'enfant
             // *** grace a waitpid
			// close(pipex->pipefd[1]);
			close(pipex->pipefd[0]);
			wait(NULL);
			wait(NULL);
		}
		free(pipex);
	}
	return (0);
}



if (WIFEXITED(status))// WIFEXITED(status): quand l'enfant finit bien
{
    int returned = WEXITSTATUS(status);
     // WEXITSTATUS(status) : pour recuperer la valeur du retour du processus enfant
     printf("exited normally with status %d\n",returned);
}