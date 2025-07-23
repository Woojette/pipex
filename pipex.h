#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

int     main(int argc, char **argv, char **env);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

typedef struct s_pipex
{
    char    *path;
    char    *cmd;
    char    *temp;
    char    *resultat;
    char    **pathd;
    char    **commande;
    char    **args;
    pid_t   pid1;
    pid_t   pid2;
    int     pipefd[2];
    int     inf;
    int     outf;
}t_pipex;

void    ft_execve(char ***argv, char ***env, int nb, t_pipex *pipex);
void    ft_fork(char ***argv, int nb, t_pipex *pipex);

#endif