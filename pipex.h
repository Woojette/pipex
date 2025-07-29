/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooyang <wooyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:09:10 by wooyang           #+#    #+#             */
/*   Updated: 2025/07/24 15:09:16 by wooyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

int		main(int argc, char **argv, char **env);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free_tab(char **str);

typedef struct s_pipex
{
	char	*path;
	char	*cmd;
	char	*temp;
	char	*resultat;
	char	**pathd;
	char	**commande;
	char	**args;
	int		status;
	int		pid1;
	int		pid2;
	int		pipefd[2];
	int		inf;
	int		outf;
}t_pipex;

void	ft_execve(char ***argv, char ***env, int nb, t_pipex *pipex);
void	ft_fork1(char **argv, char **env, int nb, t_pipex *pipex);
void	ft_fork4(char **argv, char **env, int nb, t_pipex *pipex);
int		exec(char *arg, char **env);

#endif
