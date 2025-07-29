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
/*
char	*adresse(char ***argv, char ***env, int nb, t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	pipex->path = "PATH=";
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], pipex->path, 5) == 0)
			break ;
		i++;
	}
	pipex->commande = ft_split((*argv)[nb], ' ');
	if (!pipex->commande)
		return (NULL);
	pipex->pathd = ft_split((*env)[i] + 5, ':');
	if (!pipex->pathd)
		return (NULL);
	pipex->cmd = ft_strjoin("/", pipex->commande[0]);
	if (!pipex->cmd)
		return (NULL);
	while (pipex->pathd[j])
	{
		pipex->temp = ft_strjoin(pipex->pathd[j], pipex->cmd);
		if (!pipex->temp)
			return (NULL);
		if (access(pipex->temp, F_OK) == 0)
			break ;
		free(pipex->temp);
		j++;
	}
	ft_free_tab(pipex->commande);
	ft_free_tab(pipex->pathd);
	return (free(pipex->cmd), pipex->temp);
}
*/

void	ft_execve(char ***argv, char ***env, int nb, t_pipex *pipex)
{
	// char	*pathd;
	// char	**cmdd;

	// pathd = adresse(argv, env, nb, pipex);
	// if (!pipex->pathd)
	// {
	// 	perror ("path_adresse");
	// 	exit (1);
	// }
	// cmdd = ft_split((*argv)[nb], ' ');
	// if (!cmdd)
	// {
	// 	perror("argv");
	// 	exit (1);
	// }
	// if (execve(pathd, cmdd, NULL) == -1)
	// {
	// 	perror("execve");
	// 	exit (1);
	// }

	int i;
	
	i = 0;
	pipex->commande = ft_split((*argv)[nb], ' ');
	if (pipex->commande[0] == NULL)
	{
		// perror("errortesttest");
		free(pipex->commande);
		// ft_free_tab(pipex->pathd);
		free(pipex);
		exit(1);
		// return ;
	}

	if (access((*argv)[nb], X_OK) == 0)
	{
		// write(2, "bon1\n", 5);
		// pipex->commande = ft_split((*argv)[nb], ' ');
		// if (!pipex->commande)
		// {
		// 	// ft_free_tab(pipex->pathd);
		// 	// free(pipex);
		// 	// exit(1);
		// 	return ;
		// }
		if (execve((*argv)[nb], pipex->commande, *env) == -1)
		{
			perror("execve");
			ft_free_tab(pipex->commande);
			free(pipex);
			exit (1);
		}
		exit(0);
	}
	// write(2, "bon2\n", 5);

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
	// pipex->commande = ft_split((*argv)[nb], ' ');
	// if (pipex->commande == NULL)
	// {
	// 	perror("errortesttest");
	// 	ft_free_tab(pipex->pathd);
	// 	free(pipex);
	// 	exit(1);
	// 	// return ;
	// }
	// perror("errortest2");
	char *temp = check_path(pipex->pathd, pipex->commande);
	if (!temp)
	{
		ft_free_tab(pipex->commande);
		ft_free_tab(pipex->pathd);
		free(pipex);
		exit (127);
	}
	// write(2, temp, 12);
	if (execve(temp, pipex->commande, *env) == -1)
	{
		perror("execve");
		ft_free_tab(pipex->commande);
		ft_free_tab(pipex->pathd);
		free(pipex);
		exit (127);
	}


	// pipex->cmd = ft_strjoin("/", pipex->commande[0]);
	// if (!pipex->cmd)
	// 	return (NULL);

	// while (pipex->pathd[j])
	// {
	// 	pipex->temp = ft_strjoin(pipex->pathd[j], pipex->cmd);
	// 	if (!pipex->temp)
	// 		return (NULL);
	// 	if (access(pipex->temp, F_OK) == 0)
	// 		break ;
	// 	free(pipex->temp);
	// 	j++;
	// }
}
