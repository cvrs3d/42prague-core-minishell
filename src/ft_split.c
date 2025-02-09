/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:22:38 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/09 15:22:46 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*freeall(char **split, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size && split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static int	count_s(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (count);
}

static int	strlen_sep(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*makeword(char *s, char c)
{
	int		wlen;
	int		i;
	char	*word;

	i = 0;
	wlen = strlen_sep(s, c);
	word = (char *)malloc((wlen + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (i < wlen)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char			**split;
	unsigned int	size;

	if (s == NULL)
		return (NULL);
	split = (char **)malloc((count_s((char *)s, c) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	size = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			split[size] = makeword((char *)s, c);
			if (split[size] == NULL)
				return (freeall(split, size));
			size++;
		}
		while (*s != '\0' && *s != c)
			s++;
	}
	split[size] = 0;
	return (split);
}
