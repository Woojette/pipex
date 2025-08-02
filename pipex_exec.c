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

void	ft_erreur127(char *temp, char ***env, t_pipex *pipex)
{
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

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while ((env)[i])
	{
		if (ft_strncmp((env)[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (env[i] + 5);
}

void	ft_execve(char ***argv, char ***env, int nb, t_pipex *pipex)
{
	int		i;
	char	*temp;

	i = 0;
	pipex->commande = ft_split((*argv)[nb], ' ');
	if (pipex->commande[0] == NULL)
		return (free(pipex->commande), free(pipex), exit(1));
	if (access(pipex->commande[0], X_OK) == 0)
	{
		if (execve(pipex->commande[0], pipex->commande, *env) == -1)
		{
			perror("execve");
			return (ft_free_tab(pipex->commande), free(pipex), exit (1));
		}
		exit(0);
	}
	pipex->path = get_path(*env);
	pipex->pathd = ft_split(pipex->path, ':');
	if (!pipex->pathd)
		return (ft_free_tab(pipex->commande), exit(1));
	temp = check_path(pipex->pathd, pipex->commande);
	ft_erreur127(temp, env, pipex);
}
