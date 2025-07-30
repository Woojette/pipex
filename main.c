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

int	ft_init(t_pipex **pipex)
{
	*pipex = malloc(sizeof(t_pipex));
	if (!*pipex)
		return (1);
	(*pipex)->inf = -1;
	(*pipex)->outf = -1;
	if (pipe((*pipex)->pipefd) == -1)
		return (perror("pipe"), free(*pipex), 1);
	return (0);
}

void	ft_waitpid(t_pipex *pipex, int *exitstatus)
{
	waitpid(pipex->pid1, &pipex->status, 0);
	waitpid(pipex->pid2, &pipex->status, 0);
	if (WIFEXITED(pipex->status))
		*exitstatus = WEXITSTATUS(pipex->status);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex		*pipex;
	int			exitstatus;

	exitstatus = 0;
	if (argc != 5)
		return (1);
	pipex = NULL;
	if (ft_init(&pipex) == 1)
		return (1);
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		return (perror("fork_pid1"), free(pipex), 1);
	if (pipex->pid1 == 0)
		ft_fork1(argv, env, 1, pipex);
	close(pipex->pipefd[1]);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		return (perror("fork_pid2"), 1);
	if (pipex->pid2 == 0)
		ft_fork4(argv, env, 4, pipex);
	close(pipex->pipefd[0]);
	ft_waitpid(pipex, &exitstatus);
	return (free(pipex), exitstatus);
}
