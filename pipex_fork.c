/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooyang <wooyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:49:31 by wooyang           #+#    #+#             */
/*   Updated: 2025/07/24 14:49:34 by wooyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_fd(char *str, t_pipex *pipex)
{
	perror(str);
	if (pipex->inf >= 0)
		close(pipex->inf);
	if (pipex->outf >= 0)
		close(pipex->outf);
	if (pipex->pipefd[0] >= 0)
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] >= 0)
		close(pipex->pipefd[1]);
	free(pipex);
	exit (1);
}

void	ft_fork1(char **argv, char **env, int nb, t_pipex *pipex)
{
	pipex->inf = open(argv[nb], O_RDONLY);
	if (pipex->inf == -1)
		ft_close_fd("infile", pipex);
	if (dup2(pipex->inf, 0) == -1)
		ft_close_fd("dup2", pipex);
	if (dup2(pipex->pipefd[1], 1) == -1)
		ft_close_fd("dup2", pipex);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	close(pipex->inf);
	ft_execve(&argv, &env, 2, pipex);
}

void	ft_fork4(char **argv, char **env, int nb, t_pipex *pipex)
{
	pipex->outf = open(argv[nb], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outf == -1)
		ft_close_fd("outfile", pipex);
	if (dup2(pipex->pipefd[0], 0) == -1)
		ft_close_fd("dup2", pipex);
	if (dup2(pipex->outf, 1) == -1)
		ft_close_fd("dup2", pipex);
	close(pipex->pipefd[0]);
	close(pipex->outf);
	ft_execve(&argv, &env, 3, pipex);
}
