/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooyang <wooyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:40:46 by wooyang           #+#    #+#             */
/*   Updated: 2025/07/24 15:04:54 by wooyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;
	int		status; // pour le 2e argument de waitpid
	int		exitstatus; // la valeur du retour 

	exitstatus = 0;
	if (argc != 5)
		return (1);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (1);
	if (pipe(pipex->pipefd) == -1)
	{
		
		return (perror("pipe"),free(pipex), 1);
	}
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		perror("fork_pid1");
		return (free(pipex), 1);
	}
	if (pipex->pid1 == 0)
	{
		ft_fork(argv, 1, pipex);
		ft_execve(&argv, &env, 2, pipex);
		// argv[2]
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
			ft_fork(argv, 4, pipex);
			ft_execve(&argv, &env, 3, pipex);
			// if ()
		}
		else
		{
			// close(pipex->pipefd[1]);
			close(pipex->pipefd[0]);
			// wait(NULL);
			// wait(NULL);
			// status = 0;
			// printf("status:%d\n" ,WIFEXITED(status));
			waitpid(pipex->pid1, &status, 0);
			waitpid(pipex->pid2, &status, 0);
			// waitpid(-1, &status, 0);
			// waitpid(-1, &status, 0);
			// printf("status:%d\n" ,WIFEXITED(status));
		if (WIFEXITED(status))
		{
			exitstatus = WEXITSTATUS(status);
		}
		}
		free(pipex);
		// exitstatus = 
	}
	return (exitstatus); // si tout marche bien
}
