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

void	ft_close_inf(int fd, t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	if (fd == pipex->inf)
		perror("infile");
	if (fd == dup2(pipex->inf, 0))
	{
		close(pipex->inf);
		perror("dup2_inf");	
	}
	if (fd == dup2(pipex->pipefd[1], 1))
	{
		close(pipex->inf);
		perror("dup2_pipefd[1]");
	}
	free(pipex);
	exit (1);
}

void	ft_close_outf(int fd, t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	if (fd == pipex->outf)
		perror("outfile");
	if (fd == dup2(pipex->pipefd[0], 0))
	{
		close(pipex->outf);
		perror("pipefd[0]");
	}
	if (fd == dup2(pipex->outf, 1))
	{
		close(pipex->outf);
		perror("outf");
	}
	free(pipex);
	exit (1);
}

void	ft_fork(char **argv, int nb, t_pipex *pipex)
{
	if (nb == 1)
	{
		pipex->inf = open(argv[nb], O_RDONLY);
		if (pipex->inf == -1)
			ft_close_inf(pipex->inf, pipex);
		if (dup2(pipex->inf, 0) == -1)
			ft_close_inf(dup2(pipex->inf, 0), pipex);
		if (dup2(pipex->pipefd[1], 1) == -1)
			ft_close_inf(dup2(pipex->pipefd[1], 1), pipex);
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		close(pipex->inf);
	}
	if (nb == 4)
	{
		pipex->outf = open(argv[nb], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex->outf == -1)
		{
			ft_close_outf(pipex->outf, pipex);
			// close(pipex->pipefd[0]);
			// perror("outfile");
			// free(pipex);
			// exit (1);
		}
		if (dup2(pipex->pipefd[0], 0) == -1)
        {
			ft_close_outf(dup2(pipex->pipefd[0], 0), pipex);
			// close(pipex->pipefd[0]);
			// close(pipex->outf);
            // perror("pipefd[0]");
			// free(pipex);
            // exit (1);            
		}
		if (dup2(pipex->outf, 1) == -1)
		{
			ft_close_outf(dup2(pipex->outf, 1), pipex);
			// close(pipex->pipefd[0]);
			// close(pipex->outf);
			// perror("outf");
			// free(pipex);
			// exit (1);
		}
		close(pipex->pipefd[0]);
		close(pipex->outf);
	}
}
