/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:27:02 by yustinov          #+#    #+#             */
/*   Updated: 2025/01/30 17:28:26 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return len;
}

char	*ft_strcpy(char *dest, const char *src)
{
	char *ptr = dest;
	while (*src != '\0')
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return dest;
}

char	*ft_strcat(char *dest, const char *src)
{
	char *ptr = dest;
	while (*ptr != '\0')
	{
		ptr++;
	}
	while (*src != '\0')
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return dest;
}
