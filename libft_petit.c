/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_petit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooyang <wooyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:41:57 by wooyang           #+#    #+#             */
/*   Updated: 2025/07/24 14:42:10 by wooyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//ft_strncmp
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		resultat;

	i = 0;
	resultat = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
		{
			resultat = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (resultat);
		}
		i++;
	}
	return (0);
}

//ft_strlen
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

//ft_strdup
char	*ft_strdup(char *str)
{
	char	*resultat;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(str);
	resultat = malloc(sizeof(char) * (len + 1));
	if (resultat == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		resultat[i] = str[i];
		i++;
	}
	resultat[i] = '\0';
	return (resultat);
}

//ft_substr
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			n;
	char			*resultat;

	i = 0;
	n = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	resultat = malloc((len + 1) * sizeof(char));
	if (resultat == NULL)
		return (NULL);
	while (s[start + i] != '\0' && n < len && start < ft_strlen(s))
	{
		resultat[i] = s[start + i];
		n++;
		i++;
	}
	resultat[i] = '\0';
	return (resultat);
}

//ft_split
static size_t	ft_compter_split(char const *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
		{
			j++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
	}
	return (j);
}

static size_t	ft_pareil(size_t i, char const *s, char c)
{
	while (s[i] == c)
		i++;
	return (i);
}

static void	ft_free(char **resultat, size_t j)
{
	while (j > 0)
	{
		j--;
		free(resultat[j]);
	}
	free(resultat);
}

char	**ft_split(char const *s, char c)
{
	char	**resultat;
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	resultat = malloc(sizeof(char *) * (ft_compter_split(s, c) + 1));
	if (resultat == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		i = ft_pareil(i, s, c);
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i > start)
		{
			resultat[j] = ft_substr(s, start, i - start);
			if (resultat[j] == NULL)
				return (ft_free(resultat, j), NULL);
			j++;
		}
	}
	return (resultat[j] = NULL, resultat);
}

//ft_strjoin
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*resultat;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	resultat = malloc(sizeof(char) * (len + 1));
	if (resultat == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		resultat[i + j] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		resultat[i + j] = s2[j];
		j++;
	}
	resultat[i + j] = '\0';
	return (resultat);
}
