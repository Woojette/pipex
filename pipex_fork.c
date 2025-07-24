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

void	ft_fork(char ***argv, int nb, t_pipex *pipex)
{
	if (nb == 1)
	{
		pipex->inf = open((*argv)[nb], O_RDONLY);
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
	}
	if (nb == 4)
	{
		pipex->outf = open((*argv)[nb], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex->outf == -1)
		{
			perror("outfile");
			exit (1);
		}
		if (dup2(pipex->outf, 1) == -1)
		{
			perror("outf");
			exit (1);
		}
		close(pipex->pipefd[0]);
		close(pipex->outf);
	}
}
