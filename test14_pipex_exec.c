/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooyang <wooyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:59:34 by wooyang           #+#    #+#             */
/*   Updated: 2025/07/24 14:59:36 by wooyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*check_path(char **tab, char **cmd)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	while (tab[i])
	{
		temp = ft_strjoin(tab[i], "/");
		if (!temp)
			return (NULL);
		temp2 = ft_strjoin(temp, cmd[0]);
		if (!temp2)
			return (free(temp), NULL);
		free(temp);
		if (access(temp2, X_OK) == 0)
			return (temp2);
		free(temp2);
		i++;
	}
	return (NULL);
}

void	ft_check_commande(char **argv, char **env, int nb, t_pipex *pipex)
{
	if (pipex->commande[0] == NULL)
	{
		free(pipex->commande);
		free(pipex);
		exit(1);
	}
	if (access((*argv)[nb], X_OK) == 0)
	{
		if (execve((*argv)[nb], pipex->commande, *env) == -1)
		{
			perror("execve");
			ft_free_tab(pipex->commande);
			free(pipex);
			exit (1);
		}
		exit(0);
	}
}

void	ft_execve(char ***argv, char ***env, int nb, t_pipex *pipex)
{
	int		i;
	char	*temp;

	i = 0;
	pipex->commande = ft_split((*argv)[nb], ' ');
	ft_check_commande(pipex->commande, env, nb, pipex);
	pipex->path = "PATH=";
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], pipex->path, 5) == 0)
			break ;
		i++;
	}
	pipex->pathd = ft_split((*env)[i] + 5, ':');
	if (!pipex->pathd)
	{
		ft_free_tab(pipex->commande);
		return ;
	}
	temp = check_path(pipex->pathd, pipex->commande);
	if (!temp)
	{
		ft_free_tab(pipex->commande);
		ft_free_tab(pipex->pathd);
		free(pipex);
		exit (127);
	}
	if (execve(temp, pipex->commande, *env) == -1)
	{
		perror("execve");
		ft_free_tab(pipex->commande);
		ft_free_tab(pipex->pathd);
		free(pipex);
		exit (127);
	}
}
