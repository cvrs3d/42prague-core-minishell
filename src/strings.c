/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:04:53 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/10 14:41:38 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*s != '\0')
	{
		s++;
		size++;
	}
	return (size);
}

char	*ft_strdup(const char *s)
{
	char		*dest;
	size_t		len;
	char		*temp;

	len = ft_strlen(s);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	temp = dest;
	while (*s)
		*temp++ = *s++;
	*temp = '\0';
	return (dest);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	slen1;
	size_t	slen2;
	char	*joined;
	char	*dummy;

	if (!s1 || !s2)
		return (NULL);
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	joined = (char *)malloc(slen1 + slen2 + 1);
	if (joined == NULL)
		return (NULL);
	dummy = joined;
	while (*s1)
		*dummy++ = *s1++;
	while (*s2)
		*dummy++ = *s2++;
	*dummy = '\0';
	return (joined);
}
